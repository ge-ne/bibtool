/*** s_parse.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2014 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/error.h>
#include <bibtool/parse.h>
#include <bibtool/s_parse.h>

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Uchar * s_parse _ARG((int type,Uchar **sp,int errp));/* s_parse.c           */
 int sp_open _ARG((Uchar * s));			   /* s_parse.c              */
 void sp_close _ARG((void));			   /* s_parse.c              */
 void sp_error _ARG((Uchar *s,char *a,char *b));   /* s_parse.c              */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

#define Error(E,S,A,B)	\
  if(E) error(ERR_ERROR|ERR_POINT,(Uchar*)A,(Uchar*)B,(Uchar*)0,sp_line,(Uchar*)S,0,(char*)0)

 static Uchar *sp_line = NULL;

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
  Uchar *s;				   	   /*                        */
{ sp_line = s;				   	   /*                        */
  return TRUE;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	s_parse()
** Purpose:	Parse a string for a certain entity. Leading
**		whitespace is ignored. |type| determines which kind of
**		entity should be exepected. It can take the following
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
**	type	is the type of construct to parse. it is defined in s_parse.h
**	sp	is a pointer to the string which is parsed. The value is
**		changed to hold the remaining characters at the end.
**	errp	this boolean indicated whether or not a verbose error
**		message should be created in case of an error.
** Returns:	A symbol containing the requested entity or |NULL|.
**___________________________________________________			     */
Uchar * s_parse(type,sp,errp)			   /*                        */
  int 		 type;				   /*                        */
  Uchar		 **sp;				   /*                        */
  int		 errp;				   /*                        */
{ register Uchar *s = *sp;			   /*                        */
  Uchar          c;				   /*                        */
  char		 *cp;				   /*                        */
  static char    *unexpected = "Unexpected ";	   /*                        */
  static char    *expected   = " expected.";	   /*                        */
 						   /*                        */
  DebugPrint2((type == StringParseSkip ? "ParseSkip ":
	       type == StringParseNext ? "ParseNext ":
	       type == StringParseNumber ? "ParseNumber ":
	       type == StringParseSymbol ? "ParseSymbol ":
	       type == StringParseString ? "ParseString ":
	       type == StringParseUnquotedString ? "ParseUnquotedString ":
	       type == StringParseBraces ? "ParseBraces ":
	       type == StringParseUnquotedBraces ? "ParseUnquotedBraces ":
	       type == StringParseEOS ? "ParseEOS ":
	       type == StringParseValue ? "ParseValue ":
	       "???"),s);		   	   /*			     */
  while( is_space(*s) ) s++;			   /*                        */
  *sp = s;					   /*                        */
 						   /*                        */
  switch ( type )				   /*                        */
  { case StringParseSymbol:			   /*                        */
      if ( is_allowed(*s) )			   /*                        */
      { do { s++; } while ( is_allowed(*s) );	   /*                        */
      }						   /*                        */
      else					   /*                        */
      { Error(errp,s,"Symbol",expected);	   /*                        */
	return NULL;				   /*                        */
      }						   /*                        */
     break;					   /*                        */
 						   /*                        */
    case StringParseNumber:			   /*                        */
      if ( is_digit(*s) )			   /*                        */
      { do { s++; } while ( is_digit(*s) );	   /*                        */
      }						   /*                        */
      else					   /*                        */
      { Error(errp,s,"Number",expected);	   /*                        */
	return NULL;				   /*                        */
      }						   /*                        */
      break;					   /*                        */
 						   /*                        */
    case StringParseBraces:			   /*                        */
    case StringParseUnquotedBraces:		   /*                        */
      if ( *s != '{' )				   /*                        */
      { Error(errp,s,"Brace",expected);	   	   /*                        */
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
	{ Error(errp,s,unexpected,"end of braces.");/*                       */
	}					   /*                        */
	else if ( type==StringParseUnquotedBraces )/*                        */
	{ s--; }				   /*                        */
      }						   /*                        */
      break;					   /*                        */
 						   /*                        */
    case StringParseString:			   /*                        */
    case StringParseUnquotedString:		   /*                        */
      if ( *s != '"' )				   /*                        */
      { Error(errp,s,"String",expected);	   /*                        */
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
      { Error(errp,s,unexpected,"end of string."); /*                        */
      }						   /*                        */
      break;					   /*                        */
 						   /*                        */
    case StringParseSkip:			   /*                        */
      while(   is_space(*s) 			   /*                        */
	    || *s == '='			   /*                        */
	    || *s == '#'    ) s++;		   /*                        */
      *sp = s;					   /*                        */
      return s;					   /*                        */
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
    case StringParseEOS:			   /*                        */
      if ( *s )					   /*                        */
      { Error(errp,s,unexpected,"characters at end of string.");/*           */
      }						   /*                        */
      						   /*                        */
      sp_line = NULL;				   /*                        */
      return (*s?s:NULL);			   /*                        */
 						   /*                        */
    default:					   /*                        */
      return NULL;				   /*                        */
  }						   /*                        */
 						   /*                        */
  c   = *s;					   /*                        */
  *s  = '\0';					   /*                        */
  cp  = new_string((char*)*sp);			   /*                        */
  *s  = c;					   /*                        */
  if (   type == StringParseUnquotedString	   /*                        */
      || type == StringParseUnquotedBraces ) s++;  /*                        */
  *sp = s;					   /*                        */
 if (   type == StringParseSymbol )		   /*                        */
 { (void)lower((Uchar*)cp); }			   /*                        */
 						   /*                        */
 { Uchar *sym = symbol((Uchar*)cp);		   /*                        */
    free(cp);					   /*                        */
    return sym;					   /*                        */
  }						   /*                        */
}						   /*------------------------*/
