/******************************************************************************
** $Id: t_stack.h,v 0.00 2015/12/25 23:57:04 gene Exp $
*******************************************************************************
** Author: Gerd Neugebauer
**===========================================================================*/

#include "term.h"

typedef struct T_STACK {
  SymDef sym;
  Term term;
  struct T_STACK * prev;
} STStack, *TStack;

#define TStackNULL	(TStack)NULL
#define TSSym(TS)	((TS)->sym)
#define TSTerm(TS)	((TS)->term)
#define TSPrev(TS)	((TS)->prev)

/*---------------------------------------------------------------------------*/

extern TStack ts_pop _ARG((TStack ts));
extern TStack ts_push _ARG((TStack ts, SymDef sym, Term t));

/*---------------------------------------------------------------------------*/
