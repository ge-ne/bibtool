/*** symdef.c ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <bibtool/error.h>
#include <ctype.h>
#include "term.h"
#include "binding.h"

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
static void p_sym_name(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (t == NIL)					   /*                        */
  { fputs("??",file);				   /*                        */
    return;					   /*                        */
  }						   /*                        */
  print_quoted(file, SymName(TSym(t)));		   /*                        */
  if (Car(t)) { print_term(Car(t)); }	   	   /*                        */
  if (Cdr(t)) { print_term(Cdr(t)); }		   /*                        */
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
static void p_term_num(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  fprintf(file, "%ld", TNumber(t));		   /*                        */
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
static void p_term_str(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  fputc('"', file);				   /*                        */
  print_quoted(file, TString(t));		   /*                        */
  fputc('"', file);				   /*                        */
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
static void p_term_block(file, t)		   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  fputc('{', file);				   /*                        */
  fputs((char*)TString(t), file);		   /*                        */
  fputc('}', file);				   /*                        */
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
static void p_term_field(file, t)		   /*                        */
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
  if (q) fputc('`', file);			   /*                        */
  print_quoted(file, TString(t));		   /*                        */
  if (q) fputc('`', file);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_builtin()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	nothing
**___________________________________________________			     */
static void p_rsc(file, t)		   	   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (Cdr(t))
  { fputc('(', file);			   	   /*                        */
    fputs((char*)TString(t), file);		   /*                        */
    fputc(' ', file);			   	   /*                        */
    print_term(file, Cdr(t));	   		   /*                        */
    fputc(')', file);			   	   /*                        */
  } else {
    fputs((char*)TString(t), file);		   /*                        */
  }
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
static void p_cons(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{ fputc('(', file);				   /*                        */
  print_term(file, Car(t));			   /*                        */
  while (Cdr(t))				   /*                        */
  { t = Cdr(t);				   	   /*                        */
    if (t && TSym(t) == sym_cons)		   /*                        */
    { fputc(' ', file);			   	   /*                        */
      print_term(file, Car(t));		   	   /*                        */
    } else					   /*                        */
    { fputs(" . ", file);			   /*                        */
      print_term(file, Cdr(t));		   	   /*                        */
      break;					   /*                        */
    }						   /*                        */
  }						   /*                        */
  fputc(')', file);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sym_def()
** Type:	static SymDef
** Purpose:	
**		
** Arguments:
**	name	
**	op	
**	term	
**	print	
** Returns:	
**___________________________________________________			     */
static SymDef sym_def(name, op, term, print) 	   /*                        */
  String name;					   /*                        */
  int op;					   /*                        */
  Term term;					   /*                        */
  void (*print)_ARG((FILE*, Term));		   /*                        */
{						   /*                        */
  SymDef sym    = (SymDef) malloc(sizeof(SSymDef));/*                        */
  if (sym == SymDefNull) OUT_OF_MEMORY("symdef");  /*                        */
  SymName(sym)  = name;				   /*                        */
  SymOp(sym)    = op;				   /*                        */
  SymTerm(sym)  = term;				   /*                        */
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
  char * s;					   /*                        */
 						   /*                        */
#define Declare(T,N,V) N = V
#include "symdef.h"

#define InitSymChar(S,OP)				       \
  sym_char[i] = sym_def(S, OP, NIL, p_sym_name);	       \
  SymTerm(sym_char[i]) = new_term(sym_char[i], NIL, NIL)
 						   /*                        */
  for (i = 1; i < 256; i++) {			   /*                        */
 						   /*                        */
    switch (i)			   		   /*                        */
    { case ';':	InitSymChar( ";",     0); break;   /*                        */
      case '=':	InitSymChar( "=",    30); break;   /*                        */
      case '<':	InitSymChar( "<",    30); break;   /*                        */
      case '>':	InitSymChar( ">",    30); break;   /*                        */
      case '#':	InitSymChar( "#",    40); break;   /*                        */
      case '+':	InitSymChar( "+",    50); break;   /*                        */
      case '-':	InitSymChar( "-",    52); break;   /*                        */
      case '*':	InitSymChar( "*",    60); break;   /*                        */
      case '/':	InitSymChar( "/",    60); break;   /*                        */
      case '%':	InitSymChar("mod",   60); break;   /*                        */
      case '\'':InitSymChar("quote", 71); break;   /*                        */
      case '"':					   /*                        */
      case '_':					   /*                        */
      case '@':					   /*                        */
      case '$':					   /*                        */
      case '.':					   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	if (isalnum(i) || isspace(i)) break;	   /*                        */
 						   /*                        */
	s     = malloc(2 * sizeof(char));	   /*                        */
	if (s == NULL) OUT_OF_MEMORY("symdef");	   /*                        */
	*s     = (char)i;			   /*                        */
	*(s+1) = '\0';				   /*                        */
	sym_char[i] = sym_def(s,		   /*                        */
			      0,		   /*                        */
			      NIL,		   /*                        */
			      p_sym_name); 	   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  term_eof	 = new_term(NULL,      NIL, NIL);  /*                        */
  term_true  	 = new_term(sym_true,  NIL, NIL);  /*                        */
  term_false	 = new_term(sym_false, NIL, NIL);  /*                        */
 						   /*                        */
  term_mod	 = new_term(sym_mod,   NIL, NIL);  /*                        */
  term_and	 = new_term(sym_and,   NIL, NIL);  /*                        */
  term_or	 = new_term(sym_or,    NIL, NIL);  /*                        */
  term_not	 = new_term(sym_not,   NIL, NIL);  /*                        */
  term_like	 = new_term(sym_like,  NIL, NIL);  /*                        */
  term_ilike	 = new_term(sym_ilike, NIL, NIL);  /*                        */
 						   /*                        */
  SymTerm(sym_and)   = term_and;		   /*                        */
  SymTerm(sym_or)    = term_or;			   /*                        */
  SymTerm(sym_not)   = term_not;		   /*                        */
  SymTerm(sym_like)  = term_like;		   /*                        */
  SymTerm(sym_ilike) = term_ilike;		   /*                        */
  SymTerm(sym_mod)   = term_mod;		   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
