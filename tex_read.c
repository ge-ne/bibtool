/*** tex_read.c ***************************************************************
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
** 
** Purpose: Simulate the TeX reading mechanism.
**
** Compilation: cc tex_read.c -o tex_read -DSTANDALONE
** 
**-----------------------------------------------------------------------------
** Description:
**	This module contains functions which immitate the reading
**	apparatus of \TeX{}. Macro expansion can be performed. 
** 
**	    
******************************************************************************/

#include <bibtool/general.h>
#include <ctype.h>

#ifndef STANDALONE
#include <bibtool/error.h>
#include <bibtool/symbols.h>
#else
#define Err(X)		 (void)fputs(X,stderr)
#define ERROR_EXIT(X)	 Err(X); exit(1)
#define OUT_OF_MEMORY(X) Err("Out of memory for "); Err(X); exit(1)
#endif

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

#define CARET_CARET	    /* enable ^^A type specification of unprintables */
#undef	TRANSLATE_NEWLINE   /* Translate nl to space or \par */

 typedef struct tOKEN				   /*			     */
 { short int	 to_char;			   /*			     */
   String	 to_s;				   /*			     */
   struct tOKEN  *to_next;			   /*			     */
 } *Token, SToken;				   /*			     */

#define TokenChar(X) ((X)->to_char)
#define TokenSeq(X)  ((X)->to_s)
#define NextToken(X) ((X)->to_next)

#define TokenNULL (Token)0

 typedef struct mACdEF				   /*			     */
 { short int	 md_arity;			   /*			     */
   String        md_name;			   /*			     */
   Token	 md_token;			   /*			     */
   struct mACdEF *md_next;			   /*			     */
 } *MacDef, SMacDef;				   /*			     */

#define MacroArity(X)  ((X)->md_arity)
#define MacroName(X)   ((X)->md_name)
#define MacroToken(X)  ((X)->md_token)
#define NextMacro(X)   ((X)->md_next)
#define MacDefNULL     (MacDef)0

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 bool TeX_read _ARG((String  cp,String *sp));	   /* tex_read.c             */
 static MacDef find_macro _ARG((String name,MacDef md));/* tex_read.c        */
 static MacDef new_macdef _ARG((String name,int arity,Token tokens));/* tex_read.c*/
 static Token TeX_get_token _ARG((int (*get_fct)_ARG((void))));/* tex_read.c */
 static Token new_token _ARG((int type,String string));/* tex_read.c         */
 static Token token_list_copy _ARG((Token t,Token nt,Token *argp));/* tex_read.c*/
 static Token tokenize _ARG((String s,int arity)); /* tex_read.c             */
 static int TeX_fill_line _ARG((int (*get_fct)_ARG((void))));/* tex_read.c   */
 static int do_get _ARG((void));		   /* tex_read.c             */
 static int fill_token _ARG((Token*tp));	   /* tex_read.c             */
 static int get_EOF _ARG((void));		   /* tex_read.c             */
 static int get_file _ARG((void));		   /* tex_read.c             */
 static int get_string _ARG((void));		   /* tex_read.c             */
 static String tokens_to_string _ARG((Token t));   /* tex_read.c             */
 static void free_1_token _ARG((Token t));	   /* tex_read.c             */
 static void free_macdef _ARG((MacDef mac));	   /* tex_read.c             */
 static void free_tokens _ARG((Token t));	   /* tex_read.c             */
 static void init_TeX _ARG((void));		   /* tex_read.c             */
 static void init_get _ARG((String s));   	   /* tex_read.c             */
 void TeX_active _ARG((int c,int arity,String  s));/* tex_read.c             */
 void TeX_close _ARG((void));			   /* tex_read.c             */
 void TeX_def _ARG((String s));		   	   /* tex_read.c             */
 void TeX_define _ARG((String name,int arity,String body));/* tex_read.c     */
 void TeX_open_file _ARG((FILE * file));	   /* tex_read.c             */
 void TeX_open_string _ARG((String s));		   /* tex_read.c             */
 void TeX_reset _ARG((void));			   /* tex_read.c             */

#ifdef STANDALONE
 int main _ARG((int argc,char *argv[]));	   /* tex_read.c             */
 static char * new_string _ARG((char * s));	   /* tex-read.c	     */
 static void show_tokens _ARG((Token t));	   /* tex-read.c	     */
#else
 extern char * new_string _ARG((char * s));
#endif

/*---------------------------------------------------------------------------*/

/*****************************************************************************/
/*** catcode Management.						   ***/
/*****************************************************************************/

#define CHAR_ESCAPE		'\\'
#define CHAR_BEG_GROUP		'{'
#define CHAR_END_GROUP		'}'
#define CHAR_MATH		'$'
#define CHAR_ALIGN		'&'
#define CHAR_EOL		'\n'
#define CHAR_PARAMETER		'#'
#define CHAR_SUPERSCRIPT	'^'
#define CHAR_SUBSCRIPT		'_'
#define CHAR_IGNORED		'\0'
#define CHAR_SPACE		' '
#define CHAR_COMMENT		'%'

