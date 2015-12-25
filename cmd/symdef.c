/*** symdef.c ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "term.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


#define Declare(T,N,V) T N
#include "symdef.h"

/*-----------------------------------------------------------------------------
** Function:	print_quoted()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	file	
**	 s	
** Returns:	nothing
**___________________________________________________			     */
static void print_quoted(file, s)		   /*                        */
  FILE * file;					   /*                        */
  String s;					   /*                        */
{						   /*                        */
  for (; *s; s++)				   /*                        */
  { switch (*s)					   /*                        */
    { case '\n':				   /*                        */
	fputs("\\n", file);			   /*                        */
	break;					   /*                        */
      case '\r':				   /*                        */
	fputs("\\r", file);			   /*                        */
	break;					   /*                        */
      case '\b':				   /*                        */
	fputs("\\b", file);			   /*                        */
	break;					   /*                        */
      case '\f':				   /*                        */
	fputs("\\f", file);			   /*                        */
	break;					   /*                        */
      case '"':					   /*                        */
	fputs("\\\"", file);			   /*                        */
	break;					   /*                        */
      case '\'':				   /*                        */
	fputs("\\'", file);			   /*                        */
	break;					   /*                        */
      case '\\':				   /*                        */
	fputs("\\\\", file);			   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	fputc((char)*s, file);			   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_sym_name()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
static int p_sym_name(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  print_quoted(file, SymName(TSym(t)));		   /*                        */
  if (TTerm(t)) { print_term(TTerm(t)); }	   /*                        */
  if (TArg(t)) { print_term(TArg(t)); }		   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_term_num()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
static int p_term_num(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  fprintf(file, "%ld", TNumber(t));		   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_term_str()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
static int p_term_str(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  fputc('"', file);				   /*                        */
  print_quoted(file, TString(t));		   /*                        */
  fputc('"', file);				   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_term_field()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
static int p_term_field(file, t)		   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{ int q	 = 0;					   /*                        */
  String s = TString(t);			   /*                        */
  if (*s >= '0' && *s <= '9') {			   /*                        */
    q = 1;					   /*                        */
  } else {					   /*                        */
    for (; *s; s++)				   /*                        */
    { if (!(   (*s >='a' && *s <='z') 		   /*                        */
	    || (*s >='A' && *s <='Z')		   /*                        */
	    || (*s >='0' && *s <='9')		   /*                        */
	    || *s == '@'			   /*                        */
	    || *s == '$'			   /*                        */
	    || *s == '_'			   /*                        */
	    || *s == '.'))			   /*                        */
      { q = 1;					   /*                        */
	break;					   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
  if (q) fputc('\'', file);			   /*                        */
  print_quoted(file, TString(t));		   /*                        */
  if (q) fputc('\'', file);			   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_cons()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
static int p_cons(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{ fputc('(', file);				   /*                        */
  print_term(file, TTerm(t));			   /*                        */
  while (TArg(t))				   /*                        */
  { t = TArg(t);				   /*                        */
    if (t && TSym(t) == sym_cons)		   /*                        */
    { fputc(' ', file);				   /*                        */
      print_term(file, TTerm(t));		   /*                        */
    } else					   /*                        */
    { fputs(" . ", file);			   /*                        */
      print_term(file, TArg(t));		   /*                        */
      break;					   /*                        */
    }						   /*                        */
  }						   /*                        */
  fputc(')', file);				   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sym_def()
** Type:	static SymDef
** Purpose:	
**		
** Arguments:
**	name	
**	 parse	
** Returns:	
**___________________________________________________			     */
static SymDef sym_def(name, op, parse, print)	   /*                        */
  String name;					   /*                        */
  int op;					   /*                        */
  Term (*parse)_ARG((FILE*));			   /*                        */
  int (*print)_ARG((FILE*, Term));		   /*                        */
{						   /*                        */
  SymDef sym    = (SymDef) malloc(sizeof(SSymDef));/*                        */
  SymName(sym)  = name;				   /*                        */
  SymOp(sym)    = op;				   /*                        */
  SymValue(sym) = 0L;				   /*                        */
  SymParse(sym) = parse;			   /*                        */
  SymPrint(sym) = print;			   /*                        */
  return sym;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	init_symdef()
** Type:	void
** Purpose:	
**		
** Arguments:
**		
** Returns:	nothing
**___________________________________________________			     */
void init_symdef()				   /*                        */
{ int i;					   /*                        */
 						   /*                        */
#define Declare(T,N,V) N = V
#include "symdef.h"
 						   /*                        */
  for (i = 0; i < 256; i++) {			   /*                        */
    char * s 	= malloc(2 * sizeof(char));	   /*                        */
    *s 		= (char)i;			   /*                        */
    *(s+1)	= '\0';				   /*                        */
    sym_char[i]	= sym_def(s, 0, NULL, p_sym_name); /*                        */
  }						   /*                        */
 						   /*                        */
  term_eof	 = new_term(NULL, NIL, NIL);	   /*                        */
  term_semicolon = new_term(sym_char[';'], NIL, NIL);/*                      */
  term_true  	 = new_term(sym_true, NIL, NIL);   /*                        */
  term_false	 = new_term(sym_false, NIL, NIL);  /*                        */

  term_plus	 = new_term(sym_plus, NIL, NIL);
  term_minus	 = new_term(sym_minus, NIL, NIL);
  term_times	 = new_term(sym_times, NIL, NIL);
  term_div	 = new_term(sym_div, NIL, NIL);
  term_mod	 = new_term(sym_mod, NIL, NIL);
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
