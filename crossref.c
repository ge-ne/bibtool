/******************************************************************************
** $Id: crossref.c,v 1.6 2013-11-24 22:07:52 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2007-2013 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This module contains functions to expand crossref entries.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/error.h>
#include <bibtool/crossref.h>
#include <bibtool/symbols.h>
#include <bibtool/s_parse.h>
#include <bibtool/database.h>
#include <bibtool/sbuffer.h>
#include <bibtool/rsc.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int expand_crossref _ARG((DB db,Record rec));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Function:	expand_crossref()
** Purpose:	Expand all items inherited via a crossref.
** Arguments:
**	db	Database containing the entries.
**	rec	The record to expand
** Returns:	...
**___________________________________________________			     */
int expand_crossref(db,rec)		   	   /*                        */
  DB     db;					   /*                        */
  Record rec;					   /*                        */
{ register Uchar **hp;				   /*			     */
  register int   i;				   /*                        */
  Uchar		 *t, *s;			   /*			     */
  Record         r = rec;			   /*                        */
  int            limit = rsc_xref_limit;	   /*                        */
 						   /*                        */
  DebugPrint1("expand_crossref");		   /*                        */
 						   /*                        */
  while	( RecordIsXREF(r) && limit-->=0 )	   /*                        */
  {						   /*                        */
    for ( i=RecordFree(r), hp = RecordHeap(r); 	   /* search crossref field  */
	  i>0 && *hp != sym_crossref;		   /*			     */
	  i-=2, hp += 2 )			   /*			     */
    { }						   /*			     */
    if ( i <= 0 )				   /*			     */
    { DebugPrint1("*** No crossref found.");	   /*			     */
      return FALSE;				   /*			     */
    }						   /*			     */
    if (rec == r) { *hp = NULL; }		   /* Delete the first xref  */
    t = *++hp;					   /*                        */
    t++;				   	   /*			     */
    (void)sp_open(t);				   /* Try to extract	     */
    if ( (s = SParseSymbol(&t)) == (Uchar*)0 )     /*  the crossref as symbol*/
    { return FALSE; }				   /*			     */
						   /*			     */
    if ( (r = db_find(db,s)) == (Record)NULL )	   /*			     */
    { ERROR2("Crossref entry not found: ",(char*)s);/*			     */
      return FALSE;				   /*			     */
    }						   /*			     */
    						   /*                        */
    for ( i=RecordFree(r), hp = RecordHeap(r);	   /* visit all fields       */
	  i>0;		   			   /*			     */
	  i-=2 )			   	   /*			     */
    {						   /*                        */
      s	= *hp++;                                   /*                        */
      t	= *hp++;                                   /*                        */
      if (t != (Uchar*)0)                          /*                        */
      { provide_to_record(rec,s,t);                /*                        */
      }                                            /*                        */
    }						   /*			     */
    						   /*                        */
  }						   /*                        */
 						   /*                        */
  return FALSE;	   				   /*			     */
}						   /*------------------------*/
