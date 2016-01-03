/*** tstack.c *****************************************************************
** 
** This file is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include "tstack.h"
#include <stdlib.h>
#include <bibtool/error.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

TStack ts_pop _ARG((TStack ts));
TStack ts_push _ARG((TStack ts, int c, Term t));
void dump_tstack _ARG((FILE* file, TStack stack));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	ts_pop()
** Type:	TStack
** Purpose:	
**		
** Arguments:
**	ts	
** Returns:	
**___________________________________________________			     */
TStack ts_pop(ts)				   /*                        */
  TStack ts;					   /*                        */
{ TStack prev = StackPrev(ts);			   /*                        */
  free((void*)ts);				   /*                        */
  return prev;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	ts_push()
** Type:	TStack
** Purpose:	
**		
** Arguments:
**	ts	
**	c	
**	t	
** Returns:	
**___________________________________________________			     */
TStack ts_push(ts, c, t)			   /*                        */
  TStack ts;					   /*                        */
  int c;					   /*                        */
  Term t;					   /*                        */
{ TStack frame = (TStack)malloc(sizeof(STStack));  /*                        */
  if (frame == StackNULL)			   /*                        */
  { OUT_OF_MEMORY("term stack"); }		   /*                        */
 						   /*                        */
  StackChar(frame) = c;			   	   /*                        */
  StackTerm(frame) = t;				   /*                        */
  StackPrev(frame) = ts;			   /*                        */
  return frame;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_tstack()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	
**	 stack	
** Returns:	nothing
**___________________________________________________			     */
void dump_tstack(file, stack)			   /*                        */
  FILE* file;					   /*                        */
  TStack stack;					   /*                        */
{						   /*                        */
  if (stack)
  { dump_tstack(file, StackPrev(stack));
    fprintf(file," %d ", StackChar(stack));
    print_term(file, StackTerm(stack));
    fprintf(file,"\n");
  } else {
    fprintf(file,"-----\n");
  }
}						   /*------------------------*/
