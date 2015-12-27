/*** xxx.c *****************************************************************
** 
** This file is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include "t_stack.h"
#include <stdlib.h>
#include <bibtool/error.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

TStack ts_pop _ARG((TStack ts));
TStack ts_push _ARG((TStack ts, SymDef sym, Term t));

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
{ TStack prev = TSPrev(ts);			   /*                        */
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
**	 sym	
**	 t	
** Returns:	
**___________________________________________________			     */
TStack ts_push(ts, sym, t)			   /*                        */
  TStack ts;					   /*                        */
  SymDef sym;					   /*                        */
  Term t;					   /*                        */
{ TStack frame = (TStack)malloc(sizeof(STStack));  /*                        */
  if (frame == NULL)				   /*                        */
  { OUT_OF_MEMORY("term stack"); }		   /*                        */

  frame->sym = sym;				   /*                        */
  frame->term = t;				   /*                        */
  frame->prev = ts;				   /*                        */

  return frame;					   /*                        */
}						   /*------------------------*/

