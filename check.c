/*** check.c **********************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2019 Gerd Neugebauer
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
**
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/rsc.h>
#include <bibtool/error.h>
#include <bibtool/check.h>
#include <bibtool/wordlist.h>
#include <bibtool/sbuffer.h>
#include "config.h"

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 static bool do_checks _ARG((DB db,Record rec));

/*****************************************************************************/
/* External Programs and Variables					     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

 static WordList unique_fields = WordNULL;	   /*                        */

 bool need_sort_key = false;

/*-----------------------------------------------------------------------------
** Function:	add_unique_field()
** Type:	void
** Purpose:	A unique constraint for a field.
**		
** Arguments:
**	key	the key to check
** Returns:	nothing
**___________________________________________________			     */
void add_unique_field(key)			   /*                        */
  Symbol key;					   /*                        */
{ StringBuffer *sb = sbopen();			   /*                        */
  sbputs((char*)SymbolValue(key), sb);		   /*                        */
  key = symbol(lower((String)sbflush(sb)));	   /*                        */
  add_word(key, &unique_fields);		   /*                        */
  (void)sbclose(sb);				   /*                        */
  if (key == sym_sortkey) { need_sort_key = true; }/*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	apply_checks()
** Type:	void
** Purpose:	
**		
** Arguments:
**	db	
** Returns:	nothing
**___________________________________________________			     */
void apply_checks(db)				   /*                        */
  DB db;					   /*                        */
{						   /*                        */
  if (rsc_double_check || unique_fields)	   /* Maybe look for doubles */
  { db_forall(db, do_checks); }		   	   /* or apply unique checks */
}						   /*------------------------*/

#define equal_records(R1,R2) RecordSortkey(R1) == RecordSortkey(R2)

/*-----------------------------------------------------------------------------
** Function*:	do_checks()
** Purpose:	Check whether the given record has a double.
**
** Arguments:
**	db	the database
**	rec	the record
** Returns:	|false|
**___________________________________________________			     */
static bool do_checks(db,rec)			   /*                        */
  DB	 db;					   /*                        */
  Record rec;					   /*                        */
{ register Record prev;				   /*                        */
  register Record rec2;				   /*                        */
  WordList wl;					   /*                        */
  Symbol k1 = *RecordHeap(rec);		   	   /*                        */
  if (k1 == NO_SYMBOL) k1 = sym_empty;	   	   /*                        */
   						   /*                        */
  for (rec2 = PrevRecord(rec);			   /*                        */
       rec2 != RecordNULL;			   /*                        */
       rec2 = prev)				   /*                        */
  { Symbol k2 = *RecordHeap(rec2);		   /*                        */
    if (k2 == NO_SYMBOL) k2 = sym_empty;	   /*                        */
 						   /*                        */
    prev = PrevRecord(rec2);			   /*                        */
						   /*                        */
    if (rsc_double_check && equal_records(rec,rec2))/*			     */
    {						   /*                        */
      if (!rsc_quiet)				   /*                        */
      {	ErrPrint("*** BibTool WARNING");	   /*                        */
	err_location(RecordLineno(rec),		   /*                        */
		     RecordSource(rec),		   /*                        */
		     ": Possible double entry discovered to");/*             */
	err_location(RecordLineno(rec2),	   /*                        */
		     RecordSource(rec2), NULL);	   /*                        */
	ErrPrintF(" `%s'\n", (char*)k2);	   /*                        */
						   /*                        */
	DebugPrintF3("***\t%s =?= %s\n",	   /*                        */
		     (char*)SymbolValue(k2),	   /*                        */
		     (char*)SymbolValue(k1));	   /*                        */
	DebugPrintF2("***\tsort key: %s\n",	   /*                        */
		     (char*)SymbolValue(RecordSortkey(rec))); /*             */
      }						   /*                        */
      if (rsc_del_dbl)				   /*                        */
      { delete_record(db,rec); }	   	   /*                        */
      else 					   /*                        */
      { SetRecordDELETED(rec); }		   /*                        */
    }						   /*			     */
 						   /*                        */
    for (wl = unique_fields; wl; wl = NextWord(wl))/*                        */
    { String key = ThisWord(wl);		   /*                        */
      Symbol val;				   /*                        */
      switch (*(char*)key)			   /*                        */
      { case '$':				   /*                        */
	  if (key == sym_key)	   		   /*                        */
	  { if (k1 == NO_SYMBOL || k1 != k2)	   /*                        */
	    { continue; }			   /*                        */
	    val = k1;				   /*                        */
	    break;				   /*                        */
	  } else if (key == sym_sortkey)	   /*                        */
	  { val = RecordSortkey(rec);	   	   /*                        */
	    if (val == NO_SYMBOL ||		   /*                        */
		val != RecordSortkey(rec2))	   /*                        */
	    { continue; }			   /*                        */
	    break;				   /*                        */
	  }					   /*                        */
	default:				   /*                        */
	  val = record_get(rec, ThisWord(wl));	   /*                        */
	  if (val == NO_SYMBOL ||		   /*                        */
	      val != record_get(rec2, ThisWord(wl)))/*                       */
	  { continue; }				   /*                        */
      }						   /*                        */
      						   /*                        */
      ErrPrint("*** BibTool WARNING");	   	   /*                        */
      err_location(RecordLineno(rec2),		   /*                        */
		   RecordSource(rec2), " and");	   /*                        */
      err_location(RecordLineno(rec),	   	   /*                        */
		   RecordSource(rec), NULL);   	   /*                        */
      ErrPrintF2(": field `%s' is not unique: %s\n",/*                       */
		(char*)ThisWord(wl), (char*)val);  /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  return false;					   /*                        */
}						   /*------------------------*/