#define CATCODE_ESCAPE		0x0000
#define CATCODE_BEG_GROUP	0x0100
#define CATCODE_END_GROUP	0x0200
#define CATCODE_MATH		0x0300
#define CATCODE_ALIGN		0x0400
#define CATCODE_EOL		0x0500
#define CATCODE_PARAMETER	0x0600
#define CATCODE_SUPERSCRIPT	0x0700
#define CATCODE_SUBSCRIPT	0x0800
#define CATCODE_IGNORED		0x0900
#define CATCODE_SPACE		0x0A00
#define CATCODE_LETTER		0x0B00
#define CATCODE_OTHER		0x0C00
#define CATCODE_ACTIVE		0x0D00
#define CATCODE_COMMENT		0x0E00
#define CATCODE_INVALID		0x0F00

#define CATCODE_MASK		0x0F00

 static short int catcode[256];

 static MacDef macro	   = MacDefNULL;
 static MacDef active[256];

#define EnsureInit init_TeX()

/*-----------------------------------------------------------------------------
** Function:	init_TeX()
** Purpose:	Initialize the \TeX{} reading apparatus.
**		Mainly the catcodes are assigned and the macros are
**		cleared.  This function has to be called before the
**		other functions in this module. Thus this function  is
**		called automatically from different places to ensure
**		that the reading apparatus is initialized.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
static void init_TeX()				   /*			     */
{ register int i;				   /*			     */
  static bool  initialized = false;		   /*			     */
						   /*			     */
  if (initialized) return;			   /*			     */
  initialized = true;				   /*			     */
						   /*			     */
  for (i = 0; i < 256; ++i)			   /*			     */
  { active[i]  = MacDefNULL;			   /*			     */
    catcode[i] = (  isalpha(i)			   /*			     */
		  ? CATCODE_LETTER		   /*			     */
		  : CATCODE_OTHER  );		   /*			     */
  }						   /*			     */
  catcode[CHAR_ESCAPE]	    = CATCODE_ESCAPE;	   /*			     */
  catcode[CHAR_BEG_GROUP]   = CATCODE_BEG_GROUP;   /*			     */
  catcode[CHAR_END_GROUP]   = CATCODE_END_GROUP;   /*			     */
  catcode[CHAR_MATH]	    = CATCODE_MATH;	   /*			     */
  catcode[CHAR_ALIGN]	    = CATCODE_ALIGN;	   /*			     */
  catcode[CHAR_EOL]	    = CATCODE_EOL;	   /*			     */
  catcode[CHAR_PARAMETER]   = CATCODE_PARAMETER;   /*			     */
  catcode[CHAR_SUPERSCRIPT] = CATCODE_SUPERSCRIPT; /*			     */
  catcode[CHAR_SUBSCRIPT]   = CATCODE_SUBSCRIPT;   /*			     */
  catcode[CHAR_IGNORED]     = CATCODE_IGNORED;	   /*			     */
  catcode[CHAR_SPACE]	    = CATCODE_SPACE;	   /*			     */
  catcode[CHAR_COMMENT]	    = CATCODE_COMMENT;	   /*			     */
  catcode['~']		    = CATCODE_ACTIVE;	   /*			     */
}						   /*------------------------*/
 
/*****************************************************************************/
/*** Token Management.							   ***/
/*****************************************************************************/

 static Token token_free_list = TokenNULL;

/*-----------------------------------------------------------------------------
** Function:	new_token()
** Purpose:	Allocate a new token cell and fill it with values.
** Arguments:
**	type	the type
**	string	the strign value
** Returns:	the new token
**___________________________________________________			     */
static Token new_token(type, string)		   /*			     */
  int	 type;				   	   /*			     */
  String string;			   	   /*			     */
{ Token  new;					   /*			     */
						   /*			     */
  if ( token_free_list != TokenNULL )		   /*			     */
  { new = token_free_list;			   /*			     */
    token_free_list = NextToken(token_free_list);  /*			     */
  }						   /*			     */
  else if ( (new=(Token)malloc(sizeof(SToken))) == TokenNULL )/*	     */
  { OUT_OF_MEMORY("TeX token."); }  		   /*			     */
 						   /*                        */
  TokenChar(new) = type;			   /*			     */
  TokenSeq(new)	 = string;			   /*			     */
  NextToken(new) = TokenNULL;			   /*			     */
  return new;					   /*			     */
}						   /*------------------------*/

#define CopyToken(t) new_token(TokenChar(t),	\
			       TokenSeq(t) ? newString(TokenSeq(t)) : NULL)

#define NewToken(C) new_token(C, StringNULL)

