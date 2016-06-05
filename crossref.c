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
#include <bibtool/entry.h>

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
 { int src_rec;
   String src_field;
   int dest_rec;
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
  int sr;					   /*                        */
  Symbol sf;					   /*                        */
  int dr;					   /*                        */
  Symbol df;					   /*                        */
{ Map m;					   /*                        */
  if ( (m = (Map)malloc(sizeof(SMap))) == (Map)NULL)/*                       */
  { OUT_OF_MEMORY("map"); }		   	   /*                        */
 						   /*                        */
  SourceRecord(m)      = sr;			   /*                        */
  SourceField(m)       = sf;			   /*                        */
  DestinationRecord(m) = dr;			   /*                        */
  DestinationField(m)  = df;			   /*                        */
  NextMap(m)           = NULL;			   /*                        */
  return m;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_map()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	m	
** Returns:	nothing
**___________________________________________________			     */
static void free_map(m)				   /*                        */
  Map m;					   /*                        */
{ Map nxt;					   /*                        */
  while (m)					   /*                        */
  { nxt = NextMap(m);
    (void)free(m);
    m = nxt;
  }						   /*                        */
}						   /*------------------------*/

#define MAP_SIZE 101

static Map map[MAP_SIZE];

#define MAP_INDEX(SR,SF,DR)			\
	(int)(((((long)SR) % 31) +		\
	       (((long)DR) % 37)*16 +		\
	       (((long)SF) % 1023)) % MAP_SIZE);

/*-----------------------------------------------------------------------------
** Function:	clear_map()
** Type:	void
** Purpose:	
**		
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void clear_map()				   /*                        */
{ register int i;				   /*                        */
  						   /*                        */
  for (i = 0; i < MAP_SIZE; i++ )		   /*                        */
  { free_map(map[i]);				   /*                        */
    map[i] = NULL;				   /*                        */
  }				   		   /*                        */
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
void map_add(s_rec,s_fld,d_rec,d_fld)		   /*                        */
  Symbol s_rec;					   /*                        */
  Symbol s_fld;					   /*                        */
  Symbol d_rec;					   /*                        */
  Symbol d_fld;					   /*                        */
{ int s_idx = find_entry_type(s_rec);		   /*                        */
  int d_idx = find_entry_type(d_rec);		   /*                        */
  int idx;					   /*                        */
  Map m;					   /*                        */
 						   /*                        */
  if (s_idx == BIB_NOOP)			   /*                        */
  { WARNING3("Unknown entry type `", s_rec,	   /*                        */
	     "'. Mapping ignored.");		   /*                        */
    return;					   /*                        */
  }						   /*                        */
  if (d_idx == BIB_NOOP)			   /*                        */
  { WARNING3("Unknown entry type `", d_rec,	   /*                        */
	     "'. Mapping ignored.");		   /*                        */
    return;					   /*                        */
  }						   /*                        */

  idx = MAP_INDEX(s_idx, s_fld, d_idx);
  m = map[idx];
  if (m == NULL )
  { map[idx] = new_map(s_idx, s_fld, d_idx, d_fld);
    return;
  }

  for (;;)
  { if (  SourceRecord(m)      == s_idx &&
	  SourceField(m)       == s_fld &&
	  DestinationRecord(m) == d_idx )
    { DestinationField(m) = d_fld;
      return;					   /*                        */
    }		   				   /*                        */
    if (NextMap(m) == NULL )			   /*                        */
    { NextMap(m) = new_map(s_rec, s_fld,	   /*                        */
			   d_rec, d_fld);	   /*                        */
      return;					   /*                        */
    }						   /*                        */
    m = NextMap(m);				   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	map_get()
** Type:	String
** Purpose:	
**		
** Arguments:
**	s_rec	the index of the source entry type
**	s_fld	the name of the source field
**	d_rec	the index of the destination entry type
** Returns:	the new field name or |NO_SYMBOL|
**___________________________________________________			     */
Symbol map_get(s_rec, s_fld, d_rec)		   /*                        */
  int s_rec;					   /*                        */
  Symbol s_fld;					   /*                        */
  int d_rec;					   /*                        */
{ int i = MAP_INDEX(s_rec, s_fld, d_rec);	   /*                        */
  Map m	= map[i];	   			   /*                        */
						   /*                        */
  for (; m; m = NextMap(m))			   /*                        */
  { if (  SourceRecord(m)      == s_rec &&	   /*                        */
	  SourceField(m)       == s_fld &&	   /*                        */
	  DestinationRecord(m) == d_rec )	   /*                        */
    { return DestinationField(m); }		   /*                        */
  }						   /*                        */
  return NO_SYMBOL;				   /*                        */
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
 						   /*                        */
  (void)sp_open(spec);				   /*                        */
  if ((src        = sp_symbols(&spec))   == NULL ||/*                        */
      SParseSkip(&spec)	== 0 ||			   /*                        */
      (src_field  = SParseSymbol(&spec)) == NULL ||/*                        */
      SParseSkip(&spec)	== 0 ||			   /*                        */
      (dest       = sp_symbols(&spec))   == NULL ||/*                        */
      SParseSkip(&spec)	== 0 ||			   /*                        */
      (dest_field = SParseSymbol(&spec)) == NULL ||/*                        */
      SParseEOS(&spec) != NULL			   /*                        */
     )						   /*                        */
  { return; }					   /*                        */
  sp_close();					   /*                        */
 						   /*                        */
  for (sp = src; *sp; sp++)			   /*                        */
  { for (dp = dest; *dp; dp++)			   /*                        */
    { map_add(*sp, src_field, *dp, dest_field); }  /*                        */
  }						   /*                        */
 						   /*                        */
  (void)free(src);				   /*                        */
  (void)free(dest);				   /*                        */
}						   /*------------------------*/

 static String NONE = (String)"x";		   /*                        */

/*-----------------------------------------------------------------------------
** Function:	insert_record()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	db	
**	rec	
**	hp	
**	s	
** Returns:	
**___________________________________________________			     */
static int insert_record(db,rec,hp,s)		   /*                        */
  DB     db;					   /*                        */
  Record rec;					   /*                        */
  register String *hp;				   /*			     */
  String s;					   /*                        */
{ Record r;					   /*                        */
  String t, ms;					   /*                        */
  int i;					   /*                        */

  if ( (r = db_find(db,s)) == (Record)NULL )   	   /*			     */
  { ERROR2("Crossref entry not found: ",(char*)s); /*		             */
    return FALSE;				   /*			     */
  }						   /*			     */
    						   /*                        */
  for (i = RecordFree(r), hp = RecordHeap(r);  	   /* visit all fields       */
       i > 0;				   	   /*			     */
       i -= 2)			   	   	   /*			     */
  { s = *hp++;			   	   	   /*                        */
    t = *hp++;			   	   	   /*                        */
    if (t != StringNULL)			   /*                        */
    { ms = map_get(RecordType(r), s,	   	   /*                        */
		   RecordType(rec));	   	   /*                        */
#ifdef DEBUG
      printf("--- %s\n",s);
#endif
      provide_to_record(rec, ms ? ms : s, t);  	   /*                        */
    }	   				   	   /*                        */
  }						   /*                        */
  return TRUE;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	expand_crossref()
** Purpose:	Expand all items inherited via a crossref.
** Arguments:
**	db	Database containing the entries.
**	rec	The record to expand
** Returns:	FALSE
**___________________________________________________			     */
int expand_crossref(db, rec)		   	   /*                        */
  DB     db;					   /*                        */
  Record rec;					   /*                        */
{ register String *hp;				   /*			     */
  register int    i;				   /*                        */
  String	  t, s, ms;			   /*			     */
  Record          r	= rec;			   /*                        */
  int             limit	= rsc_xref_limit;	   /*                        */
  String xdata 		= (rsc_expand_xdata ? sym_xdata : NONE);/*           */
  String crossref	= (rsc_expand_crossref ? sym_crossref : NONE);/*     */
 						   /*                        */
  DebugPrint1("expand_crossref");		   /*                        */
 						   /*                        */
  while	( RecordIsXREF(r) && limit-- >= 0 )	   /*                        */
  {						   /*                        */
    for ( i = RecordFree(r), hp = RecordHeap(r);   /* search crossref field  */
	  i > 0					   /*                        */
	    && (*hp != crossref && *hp != xdata);  /*			     */
	  i -= 2, hp += 2 )			   /*			     */
    { }					   	   /*			     */
 						   /*                        */
    if (i <= 0)
    { DebugPrint1("*** No crossref found.");	   /*			     */
      return FALSE;				   /*			     */
    }
    else if (*hp == sym_crossref)		   /* ---------------------- */
    {						   /*                        */
      if (rec == r) { *hp = NULL; }		   /* Delete the first xref  */
      t = *++hp;				   /*                        */
      t++;				   	   /*			     */
      (void)sp_open(t);				   /* Try to extract	     */
      if ( (s = SParseSymbol(&t)) == StringNULL )  /*  the crossref as symbol*/
      { return FALSE; }				   /*			     */
						   /*			     */
      insert_record(db,rec,hp,s);
    }						   /*			     */
    else if (*hp == sym_xdata)			   /* ---------------------- */
    {						   /*                        */


      if (rec == r) { *hp = NULL; }		   /* Delete the first xref  */
      t = *++hp;				   /*                        */
      t++;				   	   /*			     */
      (void)sp_open(t);				   /* Try to extract	     */

      if (sp_expect(&t, "}", 0) ) return FALSE;
      for(;;)
      { if ((s = SParseSymbol(&t)) == NULL)
	{ return TRUE; }

	insert_record(db,rec,hp,s);

	if (sp_expect(&t, "}", 0) ) break;
	sp_expect(&t, ",", 1);
      }
    }
  }						   /*                        */
 						   /*                        */
  return FALSE;	   				   /*			     */
}						   /*------------------------*/
