/*** tstack.h *****************************************************************
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

#include "term.h"

/*-----------------------------------------------------------------------------
** Typedef:	STStack
** Purpose:	
**		
**		
**___________________________________________________			     */
typedef struct T_STACK {			   /*                        */
  SymDef sym;					   /*                        */
  Term term;					   /*                        */
  struct T_STACK * prev;			   /*                        */
} STStack, *TStack;				   /*------------------------*/

#define StackNULL	(TStack)NULL
#define StackSym(TS)	((TS)->sym)
#define StackTerm(TS)	((TS)->term)
#define StackPrev(TS)	((TS)->prev)

#define StackSymIs(STACK, C) SymIs(StackSym(STACK), C)
#define StackSymIsNumber(STACK) SymIsNumber(StackSym(STACK))
#define StackSymIsOperator(STACK) SymIsOperator(StackSym(STACK))
#define StackSymOp(STACK) SymOp(StackSym(STACK))

/*---------------------------------------------------------------------------*/

extern TStack ts_pop _ARG((TStack ts));
extern TStack ts_push _ARG((TStack ts, SymDef sym, Term t));

/*---------------------------------------------------------------------------*/
