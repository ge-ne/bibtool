/*** expnad.c *****************************************************************
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
**-----------------------------------------------------------------------------
** Description:
**	This module contains functions to expand macros as they are
**	appearing in right hand sides of equations. This can be used
**	to get rid of additional macro definitions.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/error.h>
#include <bibtool/expand.h>
#include <bibtool/symbols.h>
#include <bibtool/macros.h>
#include <bibtool/sbuffer.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 String  expand_rhs _ARG((String s,String pre,String post,DB db));/* expand.c*/
 static int expand _ARG((String s,StringBuffer *sb,int brace,int first,String q_open,String q_close,DB db));/* expand.c*/
 static void expand__ _ARG((String s,StringBuffer *sb,String q_open,String q_close,DB db));/* expand.c*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Function:	expand_rhs()
** Purpose:	Expand the right hand side of an item. Each macro
**		which is defined in this database is replaced by its
**		value. The result is kept in a static variable until
**		the next invocation of this function overwrites it.
** Arguments:
**	s	String to expand
**	pre	This is the opening brace character to be used. For
**		\BibTeX{} the valid values are |{| or |"|. This value
**		has to match to |post|.
**	post	This is the closing brace character to be used. For
**		\BibTeX{} the valid values are |}| or |"|. This value
**		has to match to |pre|.
**	db	Database containing the macros.
** Returns:	A pointer to the expanded string. This value is kept in a
**		static variable of this function and will be overwritten with
**		the next invocation.
**___________________________________________________			     */
String  expand_rhs(s,pre,post,db)		   /*                        */
  String s;					   /*                        */
  String pre;					   /*                        */
  String post;					   /*                        */
  DB   db;					   /*                        */
{ static StringBuffer *sb = NULL;		   /*                        */
						   /*                        */
  DebugPrint1("expand_rhs");			   /*                        */
  if ( sb == NULL && (sb = sbopen()) == NULL )	   /*                        */
  { OUT_OF_MEMORY("string expansion");}		   /*                        */
 						   /*                        */
  DebugPrint2("Expanding ",s);			   /*                        */
 						   /*                        */
  sbrewind(sb);					   /*                        */
  expand__(s, sb, pre, post, db);		   /*                        */
  return (String)sbflush(sb);			   /*                        */
}						   /*------------------------*/

#define PUTS(S,SB) (void)sbputs((char*)S,SB)
#define PUTC(C,SB) (void)sbputchar(C,SB)

