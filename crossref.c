/*** crossref.c ***************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
**
** (c) 2007-2016 Gerd Neugebauer
**
** Net: gene@gerd-neugebauer.de
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2, or (at your option)
** any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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
** Returns:	FALSE
**___________________________________________________			     */
int expand_crossref(db,rec)		   	   /*                        */
  DB     db;					   /*                        */
  Record rec;					   /*                        */
{ register String *hp;				   /*			     */
  register int    i;				   /*                        */
  String	  t, s;			   	   /*			     */
  Record          r = rec;			   /*                        */
  int             limit = rsc_xref_limit;	   /*                        */
 						   /*                        */
  DebugPrint1("expand_crossref");		   /*                        */
 						   /*                        */
  while	( RecordIsXREF(r) && limit-- >= 0 )	   /*                        */
  {						   /*                        */
    for ( i = RecordFree(r), hp = RecordHeap(r);   /* search crossref field  */
	  i > 0 && *hp != sym_crossref;		   /*			     */
	  i -= 2, hp += 2 )			   /*			     */
    { }						   /*			     */
    if (i <= 0)					   /*			     */
    { DebugPrint1("*** No crossref found.");	   /*			     */
      return FALSE;				   /*			     */
    }						   /*			     */
    if (rec == r) { *hp = NULL; }		   /* Delete the first xref  */
    t = *++hp;					   /*                        */
    t++;				   	   /*			     */
    (void)sp_open(t);				   /* Try to extract	     */
    if ( (s = SParseSymbol(&t)) == StringNULL )	   /*  the crossref as symbol*/
    { return FALSE; }				   /*			     */
						   /*			     */
    if ( (r = db_find(db,s)) == (Record)NULL )	   /*			     */
    { ERROR2("Crossref entry not found: ",(char*)s);/*			     */
      return FALSE;				   /*			     */
    }						   /*			     */
    						   /*                        */
    for (i = RecordFree(r), hp = RecordHeap(r);    /* visit all fields       */
	 i > 0;					   /*			     */
	 i -= 2)			   	   /*			     */
    { s	= *hp++;                                   /*                        */
      t	= *hp++;                                   /*                        */
      if (t != StringNULL)			   /*                        */
      { provide_to_record(rec,s,t); }              /*                        */
    }						   /*			     */
  }						   /*                        */
 						   /*                        */
  return FALSE;	   				   /*			     */
}						   /*------------------------*/
