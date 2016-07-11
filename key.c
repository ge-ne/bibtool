/*** key.c ********************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2, or (at your option)
** any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/type.h>
#include <bibtool/entry.h>
#include <bibtool/error.h>
#include <bibtool/key.h>
#include <bibtool/rsc.h>
#include <bibtool/names.h>
#include <bibtool/tex_read.h>
#include <bibtool/wordlist.h>
#include <bibtool/expand.h>
#ifdef HAVE_TIME_H
#include <time.h>
#endif
#include "config.h"

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 static KeyNode new_key_node _ARG((int type,Symbol sym));/* key.c            */
 static bool fmt_digits _ARG((StringBuffer *sb,String s,int mp,int pp,int n,int sel,bool trunc));/* key.c*/
 static bool fmt_c_words _ARG((String line,int min,int max,bool not,bool ignore));/* key.c*/
 static bool fmt_c_names _ARG((String line,int min,int max,int not));/* key.c*/
 static bool fmt_c_string _ARG((String  s,int min,int max,bool not));/* key.c  */
 static bool add_fmt_tree _ARG((char *s,KeyNode *treep));/* key.c             */
 static bool eval__fmt _ARG((StringBuffer *sb,KeyNode kn,Record rec));/* key.c*/
 static bool eval_fmt _ARG((StringBuffer *sb,KeyNode kn,Record rec,DB db));/* key.c*/
 static char * itostr _ARG((int i,char *digits));  /* key.c                  */
 static int deTeX _ARG((String line,void (*save_fct)_ARG((String)),int commap));/*key.c*/
 static int fmt__parse _ARG((char **sp,KeyNode *knp));/* key.c               */
 static int fmt_parse _ARG((char **sp,KeyNode *knp));/* key.c                */
 static void Push_Word _ARG((String s));	   /* key.c                  */
 static void eval__special _ARG((StringBuffer *sb,KeyNode kn,Record rec));/* key.c*/
 static void fmt_names _ARG((StringBuffer *sb,String line,int maxname,int post,String trans));/* key.c*/
 static void fmt_string _ARG((StringBuffer *sb,String  s,int n,String trans,String sep));/* key.c*/
 static void fmt_title _ARG((StringBuffer *sb,String line,int len,int in,String trans,bool ignore,Symbol sep));/* key.c*/
 static void init_key _ARG(());	   		   /* key.c                  */
 static void key_init _ARG((void));		   /* key.c                  */
 static void push_s _ARG((StringBuffer *sb,String s,int max,String trans));/* key.c*/
 static void push_word _ARG((String s));	   /* key.c                  */

#ifdef DEBUG
 static void show_fmt _ARG((KeyNode kn,int in));   /* key.c                  */
#endif

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

 static DB tmp_key_db;

/*---------------------------------------------------------------------------*/

#define KEYSTYLE_EMPTY		0x0010
#define KEYSTYLE_SHORT		0x0020
#define KEYSTYLE_LONG		0x0030
#define KEYSTYLE_EXTENDED	0x0040

 static char *percent_chars = "NntTdDsSwWp";	   /*                        */

#define DetexNone  0
#define DetexLower 1
#define DetexUpper 2

 static StringBuffer *key_sb = (StringBuffer*)NULL;/*                        */
 static StringBuffer *tmp_sb = (StringBuffer*)NULL;/*                        */

/*---------------------------------------------------------------------------*/

 static KeyNode key_tree      = (KeyNode)0;	   /*                        */
 static KeyNode sort_key_tree = (KeyNode)0;	   /*                        */

 static NameNode format[NUMBER_OF_FORMATS];	   /*                        */

#define SkipSpaces(CP)	  while ( is_space(*CP) ) ++(CP)
#define SkipAllowed(CP)	  while ( is_allowed(*CP) ) ++(CP)
#define ParseNumber(CP,N) if (is_digit(*CP)) { N = 0;			\
   while(is_digit(*CP) ){ N = N*10 + (*CP)-'0'; ++CP; }}
#define Expect(CP,C,RET)  SkipSpaces(CP);				\
			  if ( *CP == C ) { ++(CP); }			\
			  else { ErrPrintF("*** BibTool: Missing %c",C);\
				   return RET; }
#define ExpectVoid(CP,C)  SkipSpaces(CP);				\
			  if ( *CP == C ) { ++(CP); }			\
			  else { ErrPrintF("*** BibTool: Missing %c",C);\
				   return; }
#define MakeNode(KNP,TYPE,SP,CP) c = *CP; *CP = '\0';			\
			  *KNP = new_key_node(TYPE,symbol((String)*SP));\
			  *CP  = c;
#define ParseOrReturn(CP,NODEP,MSG)					\
  if ( (ret=fmt_parse(CP,NODEP)) != 0  )				\
  { DebugPrintF1(MSG); return ret; }


/*****************************************************************************/
/***				Private word stack			   ***/
/*****************************************************************************/

static String *words	 = (String*)NULL;
static size_t words_len  = 0;
static size_t words_used = 0;
#define WordLenInc 16

#define PushWord(S)	if(words_len>words_used) words[words_used++]=S;	\
			else			 Push_Word(S)
#define ResetWords	words_used = 0

