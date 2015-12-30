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

#define StackNULL	(TStack)NULL
#define StackSym(TS)	((TS)->sym)
#define StackTerm(TS)	((TS)->term)
#define StackPrev(TS)	((TS)->prev)

#define StackSymIs(STACK, C) SymIs(StackSym(STACK), C)
#define StackSymOp(STACK) SymOp(StackSym(STACK))

/*---------------------------------------------------------------------------*/

extern TStack ts_pop _ARG((TStack ts));
extern TStack ts_push _ARG((TStack ts, SymDef sym, Term t));

/*---------------------------------------------------------------------------*/
