/*** rec_sort.c ****************************************************************
** 
** This file is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <string.h>
#include <bibtool/macros.h>
#include "rec_sort.h"
#include "lcore.h"


/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	rec_gt()
** Purpose:	
**		
**
** Arguments:
**	r1
**	r2
** Returns:	
**___________________________________________________			     */
static int rec_gt(r1, r2)			   /*                        */
  Record r1;					   /*                        */
  Record r2;					   /*                        */
{ return (strcmp((char*)RecordSortkey(r1),	   /*                        */
		 (char*)RecordSortkey(r2)) < 0);   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_lt()
** Purpose:	
**		
**
** Arguments:
**	r1
**	r2
** Returns:	
**___________________________________________________			     */
static int rec_lt(r1, r2)			   /*                        */
  Record r1;					   /*                        */
  Record r2;					   /*                        */
{ return (strcmp((char*)RecordSortkey(r1),	   /*                        */
		 (char*)RecordSortkey(r2)) > 0);   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_gt_cased()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	r1	
**	r2	
** Returns:	
**___________________________________________________			     */
static int rec_gt_cased(r1, r2)			   /*                        */
  Record r1;					   /*                        */
  Record r2;					   /*                        */
{ return (strcmp((char*)get_key_name(RecordSortkey(r1)),/*                   */
		 (char*)get_key_name(RecordSortkey(r2))) < 0);/*             */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_lt_cased()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	r1	
**	r2	
** Returns:	
**___________________________________________________			     */
static int rec_lt_cased(r1, r2)			   /*                        */
  Record r1;					   /*                        */
  Record r2;					   /*                        */
{ return (strcmp((char*)get_key_name(RecordSortkey(r1)),/*                   */
		 (char*)get_key_name(RecordSortkey(r2))) > 0);/*             */
}						   /*------------------------*/

static Binding srt_bind;			   /*                        */
static Term srt_fct;				   /*                        */
static Term srt_args;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	rec_gt_fct()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	r1	
**	r2	
** Returns:	
**___________________________________________________			     */
static int rec_gt_fct(r1, r2)			   /*                        */
  Record r1;					   /*                        */
  Record r2;					   /*                        */
{ Term t;					   /*                        */
  Term t2;					   /*                        */
  long ret;					   /*                        */
 						   /*                        */
  TRecord(Car(srt_args)) = r1;
  TRecord(Cadr(srt_args)) = r2;
 						   /*                        */
  t  = funcall(srt_bind, (String)"", srt_fct, srt_args);/*                   */
  t2 = eval_num(srt_bind, t);			   /*                        */
  UnlinkTerm(t);				   /*                        */
  ret = TNumber(t2);				   /*                        */
  UnlinkTerm(t2);				   /*                        */
  return ret;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_lt_fct()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	r1	
**	r2	
** Returns:	
**___________________________________________________			     */
static int rec_lt_fct(r1, r2)			   /*                        */
  Record r1;					   /*                        */
  Record r2;					   /*                        */
{						   /*                        */
  return -rec_gt_fct(r1,r2);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_sorter()
** Type:	FunPtr
** Purpose:	
**		
** Arguments:
**	cased	
**	desc	
**	b	
**	f	
** Returns:	
**___________________________________________________			     */
FunPtr get_sorter(cased, desc, b, f)		   /*                        */
  int cased;					   /*                        */
  int desc;					   /*                        */
  Binding b;					   /*                        */
  Term f;					   /*                        */
{						   /*                        */
  if (f)					   /*                        */
  { srt_bind = b;				   /*                        */
    srt_fct = f;				   /*                        */
    if (srt_args == NIL)
    { srt_args = Cons(RecordTerm(NULL),
		      RecordTerm(NULL));
    }
    return desc ? rec_lt_fct : rec_gt_fct;	   /*                        */
  }						   /*                        */
  if (cased)					   /*                        */
  { return desc ? rec_lt_cased : rec_gt_cased; }   /*                        */
 						   /*                        */
  return desc ? rec_lt : rec_gt; 		   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
