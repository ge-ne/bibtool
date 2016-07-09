/*** s_parse.c ****************************************************************
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
#include <bibtool/error.h>
#include <bibtool/parse.h>
#include <bibtool/s_parse.h>
#include <bibtool/type.h>

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Symbol s_parse _ARG((int type,String *sp,int errp));/* s_parse.c            */
 int sp_open _ARG((String  s));			   /* s_parse.c              */
 void sp_close _ARG((void));			   /* s_parse.c              */
 int sp_expect _ARG((String*sp, String expect, int verbose));/* s_parse.c    */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

#define Error(E,S,A,B)	\
  if(E) error(ERR_ERROR|ERR_POINT,(String)A,(String)B,(String)0,sp_line,(String)S,0,(char*)0)

 static String unexpected = (String)"Unexpected "; /*                        */
 static String expected   = (String)" expected.";  /*                        */

 static String sp_line = StringNULL;		   /*                        */

/*-----------------------------------------------------------------------------
** Function:	sp_open()
** Purpose:	Open a string for parsing. The argument string is used
**		for the parsing process.  Thus this string should not
**		be modified during this time.  Especially it should
**		not be freed if it is a pointer to dynamically
**		allocated memory.
** Arguments:
**	s	String to open for parsing.
** Returns:	|TRUE|
**___________________________________________________			     */
int sp_open(s)					   /*                        */
  String s;				   	   /*                        */
{ sp_line = s;				   	   /*                        */
  return TRUE;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sp_close()
** Type:	void
** Purpose:	Release the string parser and rest it to its initial state.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void sp_close()					   /*                        */
{						   /*                        */
  sp_line = StringNULL;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sp_eos()
** Type:	Sting
** Purpose:	
**		
** Arguments:
**	sp	the string pointer
** Returns:	
**___________________________________________________			     */
String sp_eos(sp)				   /*                        */
  String *sp;					   /*                        */
{ register String s = *sp;			   /*                        */
 						   /*                        */
  while( is_space(*s) ) s++;			   /*                        */
  *sp = s;					   /*                        */
 						   /*                        */
  if ( *s )					   /*                        */
  { Error(-1, s, unexpected,		   	   /*                        */
	  "characters at end of string.");	   /*                        */
  }						   /*                        */
      						   /*                        */
  sp_line = NULL;				   /*                        */
  return (*s ? s : NULL);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sp_skip()
** Type:	void
** Purpose:	Advance a String pointer to the next character which is not a
**		white-space, equals or hash.
** Arguments:
**	sp	the string pointer
** Returns:	
**___________________________________________________			     */
void sp_skip(sp)				   /*                        */
  register String *sp;				   /*                        */
{ register String s = *sp;			   /*                        */
  while (   is_space(*s) 			   /*                        */
	 || *s == '='			   	   /*                        */
	 || *s == '#'    ) s++;		   	   /*                        */
  *sp = s;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	s_parse()
** Purpose:	Parse a string for a certain entity. Leading
**		whitespace is ignored. |type| determines which kind of
**		entity should be expected. It can take the following
**		values which are defined in |s_parse.h|:
**		\begin{description}
**		\item[StringParseValue] The string is analyzed and the
**		  proper type is determined automatically. This can be
**		  considered as the normal way of operation.
**		\item[StringParseSymbol] The string is analyzed and
**		  only a symbol is accepted, i.e.\ a sequence of
**		  allowed characters.
**		\item[StringParseNumber] The string is analyzed and
**		  only a number is accepted.
**		\item[StringParseBraces] The string is analyzed and
**		  only an expression in braces is accepted. The braced
**		  contained must come in matching pairs. The whole
**		  expression -- including the braces -- is returned.
**		\item[StringParseUnquotedBraces] The string is analyzed and
**		  only an expression in braces is accepted. The braced
**		  contained must come in matching pairs. The
**		  expression without the outer braces is returned.
**		\item[StringParseString] The string is analyzed and
**		  only a string enclosed in double quotes is
**		  accepted. The string must contain braces in matching
**		  pairs. Double quotes which are inside of braces are
**		  not considered as end of the string. The whole
**		  string -- including the double quotes is returned.
**		\item[StringParseUnquotedString] The string is analyzed and
**		  only a string enclosed in double quotes is
**		  accepted. The string must contain braces in matching
**		  pairs. Double quotes which are inside of braces are
**		  not considered as end of the string. The string
**		  without the outer double quotes is returned.
**		\item[StringParseSkip] The string is analyzed and the
**		  first position not containing whitespace, |=|, or |#|
**		  is returned. In this case the returned value is not
**		  translated into a symbol.
**		\item[StringParseEOS] The string is analyzed and any
**		  remaining characters which are not whitespace are
**		  reported as error. A pointer to the terminating 0 byte
**		  is returned upon success
**		\end{description}
**		If an error occurs or the requested entity is not
**		found then |NULL| is returned. As a side effect |sp|
**		is advanced to point to the next unprocessed
**		character.
**
**		The string analyzed should be opened at the beginning
**		with |sp_open()| in order to get an appropriate error
**		message. 
**
**		This function is usually not called directly but the
**		convenience macros defined in |s_parse.h| should be
**		used instead.
** Arguments:
**	type	is the type of construct to parse. It is defined in s_parse.h
**	sp	is a pointer to the string which is parsed. The value is
**		changed to hold the remaining characters at the end.
**	errp	this boolean indicated whether or not a verbose error
**		message should be created in case of an error.
** Returns:	A symbol containing the requested entity or |NULL|.
**___________________________________________________			     */
Symbol s_parse(type, sp, errp)			   /*                        */
  int 		  type;				   /*                        */
  String	  *sp;				   /*                        */
  int		  errp;				   /*                        */
{ register String s = *sp;			   /*                        */
  Uchar           c;				   /*                        */
  String	  cp;				   /*                        */
 						   /*                        */
  DebugPrint2((type == StringParseNext ? "ParseNext ":
	       type == StringParseNumber ? "ParseNumber ":
	       type == StringParseSymbol ? "ParseSymbol ":
	       type == StringParseString ? "ParseString ":
	       type == StringParseUnquotedString ? "ParseUnquotedString ":
	       type == StringParseBraces ? "ParseBraces ":
	       type == StringParseUnquotedBraces ? "ParseUnquotedBraces ":
	       type == StringParseValue ? "ParseValue ":
	       "???"),s);		   	   /*			     */
  while( is_space(*s) ) s++;			   /*                        */
  *sp = s;					   /*                        */
 						   /*                        */
  switch ( type )				   /*                        */
  { case StringParseSymbol:			   /*                        */
      if ( is_allowed(*s) && !is_digit(*s) )	   /*                        */
      { do { s++; } while ( is_allowed(*s) );	   /*                        */
      }						   /*                        */
      else			   		   /*                        */
      { Error(errp, s, "Symbol", expected);	   /*                        */
	return NULL;				   /*                        */
      }						   /*                        */
      break;					   /*                        */
 						   /*                        */
    case StringParseNumber:			   /*                        */
      if ( is_digit(*s) )			   /*                        */
      { do { s++; } while ( is_digit(*s) );	   /*                        */
      }						   /*                        */
      else					   /*                        */
      { Error(errp, s, "Number", expected);	   /*                        */
	return NULL;				   /*                        */
      }						   /*                        */
      break;					   /*                        */
 						   /*                        */
    case StringParseBraces:			   /*                        */
    case StringParseUnquotedBraces:		   /*                        */
      if ( *s != '{' )				   /*                        */
      { Error(errp, s, "Brace", expected);	   /*                        */
	return NULL;				   /*                        */
      }						   /*                        */
      s++;					   /*                        */
      if ( type == StringParseUnquotedBraces )	   /*                        */
      { *sp = s; }				   /*                        */
      { int level = 1;				   /*                        */
      						   /*                        */
	while ( *s && level > 0 )		   /*                        */
	{					   /*                        */
	  switch ( *s )				   /*                        */
	  { case '{': level++; break;		   /*                        */
	    case '}': --level; break;		   /*                        */
	    case '"':				   /*                        */
	      s++;				   /*                        */
	      while (*s && *s != '"')		   /*                        */
	      { if (*s != '\\' || *++s ) s++;	   /*                        */
	      }		   			   /*                        */
	      break;				   /*                        */
	  }					   /*                        */
	  if ( *s ) s++;			   /*                        */
	}					   /*                        */
	if ( level > 0 )			   /*                        */
	{ Error(errp, s, unexpected, "end of braces.");/*                    */
	}					   /*                        */
	else if ( type==StringParseUnquotedBraces )/*                        */
	{ s--; }				   /*                        */
      }						   /*                        */
      break;					   /*                        */
 						   /*                        */
    case StringParseString:			   /*                        */
    case StringParseUnquotedString:		   /*                        */
      if ( *s != '"' )				   /*                        */
      { Error(errp, s, "String", expected);	   /*                        */
	return NULL;				   /*                        */
      }						   /*                        */
      s++;					   /*                        */
      if ( type == StringParseUnquotedString )	   /*                        */
      { *sp = s; }				   /*                        */
      						   /*                        */
      while ( *s && *s != '"' )			   /*                        */
      { if ( *s == '\\' && *(s+1) != '\0' ) s += 2;/*                        */
      else ++s;					   /*                        */
      }						   /*                        */
  						   /*                        */
      if ( *s == '"' ) 				   /*                        */
      { if ( type != StringParseUnquotedString ) s++;/*                      */
      }			   			   /*                        */
      else					   /*                        */
      { Error(errp, s, unexpected, "end of string.");/*                      */
      }						   /*                        */
      break;					   /*                        */
 						   /*                        */
    case StringParseValue:			   /*                        */
      switch ( *s )				   /*                        */
      { case '"':				   /*                        */
	  return s_parse(StringParseUnquotedString,sp,errp);/*               */
	case '{':				   /*                        */
	  return s_parse(StringParseUnquotedBraces,sp,errp);/*               */
	case '0': case '1': case '2': case '3':    /*                        */
	case '4': case '5': case '6': case '7':	   /*                        */
	case '8': case '9':			   /*			     */
	  return s_parse(StringParseNumber,sp,errp);/*                       */
	default:				   /*                        */
	  return s_parse(StringParseSymbol,sp,errp);/*                       */
      }						   /*                        */
      break;					   /*                        */
 						   /*                        */
    default:					   /*                        */
      return NULL;				   /*                        */
  }						   /*                        */
 						   /*                        */
  c  = *s;					   /*                        */
  *s = (Uchar)'\0';				   /*                        */
  cp = newString(*sp);			   	   /*                        */
  *s = c;					   /*                        */
  if (   type == StringParseUnquotedString	   /*                        */
      || type == StringParseUnquotedBraces ) s++;  /*                        */
  *sp = s;					   /*                        */
  if (type == StringParseSymbol)		   /*                        */
  { (void)lower(cp); }				   /*                        */
 						   /*                        */
  { Symbol sym = symbol(cp);			   /*                        */
    free(cp);				   	   /*                        */
    return sym;					   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sp_expect()
** Type:	int
** Purpose:	Read a sequence of expected characters after whitespace.
**		The source pointer is advanced until the expected
**		string has been read or to the first character which
**		is not expected.
** Arguments:
**	sp	the pointer to the source string
**	expect	the expected string
**	verbose	the indicator whether an error message should be produced
** Returns:	|TRUE| iff the expected string is found
**___________________________________________________			     */
int sp_expect(sp, expect, verbose)		   /*                        */
  register String *sp;				   /*                        */
  register String expect;			   /*                        */
  int verbose;					   /*                        */
{						   /*                        */
  while( is_space(**sp) ) (*sp)++;	   	   /*                        */
 						   /*                        */
  for ( ; *expect; expect++)			   /*                        */
  { if (*expect != **sp)			   /*                        */
    { if (verbose)				   /*                        */
      { Error(1, *sp, expect, expected); }	   /*                        */
      return FALSE;				   /*                        */
    }	   					   /*                        */
    (*sp)++;					   /*                        */
  }						   /*                        */
 						   /*                        */
  return TRUE;					   /*                        */
}						   /*------------------------*/

#define SkipSpaces(PTR) while( is_space(*PTR) ) (PTR)++

/*-----------------------------------------------------------------------------
** Function:	sp_symbols()
** Type:	String*
** Purpose:	
**		
** Arguments:
**	sp	the pointer to the value to be parsed
** Returns:	an array of Symbols
**___________________________________________________			     */
Symbol* sp_symbols(sp)				   /*                        */
  String *sp;					   /*                        */
{ Symbol s;					   /*                        */
  Symbol *a = NULL;				   /*                        */
  int n	= 0;					   /*                        */
  int i = 0;					   /*                        */
 						   /*                        */
  if (sp_expect(sp, (String)"{", FALSE))	   /*                        */
  { n = 4;					   /*                        */
    a = (Symbol*)malloc(n * sizeof(Symbol));	   /*                        */
    if (a == (Symbol*)NULL)			   /*                        */
    { OUT_OF_MEMORY("symbols"); }   		   /*                        */
 						   /*                        */
    SkipSpaces(*sp);				   /*                        */
    while (**sp && **sp != '}')			   /*                        */
    { SkipSpaces(*sp);				   /*                        */
      if ((s = SParseSymbol(sp)) == NO_SYMBOL) {   /*                        */
	return (Symbol*)NULL;			   /*                        */
      }						   /*                        */
      if (i >= n - 1)				   /*                        */
      { n += 4;					   /*                        */
	a = (Symbol*)realloc(a, n * sizeof(Symbol));/*                       */
	if (a == NULL) { OUT_OF_MEMORY("symbols"); }/*                       */
      }						   /*                        */
      a[i++] = s;				   /*                        */
      SkipSpaces(*sp);				   /*                        */
    }						   /*                        */
    if (**sp == '\0')				   /*                        */
    { Error(TRUE, *sp, unexpected,		   /*                        */
	    "end of symbols.");			   /*                        */
      return (Symbol*)NULL;			   /*                        */
    }					   	   /*                        */
    (*sp)++;					   /*                        */
    a[i] = NO_SYMBOL;				   /*                        */
 						   /*                        */
  } else if ( !is_digit(**sp) &&		   /*                        */
	     (s=s_parse(StringParseSymbol,	   /*                        */
			sp, 0)) != NO_SYMBOL) {   /*                        */
    a	  = (Symbol*)malloc(2 * sizeof(Symbol));   /*                        */
    if (a == NULL) { OUT_OF_MEMORY("symbols"); }   /*                        */
    a[0] = s;					   /*                        */
    a[1] = NO_SYMBOL;				   /*                        */
  } else {					   /*                        */
    Error(TRUE, *sp, "List of symbols", expected); /*                        */
  }						   /*                        */
  return a;					   /*                        */
}						   /*------------------------*/