/*-----------------------------------------------------------------------------
** Function:	expand__()
** Purpose:	Wrapper for expand().
**		Things have to be cleaned up afterwards.
** Arguments:
**	s
**	sb
**	q_open
**	q_close
**	db
** Returns:	nothing
**___________________________________________________			     */
static void expand__(s, sb, q_open, q_close, db)   /*                        */
  register String s;				   /*                        */
  StringBuffer   *sb;				   /*                        */
  String         q_open;			   /*                        */
  String         q_close;			   /*                        */
  DB		 db;				   /*                        */
{						   /*                        */
  if ( ! expand(s,sb,TRUE,TRUE,q_open,q_close,db) )/*                        */
  { PUTS(q_close, sb); }			   /*                        */
  else if ( sbtell(sb) == 0 )			   /*                        */
  { PUTS(q_open, sb);			   	   /*                        */
    PUTS(q_close, sb);			   	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	expand()
** Purpose:	
**		
**
** Arguments:
**	s	String to apply expansion to.
**	sb	String buffer which will receive the output.
**	brace	Boolean. Determine if braces should be used.
**		The strings of the braces are in q_open and q_close.
**	first	In multi parts determine if this is the first part.
**	q_open	Open delimiter. This is an open brace or a double quote.
**	q_close	Close delimiter. This is a close brace or a double quote.
** Returns:	
**___________________________________________________			     */
static int expand(s, sb, brace, first, q_open, q_close, db)/*                */
  register String s;				   /* specification          */
  StringBuffer   *sb;				   /* output device          */
  int            brace;				   /* is a brace needed?     */
  int            first;				   /* is this the first part?*/
  String         q_open;			   /* open delimiter         */
  String         q_close;			   /* close delimiter        */
  DB		 db;				   /*                        */
{						   /*                        */
  while ( *s )					   /*                        */
  { 						   /*                        */
    switch ( *s )				   /*                        */
    { case '\0': break;				   /* Just in case.          */
      case '"':					   /* Start a string part.   */
        DebugPrint2("Start String:", s);	   /*                        */
        if ( *++s == '"' ) { ++s; break; }	   /* Ignore the empty string*/
        if ( brace ) 				   /*                        */
	{ if ( !first ) { PUTS(" # ",sb); }	   /*                        */
	  PUTS(q_open,sb); brace = FALSE;  	   /*                        */
        }					   /*                        */
        first = FALSE;				   /*                        */
 						   /*                        */
        for ( ; *s && *s != '"'; ++s )		   /* Until the end is found */
	{ PUTC(*s,sb);		   		   /*  transfer character.   */
	  if ( *s == '\\' && *(s+1) ) 		   /*  \ is for quoting.     */
	  { ++s; PUTC(*s,sb); }	   		   /*                        */
	}					   /*                        */
        if ( *s ) ++s;				   /* Advance if not end     */
        break;					   /*                        */
      case '{': 				   /* Start a block.         */
        DebugPrint2("Start block:",s);		   /*                        */
        if ( *++s == '}' ) { ++s; break; }	   /* Ignore empty block.    */
        if ( brace ) 				   /*                        */
	{ if ( !first ) { PUTS(" # ",sb); }	   /*                        */
	  PUTS(q_open,sb); brace = FALSE;  	   /*                        */
        }					   /*                        */
        first = FALSE;				   /*                        */
 						   /*                        */
        { register int level = 1;		   /* Initialize brace count */
	  for ( ; *s && level > 0; ++s )	   /* Until level 0 or end   */
	  { switch ( *s )			   /*                        */
	    { case '\\':			   /* \ is for quoting.      */
		PUTC(*s,sb);		   	   /*                        */
		if ( *++s ) { PUTC(*s,sb); }	   /*                        */
		break;				   /*                        */
	      case '{':				   /*                        */
		++level;			   /*                        */
		PUTC(*s,sb);			   /*                        */
		break;		   		   /*                        */
	      case '}': 			   /*                        */
		if ( --level > 0 ) PUTC(*s,sb);	   /*                        */
		break;		   		   /*                        */
	      default:				   /*                        */
		PUTC(*s,sb);			   /*                        */
	    }					   /*                        */
	  }					   /*                        */
	}					   /*                        */
        break;					   /*                        */
      case '#': ++s;  break;			   /* Silently assume #.     */
      case '0': case '1': case '2': case '3': case '4':/* Start a number     */
      case '5': case '6': case '7': case '8': case '9':/*                    */
        DebugPrint2("Start number:",s);		   /*                        */
        					   /*                        */
        if ( brace ) 				   /*                        */
	{ if ( !first ) { PUTS(" # ",sb); }	   /*                        */
	  PUTS(q_open,sb); brace = FALSE;  	   /*                        */
        }					   /*                        */
        first = FALSE;				   /*                        */
 						   /*                        */
        do					   /*                        */
	{ PUTC(*s,sb);		   		   /*                        */
	  ++s;					   /*                        */
	} while ( is_digit(*s) );		   /*                        */
        break;        				   /*                        */
      default:					   /*                        */
        if ( is_space(*s) ) ++s;		   /* Ignore spaces.         */
        else if (!is_allowed(*s))		   /*                        */
	{ PUTC(*s, sb);				   /*                        */
	  s++;					   /*                        */
	}					   /*                        */
        else		   			   /* Only macros are left.  */
	{ String sym = (String)s;	   	   /*                        */
	  String val;			   	   /*                        */
	  Uchar  c;			   	   /*                        */
 						   /*                        */
          DebugPrint2("Start symbol: ",s);	   /*                        */
	  while ( is_allowed(*s) ) ++s;		   /*                        */
	  c = *s; *s = '\0';			   /*                        */
	  { String sym_copy =			   /*                        */
	      (String)malloc(strlen((char*)sym)+1);/* Copy of sym            */
	    if (sym_copy == StringNULL )	   /* Allocate memory        */
	    { OUT_OF_MEMORY("expand string"); }	   /* Upon failure exit.     */
	    (void)strcpy((char*)sym_copy,(char*)sym);/* Save sym             */
	    *s = c;				   /* Restore end mark       */
	    sym = symbol(sym_copy);		   /* Intern the symbol.     */
	    free((char*)sym_copy);		   /* Free the temp. memory  */
	  }					   /*                        */
	  val = db_string(db,sym,1);	   	   /*                        */
	  if ( val )			   	   /*                        */
	  { brace = expand(val,sb,brace,first,q_open,q_close,db); }/*        */
	  else					   /*                        */
	  { if ( !brace ) PUTS(q_close,sb);	   /*                        */
	    if ( !first ) PUTS(" # ",sb);  	   /*                        */
	    PUTS(sym,sb);		   	   /*                        */
	    brace = TRUE;			   /*                        */
	    first = FALSE;			   /*                        */
	  }					   /*                        */
	}	   				   /*                        */
    }    					   /*                        */
  }						   /*                        */
  return brace;					   /*                        */
}						   /*------------------------*/
