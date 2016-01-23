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

 Term new_term _ARG((short int type, Term car, Term cdr ));
 Term new_term_num _ARG((long value));
 Term new_t_string _ARG((short int type, unsigned char* s));
 void free_term _ARG((Term term));
 void print_term _ARG((FILE* file, Term term));

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
Term new_term(type, car, cdr)			   /*                        */
  short int type;				   /*                        */
  Term car;					   /*                        */
  Term cdr;					   /*                        */
{ register Term t = terms;			   /*                        */
  						   /*                        */
  if (t) { terms = Car(t); }			   /*                        */
  else						   /*                        */
  { t = (Term)malloc(sizeof(STerm));		   /*                        */
    if (t == NIL) OUT_OF_MEMORY("term");	   /*                        */
  }	   					   /*                        */
  TermOp(t) = type;			   	   /*                        */
  Car(t)    = car;				   /*                        */
  Cdr(t)    = cdr;				   /*                        */
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
  TermOp(t)  = L_NUMBER;			   /*                        */
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
Term new_t_string(type, s)		   	   /*                        */
  short int type;				   /*                        */
  String s;					   /*                        */
{ register Term t = terms;			   /*                        */
  						   /*                        */
  if (t) { terms = Car(t); }			   /*                        */
  else						   /*                        */
  { t = (Term)malloc(sizeof(STerm));		   /*                        */
    if (t == NIL) OUT_OF_MEMORY("term");	   /*                        */
  }	   					   /*                        */
  TermOp(t)  = type;			   	   /*                        */
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
** Function:	prt_field()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
void prt_field(file, t)		   	   /*                        */
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
** Function:	prt_args()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	nothing
**___________________________________________________			     */
static void prt_args(file, term)		   /*                        */
  FILE * file;					   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  if (term == NIL) return;			   /*                        */
 						   /*                        */
  print_term(file, Car(term));		   	   /*                        */
  for (term = Cdr(term); term; term= Cdr(term))	   /*                        */
  { fputs(" ", file);			   	   /*                        */
    print_term(file, Car(term));		   /*                        */
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
void print_term(file, term)			   /*                        */
  FILE * file;					   /*                        */
  Term term;					   /*                        */
{ char * key;					   /*                        */
  if (term == NIL) {				   /*                        */
    fputs("nil", file);				   /*                        */
    return;					   /*                        */
  }						   /*                        */
 						   /*                        */
  switch (TermOp(term))				   /*                        */
  { case L_STRING:				   /*                        */
      fputc('"', file);	   			   /*                        */
      print_quoted(file, TString(term));	   /*                        */
      fputc('"', file);	   			   /*                        */
      return;					   /*                        */
    case L_BLOCK:				   /*                        */
      fputc('{', file);	   			   /*                        */
      fputs((char*)TString(term), file);	   /*                        */
      fputc('}', file);	   			   /*                        */
      return;					   /*                        */
    case L_FIELD:				   /*                        */
      prt_field(file, term);			   /*                        */
      return;					   /*                        */
    case L_NUMBER:				   /*                        */
      fprintf(file, "%ld", TNumber(term));	   /*                        */
      return;					   /*                        */
    case L_TRUE:				   /*                        */
      fputs("true", file);			   /*                        */
      return;					   /*                        */
    case L_FALSE:				   /*                        */
      fputs("false", file);			   /*                        */
      return;					   /*                        */
    case L_LIST:				   /*                        */
      fputs("[", file);			   	   /*                        */
      prt_args(file, term);		   	   /*                        */
      fputs("]", file);			   	   /*                        */
      return;					   /*                        */
    case 0:					   /*                        */
    case EOF:					   /*                        */
      return;	   			   	   /*                        */
    case L_UMINUS:				   /*                        */
      fputs("-", file);			   	   /*                        */
      print_term(file, Cadr(term));		   /*                        */
      return;					   /*                        */
    case L_QUOTE:    key = "'";		     break;/*                        */
    case L_FUNCTION: key = (char*)TString(term);break;/*                     */
    case L_MINUS:    key = " - ";	     break;/*                        */
    case L_PLUS:     key = " + ";	     break;/*                        */
    case L_TIMES:    key = " * ";	     break;/*                        */
    case L_DIV:      key = " / ";	     break;/*                        */
    case L_MOD:      key = " mod ";          break;/*                        */
    case L_SET:      key = " = ";	     break;/*                        */
    case L_LIKE:     key = " like ";         break;/*                        */
    case L_ILIKE:    key = " ilike ";        break;/*                        */
    case L_EQ:       key = " == ";           break;/*                        */
    case L_NE:       key = " != ";           break;/*                        */
    case L_GT:       key = " > ";	     break;/*                        */
    case L_GE:       key = " >= ";           break;/*                        */
    case L_LT:       key = " < ";	     break;/*                        */
    case L_LE:       key = " <= ";           break;/*                        */
    case L_NOT:      key = "not";            break;/*                        */
    case L_AND:      key = " and ";          break;/*                        */
    case L_OR:       key = " or ";           break;/*                        */
    default:					   /*                        */
      fprintf(file, "?0x%x?", TermOp(term));	   /*                        */
      return;					   /*                        */
  }						   /*                        */
 						   /*                        */
  if (L_IS_BINARY(TermOp(term)) )		   /*                        */
  { term = Cdr(term);				   /*                        */
    fputc('(', file);				   /*                        */
    print_term(file, Car(term));		   /*                        */
    fputs(key, file);		   		   /*                        */
    print_term(file, Cadr(term));		   /*                        */
  } else {					   /*                        */
    fputs(key, file);		   		   /*                        */
    fputc('(', file);				   /*                        */
    if (term) prt_args(file, Cdr(term));	   /*                        */
  }						   /*                        */
  fputc(')', file);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	list_length()
** Type:	int
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	
**___________________________________________________			     */
int list_length(t)				   /*                        */
  Term t;					   /*                        */
{ int i = 0;					   /*                        */
  while (t && TermIsCons(t))			   /*                        */
  { i++;					   /*                        */
    t = Cdr(t);					   /*                        */
  }						   /*                        */
  return i;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	symdef()
** Type:	SymDef
** Purpose:	
**		
** Arguments:
**	name	
**	op	
**	get	
** Returns:	
**___________________________________________________			     */
SymDef symdef(name, op, get)	   	   	   /*                        */
  String name;					   /*                        */
  int op;					   /*                        */
  Term (*get)_ARG((Binding, Term));		   /*                        */
{						   /*                        */
  SymDef sym    = (SymDef) malloc(sizeof(SSymDef));/*                        */
  if (sym == SymDefNULL) OUT_OF_MEMORY("symdef");  /*                        */
  SymName(sym)  = name;				   /*                        */
  SymOp(sym)    = op;				   /*                        */
  SymHash(sym)  = hash(name);			   /*                        */
  SymTerm(sym)  = NIL;				   /*                        */
  SymValue(sym) = NIL;				   /*                        */
  SymGet(sym)   = get;			   	   /*                        */
  SymSet(sym)   = NULL;			   	   /*                        */
  return sym;					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