/*-----------------------------------------------------------------------------
** Function:	token_list_copy()
** Purpose:	Copy a list of tokens.
** Arguments:
**	t
**	nt
**	argp
** Returns:	
**___________________________________________________			     */
static Token token_list_copy(t,nt,argp)		   /*			     */
  register Token t;				   /*			     */
  Token		 nt;				   /*			     */
  Token		 *argp;				   /*			     */
{ register Token a,p;				   /*			     */
  int		 i;				   /*			     */
						   /*			     */
  if ( t == TokenNULL ) return TokenNULL;	   /*			     */
  if ( (i=TokenChar(t)) > 0xff )		   /*			     */
  { a = p = token_list_copy(argp[i>>8],TokenNULL,argp);/*		     */
    while ( NextToken(p) != TokenNULL )		   /*			     */
    { p = NextToken(p); }			   /*			     */
  }						   /*			     */
  else { a = p = CopyToken(t);	}		   /*			     */
						   /*			     */
  while ( (t=NextToken(t)) != TokenNULL )	   /*			     */
  {						   /*			     */
    if ( (i=TokenChar(t)) > 0xff )		   /*			     */
    { NextToken(p) = token_list_copy(argp[i>>8],TokenNULL,argp);/*	     */
      while ( NextToken(p) != TokenNULL )	   /*			     */
      { p = NextToken(p); }			   /*			     */
    }						   /*			     */
    else					   /*			     */
    { NextToken(p) = CopyToken(t);		   /*			     */
      p = NextToken(p);				   /*			     */
    }						   /*			     */
  }						   /*			     */
  NextToken(p) = nt;				   /*			     */
  return a;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_1_token()
** Purpose:	Free a single Token.
**		Free the string and place it in the free list.
** Arguments:
**	t
** Returns:	nothing
**___________________________________________________			     */
static void free_1_token(t)			   /*			     */
  register Token t;				   /*			     */
{ NextToken(t) = token_free_list;		   /*			     */
  token_free_list = t;				   /*			     */
  if ( TokenSeq(t) ) free(TokenSeq(t));		   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_tokens()
** Purpose:	Free a list of Tokens.
**		Walk along to the end and free the strings on the way.
**		Link it into the free list.
** Arguments:
**	t
** Returns:	nothing
**___________________________________________________			     */
static void free_tokens(t)			   /*			     */
  register Token t;				   /*			     */
{ register Token t0;				   /*			     */
						   /*			     */
  for ( t0 = t;					   /*			     */
	NextToken(t0) != TokenNULL;		   /*			     */
	t0 = NextToken(t0) )			   /*			     */
  { if ( TokenSeq(t0) ) free(TokenSeq(t0)); }	   /*			     */
						   /*			     */
  if ( TokenSeq(t0) ) free(TokenSeq(t0));	   /*			     */
  NextToken(t0) = token_free_list;		   /*			     */
  token_free_list = t;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	tokens_to_string()
** Purpose:	Make a string out of a list of tokens.
** Arguments:
**	t
** Returns:	
**___________________________________________________			     */
static String tokens_to_string(t)		   /*			     */
  Token		  t;				   /*			     */
{ register Token  t1;				   /*			     */
  register String s,				   /*			     */
		  sp;				   /*			     */
  register int	  len;				   /*			     */
						   /*			     */
  for (len = 1, t1 = t;				   /* Count the elements of  */
       t1 != TokenNULL;				   /*  the token list.	     */
       t1 = NextToken(t1))			   /*  (+1 for '\0')	     */
  { ++len; }					   /*			     */
						   /*			     */
  if ( (s=(String)malloc(len * sizeof(Uchar)))     /*                        */
       == NULL )	   			   /* Try to get             */
  { OUT_OF_MEMORY("TeX string."); } 		   /*     new memory.	     */
						   /*			     */
  for (sp = s, t1 = t;				   /* Transfer the characters*/
       t1 != TokenNULL;				   /*  from the token list   */
       t1 = NextToken(t1))			   /*  to the string.	     */
  { *(sp++) = TokenChar(t1); }			   /*			     */
  *sp = '\0';					   /*			     */
  return s;					   /* Return the string.     */
}						   /*------------------------*/

/*****************************************************************************/
/*** Reading Apparatus.							   ***/
/*****************************************************************************/

#define StateN 0
#define StateM 1
#define StateS 2

 static int   tex_state = StateN;		   /*			     */
 static Token tex_line	= TokenNULL;		   /*			     */

#define tex_clear tex_state = StateN; tex_line = TokenNULL

/*-----------------------------------------------------------------------------
** Function:	TeX_fill_line()
** Purpose:	
**		
**
** Arguments:
**	get_fct
** Returns:	
**___________________________________________________			     */
static int TeX_fill_line(get_fct)		   /*			     */
  int		(*get_fct)_ARG((void));		   /* function * to get char */
{ register int	 c;				   /*			     */
  register Token t;				   /*			     */
  register int	 spaces = 0;			   /*			     */
						   /*			     */
  if ( (c=(*get_fct)()) == EOF ) return 1;	   /*			     */
  tex_line = t = NewToken(c);			   /*			     */
						   /*			     */
  while ( (c=(*get_fct)()) != EOF && c != '\n' )   /*			     */
  { if ( isspace(c) ) { ++spaces; }		   /* Spaces are delayed.    */
    else					   /*			     */
    { while ( spaces > 0 )			   /*			     */
      { NextToken(t) = NewToken(CHAR_SPACE);	   /*			     */
	t = NextToken(t);			   /*			     */
	spaces--;				   /*			     */
      }						   /*			     */
      NextToken(t) = NewToken(c);		   /*			     */
      t = NextToken(t);				   /*			     */
    }						   /*			     */
  }						   /*			     */
  if ( TokenChar(t) == CHAR_SPACE ) TokenChar(t) = CHAR_EOL;/*		     */
  else NextToken(t) = NewToken(CHAR_EOL);	   /*			     */
						   /*			     */
#ifdef CARET_CARET
  { register Token *tp;				   /*			     */
    for ( tp= &tex_line;			   /* Loop over the read     */
	 *tp!=TokenNULL;			   /*  line.		     */
	 tp= &NextToken(*tp) )			   /*			     */
    { t = NextToken(*tp);			   /*			     */
      if ( TokenChar(*tp) == '^'		   /* Translate ^^.	     */
	  && TokenChar(t=NextToken(*tp)) == '^'	   /*  to single characters  */
	  && (c=TokenChar(NextToken(t))) != '\n' ) /*			     */
      { NextToken(*tp) = NextToken(NextToken(t));  /*			     */
	free_1_token(NextToken(t));		   /*			     */
	free_1_token(t);			   /*			     */
	TokenChar(*tp) = (c >= 64 ? c - 64 : c + 64);/*			     */
      }						   /*			     */
    }						   /*			     */
  }						   /*			     */
#endif
						   /*			     */
  return 0;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	TeX_get_token()
** Purpose:	Get characters and pack them into a Token structure.
**		The argument is a function called to get the next character.
**		It returns the next character of EOF if no more can be read.
** Arguments:
**	get_fct
** Returns:	
**___________________________________________________			     */
static Token TeX_get_token(get_fct)		   /*			     */
  int		 (*get_fct)_ARG((void));	   /* function * to get char */
{ register Token t, t1, t2;			   /*			     */
						   /*			     */
  for (;;)					   /*			     */
  {						   /*			     */
   if (    tex_line == TokenNULL		   /*			     */
	&& TeX_fill_line(get_fct) )		   /*			     */
    { return TokenNULL; }			   /*			     */
						   /*			     */
    t		 = tex_line;			   /*			     */
    tex_line	 = NextToken(t);		   /*			     */
    NextToken(t) = TokenNULL;			   /*			     */
						   /*			     */
    switch ( TokenChar(t) )			   /*			     */
    { case CHAR_IGNORED:			   /*			     */
	break;					   /*			     */
#ifdef TRANSLATE_NEWLINE
      case CHAR_EOL:				   /*			     */
	switch (tex_state)			   /*			     */
	{ case StateN:				   /*			     */
	    TokenChar(t) = CHAR_ESCAPE;		   /*			     */
	    TokenSeq(t)	 = newString("par");	   /*			     */
	    return t;				   /*			     */
	  case StateM:				   /*			     */
	    TokenChar(t) = CHAR_SPACE;		   /*			     */
	    return t;				   /*			     */
	}					   /*			     */
#endif
      case CHAR_COMMENT:			   /*			     */
	free_tokens(tex_line);			   /*			     */
	tex_line = TokenNULL;			   /*			     */
	break;					   /*			     */
      case CHAR_SPACE:				   /*			     */
	if ( tex_state == StateM )		   /*			     */
	{ tex_state = StateS;			   /*			     */
	  return t;				   /*			     */
	}					   /*			     */
	break;					   /*			     */
      case CHAR_ESCAPE:				   /*			     */
	t1 = tex_line;				   /*			     */
	if ( isalpha(TokenChar(tex_line)) )	   /*			     */
	{ while ( isalpha(TokenChar(NextToken(tex_line))) )/*		     */
	  { tex_line = NextToken(tex_line); }	   /*			     */
	}					   /*			     */
	else if ( TokenChar(tex_line) == CHAR_EOL )/*			     */
	{ tex_state   = StateM;			   /*			     */
	  TokenSeq(t) = newString("");	   	   /*			     */
	  return t;				   /*			     */
	}					   /*			     */
	t2	      = tex_line;		   /*			     */
	tex_line      = NextToken(tex_line);	   /*			     */
	NextToken(t2) = TokenNULL;		   /*			     */
	TokenSeq(t)   = tokens_to_string(t1);	   /*			     */
	free_tokens(t1);			   /*			     */
	tex_state     = StateM;			   /*			     */
	return t;				   /*			     */
						   /*			     */
      default:					   /*			     */
	tex_state = StateM;			   /*			     */
	return t;				   /*			     */
    }						   /*			     */
    free_1_token(t);				   /*			     */
  }						   /*			     */
}						   /*------------------------*/

 static String g_s;				   /*			     */
 static String g_p;				   /*			     */

/*-----------------------------------------------------------------------------
** Function:	init_get()
** Purpose:	
**		
**
** Arguments:
**	s
** Returns:	nothing
**___________________________________________________			     */
static void init_get(s)				   /*			     */
  register String s;				   /*			     */
{ g_p = g_s = s;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	do_get()
** Purpose:	
**		
**
** Arguments:
**	
** Returns:	
**___________________________________________________			     */
static int do_get()				   /*			     */
{ return ( *g_p == '\0' ? EOF : *(g_p++));	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	tokenize()
** Purpose:	
**		
**
** Arguments:
**	s
**	arity
** Returns:	
**___________________________________________________			     */
static Token tokenize(s, arity)			   /*			     */
  String s;					   /*			     */
  int	 arity;					   /*			     */
{ Token	 t = TokenNULL,				   /*			     */
	 t_ret = TokenNULL,			   /*			     */
	 nt, t0;				   /*			     */
  int	 a;					   /*			     */
						   /*			     */
  EnsureInit;					   /*			     */
  init_get(s);					   /*			     */
						   /*			     */
  while ( (nt=TeX_get_token(do_get)) != TokenNULL )/*			     */
  { if ( TokenChar(nt) =='\n' )			   /*			     */
    { free_1_token(nt); }			   /*			     */
    else					   /*			     */
    { if ( TokenChar(nt) == CHAR_PARAMETER	   /*			     */
	  && (t0=TeX_get_token(do_get)) != TokenNULL )/*		     */
      { a = TokenChar(t0) - '0';		   /*			     */
	if ( 0<a && a<=arity ) TokenChar(nt) |= a<<8;/*			     */
	else { Err("*** Argument error.\n"); }	   /*			     */
	free_1_token(t0);			   /*			     */
      }						   /*			     */
      if ( t_ret == TokenNULL ) { t_ret = t = nt; }/*			     */
      else { NextToken(t) = nt; t = nt; }	   /*			     */
    }						   /*			     */
  }						   /*			     */
  return t_ret;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_macdef()
** Purpose:	Allocate a new macro definition.
**
** Arguments:
**	name	the name
**	arity	the arity
**	tokens	the tokens
** Returns:	
**___________________________________________________			     */
static MacDef new_macdef(name, arity, tokens)	   /*			     */
  String    name;				   /*			     */
  int	    arity;				   /*			     */
  Token	    tokens;				   /*			     */
{ MacDef    new;				   /*			     */
						   /*			     */
  if ( (new=(MacDef)malloc(sizeof(SMacDef))) == NULL )/*		     */
  { OUT_OF_MEMORY("TeX macro."); }  		   /*			     */
						   /*			     */
  MacroName(new)  = name;			   /*			     */
  MacroArity(new) = arity;			   /*			     */
  MacroToken(new) = tokens;			   /*			     */
  NextMacro(new)  = MacDefNULL;			   /*			     */
  return new;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_macdef()
** Purpose:	
**		
**		
** Arguments:
**	mac	
** Returns:	nothing
**___________________________________________________			     */
static void free_macdef(mac)			   /*                        */
  MacDef mac;					   /*                        */
{						   /*                        */
  if ( mac == MacDefNULL ) return;		   /*                        */
  free(MacroToken(mac));			   /*                        */
  free(mac);					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	find_macro()
** Purpose:	
**		
**
** Arguments:
**	name	the name of the macro
**	md	the macro to start searching at
** Returns:	
**___________________________________________________			     */
static MacDef find_macro(name, md)		   /*			     */
  register String name;			   	   /*			     */
  register MacDef md;				   /*			     */
{						   /*			     */
  for ( ; md != MacDefNULL; md = NextMacro(md) )   /*			     */
  { if ( strcmp((char*)MacroName(md), 		   /*                        */
		(char*)name) == 0 )  		   /*			     */
      return md;				   /*			     */
  }						   /*			     */
  return MacDefNULL;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	TeX_define()
** Purpose:	Add a new \TeX{} macro definition.
**		
**
** Arguments:
**	name
**	arity
**	body
** Returns:	nothing
**___________________________________________________			     */
void TeX_define(name, arity, body)		   /*			     */
  String	  name;			   	   /*			     */
  int		  arity;			   /*			     */
  String	  body;			   	   /*			     */
{ register MacDef md;				   /*			     */
						   /*			     */
  if ( 0 > arity || arity > 9 ) return;		   /*			     */
						   /*			     */
  md		= new_macdef(name,		   /*                        */
			     arity,		   /*                        */
			     tokenize(body,arity));/*	                     */
  NextMacro(md) = macro;			   /*			     */
  macro		= md;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	TeX_def()
** Purpose:	Define a macro.
**		The argument is a string specification of the following form:
**
**		    |\name[arity]=replacement text|\\
**		    |\name=replacement text|
**
**		\(0 <= arity <= 9\)
** Arguments:
**	s
** Returns:	nothing
**___________________________________________________			     */
void TeX_def(s)					   /*			     */
  String s;			   		   /*			     */
{ String name,				   	   /*			     */
	 ep    = NULL;			   	   /*			     */
  int	 arity = 0;				   /*			     */
						   /*			     */
  while( isspace(*s) ) s++;			   /*                        */
  name = s;					   /*			     */
  while ( *s && *s != '=' )			   /*			     */
  { if ( *s == '[' )				   /*			     */
    { arity = *(s+1) - '0'; ep = s; }		   /*			     */
    ++s;					   /*			     */
  }						   /*			     */
						   /*			     */
  if ( ep == NULL ) ep = s;			   /*			     */
						   /*			     */
  if ( *name == '\\' )				   /*                        */
  { char c;				   	   /*			     */
    while (ep > name + 2 &&			   /*                        */
	   (*(ep-1)  == ' ' || *(ep-1) =='\t'))	   /*                        */
    { ep--; }					   /*                        */
    c = *ep; *ep = '\0';			   /*			     */
    TeX_define(newString(name + 1),	   	   /*			     */
	       arity,				   /*			     */
	       newString(s + 1));		   /*			     */
    *ep = c;					   /*			     */
  }						   /*                        */
  else						   /*                        */
  { TeX_active((unsigned int)*name,		   /*                        */
	       arity,				   /*                        */
	       newString(s+1));		   	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	TeX_active()
** Purpose:	Assign a macro to an active character. If the
**		character is not active then the catcode is changed.  
** Arguments:
**	c	Character to make active.
**	arity	Arity of the macro assigned to the active character.
**	s	Body of the definition as string.
** Returns:	nothing
**___________________________________________________			     */
void TeX_active(c, arity, s)			   /*			     */
  int   c;					   /*			     */
  int   arity;					   /*			     */
  String s;				   	   /*			     */
{						   /*			     */
  EnsureInit;					   /*			     */
  if ( active[c] ) free_macdef(active[c]);	   /*                        */
 						   /*                        */
  active[c] = new_macdef(StringNULL,		   /*                        */
			 arity,			   /*                        */
			 tokenize(s,arity));	   /*	                     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	TeX_reset()
** Purpose:	Reset the \TeX{} reading apparatus to its initial
**		state.  All macros and active characters are cleared
**		and the memory is released. Thus this function can
**		also be used for this purpose.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void TeX_reset()				   /*                        */
{ int    i;					   /*                        */
  MacDef md, next;				   /*                        */
 						   /*                        */
  for (i = 0; i < 256; i++)			   /*                        */
  { free_macdef(active[i]); }			   /*                        */
 						   /*                        */
  md = macro;					   /*                        */
  macro = MacDefNULL;				   /*                        */
  while ( md )					   /*                        */
  { next = NextMacro(md);			   /*                        */
    free_macdef(md);				   /*                        */
    md = next;					   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_EOF()
** Purpose:	
** Arguments:
**	
** Returns:	
**___________________________________________________			     */
static int get_EOF()				   /*			     */
{ return EOF;					   /*			     */
}						   /*------------------------*/

 static FILE  *src_file;			   /*			     */
 static String src_string;			   /*			     */
 static String src_ptr;				   /*			     */
 static int  (*src_get)() = get_EOF;		   /*			     */

/*-----------------------------------------------------------------------------
** Function:	get_string()
** Purpose:	
**		
**
** Arguments:
**	
** Returns:	
**___________________________________________________			     */
static int get_string()				   /*			     */
{ return ( *src_ptr ? *(src_ptr++) : EOF );	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_file()
** Purpose:	
**		
**
** Arguments:
**	
** Returns:	
**___________________________________________________			     */
static int get_file()				   /*			     */
{ return getc(src_file);			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	TeX_open_file()
** Purpose:	Prepare things to parse from a file.
** Arguments:
**	file	File pointer of the file to read from.
** Returns:	nothing
**___________________________________________________			     */
void TeX_open_file(file)			   /*			     */
  FILE * file;					   /*			     */
{ src_file = file;				   /*			     */
  src_get  = get_file;				   /*			     */
  tex_clear;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	TeX_open_string()
** Purpose:	Prepare things to parse from a string.
** Arguments:
**	s	String to read from.
** Returns:	nothing
**___________________________________________________			     */
void TeX_open_string(s)				   /*			     */
  String s;					   /*			     */
{ src_ptr = src_string = s;			   /*			     */
  src_get = get_string;				   /*			     */
  tex_clear;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	TeX_close()
** Purpose:	Gracefully terminate the reading of \TeX{} tokens. Any
**		remaining pieces of text which have already been
**		consumed are discarted.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void TeX_close()				   /*			     */
{ Uchar  c;					   /*                        */
  String s;				   	   /*			     */
  src_get = get_EOF;				   /*			     */
  while ( TeX_read(&c, &s) ) ;			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	fill_token()
** Purpose:	Check if *tp contains a token.
**		Otherwise try to get one and store it there.
** Arguments:
**	tp	the pointer to the token
** Returns:	
**___________________________________________________			     */
static int fill_token(tp)			   /*			     */
  register Token *tp;				   /*			     */
{						   /*                        */
  if (	 *tp == TokenNULL			   /*			     */
      && (*tp=TeX_get_token(src_get)) == TokenNULL )/*			     */
  { return 0; }				   	   /*			     */
  return 1;					   /*			     */
}						   /*------------------------*/

#define UnlinkToken(T,T2)		T2 = T; T = NextToken(T)
#define UnlinkAndFreeToken(T,T2)	UnlinkToken(T,T2); free_1_token(T2)

/*-----------------------------------------------------------------------------
** Function:	TeX_read()
** Purpose:	Read a single Token and return it as a pair consisting
**		of an ASCII code and possibly a string in case of a
**		macro token.
** Arguments:
**	cp	Pointer to position where the character is stored.
**	sp	Pointer to position where the string is stored.
** Returns:	|false| iff everything went right.
**___________________________________________________			     */
bool TeX_read(cp, sp)				   /*			     */
  String	cp;				   /*			     */
  String	*sp;				   /*			     */
{ static Token	t     = TokenNULL;		   /*			     */
  static Token	old_t = TokenNULL;		   /*			     */
  static Token	arg[10];			   /*			     */
  Token		t2, tp;				   /*			     */
  int		i, d;				   /*			     */
						   /*			     */
  EnsureInit;					   /*			     */
  if ( old_t != TokenNULL ) free_1_token(old_t);   /*			     */
						   /*			     */
  while ( fill_token(&t) )			   /* One token left or	     */
  {						   /*  I got a new one.	     */
    MacDef mac = active[TokenChar(t)];	   	   /*			     */
    if ( mac != MacDefNULL )			   /* Is it active?          */
    { UnlinkAndFreeToken(t, t2);		   /* Delete active token    */
    }						   /*                        */
    else if ( TokenChar(t) == CHAR_ESCAPE &&	   /*                        */
	      (mac=find_macro(TokenSeq(t),macro))  /*  or an undefined	     */
	      != MacDefNULL )			   /*                        */
    { UnlinkAndFreeToken(t,t2);			   /* Delete macro name token*/
      while ( fill_token(&t)			   /* While there are more   */
	     && TokenChar(t) == CHAR_SPACE)	   /*  tokens and == ' '     */
      { UnlinkAndFreeToken(t,t2); }		   /* unlink space	     */
    }						   /*                        */
    else					   /*                        */
    { *cp = TokenChar(t);			   /*			     */
      *sp = TokenSeq(t);			   /*			     */
      UnlinkToken(t,old_t);			   /*			     */
      return true;				   /*			     */
    }						   /*			     */
						   /*			     */
    for (i = 1; i <= MacroArity(mac); ++i)	   /* Fill the argument	     */
    {						   /*  vector		     */
      if ( !fill_token(&t) )			   /*			     */
      { arg[i] = TokenNULL;			   /* Not enough tokens	     */
        Err("*** Unexpected EOF\n");		   /*			     */
      }					   	   /*			     */
      else if (TokenChar(t) == CHAR_BEG_GROUP)     /* If there is a group    */
      { tp = t;				   	   /*			     */
        d  = 0;				   	   /*			     */
	while ( fill_token(&NextToken(tp))  &&     /* While there are more   */
		(TokenChar(NextToken(tp))	   /*  tokens                */
		 != CHAR_END_GROUP  		   /*  and                   */
		 || d != 0 ) )			   /*  no matching '}'	     */
	{ tp = NextToken(tp);			   /*  walk ahead and	     */
	  switch ( TokenChar(tp) )		   /*  count braces	     */
	  { case CHAR_BEG_GROUP: ++d; break;	   /*			     */
	    case CHAR_END_GROUP: d--; break;	   /*			     */
	  }					   /*			     */
	}					   /*			     */
	t2 = NextToken(NextToken(tp));	   	   /*			     */
	free_1_token(NextToken(tp));		   /* remove final '}'	     */
	NextToken(tp) = TokenNULL;		   /*			     */
	tp = t; t = t2;			   	   /*			     */
	UnlinkAndFreeToken(tp,t2);		   /* remove initial '{'     */
	arg[i] = tp;				   /*			     */
      }					   	   /*			     */
      else					   /*			     */
      { arg[i] = t;				   /* Move one token	     */
        t = NextToken(t);			   /*  to argument vector    */
	NextToken(arg[i]) = TokenNULL;	   	   /*			     */
      }					   	   /*			     */
    }						   /*			     */
						   /*			     */
    t = token_list_copy(MacroToken(mac),t,arg);    /*			     */
						   /*			     */
    for (i = 1; i < MacroArity(mac); ++i)   	   /* free the arg vector    */
    { if ( arg[i] != TokenNULL )		   /*			     */
      { free_tokens(arg[i]);			   /*			     */
        arg[i] = TokenNULL;			   /*			     */
      }					   	   /*			     */
    }						   /*			     */
  }						   /*			     */
  old_t = TokenNULL;				   /*			     */
  return false;					   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***			 Stand alone version     			   ***/
/*****************************************************************************/
#ifdef STANDALONE

/*-----------------------------------------------------------------------------
** Function*:	new_string()
** Purpose:	Allocate a space for a string and copy the argument
**		there. Note this is just a new copy of the memory not
**		a symbol!
**
**		If no more memory is available then an error is raised
**		and the program is terminated.
** Arguments:
**	s	String to duplicate
** Returns:	Pointer to newly allocated memory containing a
**		duplicate of the argument string.
**___________________________________________________			     */
static char * new_string(s)			   /*			     */
  register char * s;				   /*			     */
{ register char * t;				   /*			     */
  if ( (t=malloc(strlen(s)+1)) == NULL )	   /*			     */
  { OUT_OF_MEMORY("string"); }	   		   /*			     */
  (void)strcpy(t,s);  return(t);		   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:   main()
** Purpose:     Main routine for the stand alone version.
** Arguments:
**	argc	Number of arguments (+1)
**	argv	Array of command line arguments (and program name)
** Returns:     
**___________________________________________________                        */
int main(argc,argv)				   /*			     */
  int  argc;					   /*			     */
  char *argv[];					   /*			     */
{ FILE *file;					   /*			     */
  int  kept  = 0;				   /*			     */
  char buffer[1024];				   /*			     */
  char c;					   /*			     */
  char *s;					   /*			     */
						   /*			     */
						   /*			     */
  if ( argc > 3 )				   /*			     */
  { Err("\nTeX macro expander. gene 1/95\n\n");
    Err("Usage: tex_read [macro_file [input_file]]\n\n");
    Err("\tRead the macros and expand them in the input file\n");
    Err("\tafterwards. Comments are also eliminated.\n\n");
    Err("\tThe macros are made up of lines of the following form:\n");
    Err("\t\tmacname[args]=replacement text\n");
    Err("\twhere 0<=args<=9. If args=0 then [0] can be omitted.\n");
    Err("\treplacement text may also contain macros which are expanded.\n\n");
    Err("\tThe program mimics the reading mechanism of TeX.\n");
    Err("\t\n");
    return;					   /*                        */
  }						   /*                        */
  if ( argc > 1 )				   /*			     */
  { if ( (file = fopen(argv[1],"r")) == NULL )	   /*			     */
    { ERROR_EXIT("File open error"); }		   /*			     */
    while ( fgets(buffer,1024,file) )		   /*			     */
    { for(s=buffer;*s;++s) if(*s=='\n') *s = '\0'; /*			     */
      for(s=buffer;*s&&isspace(*s);++s) ;	   /*			     */
      if ( *s == '\\' ) TeX_def(s);		   /*			     */
    }						   /*			     */
    TeX_close();				   /*			     */
    (void)fclose(file);				   /*			     */
  }						   /*			     */
  file = stdin;					   /*			     */
  if ( argc > 2 &&				   /*			     */
      (file = fopen(argv[2],"r")) == NULL )	   /*			     */
  { ERROR_EXIT("File open error"); }		   /*			     */
						   /*			     */
  TeX_open_file(file);				   /*			     */
						   /*			     */
  while ( TeX_read(&c,&s) )			   /*			     */
  { if ( kept )					   /*			     */
    { if ( isalpha(c) ) (void)putchar(' ');	   /*			     */
      kept = 0;					   /*			     */
    }						   /*			     */
    (void)putchar(c);				   /*			     */
    if ( s )					   /*			     */
    { (void)fputs(s,stdout);			   /*			     */
      kept = isalpha(*s);			   /*			     */
    }						   /*			     */
  }						   /*			     */
						   /*			     */
  TeX_close();					   /*			     */
						   /*			     */
  if ( file != stdin ) (void)fclose(file);	   /*			     */
  return 0;					   /*			     */
}						   /*------------------------*/

#endif /*STANDALONE*/

#ifdef DEBUG
/*-----------------------------------------------------------------------------
** Function*:	show_tokens()
** Purpose:	
**		
**
** Arguments:
**	t	the token
** Returns:	nothing
**___________________________________________________			     */
static void show_tokens(t)			   /*			     */
  register Token t;				   /*			     */
{						   /*			     */
  while ( t != TokenNULL )			   /*			     */
  { if ( TokenChar(t) == CHAR_ESCAPE )		   /*			     */
    { (void)printf("_\\%s",TokenSeq(t)); }	   /*			     */
    else if ( TokenChar(t) > 0xff )		   /*			     */
    { (void)printf("_#%d",TokenChar(t)>>8);	   /*			     */
    }						   /*			     */
    else					   /*			     */
    { (void)printf("_%c",TokenChar(t)); }	   /*			     */
    t = NextToken(t);				   /*			     */
  }						   /*			     */
}						   /*------------------------*/
#endif /*DEBUG*/
