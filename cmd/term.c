/*** term.c ********************************************************************
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
#include "term.h"
#include "lcore.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

 Term new_t_string();
 Term new_term();
 Term new_term_num();
 void free_term();
 void print_term();

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


 Term term_eof;

 static Term terms = NIL;

/*-----------------------------------------------------------------------------
** Function:	new_term()
** Type:	Term
** Purpose:	Allocate a new term and initialize it.
**		
** Arguments:
**	sym	the symdef
**	car	the car
**	cdr	the cdr
** Returns:	
**___________________________________________________			     */
Term new_term(sym, car, cdr)			   /*                        */
  SymDef sym;				   	   /*                        */
  Term car;					   /*                        */
  Term cdr;					   /*                        */
{ register Term t = terms;			   /*                        */
  						   /*                        */
  if (t) { terms = Car(t); }			   /*                        */
  else						   /*                        */
  { t = (Term)malloc(sizeof(STerm));		   /*                        */
    if (t == NIL) OUT_OF_MEMORY("term");	   /*                        */
  }	   					   /*                        */
  TSym(t) = sym;			   	   /*                        */
  Car(t)  = car;				   /*                        */
  Cdr(t)  = cdr;				   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_term_num()
** Type:	Term
** Purpose:	Allocate a new term and initialize it as number.
**		
** Arguments:
**	n	the numeric value
** Returns:	
**___________________________________________________			     */
Term new_term_num(n)				   /*                        */
  long n;					   /*                        */
{ register Term t = terms;			   /*                        */
  						   /*                        */
  if (t) { terms = Car(t); }			   /*                        */
  else						   /*                        */
  { t = (Term)malloc(sizeof(STerm));		   /*                        */
    if (t == NIL) OUT_OF_MEMORY("term");	   /*                        */
  }	   					   /*                        */
  TSym(t)    = sym_number;			   /*                        */
  TNumber(t) = n;				   /*                        */
  Cdr(t)     = NIL;				   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_t_string()
** Type:	Term
** Purpose:	Allocate a new term and initialize it as string type.
**		
** Arguments:
**	sym	the symdef
**	s	the string value, i.e. a symbol
** Returns:	
**___________________________________________________			     */
Term new_t_string(sym, s)		   	   /*                        */
  SymDef sym;					   /*                        */
  String s;					   /*                        */
{ register Term t = terms;			   /*                        */
  						   /*                        */
  if (t) { terms = Car(t); }			   /*                        */
  else						   /*                        */
  { t = (Term)malloc(sizeof(STerm));		   /*                        */
    if (t == NIL) OUT_OF_MEMORY("term");	   /*                        */
  }	   					   /*                        */
  TSym(t)    = sym;			   	   /*                        */
  TString(t) = s;				   /*                        */
  Cdr(t)     = NIL;			   	   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_term()
** Type:	void
** Purpose:	Free the memory of a term and arrange for reuse.
**		The term odes are linked into the |terms| list to be reused.
**		This happens only for those term nodes which are not locked.
**		
** Arguments:
**	t	
** Returns:	nothing
**___________________________________________________			     */
void free_term(t)				   /*                        */
  register Term t;				   /*                        */
{ Term cdr;					   /*                        */
 						   /*                        */
  if (t == NIL) return;				   /*                        */
 						   /*                        */
  cdr = Cdr(t);					   /*                        */
 						   /*                        */
#ifdef TODO
  switch (TermOp(t))				   /*                        */
  { case -10:					   /* list type              */
      free_term(Car(t));			   /*                        */
      break;					   /*                        */
    case -11:					   /* number type            */
    case -12:					   /* string type            */
      break;					   /*                        */
    default:					   /* locked                 */
      return;					   /*                        */
  }						   /*                        */
#endif
  Car(t) = terms;				   /*                        */
  terms = t;					   /*                        */
 						   /*                        */
  if (cdr)					   /*                        */
  { free_term(cdr);			   	   /*                        */
    Cdr(t) = NIL;				   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	print_term()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	
**	t	
** Returns:	nothing
**___________________________________________________			     */
void print_term(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (t == NIL) {				   /*                        */
    fputs("nil", file);				   /*                        */
    return;					   /*                        */
  }						   /*                        */
  if (TSym(t) != NULL && SymPrint(TSym(t)) != NULL) {/*                      */
    SymPrint(TSym(t))(file, t);			   /*                        */
  } else {					   /*                        */
    fputs("???", file);				   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	symdef()
** Type:	SymDef
** Purpose:	
**		
** Arguments:
**	name	
**	op	
**	term	
**	print	
** Returns:	
**___________________________________________________			     */
SymDef symdef(name, op, term, print) 	   	   /*                        */
  String name;					   /*                        */
  int op;					   /*                        */
  Term term;					   /*                        */
  void (*print)_ARG((FILE*, Term));		   /*                        */
{						   /*                        */
  SymDef sym    = (SymDef) malloc(sizeof(SSymDef));/*                        */
  if (sym == SymDefNULL) OUT_OF_MEMORY("symdef");  /*                        */
  SymName(sym)  = name;				   /*                        */
  SymOp(sym)    = op;				   /*                        */
  SymHash(sym)  = hash(name);			   /*                        */
  SymTerm(sym)  = term;				   /*                        */
  SymValue(sym) = NIL;				   /*                        */
  SymPrint(sym) = print;			   /*                        */
  SymGet(sym)   = NULL;			   	   /*                        */
  SymSet(sym)   = NULL;			   	   /*                        */
  return sym;					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
