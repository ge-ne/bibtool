/*** term.c ********************************************************************
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
#include <bibtool/error.h>
#include "term.h"
#include "symdef.h"

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
 Term term_true;
 Term term_false;
 Term term_mod;
 Term term_and;
 Term term_or;
 Term term_not;
 Term term_like;
 Term term_ilike;

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
