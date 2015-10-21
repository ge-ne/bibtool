/*** sel.c ********************************************************************
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

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


int eval_select(t)
  Term t;
{
  if (t == TermNULL) return FALSE;

  switch(TermType(t))
  {
    case T_AND:
      return eval_select(TermTerm(t)) && eval_select(TermArg2(t);
    case T_OR:
      return eval_select(TermTerm(t)) || eval_select(TermArg2(t);
    case T_NOT:
      return ! eval_select(TermTerm(t));
    case T_EQ:
    case T_NE:
    case T_LT:
    case T_LE:
    case T_GT:
    case T_GE:
    case T_LIKE:
    case T_ILIKE:
  }

  return FALSE;
}