/*-----------------------------------------------------------------------------
** Function*:	push_word()
** Purpose:	Push a word to the stack. Wrapper function.
** Arguments:
**	word	word to push
** Returns:	nothing
**___________________________________________________			     */
static void push_word(word)			   /*			     */
  register String word;				   /*			     */
{ PushWord(word);				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	Push_Word()
** Purpose:	Push a word to the stack when no space is left in the
**		allocated array. 
** Arguments:
**	s	word to push
** Returns:	nothing
**___________________________________________________			     */
static void Push_Word(s)			   /*			     */
  register String s;				   /*			     */
{ register String *wp;				   /*			     */
						   /*			     */
  words_len += WordLenInc;			   /*			     */
  if ( words_len == WordLenInc )		   /*			     */
  { wp = (String*)malloc(words_len*sizeof(String)); }/*			     */
  else						   /*			     */
  { wp = (String*)realloc(words,words_len*sizeof(String)); }/*		     */
  if ( wp == (String*)0 )			   /*			     */
  { words_len -= WordLenInc;			   /*			     */
    ERROR((String)"Push_Word() failed: Word not pushed.");/*		     */
    return;					   /*			     */
  }						   /*			     */
						   /*			     */
  words = wp;					   /*			     */
  PushWord(s);					   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***			Key Separator Section				   ***/
/*****************************************************************************/

#define NoSeps 8

 static Symbol *key_seps = NULL;

#define DefaultKey    key_seps[0]
#define InterNameSep  key_seps[1]
#define NamePreSep    key_seps[2]
#define NameNameSep   key_seps[3]
#define NameTitleSep  key_seps[4]
#define TitleTitleSep key_seps[5]
#define KeyNumberSep  key_seps[6]
#define EtAl	      key_seps[7]

/*-----------------------------------------------------------------------------
** Function:	set_separator()
** Purpose:	Modify the |key_seps| array. This array contains the
**		different separators used during key formatting. The
**		elements of the array have the following meaning:
**		\begin{description}
**		\item[0] The default key which is used when the
**		  formatting instruction fails completely.
**		\item[1] The separator which is inserted between
**		  different names of a multi-authored publication.
**		\item[2] The separator inserted between the first name
**		  and the last name when a name is formatted.
**		\item[3] The separator inserted between the last names
**		  when more then one last name is present
**		\item[4] The separator between the name and the title
**		  of a publication.
**		\item[5] The separator inserted between words of the
**		  title.
**		\item[6] The separator inserted before the number
**		  which might be added to disambiguate reference keys.
**		\item[7] The string which is added when a list of
**		  names is truncated. (|.ea|)
**		\end{description}
** Arguments:
**	n	Array index to modify.
**	s	New value for the given separator. The new value is
**		stored as a symbol. Thus the memory of |s| need not to
**		be preserved after this function is completed.
**		The characters which are not allowed are silently sypressed.
** Returns:	nothing
**___________________________________________________			     */
void set_separator(n,s)				   /*			     */
  register int	n;				   /*			     */
  String s;				   	   /*			     */
{ 						   /*                        */
  if ( n < 0 || n >= NoSeps || !is_allowed(*s) )   /*			     */
  { ERROR("Invalid separator specification.");     /*			     */
    return;					   /*			     */
  }						   /*			     */
 						   /*                        */
  if (key_seps == NULL) init_key();		   /*                        */
 						   /*                        */
  key_seps[n] = sym_extract(&s, false);		   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_separator()
** Type:	String
** Purpose:	
**		
** Arguments:
**	n	
** Returns:	
**___________________________________________________			     */
Symbol get_separator(n)				   /*                        */
  int n;					   /*                        */
{ return key_seps[n];				   /*                        */
}						   /*------------------------*/


/*****************************************************************************/
/***			   Key Base Section				   ***/
/*****************************************************************************/

 static char * key__base[] = 
 { "0123456789",
   "_abcdefghijklmnopqrstuvwxyz",
   "_ABCDEFGHIJKLMNOPQRSTUVWXYZ"
 };
#define KEY_BASE_DIGIT 0
#define KEY_BASE_LOWER 1
#define KEY_BASE_UPPER 2
 static int key_base = KEY_BASE_DIGIT;

/*-----------------------------------------------------------------------------
** Function:	set_base()
** Purpose:	Define the key base. This value determines the format
**		of the disambiguation string added to a key if
**		required. The following values are considered:
**		\begin{itemize}
**		\item If the value is |upper| or starts with an upper
**		  case letter then the disambiguation is done with
**		  upper-case letters.
**		\item If the value is |lower| or starts with a lower
**		  case letter then the disambiguation is done with
**		  lower-case letters.
**		\item If the value is |digit| or starts with an digit
**		  then the disambiguation is done with arabic numbers. 
**		\end{itemize}
**		The comparison of the keywords is done case
**		insensitive. The special values take precedence before
**		the first character rules.
**		
**		If an invalid value is given to this function then an
**		error is raised and the program is terminated.
** Arguments:
**	value	String representation of the new value.
** Returns:	nothing
**___________________________________________________			     */
void set_base(value)				   /*			     */
  String value;				   	   /*			     */
{						   /*			     */
  if	  ( case_eq(value,(String)"upper") ) key_base = KEY_BASE_UPPER;/*    */
  else if ( case_eq(value,(String)"lower") ) key_base = KEY_BASE_LOWER;/*    */
  else if ( case_eq(value,(String)"digit") ) key_base = KEY_BASE_DIGIT;/*    */
  else if ( is_upper(*value) )	      key_base = KEY_BASE_UPPER;/*	     */
  else if ( is_lower(*value) )	      key_base = KEY_BASE_LOWER;/*	     */
  else if ( is_digit(*value) )	      key_base = KEY_BASE_DIGIT;/*	     */
  else { ERROR("Unknown base ignored."); }	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_base()
** Type:	String
** Purpose:	Getter for the printable representation of the key_base.
**		
** Arguments:	none
** Returns:	
**___________________________________________________			     */
String get_base()				   /*                        */
{						   /*                        */
  switch(key_base)				   /*                        */
  { case KEY_BASE_UPPER: return (String)"upper";   /*                        */
    case KEY_BASE_LOWER: return (String)"lower";   /*                        */
    case KEY_BASE_DIGIT: return (String)"digit";   /*                        */
    default: return s_empty;			   /*                        */
  }						   /*                        */
}						   /*------------------------*/

#define ITOA_LEN 64

/*-----------------------------------------------------------------------------
** Function*:	itostr()
** Purpose:	Translate number using the ``digits'' given.
**		A static string is returned containing the result.
**		This is a routine generalizing |itoa()|.
** Examples:
**	itostr(X,"0123456789ABCDEF")	 returns the hexadecimal representation
**	itostr(X,"0123456789")		 returns the decimal representation
**	itostr(X,"01234567")		 returns the octal representation
**	itostr(X,"01")			 returns the binary representation
**
** Arguments:
**	i	Integer to translate
**	digits	String of digits to use
** Returns:	
**___________________________________________________			     */
static char * itostr(i,digits)			   /*			     */
  register int	 i;				   /*			     */
  register char	 *digits;			   /*			     */
{ static char	 buffer[ITOA_LEN];		   /* buffer to store result */
  register char	 *bp;				   /* buffer pointer	     */
  register int	 sign,				   /*			     */
		 base;				   /*			     */
						   /*			     */
  base	  = strlen(digits);			   /* how many digits?	     */
  bp	  = buffer+ITOA_LEN-1;			   /* set pointer to the end.*/
  *(bp--) = '\0';				   /* mark the end.	     */
  if ( i<0 ) { sign = -1; i = -i; }		   /*			     */
  else { sign = 0; if ( i == 0 ) *(bp--) = '0'; }  /*			     */
  while ( i > 0 )				   /*			     */
  { *(bp--) = digits[i%base];			   /*			     */
    i	    = i/base;				   /*			     */
  }						   /*			     */
  if ( sign ) *bp = '-'; else ++bp;		   /*			     */
  return(bp);					   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***			       Key Init Section				   ***/
/*****************************************************************************/

/*-----------------------------------------------------------------------------
** Function*:	init_key()
** Purpose:	Global initializations for the key module.
**		This function has to be called before some of the
**		functions provided in this module are guaranteed to
**		work properly.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
static void init_key()			   	   /*                        */
{ int  i;					   /*			     */
  String s;					   /*                        */
  						   /*                        */
  if (key_seps != NULL) return;			   /*                        */

  key_seps   = (Symbol*)malloc(8*sizeof(Symbol));/*                        */
  key_seps[0] = symbol((String)"**key*");	   /*                        */
  key_seps[1] = symbol((String)"-");		   /*                        */
  key_seps[2] = symbol((String)".");		   /*                        */
  key_seps[3] = symbol((String)".");		   /*                        */
  key_seps[4] = symbol((String)":");		   /*                        */
  key_seps[5] = symbol((String)"-");		   /*                        */
  key_seps[6] = symbol((String)"*");		   /*                        */
  key_seps[7] = symbol((String)".ea");	   	   /*                        */
 						   /*                        */
  for (i = 0; i < NUMBER_OF_FORMATS; i++)	   /*                        */
  { format[i] = NameNULL; }			   /*                        */
 						   /*                        */
  if ( format[0] == NameNULL )		   	   /*                        */
  { s = newString("%*l");		   	   /*                        */
    format[0] = name_format(s);		   	   /*                        */
    free(s);				   	   /*                        */
  }						   /*                        */
  NameMid(format[0]) = InterNameSep;	   	   /*                        */
 						   /*                        */
  if ( format[1] == NameNULL )		   	   /*                        */
  { s = newString("%*l%*1f");	   	   	   /*                        */
    format[1] = name_format(s);		   	   /*                        */
    free(s);				   	   /*                        */
  }						   /*                        */
  NameMid(format[1]) = InterNameSep;	   	   /*                        */
  if (NextName(format[1]))			   /*                        */
  { NamePre(NextName(format[1])) = NamePreSep;     /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	key_init()
** Purpose:	Perform initializations for key generation.
**		The string buffer is opened.
**		Ignored words are initialized if necessary.
** Arguments:   none
** Returns:	nothing
**___________________________________________________			     */
static void key_init()				   /*			     */
{						   /*                        */
#ifdef INITIALIZE_IGNORED_WORDS
  static char *word_list[] =			   /* default ignored words. */
  { INITIALIZE_IGNORED_WORDS, NULL };		   /* Mark the end with NULL */
  register char**wp;				   /*			     */
#endif
						   /*			     */
  if ( key_sb == (StringBuffer*)0 )		   /* Is it the first time?  */
  {						   /*                        */
    if ( (key_sb=sbopen()) == (StringBuffer*)0 )   /* open string buffer     */
    { OUT_OF_MEMORY("key generation."); }	   /*			     */
#ifdef INITIALIZE_IGNORED_WORDS
    for ( wp = word_list; *wp != NULL; ++wp )	   /* add ignored words.     */
    { add_ignored_word(symbol((String)*wp)); }	   /*			     */
#endif
  }						   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***			      Key DeTeX Section				   ***/
/*****************************************************************************/

#define DeTeX_BUFF_LEN 256

#define DETEX_FLAG_NONE    0
#define DETEX_FLAG_COMMA   1
#define DETEX_FLAG_ALLOWED 2

/*-----------------------------------------------------------------------------
** Function*:	deTeX()
** Purpose:	Expand TeX sequences or eliminate them.
**
** Arguments:
**	line	string to work on
**	save_fct Function pointer which is called to store resulting
**		characters. 
**	flags	
** Returns:	
**___________________________________________________			     */
static int deTeX(line,save_fct,flags)		   /*			     */
  String	line;				   /*			     */
  int		flags;				   /*			     */
  void		(*save_fct)_ARG((String));	   /*			     */
{ static String	buffer;			   	   /*			     */
  static size_t len   = 0;			   /*			     */
  Uchar		c;				   /*                        */
  String	s, bp;			   	   /*			     */
  Uchar		last  = (Uchar)' ';		   /*			     */
  int		wp    = 0;			   /*			     */
  int		brace;				   /*			     */
						   /*			     */
#define SaveWord     wp++; (*save_fct)(bp)
#define SaveChar(C)  *(bp++) = last = C
#define StoreChar(C) *(bp++) = C
						   /*			     */
  brace = 8 * strlen((char*)line);		   /*			     */
  if ( brace > (int)len )			   /*			     */
  { if ( len == 0 )				   /*			     */
    { len    = ( brace < DeTeX_BUFF_LEN		   /*			     */
		? DeTeX_BUFF_LEN : brace );	   /*			     */
      buffer = (String)malloc(sizeof(Uchar)*len);  /*			     */
    }						   /*			     */
    else					   /*			     */
    { len    = brace;				   /*			     */
      buffer = (String)realloc((char*)buffer,	   /*                        */
			       sizeof(Uchar)*len); /*	                     */
    }						   /*			     */
    if ( buffer == NULL ) 			   /*                        */
    { OUT_OF_MEMORY("deTeX()"); }   		   /*			     */
  }						   /*			     */
						   /*			     */
  TeX_open_string(line);		   	   /*			     */
  bp	= buffer;				   /*			     */
  brace = 0;					   /*			     */
  wp    = 0;					   /*                        */
  SaveWord;					   /*			     */
						   /*			     */
  while ( TeX_read(&c, &s) )			   /*			     */
  {						   /*			     */
    if (   is_alpha(c)				   /* Letters and	     */
	|| is_digit(c)				   /* digits and	     */
	|| is_extended(c)			   /* extended chars and     */
	|| ( c == (Uchar)'-' && last != c ) )	   /* non-repeated hyphens   */
    { SaveChar(c); }				   /*			     */
    else if ( c == (Uchar)'{' ) { ++brace; }	   /* Count braces.	     */
    else if ( c == (Uchar)'}' )		   	   /*                        */
    { if ( --brace < 0 ) brace = 0;		   /*                        */
    }						   /*			     */
    else if ( ( c == ',' 			   /* Commas                 */
		&& (flags&DETEX_FLAG_COMMA) )	   /*                        */
	      ||				   /* or                     */
	      ( (flags&DETEX_FLAG_ALLOWED)	   /* allowed characters     */
		&& is_allowed(c) )		   /*                        */
	    )					   /*                        */
    { if ( bp != buffer && *(bp-1) != '\0' )	   /*  are treated as        */
      { StoreChar('\0');			   /*  single words upon     */
	SaveWord;				   /*  request, or ignored.  */
      }						   /*                        */
      StoreChar(c);				   /*			     */
      StoreChar('\0');				   /*			     */
      SaveWord;					   /*			     */
      last = ' ';				   /*			     */
    }						   /*                        */
    else if ( !(flags&DETEX_FLAG_ALLOWED)	   /*                        */
	      && is_wordsep(c)			   /*                        */
	      && !is_wordsep(last) ) 		   /* Don't repeat spaces.   */
    { if ( brace == 0 )				   /* Remember the beginning */
      { StoreChar('\0'); SaveWord; last = ' '; }   /*  of the next word.     */
      else					   /*                        */
      { String t;				   /*                        */
	for (t = SymbolValue(InterNameSep); *t; ++t)/*                       */
	{ SaveChar(*t);	}			   /*                        */
      }		   				   /*			     */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  if (buffer) {					   /*			     */
    if ( bp != buffer && *(bp-1) != '\0' )	   /*                        */
    { StoreChar('\0');				   /*                        */
      SaveWord;					   /*                        */
    }						   /*                        */
      						   /*                        */
    StoreChar('\0');				   /* Mark the end.	     */
						   /*			     */
    if ( bp-buffer >= (int)len )		   /*			     */
    { ERROR_EXIT("deTeX buffer overflow."); }	   /*			     */
  }						   /*			     */
						   /*			     */
  TeX_close();					   /*			     */
  return wp-1;					   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***		       Title Formatting Section				   ***/
/*****************************************************************************/

#define PushS(SB,S)	push_s(SB,S,0,trans)
#define PushStr(SB,S,M)	push_s(SB,S,M,trans)
#define PushC(SB,C)	(void)sbputchar(trans[(unsigned int)(C)],SB);

/*-----------------------------------------------------------------------------
** Function*:	push_s()
** Purpose:	Write a translated string to the key string buffer.
** Arguments:
**	s	String to translate
**	max	Maximum number of characters
**	trans	Translation table
** Returns:	nothing
**___________________________________________________			     */
static void push_s(sb,s,max,trans)		   /*			     */
  StringBuffer *sb;				   /*                        */
  String s;			   	   	   /*			     */
  int max;				   	   /*                        */
  String trans;		   		   	   /*			     */
{						   /*                        */
  if ( max <= 0 ) 				   /*                        */
  { while ( *s )				   /*			     */
    { (void)sbputchar(trans[*(s++)],sb); }	   /*                        */
  }						   /*			     */
  else						   /*                        */
  { while ( *s && max-->0 )			   /*			     */
    { (void)sbputchar(trans[*(s++)],sb); }	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

 static WordList ignored_words[32] = 
 { WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL
 };

/*-----------------------------------------------------------------------------
** Function:	add_ignored_word()
** Purpose:	Add a new word to the list of ignored words for title
**		key generation.
**		The argument has to be saved by the caller! This means
**		that it is assumed that the argument is a symbol.
** Arguments:
**	word	Word to add.
** Returns:	nothing
**___________________________________________________			     */
void add_ignored_word(word)			   /*			     */
  Symbol word;				   	   /*			     */
{						   /*                        */
  key_init();					   /*                        */
  add_word(word,				   /*                        */
	   &ignored_words[(*SymbolValue(word))&31]);/*			     */
  DebugPrint2("Adding ignored word ",		   /*                        */
	      SymbolValue(word));	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	clear_ignored_words()
** Purpose:	Delete the list of ignored words. Afterwards no words are
**		recognized as ignored words.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void clear_ignored_words()			   /*                        */
{ int i;					   /*                        */
  key_init();					   /*                        */
 						   /*                        */
  for (i = 0; i < 32; i++)			   /*                        */
  { free_words(&ignored_words[i], NULL); }	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	foreach_ignored_word()
** Purpose:	Iterator a given function |fct| is applied to each
**		ignored word in turn. If the function returns 0 then
**		the loop is terminated. The different words are
**		visited in a fixed order which does not necessarily
**		coincide with the natural order of words. Thus don't
**		assume this.
** Arguments:
**	fct	Function to apply.
** Returns:	The return status of the last |fct| call.
**___________________________________________________			     */
bool foreach_ignored_word(fct)			   /*                        */
  bool (*fct)_ARG((Symbol));			   /*                        */
{ int i;					   /*                        */
 						   /*                        */
  key_init();					   /*                        */
 						   /*                        */
  for (i = 0; i < 32; i++)			   /*                        */
  { if (!foreach_word(ignored_words[i], fct))	   /*                        */
    { return false; }				   /*                        */
  }						   /*                        */
  return true;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	fmt_title()
** Purpose:	Format a string according to rules for titles.
**		\TeX{} sequences are expanded and some words may be ignored.
**		The result is pushed to the local string buffer.
** Arguments:
**	line	String to format.
**	len	Number of words to use
**	in	Number of characters per word to use
**	trans	Translation table
**	ignore	Boolean. Certain words are ignored if it is |true|
**	sep	String separating the words.
** Returns:	nothing
**___________________________________________________			     */
static void fmt_title(sb, line, len, in, trans, ignore, sep)/*		     */
  StringBuffer  *sb;				   /*                        */
  String        line;				   /*			     */
  int	        len;				   /*			     */
  int	        in;				   /*			     */
  String	trans;				   /* Translation table	     */
  bool          ignore;				   /*                        */
  Symbol        sep;				   /*                        */
{ bool	        first = true;			   /*			     */
  int	        nw, i, j;			   /*			     */
  String        s;				   /*			     */
						   /*			     */
  /*  if ( len == 0 ) return;			                             */
 						   /*                        */
  if (	 tmp_sb == (StringBuffer*)NULL		   /*			     */
      && (tmp_sb=sbopen()) == (StringBuffer*)NULL )/*			     */
  { OUT_OF_MEMORY("fmt_title()"); } 		   /*			     */
						   /*			     */
  ResetWords;					   /*                        */
  nw = deTeX(*line == (Uchar)'{' ? line + 1 : line,/*                        */
	     push_word,				   /*                        */
	     DETEX_FLAG_NONE);			   /*	                     */
 						   /*                        */
  for (i = 0; i < nw; ++i)		   	   /*			     */
  {						   /*			     */
    sbrewind(tmp_sb);				   /* Reset the string buffer*/
    for (s = words[i]; *s; ++s)	   		   /* Translate the current  */
    { (void)sbputchar(trans[*s],tmp_sb); }	   /*  word into the sbuffer */
    s = (String)sbflush(tmp_sb);		   /* Get the translated word*/
						   /*			     */
    if ( ! ignore || 				   /*                        */
	 ! find_word((String)s,		   	   /*                        */
		     ignored_words[(*s)&31] ) )	   /*		             */
    { if (first) { first = false; }		   /*			     */
      else { PushS(sb, SymbolValue(sep)); }	   /*			     */
      if ( in <= 0 )				   /*                        */
      { PushS(sb, words[i]); }	   		   /* Push the current word  */
      else					   /*                        */
      { for (s = words[i], j = in;	   	   /*                        */
	     *s && j-->0;			   /*                        */
	     ++s)				   /* Push the initial part  */
	{ PushC(sb, *s); }			   /*  of the current word.  */
      }						   /*                        */
      if ( len == 1 ) return;	   		   /*                        */
      if ( len > 0  ) len--;			   /*                        */
    }						   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	fmt_c_words()
** Purpose:	Count a list of words.
** Arguments:
**	line	string to analyze
**	min	minimum
**	max	maximum or 0
**	not	negation flag
**	ignore	flag to indicate if certain words should be ignored.
** Returns:	
**___________________________________________________			     */
static bool fmt_c_words(line, min, max, not, ignore)/*			     */
  String line;					   /*			     */
  int	 min;					   /*			     */
  int	 max;					   /*			     */
  bool	 not;					   /*			     */
  bool	 ignore;				   /*			     */
{ int	 n, i, nw;				   /*			     */
						   /*			     */
  ResetWords;					   /*                        */
  nw = deTeX(*line == (Uchar)'{' ? line + 1 : line,/*                        */
	     push_word,				   /*                        */
	     DETEX_FLAG_NONE);			   /*                        */
  n = 0;					   /*                        */
 						   /*                        */
  for (i = 0; i < nw; ++i)		   	   /*			     */
  {						   /*			     */
    if (!ignore || 				   /*                        */
	!find_word(words[i],			   /*                        */
		   ignored_words[(*words[i])&31]) )/*	                     */
    { n++; }					   /*			     */
  }						   /*			     */
 						   /*                        */
  if (n < min || (max > 0 && n > max))		   /*                        */
  { return (not ? false : true); }		   /*                        */
 						   /*                        */
  return (not ? true : false);			   /*                        */
}						   /*------------------------*/


/*****************************************************************************/
/***		         Name Formatting Section			   ***/
/*****************************************************************************/


/*-----------------------------------------------------------------------------
** Function:	def_format_type()
** Purpose:	
**		
**
** Arguments:
**	s
** Returns:	nothing
**___________________________________________________			     */
void def_format_type(s)				   /*                        */
  String s;					   /*                        */
{ int    n;					   /*                        */
  String cp;					   /*                        */
  Uchar  c;					   /*                        */
 						   /*                        */
  SkipSpaces(s);				   /*                        */
  n = 0;					   /*                        */
  while ( is_digit(*s) ) { n = n*10 + (*s++) - '0'; }/*                      */
  if ( n >= NUMBER_OF_FORMATS )			   /*                        */
  { WARNING("Format type number is out of range.");/*                        */
    return;					   /*                        */
  }						   /*                        */
  if ( rsc_verbose && n <= 1 )			   /*                        */
  { VerbosePrint3("Name format specifier ",	   /*                        */
		  (n==0?"0":"1"),		   /*                        */
		  " has been changed.\n");	   /*                        */
  }						   /*                        */
 						   /*                        */
  if (key_seps == NULL)	{ init_key(); }	   	   /*                        */
 						   /*                        */
  SkipSpaces(s);				   /*                        */
  if ( *s == '=' ) s++;				   /*                        */
  ExpectVoid(s,'"');				   /*                        */
  cp = s;					   /*                        */
  while ( *cp && *cp != '"' ) cp++;		   /*                        */
  c   = *cp;					   /*                        */
  *cp = (Uchar)'\0';				   /*                        */
  format[n] = name_format(s);			   /*                        */
  *cp = c;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	fmt_names()
** Purpose:	Format a list of names separated by 'and'.
**		'and others' is handled properly.
** Arguments:
**	line	String to format.
**	maxname	number of names to consider
**	maxlen  number of characters per name to consider
**	post	the number of relevant char
**	trans	translation table
** Returns:	nothing
**___________________________________________________			     */
static void fmt_names(sb,line,maxname,post,trans)  /*		             */
  StringBuffer  *sb;				   /*                        */
  String        line;				   /* Name list string	     */
  int	        maxname;			   /* number of names b4 etal*/
  int           post;				   /* number of relevant char*/
  String	trans;				   /* Translation table	     */
{ int	        wp,				   /*			     */
	        i;				   /*			     */
  static bool   undef_warning = false;		   /*                        */
  						   /*                        */
  if ( maxname == 0 ) return;			   /*                        */
 						   /*                        */
  if (   post < 0				   /*                        */
      || post >= NUMBER_OF_FORMATS		   /*                        */
      || format[post] == NameNULL )		   /*                        */
  { if (undef_warning)				   /*                        */
    { ErrPrintF("*** BibTool: Format %d is not defined. Ignored.\n",/*       */
		post);				   /*                        */
      undef_warning = true;			   /*                        */
    }						   /*                        */
    return;					   /*                        */
  }						   /*                        */
 						   /*                        */
  ResetWords;					   /*                        */
  wp = deTeX(*line == (Uchar)'{' ? line + 1 : line,/*                        */
	     push_word,				   /*                        */
	     DETEX_FLAG_COMMA);			   /*	                     */
  words[wp] = StringNULL;			   /*                        */
 						   /*                        */
  for (i = 0; i < wp; i++)			   /*			     */
  {						   /*                        */
    DebugPrintF3("+++ %3d '%s'\n", i, words[i]);   /*                        */
 						   /*                        */
    if (strcmp((char*)words[i],"and") == 0)	   /*                        */
    { words[i] = SymbolValue(sym_et); }	   	   /*                        */
    else if (strcmp((char*)words[i], ",") == 0)    /*                        */
    { words[i] = SymbolValue(sym_comma); } 	   /*                        */
  }						   /*                        */
 						   /*                        */
  PushS(sb,					   /*                        */
	pp_list_of_names(words,		   	   /*                        */
			 format[post],	   	   /*                        */
			 trans,		   	   /*                        */
			 maxname,		   /*                        */
			 SymbolValue(sym_comma),   /*                        */
			 SymbolValue(sym_et),	   /*                        */
			 (char*)SymbolValue(NameNameSep),/*                  */
			 (char*)SymbolValue(EtAl)));/*                       */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	fmt_c_names()
** Purpose:	Count a list of names
** Arguments:
**	line	string to analyze
**	min	minimum
**	max	maximum or 0
**	not	negation flag
** Returns:	
**___________________________________________________			     */
static bool fmt_c_names(line,min,max,not)	   /*		             */
  String line;				   	   /* Name list string	     */
  int   min;				   	   /* number of relevant char*/
  int   max;				   	   /* number of names b4 etal*/
  int   not;				   	   /* negation flag          */
{ int   wp,				   	   /*			     */
        i,				   	   /*                        */
	n;				   	   /*			     */
  						   /*                        */
  ResetWords;					   /*                        */
  wp = deTeX(*line == (Uchar)'{' ? line + 1 : line,/*                        */
	     push_word,				   /*                        */
	     DETEX_FLAG_COMMA);			   /*	                     */
  words[wp] = NULL;				   /*                        */
 						   /*                        */
  for ( i = 0, n = 1; i < wp; i++)		   /*			     */
  { if (strcmp((char*)words[i],"and") == 0)	   /*                        */
    { n++; }					   /*                        */
  }						   /*                        */
 						   /*                        */
  if (n < min || (max > 0 && n > max))		   /*                        */
  { return (not ? false : true); }		   /*                        */
 						   /*                        */
  return (not ? true : false);			   /*                        */
}						   /*------------------------*/


/*****************************************************************************/
/***		         Number Formatting Section			   ***/
/*****************************************************************************/

/*-----------------------------------------------------------------------------
** Function*:	fmt_digits()
** Purpose:	Search a sequence of digits and push at most n of them 
**		counting from right to the string buffer.
** Example:	fmt_digits("jun 1958",2) pushes "58" to the string buffer.
** Arguments:
**	sb	String buffer to store the result in
**	s	String to format
**	mp	Boolean indicating whether padding with 0s should be performed
**		(true) or not.
**	pp	Boolean indicating whether no number should be 0 or fail
**	n	Length
**	sel	The number to select.
**	trunc	Boolean indicating whether or not to truncate the number.
** Returns:	
**___________________________________________________			     */
static bool fmt_digits(sb,s,mp,pp,n,sel,trunc)	   /*			     */
  StringBuffer    *sb;				   /*                        */
  register String s;				   /*			     */
  int             mp;				   /*                        */
  int             pp;				   /*                        */
  register int 	  n;				   /*			     */
  int		  sel;				   /*                        */
  bool            trunc;			   /*                        */
{ register String cp;				   /*			     */
						   /*			     */
  if (n < 0) { n = ( mp ? 1 : 0x7fff ); }	   /*                        */
 						   /*                        */
  cp = s;					   /*                        */
  while (sel-->0)				   /*                        */
  { s = cp;					   /*                        */
    while (*s && !is_digit(*s)) { ++s; }   	   /* search first digit     */
    if ( *s == '\0' )				   /*                        */
    { cp = s; sel = 0; }			   /*                        */
    else					   /*                        */
    { for (cp = s; *cp && is_digit(*cp); ++cp) {}  /* skip over digits	     */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  if (trunc && cp-s > n) s = cp-n;		   /*			     */
  else if (mp)				   	   /*                        */
  { while (cp - s < n--)			   /*                        */
    { (void)sbputchar('0', sb); }		   /*                        */
  }						   /*                        */
  if (!mp && *s == '\0')			   /*                        */
  { if (pp) (void)sbputchar('0', sb);	   	   /*                        */
    else return true;				   /*                        */
  }						   /*                        */
  else						   /*                        */
  {						   /*                        */
    while ( s != cp )				   /*			     */
    { (void)sbputchar((char)(*s), sb);		   /*                        */
      ++s;					   /*                        */
    }	   					   /*			     */
  }						   /*                        */
  return false;					   /*                        */
}						   /*------------------------*/


/*****************************************************************************/
/***		         String Formatting Section			   ***/
/*****************************************************************************/

/*-----------------------------------------------------------------------------
** Function*:	fmt_string()
** Purpose:	Push characters from s onto the string buffer.
**		At most n characters are transfered.
**		Letters are translated according to mode.
** Arguments:
**	s	String to format
**	n	Length
**	trans	Translation table
**	sep	Separator
** Returns:	nothing
**___________________________________________________			     */
static void fmt_string(sb,s,n,trans,sep)	   /*			     */
  StringBuffer	  *sb;				   /*                        */
  register String s;				   /*			     */
  register int	  n;				   /*			     */
  register String trans;			   /*			     */
  String       	  sep;			   	   /*                        */
{						   /*			     */
  while (*s && n > 0)				   /*			     */
  { if (is_allowed(*s))			   	   /*			     */
    { (void)sbputchar(trans[*s],sb);		   /*                        */
      n--;					   /*                        */
    }						   /*		             */
    else if (is_space(*s))			   /*			     */
    { (void)sbputs((char*)sep, sb);		   /*                        */
      n--;	   	   			   /*                        */
      while (is_space(*s)) s++;		   	   /* skip over multiple SPC */
      s--;					   /*                        */
    }   					   /*			     */
    ++s;					   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	fmt_c_string()
** Purpose:	Count the number of characters in a string and compare it
**		against an interval.
**
** Arguments:
**	s	string to analyze
**	min	minimum
**	max	maximum or 0
**	not	negation flag
** Returns:	
**___________________________________________________			     */
static bool fmt_c_string(s,min,max,not)		   /*			     */
  register String  s;				   /*			     */
  register int   min;				   /*			     */
  register int   max;				   /*			     */
  register bool  not;				   /*			     */
{ int            n = 0;				   /*			     */
 						   /*                        */
  while (*s)				   	   /*			     */
  { if (is_allowed(*s)) { n++; }	   	   /*			     */
    else if (is_space(*s))			   /*			     */
    { n += symlen(TitleTitleSep);		   /*                        */
      while (is_space(*s)) s++;		   	   /* skip over multiple SPC */
    }   					   /*			     */
    ++s;					   /*			     */
  }						   /*			     */
 						   /*                        */
  if (n < min || (max > 0 && n > max))		   /*                        */
  { return (not ? false : true); }		   /*                        */
 						   /*                        */
  return (not ? true : false);			   /*                        */
}						   /*------------------------*/

#define IfGetField(S,NAME) if ((S=get_field(tmp_key_db,rec,NAME)) != NULL)

#define GetEntryOrReturn(S,NAME)					\
	if ((S=get_field(tmp_key_db,rec,NAME)) == NULL) return false

 static WordList old_keys = WordNULL;

 static Record tmp_rec = NULL;

/*-----------------------------------------------------------------------------
** Function:	start_key_gen()
** Purpose:	Start the key generation.
**		Any recorded keys are discarded.
** Arguments:
** Returns:	nothing
**___________________________________________________			     */
void start_key_gen()				   /*                        */
{						   /*                        */
  free_words(&old_keys, sym_unlink);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	end_key_gen()
** Purpose:	Finalize the key generation.
**		Any previously recorded keys are discarded.
** Arguments:
** Returns:	nothing
**___________________________________________________			     */
void end_key_gen()				   /*                        */
{						   /*                        */
  free_words(&old_keys,sym_unlink);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	mark_key()
** Purpose:	Set the key mark for the key symbol of a record.
** Arguments:
**	db	Database containing the record.
**	rec	Record to consider
** Returns:	nothing
**___________________________________________________			     */
bool mark_key(db,rec)				   /*			     */
  DB	 db;					   /*                        */
  Record rec;				   	   /*			     */
{						   /*			     */
  POSSIBLY_UNUSED(db);				   /*                        */
						   /*			     */
  if ( IsSpecialRecord(RecordType(rec)) ||	   /*                        */
       *RecordHeap(rec) == NULL )		   /*                        */
  { return false; }				   /*			     */
   						   /*                        */
  add_word(*RecordHeap(rec), &old_keys);	   /*                        */
  return false;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	make_key()
** Purpose:	Generate a key for a given record.
** Arguments:
**	db	Database containing the record.	
**	rec	Record to consider.
** Returns:	nothing
**___________________________________________________			     */
void make_key(db,rec)				   /*			     */
  DB		  db;				   /*                        */
  register Record rec;				   /*			     */
{ register String kp;			   	   /*			     */
  Symbol	  key;				   /*                        */
  Symbol          old;			   	   /*			     */
  int		  pos;				   /*			     */
						   /*			     */
  if ( IsSpecialRecord(RecordType(rec)) ) return;  /*			     */
						   /*			     */
  if (key_tree == (KeyNode)NULL)		   /*			     */
  { *RecordHeap(rec) = sym_empty;		   /* store an empty key     */
    return;					   /*			     */
  }						   /*			     */
 						   /*                        */
  if (key_seps == NULL)	{ init_key(); }	   	   /*                        */
						   /*			     */
  if (rsc_key_preserve &&			   /*                        */
      *SymbolValue(*RecordHeap(rec)) != '\0' )	   /*		             */
  { return; }					   /*			     */
						   /*			     */
  key_init();					   /*			     */
  sbrewind(key_sb);				   /* clear key		     */
						   /*			     */
  if (eval_fmt(key_sb, key_tree, rec,db))	   /*                        */
  { sbputs((char*)SymbolValue(DefaultKey), key_sb);/*                        */
  }			   			   /*			     */
						   /*			     */
  SetSym(RecordOldKey(rec), *RecordHeap(rec));	   /*                        */
 						   /*                        */
#ifndef NEW
#define trans trans_id
  ResetWords;					   /*                        */
  { char * buffer = new_string(sbflush(key_sb));   /*                        */
    int nw = deTeX((String)(*buffer == '{'	   /*                        */
			    ? buffer + 1	   /*                        */
			    : buffer), 		   /*                        */
		   push_word,			   /*                        */
		   DETEX_FLAG_ALLOWED);  	   /*                        */
    int i;					   /*                        */
    sbrewind(key_sb);				   /*                        */
    for (i = 0; i < nw; ++i)		   	   /*			     */
    { if ( strcmp((char*)words[i],	   	   /*                        */
		  "\\") )	   		   /*                        */
        PushS(key_sb, words[i]);	   	   /*			     */
    }						   /*                        */
    free(buffer);				   /*                        */
  }						   /*                        */
#undef trans
#endif
  pos = sbtell(key_sb);		   		   /*			     */
  kp  = (String)sbflush(key_sb);	   	   /* get collected key	     */
						   /*			     */
  if (find_word(kp, old_keys))		   	   /* is key already used?   */
  { int n = 1;					   /* Then disambiguate:     */
    (void)sbseek(key_sb, pos);			   /*			     */
    (void)sbputs((char*)SymbolValue(KeyNumberSep), /*                        */
		 key_sb);	   		   /* put separator at end   */
    pos = sbtell(key_sb);			   /*			     */
    do						   /* last symbol was present*/
    { (void)sbseek(key_sb, pos);		   /*			     */
      (void)sbputs(itostr(n++,key__base[key_base]),/*			     */
		   key_sb);			   /*			     */
      kp = (String)sbflush(key_sb);	   	   /*	get new key	     */
    } while (find_word(kp, old_keys));	   	   /*			     */
  }						   /*			     */
 						   /*                        */
  key = symbol(kp);				   /*                        */
  old = *RecordHeap(rec);			   /*                        */
  *RecordHeap(rec) = key;		   	   /* store new key	     */
  add_word(key, &old_keys);		   	   /* remember new key       */
 						   /* ---------------------- */
  if (rsc_make_alias				   /* if needed then make    */
      && !rsc_apply_alias			   /*                        */
      && old != NULL				   /*  an alias              */
      && key != old				   /*                        */
      && *SymbolValue(old))			   /*                        */
  {						   /*                        */
    if (tmp_rec == RecordNULL)			   /* lacy initialization    */
    { tmp_rec = new_record(BIB_ALIAS,2); }	   /*                        */
 						   /*                        */
    *RecordHeap(tmp_rec)   = old;		   /*                        */
    RecordHeap(tmp_rec)[1] = key;		   /*                        */
    db_insert(db, copy_record(tmp_rec), false);	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	make_sort_key()
** Purpose:	
**
** Arguments:
**	db	Database containing the record.
**	rec	Record to consider.
** Returns:	nothing
**___________________________________________________			     */
void make_sort_key(db,rec)			   /*			     */
  DB		  db;				   /*                        */
  register Record rec;				   /*			     */
{ register String kp;				   /*			     */
						   /*			     */
  if ( IsSpecialRecord(RecordType(rec)) ) return;  /*			     */
						   /*			     */
  key_init();					   /*			     */
  sbrewind(key_sb);				   /* clear key		     */
						   /*			     */
  if (	 sort_key_tree != (KeyNode)0		   /*			     */
      && eval_fmt(key_sb,sort_key_tree,rec,db) == 0 )/*			     */
  { kp		       = (String)sbflush(key_sb);  /* get collected key	     */
    RecordSortkey(rec) = symbol(kp);	   	   /* store new key	     */
  }						   /*			     */
  else						   /* If everything fails    */
  { RecordSortkey(rec) = RecordHeap(rec)[0];	   /* use the reference key  */
  }						   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***		      Key Format Parsing and Evaluating			   ***/
/*****************************************************************************/

/*-----------------------------------------------------------------------------
** Function*:	new_key_node()
** Purpose:	Allocate a new key node
** Arguments:
**	type	the type
**	sym	the symbol
** Returns:	The address of the new node.
**		Upon failure exit() is called.
**___________________________________________________			     */
static KeyNode new_key_node(type, sym)	   	   /*			     */
  int	  type;					   /*			     */
  Symbol  sym;				   	   /*			     */
{ KeyNode new_node;				   /*			     */
  if( (new_node=(KeyNode)malloc(sizeof(SKeyNode))) ==/*                      */
      (KeyNode)0 )				   /*		             */
  { OUT_OF_MEMORY(" new_node_key_node()"); } 	   /*			     */
						   /*			     */
  NodeType(new_node)   = type;		   	   /*			     */
  NodeSymbol(new_node) = sym;			   /*			     */
  NodeNext(new_node)   = (KeyNode)0;		   /*			     */
  NodeThen(new_node)   = (KeyNode)0;		   /*			     */
  NodeElse(new_node)   = (KeyNode)0;		   /*			     */
  NodePre(new_node)    = -1;			   /*                        */
  NodePost(new_node)   = -1;			   /*                        */
  return new_node;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_key_node()
** Purpose:	A tree rooted at a given |KeyNode| will be freed.
** Arguments:
**	kn	KeyNode to be freed.
** Returns:	nothing
**___________________________________________________			     */
void free_key_node(kn)				   /*			     */
  KeyNode kn;					   /*			     */
{ KeyNode next;					   /*                        */
						   /*			     */
  while ( kn != (KeyNode)0 )			   /*                        */
  {						   /*                        */
    free_key_node(NodeThen(kn));		   /*                        */
    free_key_node(NodeElse(kn));		   /*                        */
    next = NodeNext(kn);			   /*                        */
    free(kn);					   /*                        */
    kn = next;					   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	add_fmt_tree()
** Purpose:	Extend the format tree
** Arguments:
**	s	the specification of th format
**	treep	the pointer to the tree to be extended
** Returns:	|true| iff the operation succeeds
**___________________________________________________			     */
static bool add_fmt_tree(s, treep)		   /*			     */
  char	  *s;					   /*			     */
  KeyNode *treep;				   /*			     */
{ KeyNode kn, kn_or;				   /*			     */
  int	  special   = 0;			   /*			     */
  String  s0 = (String)s;			   /*			     */
						   /*			     */
  if (s == (char*)NULL) return false;		   /*			     */
						   /*			     */
  if ( strcmp(s,"empty") == 0 )			   /*			     */
  { free_key_node(*treep);			   /*			     */
    *treep = (KeyNode)0;			   /*                        */
    return true;				   /*                        */
  }		   				   /*                        */
  else if ( strcmp(s,"short"	) == 0 )	   /*                        */
  { special = KEYSTYLE_SHORT;	  }		   /*                        */
  else if ( strcmp(s,"long"	) == 0 )	   /*                        */
  { special = KEYSTYLE_LONG;	  }		   /*                        */
  else if ( strcmp(s,"new.short")  == 0 ||	   /*                        */
	    strcmp(s,"short.need") == 0 )	   /*                        */
  { special = KEYSTYLE_SHORT;			   /*                        */
    rsc_key_preserve = true;			   /*                        */
  }						   /*                        */
  else if ( strcmp(s,"new.long" ) == 0 ||	   /*                        */
	    strcmp(s,"long.need") == 0 )	   /*                        */
  { special = KEYSTYLE_LONG;			   /*                        */
    rsc_key_preserve = true;			   /*                        */
  }						   /*                        */
						   /*			     */
  if ( special )				   /*			     */
  { free_key_node(*treep);			   /*			     */
    *treep = new_key_node(NodeSPECIAL, NO_SYMBOL); /*			     */
    NodePre(*treep) = special;			   /*			     */
    return true;				   /*			     */
  }						   /*			     */
						   /*			     */
  if ( fmt_parse(&s,&kn) > 0 )			   /*			     */
  { error(ERR_POINT|ERR_WARN,			   /*			     */
	  (String)"Format Error. Format ignored.", /*			     */
	  StringNULL,StringNULL,s0,(String)s,0,(char*)s_empty);/*	     */
    return false;				   /*			     */
  }						   /*			     */
  if ( *treep == (KeyNode)0 ) { *treep	= kn; }	   /*			     */
  else if ( NodeType(*treep) == NodeSPECIAL )	   /*			     */
  { free_key_node(*treep);			   /*			     */
    *treep  = kn;				   /*			     */
  }						   /*			     */
  else						   /*			     */
  { kn_or = new_key_node(NodeOR, NO_SYMBOL);	   /*			     */
    NodeThen(kn_or) = *treep;			   /*			     */
    NodeElse(kn_or) = kn;			   /*			     */
    *treep	    = kn_or;			   /*			     */
  }						   /*			     */
						   /*			     */
#ifdef DEBUG
  show_fmt(*treep,0);			   	   /*			     */
#endif
  return true;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	add_format()
** Purpose:	Add a key format specification to the current
**		specification.  This specification is used for
**		generating new reference keys. Thus the resource
**		|rsc_make_key| is turned on aswell.
**
**		Several strings are treated special. If a special
**		format is encountered then the effect is that the old
**		key specification is cleared first before the new
**		format is added:
**		\begin{description}
**		\item[empty] The empty format is activated. This means that
**		  the format is cleared and without further action the
**		  default key will be used.
**		\item[long] The long format is activated. This means that
**		  authors names with initials and the first word of
**		  the title are used.
**		\item[short] The short format is activated. This means that
**		  authors last names and the first word of the title
**		  are used. 
**		\item[new.long] This means that the long format will
**		  be used but only if the record does not have a key
**		  already. 
**		\item[new.short] This means that the short format will
**		  be used but only if the record does not have a key
**		  already. 
**		\end{description}
** Arguments:
**	s	Specification string
** Returns:	nothing
**___________________________________________________			     */
void add_format(s)				   /*			     */
  register char *s;				   /*			     */
{						   /*			     */
  if (s == NULL)				   /*			     */
  { WARNING("Missing key format.");		   /*			     */
    return;					   /*			     */
  }						   /*			     */
  rsc_make_key = true;				   /*			     */
  (void)add_fmt_tree(s,&key_tree);		   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	add_sort_format()
** Purpose:	Add a sort key format specification to the current
**		specification.  This specification is used for
**		generating new sort keys.
**
**		Several strings are treated special. If a special
**		format is encountered then the effect is that the old
**		key specification is cleared first before the new
**		format is added:
**		\begin{description}
**		\item[empty] The empty format is activated. This means that
**		  the format is cleared and without further action the
**		  default key will be used.
**		\item[long] The long format is activated. This means that
**		  authors names with initials and the first word of
**		  the title are used.
**		\item[short] The short format is activated. This means that
**		  authors last names and the first word of the title
**		  are used. 
**		\item[new.long] This means that the long format will
**		  be used but only if the record does not have a key
**		  already. 
**		\item[new.short] This means that the short format will
**		  be used but only if the record does not have a key
**		  already. 
**		\end{description}
** Arguments:
**	s	Specification string
** Returns:	nothing
**___________________________________________________			     */
void add_sort_format(s)				   /*			     */
  register char *s;				   /*			     */
{						   /*			     */
  if ( s == NULL )				   /*			     */
  { WARNING("Missing sort key format.");	   /*			     */
    return;					   /*			     */
  }						   /*			     */
  (void)add_fmt_tree(s,&sort_key_tree);		   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	fmt_parse()
** Purpose:	Parse the format specification given in the string *sp.
**		Store the resulting KeyNode tree in *knp.
**		*sp is modified to point to the first character not used.
**		The return value is 0 iff no problem has been detected.
** Arguments:
**	sp
**	knp
** Returns:	Error code. 0 = success
**___________________________________________________			     */
static int fmt_parse(sp,knp)			   /*			     */
  char		**sp;				   /*			     */
  KeyNode	*knp;				   /*			     */
{ int		ret;				   /*			     */
  KeyNode	new;				   /*			     */
						   /*			     */
  *knp = (KeyNode)NULL;				   /*                        */
 						   /*                        */
  while ( (ret=fmt__parse(sp,knp)) == 0 )	   /*			     */
  { SkipSpaces(*sp);				   /*			     */
    if ( **sp == '#' )				   /*			     */
    { new  = new_key_node(NodeOR, NO_SYMBOL);	   /*			     */
      NodeThen(new) = *knp;			   /*			     */
      *knp = new;				   /*			     */
      knp  = &NodeElse(new);			   /*			     */
      (*sp)++;					   /*			     */
    }						   /*			     */
    else return 0;				   /*			     */
  }						   /*			     */
  DebugPrintF1("<-format");			   /*                        */
  return ret;					   /* return the error code. */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	fmt__parse()
** Purpose:	
**
** Arguments:
**	sp	Pointer to the string to be parsed
**	knp	Pointer to the key node in which to store the result
** Returns:	Error code or 0 upon success
**___________________________________________________			     */
static int fmt__parse(sp,knp)			   /*			     */
  char		**sp;				   /*			     */
  KeyNode	*knp;				   /*			     */
{ register char *cp;				   /*			     */
  char		c;				   /*			     */
  int		ret;				   /*			     */
						   /*			     */
  cp = *sp;					   /*			     */
						   /*			     */
  while ( *cp != '\0' )				   /*			     */
  {						   /*			     */
    switch ( *cp )				   /*			     */
    { case ' ' : case '\t': case '\r':		   /* Skip over spaces.	     */
      case '\n': case '\f': case '\b':		   /*			     */
	cp++; break;				   /*			     */
      case '#':					   /* Two cases evaluated    */
      case '}': return 0;			   /*  somewhere else.	     */
      case '%':					   /* Format specification:  */
	{ int  pre  = -1,			   /*			     */
	       post = -1,			   /* %[-][0-9]*[.[0-9]*[a-Z]*/
	       type = 0;			   /*	([a-Z]*)	     */
	  switch ( *++cp )			   /*			     */
	  { case '+': type = NodePlusMask;  ++cp; break;/*		     */
	    case '-': type = NodeMinusMask; ++cp; break;/*		     */
	  }					   /*			     */
	  ParseNumber(cp,pre);			   /*			     */
	  if ( *cp == '.' || *cp == ',' || *cp == '-' )/*		     */
	  { cp++;				   /*                        */
	    ParseNumber(cp,post);		   /*                        */
	  }	   				   /*			     */
	  if ( *cp == '#' )			   /*                        */
	  { cp++;				   /*                        */
	    type |= NodeCountMask;		   /*                        */
	  }					   /*                        */
	  if ( !is_alpha(*cp) )			   /*			     */
	  { ErrPrintF("*** BibTool: Missing format type before: %s",cp);/*   */
	    *sp = cp;				   /*                        */
	    DebugPrintF1("<-or");		   /*                        */
	    return 1;		   		   /*			     */
	  }					   /*			     */
	  if ( strchr(percent_chars,*cp) == (char*)0 )/*		     */
	  { ErrPrintF("*** BibTool: Illegal format character: %c",*cp);/*    */
	    *sp = cp;				   /*                        */
	    DebugPrintF1("<-percent");		   /*                        */
	    return 1;			   	   /*			     */
	  }					   /*			     */
	  type |= *(cp++);			   /*			     */
	  Expect(cp,'(',1);			   /*			     */
	  SkipSpaces(cp);			   /*			     */
	  *sp = cp;				   /*			     */
	  SkipAllowed(cp);			   /*			     */
	  MakeNode(knp,type,sp,cp)		   /*			     */
	  NodePre(*knp)	 = pre;			   /*			     */
	  NodePost(*knp) = post;		   /*			     */
	  SkipSpaces(cp);			   /*			     */
	  Expect(cp,')',1);			   /*			     */
	  *sp = cp;				   /*			     */
	  knp = & NodeNext(*knp);		   /*			     */
	}					   /*			     */
	break;					   /*			     */
 						   /*                        */
      case '(':					   /*			     */
	cp = (*sp)+1;				   /*			     */
	SkipSpaces(cp);				   /*			     */
	*sp = cp;				   /*			     */
	SkipAllowed(cp);			   /*			     */
	MakeNode(knp,NodeTEST,sp,cp);		   /*			     */
	Expect(cp,')',1);			   /*			     */
	Expect(cp,'{',1);			   /*			     */
	*sp = cp;				   /*			     */
	ParseOrReturn(sp,&NodeThen(*knp),"<-then");/*			     */
	Expect(*sp,'}',1);			   /*			     */
	Expect(*sp,'{',1);			   /*			     */
	ParseOrReturn(sp,&NodeElse(*knp),"<-else");/*			     */
	Expect(*sp,'}',1);			   /*			     */
	knp = & NodeNext(*knp);			   /*			     */
	cp = *sp;				   /*			     */
	break;					   /*			     */
						   /*			     */
      case '{':					   /*			     */
	DebugPrintF1("--- parse block\n");	   /*                        */
	cp++;				   	   /*			     */
	SkipSpaces(cp);				   /*			     */
	*sp = cp;				   /*                        */
	ParseOrReturn(sp,knp,"<-block");	   /*			     */
	Expect(*sp,'}',1);			   /*			     */
	knp = & NodeNext(*knp);			   /*			     */
	cp  = *sp;				   /*			     */
	break;					   /*			     */
					   	   /*                        */
      default:					   /*			     */
	*sp = cp;				   /*			     */
	if ( is_allowed(*cp) )			   /*			     */
	{					   /*			     */
	  while ( is_allowed(*cp) ) { ++cp; }	   /*			     */
	  MakeNode(knp,NodeSTRING,sp,cp);	   /*			     */
	  *sp = cp;				   /*			     */
	  knp = & NodeNext(*knp);		   /*			     */
	}					   /*			     */
	else					   /*			     */
	{ ERROR2("Parse format. Illegal character ignored: ",cp);/*          */
	  ++cp;					   /*			     */
	}					   /*			     */
    }						   /*			     */
  }						   /*			     */
  DebugPrintF1("<-fmt");			   /*                        */
  return -1;					   /* Signal end-of-string.  */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	eval_fmt()
** Purpose:	Evaluate the given KeyNode tree w.r.t. the given Record.
** Arguments:
**	kn	the key node
**	rec	the record
**	db	the database
** Returns:	|false| upon success.
**___________________________________________________			     */
static bool eval_fmt(sb,kn,rec,db)		   /*			     */
  StringBuffer *sb;				   /*                        */
  KeyNode	kn;				   /*			     */
  Record	rec;				   /*			     */
  DB		db;				   /*                        */
{ int		pos = sbtell(sb);		   /*			     */
						   /*			     */
  tmp_key_db = db;				   /*                        */
  if ( eval__fmt(sb, kn, rec) != 0 )		   /*			     */
  { (void)sbseek(sb, pos);			   /*                        */
    return true;				   /*                        */
  }	   	   				   /*			     */
						   /*			     */
  return false;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	eval__fmt()
** Purpose:	Evaluate the given KeyNode tree w.r.t. the given Record
**		Internal version. trash of conjunctions is not removed.
** Arguments:
**	sb	the sting buffer
**	kn	the key node
**	rec	the record
** Returns:	
**___________________________________________________			     */
static bool eval__fmt(sb,kn,rec)		   /*			     */
  StringBuffer  *sb;				   /*                        */
  KeyNode	kn;				   /*			     */
  Record	rec;				   /*			     */
{ Symbol	s;				   /*			     */
  int		pos;				   /*			     */
  String	trans;				   /*                        */
						   /*			     */
  DebugPrint1("eval__fmt()");			   /*                        */
  while ( kn != (KeyNode)0 )			   /*			     */
  {						   /*                        */
    switch ( NodeType(kn) )			   /*			     */
    { case NodeSTRING:				   /*			     */
	DebugPrint3("STRING \"",		   /*                        */
		    SymbolValue(NodeSymbol(kn)),   /*                        */
		    "\"");			   /*		             */
	(void)sbputs((char*)SymbolValue(NodeSymbol(kn)),/*                   */
		     sb);	   		   /*			     */
	break;					   /*			     */
      case NodeTEST:				   /*			     */
#ifdef DEBUG
	DebugPrint3("IF_THEN_ELSE (",		   /*                        */
		    SymbolValue(NodeSymbol(kn)),   /*                        */
		    ")");			   /*		             */
	IfGetField(s,NodeSymbol(kn))		   /*			     */
	  DebugPrint1("Field found. Continuing with THEN part");/*           */
	else DebugPrint1("Field NOT found. Continuing with ELSE part");/*    */
#endif
	IfGetField(s,NodeSymbol(kn))		   /*			     */
	{ (void)eval__fmt(sb,NodeThen(kn),rec); }  /*			     */
	else					   /*			     */
	{ (void)eval__fmt(sb,NodeElse(kn),rec); }  /*			     */
	break;					   /*			     */
 						   /*                        */
      case NodeOR:				   /*			     */
	DebugPrint1("OR Trying THEN part");   	   /*			     */
	pos = sbtell(sb);			   /*			     */
	if ( eval__fmt(sb,NodeThen(kn),rec) != 0 ) /*			     */
	{ (void)sbseek(sb,pos);		   	   /*			     */
	  DebugPrint1("OR THEN part failed. Trying ELSE part.");/*	     */
	  if ( eval__fmt(sb,NodeElse(kn),rec) != 0 )/*			     */
	  { (void)sbseek(sb,pos);		   /*			     */
	    DebugPrint1("OR ELSE part failed");    /*			     */
	    return true;				   /*			     */
	  }					   /*			     */
	  DebugPrint1("OR ELSE part succeeded");   /*			     */
	}					   /*			     */
	break;					   /*			     */
 						   /*                        */
      case NodeSPECIAL:				   /*			     */
	eval__special(sb,kn,rec);		   /*			     */
	break;					   /*			     */
      default:					   /*			     */
#ifdef DEBUG
	fprintf(err_file,"+++ BibTool: FORMAT %s%d.%d%s%c(%s)\n",/*	     */
		(NodeType(kn)&NodePlusMask	   /*                        */
		 ? "+"				   /*                        */
		 :(NodeType(kn)&NodeMinusMask	   /*                        */
		   ?"-":"")),			   /*		             */
		NodePre(kn),	   		   /*			     */
		NodePost(kn),	   		   /*			     */
		(NodeType(kn)&NodeCountMask?"#":""),/*			     */
		NodeType(kn)&0xff,		   /*			     */
		SymbolValue(NodeSymbol(kn)));	   /*			     */
#endif
	IfGetField(s,NodeSymbol(kn))		   /*			     */
	{					   /*			     */
	  DebugPrint1("Field found");	   	   /*			     */
 						   /*                        */
	  if (NodeType(kn)&NodeMinusMask) 	   /*                        */
	  { trans = trans_lower; }		   /*                        */
	  else if (NodeType(kn)&NodePlusMask) 	   /*                        */
	  { trans = trans_upper; }		   /*                        */
	  else					   /*                        */
	  { trans = trans_id; }			   /*                        */
#define UsePostOr(X) (NodePost(kn) > 0 ? NodePost(kn) : (X))
#define UsePreOr(X)  (NodePre(kn) >= 0 ? NodePre(kn)  : (X))
#define HasMinus     (NodeType(kn)&NodeMinusMask)
#define HasPlus      (NodeType(kn)&NodePlusMask)
						   /*			     */
	  switch ( NodeType(kn)	& 0x1ff )	   /*			     */
	  {					   /*                        */
	    case 'p':				   /*			     */
	      fmt_names(sb,			   /*                        */
			SymbolValue(s),		   /*                        */
			UsePreOr(2),		   /*                        */
			UsePostOr(0),		   /*                        */
			trans);			   /*                        */
	      break;				   /*			     */
	    case 'n':				   /*			     */
	      if (key_seps == NULL) { init_key(); }/*                        */
	      NameStrip(format[0]) = UsePostOr(-1);/*                        */
	      fmt_names(sb,			   /*                        */
			SymbolValue(s),		   /*                        */
			UsePreOr(2),		   /*                        */
			0,			   /*                        */
			trans); 		   /*                        */
	      break;				   /*			     */
	    case 'N':				   /*			     */
	      if (key_seps == NULL) { init_key(); }/*                        */
	      NameStrip(format[1]) = UsePostOr(-1);/*                        */
	      if (NextName(format[1]))		   /*                        */
	      { NamePre(NextName(format[1])) = NamePreSep;/*                 */
	      }					   /*                        */
	      fmt_names(sb,			   /*                        */
			SymbolValue(s),		   /*                        */
			UsePreOr(2),		   /*                        */
			1,			   /*                        */
			trans); 		   /*                        */
	      break;				   /*			     */
	    case 'T':				   /*			     */
	      fmt_title(sb,			   /*                        */
			SymbolValue(s),		   /*                        */
			UsePreOr(1),		   /*                        */
			UsePostOr(0),		   /*                        */
			trans,			   /*                        */
			true,			   /*                        */
			TitleTitleSep);		   /*                        */
	      break;				   /*			     */
	    case 't':				   /*			     */
	      fmt_title(sb,			   /*                        */
			SymbolValue(s),		   /*                        */
			UsePreOr(1),		   /*                        */
			UsePostOr(0),		   /*                        */
			trans,			   /*                        */
			false,			   /*                        */
			TitleTitleSep);		   /*                        */
	      break;				   /*			     */
	    case 'd':				   /*			     */
	      if ( fmt_digits(sb,		   /*                        */
			      SymbolValue(s),	   /*                        */
			      HasMinus,		   /*                        */
			      HasPlus,		   /*                        */
			      NodePre(kn),	   /*                        */
			      UsePostOr(1),	   /*                        */
			      true) )		   /*                        */
	      { return true; }			   /*                        */
	      break;				   /*			     */
	    case 'D':				   /*			     */
	      if ( fmt_digits(sb,		   /*                        */
			      SymbolValue(s),	   /*                        */
			      HasMinus,		   /*                        */
			      HasPlus,		   /*                        */
			      NodePre(kn),	   /*                        */
			      UsePostOr(1),	   /*                        */
			      false) )		   /*                        */
	      { return true; }			   /*                        */
	      break;				   /*			     */
	    case 's':				   /*			     */
	      fmt_string(sb,		   	   /*                        */
			 SymbolValue(s),	   /*                        */
			 UsePreOr(0xffff),	   /*                        */
			 trans,			   /*                        */
			 SymbolValue(TitleTitleSep));/*		             */
	      break;				   /*			     */
	    case 'W':				   /*			     */
	      fmt_title(sb,			   /*                        */
			SymbolValue(s),		   /*                        */
			UsePreOr(1),		   /*                        */
			UsePostOr(0),		   /*                        */
			trans,			   /*                        */
			true,			   /*                        */
			sym_empty);		   /*                        */
	      break;				   /*			     */
	    case 'w':				   /*			     */
	      fmt_title(sb,			   /*                        */
			SymbolValue(s),		   /*                        */
			UsePreOr(1),		   /*                        */
			UsePostOr(0),		   /*                        */
			trans,			   /*                        */
			false,			   /*                        */
			sym_empty);		   /*                        */
	      break;				   /*			     */
	    case 'p' | NodeCountMask:		   /*			     */
	    case 'n' | NodeCountMask:		   /*			     */
	    case 'N' | NodeCountMask:		   /*			     */
	      if (fmt_c_names(SymbolValue(s),	   /*                        */
			      UsePreOr(0),	   /*                        */
			      UsePostOr(0),	   /*                        */
			      HasMinus))	   /*                        */
	      { return true; }			   /*	                     */
	      break;				   /*			     */
	    case 'd' | NodeCountMask:		   /*			     */
	    case 's' | NodeCountMask:		   /*			     */
	      if (fmt_c_string(SymbolValue(s),	   /*                        */
			       UsePreOr(0),	   /*                        */
			       UsePostOr(0),	   /*                        */
			       HasMinus))	   /*                        */
	      { return true; }			   /*	                     */
	      break;				   /*			     */
	    case 'T' | NodeCountMask:		   /*			     */
	    case 'W' | NodeCountMask:		   /*			     */
	      if (fmt_c_words(SymbolValue(s),	   /*                        */
			      UsePreOr(0),	   /*                        */
			      UsePostOr(0),	   /*                        */
			      HasMinus,		   /*                        */
			      true))		   /*                        */
	      { return true; }			   /*	                     */
	      break;				   /*			     */
	    case 't' | NodeCountMask:		   /*			     */
	    case 'w' | NodeCountMask:		   /*			     */
	      if (fmt_c_words(SymbolValue(s),	   /*                        */
			      UsePreOr(0),	   /*                        */
			      UsePostOr(0),	   /*                        */
			      HasMinus,		   /*                        */
			      false))		   /*                        */
	      { return true; }			   /*	                     */
	      break;				   /*			     */
	    default: return true;		   /*			     */
	  }					   /*			     */
	}					   /*			     */
	else					   /*                        */
	{					   /*                        */
	  DebugPrint1("Field not found");	   /*			     */
	  return true;				   /*                        */
	}			   		   /*			     */
    }						   /*			     */
    kn = NodeNext(kn);				   /*			     */
  }						   /*			     */
#undef UsePostOr
#undef UsePreOr
#undef HasMinus
#undef HasPlus
  return false;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	eval__special()
** Purpose:	
**
** Arguments:
**	sb	the target StringBuffer
**	kn	the key node
**	rec	the record
** Returns:	nothing
**___________________________________________________			     */
static void eval__special(sb,kn,rec)		   /*			     */
  StringBuffer *sb;				   /*                        */
  KeyNode	kn;				   /*			     */
  Record	rec;				   /*			     */
{ Symbol	s;				   /*			     */
  bool		missing	= true;		   	   /*			     */
  int		fmt;			   	   /*			     */
  static Symbol	s_author    = NO_SYMBOL;	   /*			     */
  static Symbol	s_editor    = NO_SYMBOL;	   /*			     */
  static Symbol	s_title	    = NO_SYMBOL;	   /*			     */
  static Symbol s_booktitle = NO_SYMBOL;	   /*			     */
  static Symbol	s_key	    = NO_SYMBOL;	   /*			     */
						   /*			     */
  if ( s_author == NO_SYMBOL )		   	   /*			     */
  { s_author	= symbol((String)"author");	   /*			     */
    s_editor	= symbol((String)"editor");	   /*			     */
    s_title	= symbol((String)"title");	   /*			     */
    s_booktitle = symbol((String)"booktitle"); 	   /*			     */
    s_key	= symbol((String)"key");	   /*			     */
  }						   /*			     */
						   /*			     */
  if (key_seps == NULL) { init_key(); }	   	   /*                        */
 						   /*                        */
  fmt = ( NodePre(kn) == KEYSTYLE_LONG ? 1 : 0 );  /*                        */
  NameStrip(format[fmt]) = NodePost(kn);	   /*                        */
    					   	   /*			     */
  IfGetField(s, s_author)			   /*			     */
  { fmt_names(sb,				   /*                        */
	      SymbolValue(s),			   /*                        */
	      2,				   /*                        */
	      fmt,				   /*                        */
	      trans_lower);	   		   /*                        */
    missing = false;				   /*			     */
  }						   /*			     */
  else IfGetField(s, s_editor)			   /*			     */
  { fmt_names(sb,				   /*                        */
	      SymbolValue(s),			   /*                        */
	      2,				   /*                        */
	      fmt,				   /*                        */
	      trans_lower);	   		   /*                        */
    missing = false;				   /*			     */
  }						   /*			     */
						   /*			     */
  IfGetField(s, s_title)			   /*			     */
  { (void)sbputs((char*)SymbolValue(NameTitleSep), /*                        */
		 sb);	   			   /*			     */
    fmt_title(sb,				   /*                        */
	      SymbolValue(s),			   /*                        */
	      1,				   /*                        */
	      0,				   /*                        */
	      trans_lower,			   /*                        */
	      true,				   /*                        */
	      TitleTitleSep);			   /*		             */
    missing = false;				   /*			     */
  }						   /*			     */
  else IfGetField(s, s_booktitle)		   /*			     */
  { (void)sbputs((char*)SymbolValue(NameTitleSep), /*                        */
		 sb);	   			   /*			     */
    fmt_title(sb,				   /*                        */
	      SymbolValue(s),			   /*                        */
	      1,				   /*                        */
	      0,				   /*                        */
	      trans_lower,			   /*                        */
	      true,				   /*                        */
	      TitleTitleSep);			   /*		             */
    missing = false;				   /*			     */
  }						   /*			     */
						   /*			     */
  if (missing)				   	   /*			     */
  { sbrewind(sb);				   /*			     */
    IfGetField(s, s_key)			   /*			     */
    { fmt_title(sb,				   /*                        */
		SymbolValue(s),			   /*                        */
		1,				   /*                        */
		0,				   /*                        */
		trans_lower,			   /*                        */
		true,				   /*                        */
		TitleTitleSep); }		   /*	                     */
    else					   /*                        */
    { (void)sbputs((char*)SymbolValue(DefaultKey), /*                        */
		   sb); }			   /*	                     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	apply_fmt()
** Purpose:	Expands an arbitrary format specification for a given record.
**		The format specification is given as a string.
**		The result is stored in a string buffer.
** Arguments:
**	sb	Destination string buffer.
**	fmt	Format specification,
**	rec	Record to consider.
**	db	Database containing |rec|.
** Returns:	|1| iff the format is invalid or the evaluation fails. |0|
**		otherwise.
**___________________________________________________			     */
int apply_fmt(sb,fmt,rec,db)			   /*                        */
  StringBuffer   *sb;				   /*                        */
  char	         *fmt;				   /*                        */
  Record         rec;				   /*                        */
  DB	         db;				   /*                        */
{ static char    *old_fmt = NULL;		   /*                        */
  static KeyNode old_kn   = (KeyNode)0;		   /*                        */
 						   /*                        */
  if (   old_fmt == NULL			   /* This is the first time */
      || strcmp(fmt,old_fmt) != 0 )		   /*   or the format needs  */
  {						   /*   recompilation.       */
    key_init();					   /*                        */
    if ( old_fmt != NULL )			   /*                        */
    { free(old_fmt);				   /*                        */
      free_key_node(old_kn);			   /*                        */
      old_kn = (KeyNode)0;			   /*                        */
    }						   /*                        */
 						   /*                        */
    old_fmt = new_string(fmt);			   /*                        */
    if ( !add_fmt_tree(old_fmt, &old_kn) )	   /*                        */
    { free(old_fmt);				   /*                        */
      old_fmt = NULL;				   /*                        */
      return 1;					   /*                        */
    }						   /*                        */
  }						   /*                        */
  return eval_fmt(sb, old_kn, rec, db);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	fmt_expand()
** Purpose:	Expands a format specification of the % type into a given
**		string buffer.
**		
** Arguments:
**	sb	destination string buffer
**	cp	format
** Returns:	The first character after the % format.
**___________________________________________________			     */
String fmt_expand(sb,cp,db,rec)			   /*                        */
  StringBuffer  *sb;				   /*                        */
  Uchar         *cp;				   /*                        */
  DB	        db;				   /*                        */
  Record        rec;				   /*                        */
{ Symbol	field;				   /*                        */
  String	sp;				   /*                        */
  Uchar		c;			   	   /*                        */
  String	trans = trans_id;		   /*                        */
  int  		pre  = -1,			   /*                        */
     		post = -1,			   /*                        */
      		type = 0;			   /*                        */
 						   /*                        */
  while ( *cp && *cp != (Uchar)'%' )		   /*                        */
  { sbputchar((Uchar)*cp,sb);			   /*                        */
    cp++;					   /*                        */
  }						   /*                        */
 					       	   /*                        */
  if ( *cp == (Uchar)'%' )			   /*                        */
  { 						   /*                        */
    switch ( *++cp )			   	   /*			     */
    { case '+': trans = trans_upper; ++cp; break;  /*		             */
      case '-': trans = trans_lower; ++cp; break;  /*		             */
    }					   	   /*			     */
    ParseNumber(cp,pre);			   /*			     */
    if ( *cp == '.' || *cp == ',' || *cp == '-' )  /*		             */
    { cp++;				   	   /*                        */
      ParseNumber(cp,post);		   	   /*                        */
    }	   				   	   /*			     */
    if ( *cp == '#' )			   	   /*                        */
    { cp++;				   	   /*                        */
      type |= NodeCountMask;		   	   /*                        */
    }					   	   /*                        */
    if ( !is_alpha(*cp) )			   /*			     */
    { ErrPrintF("*** BibTool: Missing format type before: %s",cp);/*         */
      return cp;		   		   /*			     */
    }					   	   /*			     */
    if ( strchr(percent_chars,*cp) == (char*)0 )   /*		             */
    { ErrPrintF("*** BibTool: Illegal format character: %c",*cp);/*          */
      return cp;			   	   /*			     */
    }					   	   /*			     */
    type |= *(cp++);			   	   /*			     */
    Expect(cp,'(',cp);			   	   /*			     */
    SkipSpaces(cp);			   	   /*			     */
    sp = cp;				   	   /*			     */
    SkipAllowed(cp);			   	   /*			     */
    c = *cp;					   /*                        */
    *cp = '\0';					   /*                        */
    field = symbol(sp);			   	   /*                        */
    *cp = c;					   /*                        */
    SkipSpaces(cp);			   	   /*			     */
    if ( *cp == ')' ) { cp++; }			   /*                        */
    else					   /*                        */
    { ErrPrintF("*** BibTool: Missing ')' in format before: %s\n",cp);/*     */
      return cp;				   /*                        */
    }						   /*                        */
 						   /*                        */
    if ( (field=get_field(db,rec,field)) != NULL ) /*                        */
    {					   	   /*			     */
      DebugPrint1("Field found");	   	   /*			     */
 						   /*                        */
#define PostOr(X)	(post > 0 ? post : (X))
#define PreOr(X)	(pre >= 0 ? pre  : (X))
#define HasMinus	(type&NodeMinusMask)
#define HasPlus		(type&NodePlusMask)
      switch ( type & 0x1ff )	   		   /*			     */
      {					   	   /*                        */
	case 'p':				   /*			     */
	  fmt_names(sb,				   /*                        */
		    SymbolValue(field),		   /*                        */
		    PreOr(2),		   	   /*                        */
		    PostOr(0),		   	   /*                        */
		    trans);			   /*                        */
	  break;				   /*			     */
	case 'n':				   /*			     */
	  if (key_seps == NULL) { init_key(); }    /*                        */
	  NameStrip(format[0]) = PostOr(-1);	   /*                        */
	  fmt_names(sb,				   /*                        */
		    SymbolValue(field),		   /*                        */
		    PreOr(2),			   /*                        */
		    0,				   /*                        */
		    trans);    			   /*                        */
	  break;				   /*			     */
	case 'N':				   /*			     */
	  if (key_seps == NULL) { init_key(); }    /*                        */
	  NameStrip(format[1]) = PostOr(-1);	   /*                        */
	  if (NextName(format[1]))		   /*                        */
	  { NamePre(NextName(format[1])) = NamePreSep;/*                     */
	  }					   /*                        */
	  fmt_names(sb,				   /*                        */
		    SymbolValue(field),		   /*                        */
		    PreOr(2),			   /*                        */
		    1,				   /*                        */
		    trans);    			   /*                        */
	  break;				   /*			     */
	case 'T':				   /*			     */
	  fmt_title(sb,				   /*                        */
		    SymbolValue(field),		   /*                        */
		    PreOr(1),		   	   /*                        */
		    PostOr(0),		   	   /*                        */
		    trans,			   /*                        */
		    true,			   /*                        */
		    TitleTitleSep);		   /*                        */
	  break;				   /*			     */
	case 't':				   /*			     */
	  fmt_title(sb,				   /*                        */
		    SymbolValue(field),		   /*                        */
		    PreOr(1),		   	   /*                        */
		    PostOr(0),		   	   /*                        */
		    trans,			   /*                        */
		    false,			   /*                        */
		    TitleTitleSep);		   /*                        */
	  break;				   /*			     */
	case 'd':				   /*			     */
	  (void)fmt_digits(sb,			   /*                        */
			   SymbolValue(field),	   /*                        */
			   HasMinus,		   /*                        */
			   HasPlus,		   /*                        */
			   pre,	   	   	   /*                        */
			   PostOr(1),	   	   /*                        */
			   true);		   /*                        */
	  break;				   /*			     */
	case 'D':				   /*			     */
	  (void)fmt_digits(sb,			   /*                        */
			   SymbolValue(field),	   /*                        */
			   HasMinus,		   /*                        */
			   HasPlus,		   /*                        */
			   pre,	   	   	   /*                        */
			   PostOr(1),	   	   /*                        */
			   false);		   /*                        */
	  break;				   /*			     */
	case 's':				   /*			     */
	  fmt_string(sb,			   /*                        */
		     SymbolValue(field),	   /*                        */
		     PreOr(0xffff),		   /*                        */
		     trans,			   /*                        */
		     (String)" ");		   /*		             */
	  break;				   /*			     */
	case 'W':				   /*			     */
	  fmt_title(sb,				   /*                        */
		    SymbolValue(field),		   /*                        */
		    PreOr(1),		   	   /*                        */
		    PostOr(0),		   	   /*                        */
		    trans,			   /*                        */
		    true,			   /*                        */
		    sym_empty);			   /*                        */
	  break;				   /*			     */
	case 'w':				   /*			     */
	  fmt_title(sb,				   /*                        */
		    SymbolValue(field),		   /*                        */
		    PreOr(1),		   	   /*                        */
		    PostOr(0),		   	   /*                        */
		    trans,			   /*                        */
		    false,			   /*                        */
		    sym_empty);			   /*                        */
	  break;				   /*			     */
      }					   	   /*			     */
    }						   /*                        */
    else					   /*                        */
    { DebugPrint1("Field not found");	   	   /*			     */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  return cp;					   /*                        */
}						   /*------------------------*/
#undef PostOr
#undef PreOr
#undef HasMinus
#undef HasPlus


#ifdef DEBUG
/*-----------------------------------------------------------------------------
** Function*:	show_fmt()
** Purpose:	Print a format tree onto the error stream
** Arguments:
**	kn
**	in
** Returns:	nothing
**___________________________________________________			     */
static void show_fmt(kn,in)			   /*			     */
  register KeyNode kn;				   /*			     */
  register int     in;				   /*                        */
{ register int     i;				   /*			     */
#define NLin(S) ErrC('\n');for(i=in;i>0;i--) ErrC(' '); (void)fputs(S,err_file)
#define ErrS(S) (void)fputs(S,err_file)
						   /*			     */
  while ( kn != (KeyNode)0 )			   /*			     */
  { switch ( NodeType(kn) )			   /*			     */
    { case NodeSTRING:				   /*			     */
	ErrPrintF(" \"%s\"",			   /*                        */
		  SymbolValue(NodeSymbol(kn)));	   /*			     */
	NLin("");				   /*			     */
	break;					   /*			     */
      case NodeTEST:				   /*			     */
	ErrPrintF(" (%s)",			   /*                        */
		  SymbolValue(NodeSymbol(kn)));	   /*			     */
	NLin("{ ");			   	   /*			     */
	show_fmt(NodeThen(kn),in+2);		   /*			     */
	NLin("}");			   	   /*			     */
	NLin("{ ");			   	   /*			     */
	show_fmt(NodeElse(kn),in+2);		   /*			     */
	NLin("}");				   /*			     */
	break;					   /*			     */
      case NodeOR:				   /*			     */
	ErrS("{ ");				   /*			     */
	show_fmt(NodeThen(kn),in+2);		   /*			     */
	ErrS("}");			   	   /*			     */
	NLin("#");			   	   /*			     */
	NLin("{ ");			   	   /*			     */
	show_fmt(NodeElse(kn),in+2);		   /*			     */
	NLin("}");				   /*			     */
	break;					   /*			     */
      default:					   /*			     */
	fprintf(err_file,"%%%s",	   	   /*			     */
	       (NodeType(kn)&NodePlusMask?"+":	   /*                        */
		(NodeType(kn)&NodeMinusMask?"-":"")));/*		     */
	if ( NodePre(kn)>=0 )			   /*                        */
	  fprintf(err_file,"%d",NodePre(kn));	   /*			     */
	if ( NodePost(kn)>=0 )			   /*                        */
	  fprintf(err_file,".%d",NodePost(kn));	   /*			     */
	fprintf(err_file,"%s%c(%s) ",	   	   /*			     */
	       (NodeType(kn)&NodeCountMask?"#":""),/*			     */
	       NodeType(kn)&0xff,		   /*			     */
		SymbolValue(NodeSymbol(kn)));	   /*			     */
    }						   /*			     */
    kn = NodeNext(kn);				   /*			     */
  }						   /*			     */
}						   /*------------------------*/

#endif


 static Symbol sym_user = NO_SYMBOL;
 static Symbol sym_host = NO_SYMBOL;

/*-----------------------------------------------------------------------------
** Function:	get_field()
** Purpose:	Evaluate the record |rec|.
**		If name starts with |@| then check the record name.
**		If name starts with |$| then return the special info. 
**		Else search in Record |rec| for the field name and return its
**		value. |NULL| is returned to indicate failure.
** Arguments:
**	rec	Record to analyze.
**	name	Field name to search for. This has to be a symbol if a
**		normal field is sought. For pseudo fields it can be an
**		arbitrary string.
** Returns:	The address of the value or |NULL|.
**___________________________________________________			     */
Symbol get_field(db,rec,name)		   	   /*			     */
  DB		  db;				   /*                        */
  register Record rec;				   /*			     */
  register Symbol name;			   	   /*			     */
{ String s = SymbolValue(name);			   /*                        */
  Symbol sym;					   /*                        */
  DebugPrint2("get_field ", s);		   	   /*                        */
#ifdef HAVE_TIME_H
  static struct tm *tp;				   /*                        */
  static time_t the_time = 0;			   /*                        */
  static char buffer[32];			   /*                        */
 						   /*                        */
  if ( the_time == 0 )				   /*                        */
  { the_time = time(NULL);			   /*                        */
    tp = localtime(&the_time);			   /*                        */
  }						   /*                        */
#define ReturnTime(F) if ( the_time > 0 )	\
  { (void)strftime(buffer,32,F,tp);		\
    return symbol((String)buffer); }		\
  LinkSymbol(sym_empty); return sym_empty
#else
#define ReturnTime(F) return sym_empty
#endif
				   		   /*                        */
  if (*s == '@')				   /*			     */
  { sym = EntryName(RecordType(rec));		   /*                        */
    if (case_eq(s + 1, SymbolValue(sym)))	   /*		             */
    { LinkSymbol(sym);
      return sym;	   			   /*		             */
    }
  }						   /*			     */
  else if (*s == '$')			   	   /*			     */
  { ++s;					   /*			     */
    switch (*s)				   	   /*                        */
    { case 'k': case 'K':			   /*                        */
        if (case_eq(s, (String)"key"))	   	   /*			     */
	{ return (*SymbolValue(*RecordHeap(rec))   /*                        */
		  ? *RecordHeap(rec)		   /*                        */
		  : NO_SYMBOL);		   	   /*                        */
	}					   /*		             */
        break;					   /*                        */
      case 'd': case 'D':			   /*                        */
	if (case_eq(s, (String)"default.key"))     /*			     */
	{ LinkSymbol(DefaultKey);		   /*                        */
	  return DefaultKey;			   /*                        */
	}			   		   /*			     */
	else if (case_eq(s, (String)"day"))        /*			     */
	{ ReturnTime("%d"); }			   /*			     */
	break;    				   /*                        */
      case 'f': case 'F':			   /*                        */
	if (case_eq(s, (String)"fmt.et.al"))       /*			     */
	{ LinkSymbol(EtAl);		   	   /*                        */
	  return EtAl; }			   /*			     */
	else if (case_eq(s,		   	   /*                        */
			 (String)"fmt.name.pre"))  /*		             */
	{ LinkSymbol(NamePreSep);		   /*                        */
	  return NamePreSep; }			   /*			     */
	else if (case_eq(s,		   	   /*                        */
			 (String)"fmt.inter.name"))/*		             */
	{ LinkSymbol(InterNameSep);		   /*                        */
	  return InterNameSep; }		   /*			     */
	else if (case_eq(s,		   	   /*                        */
			 (String)"fmt.name.name")) /*		             */
	{ LinkSymbol(NameNameSep);		   /*                        */
	  return NameNameSep; }			   /*			     */
	else if (case_eq(s,		   	   /*                        */
			 (String)"fmt.name.title"))/*		             */
	{ LinkSymbol(NameTitleSep);		   /*                        */
	  return NameTitleSep; }		   /*			     */
	else if (case_eq(s,		   	   /*                        */
			 (String)"fmt.title.title"))/*		             */
	{ LinkSymbol(TitleTitleSep);		   /*                        */
	  return TitleTitleSep; }		   /*			     */
      case 'h': case 'H':			   /*                        */
	if (case_eq(s, (String)"hostname"))        /*			     */
	{ if (sym_host == NULL)			   /*                        */
	  { s = (String)getenv("HOSTNAME"); 	   /*                        */
	    sym_host = symbol(s ? s : s_empty);	   /*                        */
	  }					   /*                        */
	  else					   /*                        */
	  { LinkSymbol(sym_host); }		   /*                        */
	  return sym_host;			   /*                        */
	}	   	   			   /*			     */
        else if (case_eq(s, (String)"hour"))       /*			     */
	{ ReturnTime("%H"); }			   /*			     */
	break;					   /*                        */
      case 'm': case 'M':			   /*                        */
	if (case_eq(s, (String)"month"))	   /*			     */
	{ ReturnTime("%m"); }			   /*			     */
	else if (case_eq(s, (String)"minute"))     /*			     */
	{ ReturnTime("%M"); }			   /*			     */
	else if (case_eq(s, (String)"mon"))        /*			     */
	{ ReturnTime("%B"); }			   /*			     */
	break;    				   /*                        */
      case 's': case 'S':			   /*                        */
	if (case_eq(s, (String)"sortkey"))	   /*			     */
	{ LinkSymbol(RecordSortkey(rec));	   /*                        */
	  return RecordSortkey(rec); }		   /*			     */
	else if (case_eq(s, (String)"source"))     /*			     */
	{ LinkSymbol(RecordSource(rec));	   /*                        */
	  return RecordSource(rec); }		   /*			     */
	else if (case_eq(s, (String)"second"))     /*			     */
	{ ReturnTime("%S"); }			   /*			     */
	break;    				   /*                        */
      case 't': case 'T':			   /*                        */
	if (case_eq(s, (String)"type"))	   	   /*			     */
	{ sym = EntryName(RecordType(rec));	   /*                        */
	  if (sym) LinkSymbol(sym);		   /*                        */
	  return sym; }	   			   /*			     */
	else if (case_eq(s, (String)"time"))       /*			     */
	{ ReturnTime("%H:%M:%S"); }		   /*			     */
        break;					   /*                        */
      case 'u': case 'U':			   /*                        */
	if (case_eq(s, (String)"user"))	   	   /*			     */
	{ if (sym_user == NULL)			   /*                        */
	  { s = (String)getenv("USER");	   	   /*                        */
	    sym_user = symbol(s ? s : s_empty);	   /*                        */
	  }					   /*                        */
	  else					   /*                        */
	  { LinkSymbol(sym_user); }		   /*                        */
	  return sym_user;			   /*                        */
	}	   	   			   /*			     */
        break;					   /*                        */
      case 'w': case 'W':			   /*                        */
	if (case_eq(s, (String)"weekday"))	   /*			     */
	{ ReturnTime("%a"); }			   /*			     */
	break;    				   /*                        */
      case 'y': case 'Y':			   /*                        */
	if (case_eq(s, (String)"year"))	   	   /*			     */
	{ ReturnTime("%Y"); }			   /*			     */
	break;    				   /*                        */
    }						   /*                        */
  }						   /*			     */
  else						   /*			     */
  { register Symbol *cpp;			   /*			     */
    Symbol	    xref;			   /*                        */
    register int    n, count;			   /*			     */
						   /*			     */
    for (count = rsc_xref_limit;		   /*                        */
	 count >= 0;				   /*                        */
	 count-- )				   /* Prevent infinite loop  */
    {						   /*                        */
      xref = NO_SYMBOL;				   /*                        */
      for (cpp = RecordHeap(rec), n = RecordFree(rec);/*	             */
	   n > 0;				   /*			     */
	   n -= 2 )				   /*			     */
      {						   /*                        */
	if ( *cpp == name && *(cpp+1) != NO_SYMBOL )/*                       */
	{					   /*                        */
	  sym = ( rsc_key_expand_macros	   	   /*                        */
		  ? expand_rhs(*(cpp+1),	   /*                        */
			       sym_open_brace,	   /*                        */
			       sym_close_brace,    /*                        */
			       db,		   /*                        */
			       false)		   /*                        */
		  : *(cpp+1) );		   	   /*			     */
	  LinkSymbol(sym);		   	   /*                        */
	  return sym;				   /*                        */
	}					   /*                        */
 						   /*                        */
        if ( *cpp == sym_crossref )		   /*                        */
	{ xref = *++cpp; }			   /*                        */
	else cpp++;				   /*                        */
        cpp++;			   	   	   /*			     */
      }					   	   /*			     */
       						   /*                        */
      if ( xref == NO_SYMBOL ) return NO_SYMBOL;   /* No crossref field found*/
      xref = expand_rhs(xref,			   /*                        */
			sym_empty,		   /*                        */
			sym_empty,		   /*                        */
			db,			   /*                        */
			true);			   /*                        */
      if ( (rec = db_search(db, xref)) == RecordNULL )/*                     */
      { ErrPrintF("*** BibTool: Crossref `%s' not found.\n",/*               */
		  SymbolValue(xref));		   /*                        */
	return NO_SYMBOL;			   /*                        */
      }						   /*                        */
      DebugPrint2("Following crossref to ",	   /*                        */
		  SymbolValue(xref)); 		   /*                        */
    }						   /*			     */
  }						   /*                        */
 						   /*                        */
  return NO_SYMBOL;				   /* Nothing found.	     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	set_field()
** Purpose:	Store the given field or pseudo-field in a record.
**		If the field is present then the old value is
**		overwritten.  Otherwise a new field is added. Fields
**		starting with a |$| or |@| are treated special. They
**		denote pseudo fields. If such a pseudo field is
**		undefined then the assignment simply fails.
**
**		In contrast to the function |push_to_record()| this
**		function does not assume that the arguments are
**		symbols. In addition to |push_to_record()| it also
**		handles pseudo-fields.
** Arguments:
**	rec	Record to receive the value.
**	name	Field name to add.
**	value	the new value
** Returns:	|false| if the asignment has succeeded.
**___________________________________________________			     */
bool set_field(db,rec,name,value)		   /*			     */
  DB db;					   /*                        */
  register Record rec;				   /*			     */
  Symbol	  name;			   	   /*			     */
  Symbol	  value;		   	   /*			     */
{ int c = *SymbolValue(name);			   /*                        */
  POSSIBLY_UNUSED(db);				   /*                        */
						   /*			     */
  if (c == '@')				   	   /*			     */
  {						   /*                        */
  }						   /*			     */
  else if (c == '$')			   	   /*			     */
  { String s = ++SymbolValue(name);		   /*			     */
    switch (c)				   	   /*                        */
    { case 'k': case 'K':			   /*                        */
        if ( case_eq(s, (String)"key") )	   /*			     */
	{ SetSym(*RecordHeap(rec), value);	   /*                        */
	  return false;			   	   /*                        */
	}					   /*		             */
        break;					   /*                        */
      case 'd': case 'D':			   /*                        */
	if ( case_eq(s, (String)"default.key") )   /*			     */
	{ SetSym(DefaultKey, value);		   /*                        */
	  return false;				   /*                        */
	}		   			   /*			     */
	break;    				   /*                        */
      case 'f': case 'F':			   /*                        */
	if ( case_eq(s, (String)"fmt.et.al") )     /*			     */
	{ SetSym(EtAl, value);			   /*                        */
	  return false;				   /*                        */
	}	   	   			   /*			     */
	else if (case_eq(s, (String)"fmt.name.pre"))/*		             */
	{ SetSym(NamePreSep, value);		   /*                        */
	  return false;				   /*                        */
	}  	   				   /*			     */
	else if (case_eq(s, (String)"fmt.inter.name"))/*		     */
	{ SetSym(InterNameSep, value);		   /*                        */
	  return false;				   /*                        */
	}	   				   /*			     */
	else if (case_eq(s, (String)"fmt.name.name"))/*		             */
	{ SetSym(NameNameSep, value);		   /*                        */
	  return false;				   /*                        */
	} 	   				   /*			     */
	else if (case_eq(s, (String)"fmt.name.title"))/*		     */
	{ SetSym(NameTitleSep, value);		   /*                        */
	  return false;				   /*                        */
	}	   				   /*		             */
	else if (case_eq(s, (String)"fmt.title.title"))/*		     */
	{ SetSym(TitleTitleSep, value);		   /*                        */
	  return false;				   /*                        */
	}	   				   /*			     */
      case 's': case 'S':			   /*                        */
	if (case_eq(s, (String)"sortkey"))	   /*			     */
	{ SetSym(RecordSortkey(rec), value);	   /*                        */
	  return false;				   /*                        */
	}  					   /*			     */
	else if (case_eq(s, (String)"source"))     /*			     */
	{ SetSym(RecordSource(rec), value);	   /*                        */
	  return false;				   /*                        */
	}   					   /*		             */
	break;    				   /*                        */
      case 't': case 'T':			   /*                        */
	if (case_eq(s, (String)"type"))	   	   /*			     */
	{ int type;				   /*                        */
	  if (IsNormalRecord(RecordType(rec)) &&   /*                        */
	      (type=find_entry_type(SymbolValue(value))) >= 0)/*             */
	  { SetSym(RecordType(rec), type);	   /*                        */
	    return false;			   /*                        */
	  }    					   /*                        */
	}					   /*                        */
        break;					   /*                        */
      case 'u': case 'U':			   /*                        */
	if (case_eq(s, (String)"user"))	   	   /*			     */
	{ SetSym(sym_user, value);		   /*                        */
	  return false;				   /*                        */
	}	   	   			   /*			     */
        break;					   /*                        */
    }						   /*                        */
  }						   /*			     */
  else						   /*			     */
  { push_to_record(rec, name, value);	   	   /*			     */
    return false;				   /*                        */
  }						   /*                        */
 						   /*                        */
  return true;				   	   /* Nothing found.	     */
}						   /*------------------------*/
