/*** xxx.c *****************************************************************
** 
** This file is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2017 Gerd Neugebauer
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


/*-----------------------------------------------------------------------------
** Function:	lst_has_next()
** Type:	int
** Purpose:	
**		
** Arguments:
**	iterator	the iterator
** Returns:	
**___________________________________________________			     */
static int lst_has_next(iterator)		   /*                        */
  Iterator iterator;				   /*                        */
{						   /*                        */
  return ItState(iterator) != NULL;
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	lst_next()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	iterator	the iterator
** Returns:	
**___________________________________________________			     */
static Term lst_next(iterator)			   /*                        */
  Iterator iterator;				   /*                        */
{ Term t = Car((Term)ItState(iterator));
  ItState(iterator) = Cdr((Term)ItState(iterator));
  return t;
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	lst_finish()
** Type:	void
** Purpose:	
**		
** Arguments:
**	iterator	the iterator
** Returns:	nothing
**___________________________________________________			     */
static void lst_finish(iterator)		   /*                        */
  Iterator iterator;				   /*                        */
{
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_first()
** Type:	Record
** Purpose:	
**		
** Arguments:
**	db	the database
** Returns:	
**___________________________________________________			     */
static Record rec_first(db)			   /*                        */
  DB db;					   /*                        */
{ Record rec = DBnormal(db);			   /*                        */
  if (rec == RecordNULL) return rec;	   	   /*                        */
 						   /*                        */
  while (PrevRecord(rec) != RecordNULL)   	   /*                        */
  { rec = PrevRecord(rec); }	   		   /*                        */
 						   /*                        */
  return rec;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_has_next()
** Type:	int
** Purpose:	
**		
** Arguments:
**	iterator	the iterator
** Returns:	
**___________________________________________________			     */
static int rec_has_next(iterator)		   /*                        */
  Iterator iterator;				   /*                        */
{						   /*                        */
  return ItState(iterator) != NULL;
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_next()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	iterator	the iterator
** Returns:	
**___________________________________________________			     */
static Term rec_next(iterator)			   /*                        */
  Iterator iterator;				   /*                        */
{ Term t     = new_term(L_RECORD,NIL,NIL); 
  Record rec = TRecord(t) = (Record)ItState(iterator);
  while (rec)
  { rec = NextRecord(rec);
    if (rec == NULL || !RecordIsDELETED(rec)) break;
  }						   /*                        */
  ItState(iterator) = rec;			   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_finish()
** Type:	void
** Purpose:	
**		
** Arguments:
**	iterator	the iterator
** Returns:	nothing
**___________________________________________________			     */
static void rec_finish(iterator)		   /*                        */
  Iterator iterator;				   /*                        */
{
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_iterator()
** Type:	Iterator
** Purpose:	
**		
** Arguments:
**	t	the term to iterate over
** Returns:	
**___________________________________________________			     */
Iterator get_iterator(t)			   /*                        */
  Term t;					   /*                        */
{ Iterator iterator = (Iterator)malloc(sizeof(SIterator));/*                 */
 						   /*                        */
  if (iterator == NULL) return NULL;		   /*                        */
 						   /*                        */
  if (t	== NIL || TType(t) == L_CONS) {		   /*                        */
    ItState(iterator)   = t;			   /*                        */
    ItHasNext(iterator) = lst_has_next;		   /*                        */
    ItNext(iterator)    = lst_next;		   /*                        */
    ItFinish(iterator)  = lst_finish;		   /*                        */
  } else if (TType(t) == L_DB) {		   /*                        */
    ItState(iterator)   = rec_first(TDB(t));	   /*                        */
    ItHasNext(iterator) = rec_has_next;		   /*                        */
    ItNext(iterator)    = rec_next;		   /*                        */
    ItFinish(iterator)  = rec_finish;		   /*                        */
  } else {					   /*                        */
    free(iterator);				   /*                        */
    return NULL;				   /*                        */
  }						   /*                        */
 						   /*                        */
  return iterator;				   /*                        */
}						   /*------------------------*/



