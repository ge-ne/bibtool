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

 typedef struct mAP
 { String src_rec;
   String src_field;
   String dest_rec;
   String dest_field;
   struct mAP * next_map;
 } *Map, SMap;

#define SourceRecord(M)      ((M)->src_rec)
#define SourceField(M)       ((M)->src_field)
#define DestinationRecord(M) ((M)->dest_rec)
#define DestinationField(M)  ((M)->dest_field)
#define NextMap(M)	     ((M)->next_map)

/*-----------------------------------------------------------------------------
** Function:	new_map()
** Type:	Map
** Purpose:	
**		
** Arguments:
**	sr	
**	sf	
**	dr	
**	df	
** Returns:	
**___________________________________________________			     */
static Map new_map(sr,sf,dr,df)			   /*                        */
  String sr;					   /*                        */
  String sf;					   /*                        */
  String dr;					   /*                        */
  String df;					   /*                        */
{ Map m;					   /*                        */
  if ( (m = (Map)malloc(sizeof(SMap))) == (Map)NULL)/*                       */
  { OUT_OF_MEMORY("map"); }		   	   /*                        */
 						   /*                        */
  SourceRecord(m) = sr;				   /*                        */
  SourceField(m) = sf;				   /*                        */
  DestinationRecord(m) = dr;			   /*                        */
  DestinationField(m) = df;			   /*                        */
  NextMap(m) = NULL;			   	   /*                        */
  return m;					   /*                        */
}						   /*------------------------*/

#define MAP_SIZE 31

static Map map[MAP_SIZE];

/*-----------------------------------------------------------------------------
** Function:	clear_map()
** Type:	void
** Purpose:	
**		
** Arguments:
**		
** Returns:	nothing
**___________________________________________________			     */
int clear_map()					   /*                        */
{ int i;					   /*                        */
 
  for (i = 0; i < MAP_SIZE; i++ )
  { map[i] = (Map)NULL; }
  return FALSE;
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	crossref_map()
** Type:	int
** Purpose:	
**		
** Arguments:
**	spec	the argument
** Returns:	
**___________________________________________________			     */
void crossref_map(spec)				   /*                        */
  String spec;				   	   /*			     */
{ String s;					   /*                        */
  String *src, *dest;				   /*                        */
  String src_field, dest_field;			   /*                        */
  String *sp, *dp;				   /*                        */

  (void)sp_open(spec);
  if ((src        = sp_symbols(&spec))   == NULL ||
      SParseSkip(&spec)	== 0 ||
      (src_field  = SParseSymbol(&spec)) == NULL ||
      SParseSkip(&spec)	== 0 ||
      (dest       = sp_symbols(&spec))   == NULL ||
      SParseSkip(&spec)	== 0 ||
      (dest_field = SParseSymbol(&spec)) == NULL ||
      SParseEOS(&spec) != NULL
     )
  { return; }
  sp_close();

  for (sp = src; *sp; sp++)
  {
    for (dp = dest; *dp; dp++)
    {
      /*
      printf("--- %s %s = %s %s\n",*dp,dest_field,*sp, src_field);
      */
    }
  }
 						   /*                        */
  (void)free(src);
  (void)free(dest);
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	map_add()
** Type:	int
** Purpose:	
**		
** Arguments:
**	s_rec	
**	s_fld	
**	d_rec	
**	d_fld	
** Returns:	
**___________________________________________________			     */
int map_add(s_rec,s_fld,d_rec,d_fld)		   /*                        */
  String s_rec;					   /*                        */
  String s_fld;					   /*                        */
  String d_rec;					   /*                        */
  String d_fld;					   /*                        */
{
  return FALSE;
}

/*-----------------------------------------------------------------------------
** Function:	map_get()
** Type:	String
** Purpose:	
**		
** Arguments:
**	s_rec	
**	s_fld	
**	d_rec	
** Returns:	
**___________________________________________________			     */
String map_get(s_rec,s_fld,d_rec)		   /*                        */
  String s_rec;					   /*                        */
  String s_fld;					   /*                        */
  String d_rec;					   /*                        */
{
  return (String)NULL;
}

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
