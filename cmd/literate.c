/*** xxx.c *****************************************************************
** 
** This file is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "term.h"
#include "literate.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


static int lst_has_next(iterator)
  Iterator iterator;
{
  return ItState(iterator) != NULL;
}

static Term lst_next(iterator)
  Iterator iterator;
{ Term t = Car((Term)ItState(iterator));
  ItState(iterator) = Cdr((Term)ItState(iterator));
  return t;
}

static void lst_finish(iterator)
  Iterator iterator;
{
}


/*-----------------------------------------------------------------------------
** Function:	get_iterator()
** Type:	Iterator
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	
**___________________________________________________			     */
Iterator get_iterator(t)			   /*                        */
  Term t;					   /*                        */
{ Iterator iterator = (Iterator)malloc(sizeof(SIterator));/*                 */

  if (iterator == NULL) return NULL;		   /*                        */

  if (t	== NIL || TType(t) == L_CONS) {
    ItState(iterator)   = t;
    ItHasNext(iterator) = lst_has_next;
    ItNext(iterator)    = lst_next;
    ItFinish(iterator)  = lst_finish;
  } else {					   /*                        */
    free(iterator);				   /*                        */
    return NULL;				   /*                        */
  }						   /*                        */
 						   /*                        */
  return iterator;				   /*                        */
}						   /*------------------------*/



