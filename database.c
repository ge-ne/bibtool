/*** database.c ***************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-20120Gerd Neugebauer
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
**	This module contains functions which deal with databases.
**	Databases are stored in an abstract datatype |DB| which is defined
**	in |database.h|. Methods are provided to query and modify a database.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/expand.h>
#include <bibtool/symbols.h>
#include <bibtool/database.h>
#include <bibtool/record.h>
#include <bibtool/parse.h>
#include <bibtool/macros.h>
#include <bibtool/print.h>
#include <bibtool/error.h>
#include <bibtool/entry.h>
#include <bibtool/key.h>
#include <bibtool/rsc.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 static Record insert_record _ARG((Record rec, Record ptr,int (*less)_ARG((Record, Record))));/**/
 static Record rec__sort _ARG((Record rec,int (*less)_ARG((Record, Record))));/**/
 static int cmp_heap _ARG((Record r1, Record r2)); /*                        */
 static void mark_string _ARG((Record rec, String s));/*                     */

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/

#define SkipWarning	      WARNING("Skipping to next '@'")

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	new_db()
** Purpose:	Create a new database and initialize it to contain no
**		information.
**		If no memory is left then an error is raised and the program
**		is terminated.
** Arguments:	none
** Returns:	The new database.
**___________________________________________________			     */
DB new_db()				   	   /*                        */
{ register DB new;				   /*                        */
 						   /*                        */
  if ((new=(DB)malloc(sizeof(sDB))) == NoDB)	   /*                        */
  { OUT_OF_MEMORY("db"); }			   /*                        */
  DBnormal(new)   = RecordNULL;			   /*                        */
  DBstring(new)   = RecordNULL;			   /*                        */
  DBpreamble(new) = RecordNULL;			   /*                        */
  DBcomment(new)  = RecordNULL;			   /*                        */
  DBalias(new)    = RecordNULL;			   /*                        */
  DBinclude(new)  = RecordNULL;			   /*                        */
  DBmodify(new)   = RecordNULL;			   /*                        */
  return new;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_db()
** Purpose:	Deallocate the memory occupied by a database.
**		Note that any references to this database becomes invalid.
** Arguments:
**	db	Database to release.
** Returns:	nothing
**___________________________________________________			     */
void free_db(DB db)				   /*                        */
{						   /*                        */
  free_record(DBnormal(db));			   /*                        */
  free_record(DBstring(db));			   /*                        */
  free_record(DBpreamble(db));			   /*                        */
  free_record(DBcomment(db));			   /*                        */
  free_record(DBalias(db));			   /*                        */
  free_record(DBinclude(db));			   /*                        */
  free_record(DBmodify(db));			   /*                        */
  free(db);					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	apply_modify()
** Type:	int
** Purpose:	
**		
** Arguments:
**	db	the database
**	key	the key
**	rec	the record
** Returns:	
**___________________________________________________			     */
int apply_modify(DB db, Symbol key, Record rec)	   		   /*                        */
{ Symbol *hp = RecordHeap(rec);			   /*                        */
  int i;					   /*                        */
  Record r  = db_find(db, key);			   /*                        */
  if (r == RecordNULL)				   /*                        */
  { WARNING2("Entry to modify not found: ",	   /*                        */
	     SymbolValue(key));   		   /*                        */
    return 0;					   /*			     */
  }						   /*			     */
  DebugPrint2("Modify ",			   /*                        */
	      SymbolValue(*RecordHeap(rec)));	   /*                        */
						   /*			     */
  for (i = RecordFree(rec); i > 0; i -= 2)	   /*			     */
  {		   				   /* No deleted or          */
    if (*hp &&					   /*                        */
	is_allowed(*SymbolValue(*hp)) &&	   /*                        */
	*(hp+1))	   		   	   /*   private entry        */
    { DebugPrint3(SymbolValue(*hp),		   /*                        */
		  " => ",			   /*                        */
		  SymbolValue(*(hp+1)));	   /*                        */
      push_to_record(r, *hp, *(hp+1), false);	   /*                        */
    }						   /*			     */
    hp += 2;					   /* Goto next pair.	     */
  }						   /*                        */
  return 1;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	apply_alias()
** Type:	bool
** Purpose:	
**		
** Arguments:
**	db	the database
**	key	the key
**	rec	the record
**	verbose	the verbose indicator
** Returns:	
**___________________________________________________			     */
static bool apply_alias(DB db, Symbol key, Record rec, bool verbose)	   /*                        */
{ Record r = db_find(db, key);			   /*                        */
  if (r == RecordNULL)				   /*                        */
  { WARNING2("Entry to alias not found: ", key);   /*                        */
    return false;				   /*			     */
  }						   /*			     */
  DebugPrint2("Alias ",				   /*                        */
	      SymbolValue(*RecordHeap(rec)));	   /*                        */
 						   /*                        */
  r = copy_record(r);	   	   		   /* Make a private copy.   */
  RecordOldKey(r) = *RecordHeap(rec);		   /*                        */
  *RecordHeap(r)  = *RecordHeap(rec);		   /*                        */
  db_insert(db, r, verbose);		   	   /*                        */
  return true;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_insert()
** Purpose:	Add a record to a database.
**		The record can be any kind of record. It is added to the
**		appropriate category.
** Arguments:
**	db	Database to insert the record into.
**	rec	Record to add to the database.
**	verbose	Boolean to determine whether progress should be reported.
** Returns:	nothing
**___________________________________________________			     */
void db_insert(DB db, Record rec, bool verbose)		   /*                        */
{ Record *rp;					   /*                        */
						   /*                        */
  switch (RecordType(rec))			   /*                        */
  { case BIB_STRING:				   /*                        */
      rp = &DBstring(db);			   /*                        */
      DebugPrint1("Inserting String");	   	   /*                        */
      break;					   /*                        */
    case BIB_PREAMBLE:				   /*                        */
      rp = &DBpreamble(db);			   /*                        */
      DebugPrint1("Inserting Preamble");	   /*                        */
      break;					   /*                        */
    case BIB_COMMENT:				   /*                        */
      rp = &DBcomment(db);			   /*                        */
      DebugPrint1("Inserting Comment");	   	   /*                        */
      break;					   /*                        */
    case BIB_MODIFY:				   /*                        */
      if(rsc_apply_modify &&			   /*                        */
	 apply_modify(db, *RecordHeap(rec), rec))  /*                        */
      {	free_record(rec);			   /*                        */
	return;					   /*                        */
      } else {					   /*                        */
	rp = &DBmodify(db);   			   /*                        */
	DebugPrint1("Inserting Modify");   	   /*                        */
      }						   /*                        */
      break;					   /*                        */
    case BIB_INCLUDE:				   /*                        */
      if(rsc_apply_include)			   /*                        */
      {	DebugPrint2("Including ",		   /*                        */
		    SymbolValue(*RecordHeap(rec)));/*                        */
	if (read_db(db,				   /*                        */
		    SymbolValue(*RecordHeap(rec)), /*                        */
		    verbose))  			   /*                        */
	{ ERROR2("File not found: ",		   /*                        */
		 SymbolValue(*RecordHeap(rec)));   /*                        */
	}					   /*                        */
	free_record(rec);			   /*                        */
	return;					   /*                        */
      } else {					   /*                        */
	rp = &DBinclude(db);  			   /*                        */
	DebugPrint1("Inserting Include"); 	   /*                        */
      }						   /*                        */
      break;					   /*                        */
    case BIB_ALIAS:				   /*                        */
      if (rsc_apply_alias)			   /*                        */
      {	DebugPrint2("Alias ",			   /*                        */
		    SymbolValue(*RecordHeap(rec)));/*                        */
	apply_alias(db, *(RecordHeap(rec)+1),	   /*                        */
		    rec, verbose);		   /*                        */
	free_record(rec);			   /*                        */
	return;					   /*                        */
      } else {					   /*                        */
	rp = &DBalias(db);    			   /*                        */
	DebugPrint1("Inserting Alias");		   /*                        */
      }						   /*                        */
      break;					   /*                        */
    default:	       				   /*                        */
      rp = &DBnormal(db);			   /*                        */
      DebugPrint2("Inserting Entry ",		   /*                        */
		  SymbolValue(*RecordHeap(rec)));  /*                        */
      break;					   /*                        */
  }						   /*                        */
						   /*                        */
  if (*rp == RecordNULL)			   /* List is empty          */
  { *rp = rec; }		   	   	   /* Just remember the rec. */
  else					   	   /*                        */
  { NextRecord(*rp) = rec;	   	   	   /*                        */
    PrevRecord(rec) = *rp;	   	   	   /*                        */
    *rp		    = rec;		   	   /*                        */
  }					   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_db()
** Purpose:	Read records from a file and add them to a database.
**		A function has to be given as one argument. This function is
**		called for each record. If this function returns |true| then
**		the record is added to the database. Otherwise the record is
**		discarded.
**
**		The progress of reading is reported to |stderr| if the
**		boolean argument |verbose| is |true|.
** Arguments:
**	db	Database to augment.
**	file	File name to read from.
**	verbose	Boolean to determine whether progress should be reported.
** Returns:	|true| if the file can not be opened. |false| otherwise.
**___________________________________________________			     */
bool read_db(DB db, String file, bool verbose)		   	   /*                        */
{ register int	  type;				   /*			     */
  static Record	  master_record = RecordNULL;	   /*			     */
  Record	  rec;				   /*			     */
  register Record dbn;				   /*                        */
						   /*                        */
  if (!see_bib(file)) return 1;		   	   /*                        */
  if (master_record == RecordNULL)		   /*                        */
  { master_record = new_record(0, 32); }	   /*                        */
 						   /*                        */
  if (file == NULL)				   /*                        */
  { file = (String)"<stdin>";	   		   /*                        */
    RecordSource(master_record) = sym_empty;  	   /*                        */
    LinkSymbol(sym_empty);			   /*                        */
  }						   /*                        */
  else						   /*                        */
  { RecordSource(master_record) = symbol(file);    /*                        */
  }						   /*                        */
 						   /*                        */
  if (verbose) 			   	   	   /* If desired print an    */
  { VerbosePrint2("Reading ",file); }	   	   /*	open message.	     */
 						   /*                        */
  dbn = DBnormal(db);				   /*                        */
  if (dbn != RecordNULL)			   /*                        */
  {						   /*                        */
    while (NextRecord(dbn) != RecordNULL)	   /*                        */
    { dbn = NextRecord(dbn); }			   /*                        */
  }						   /*                        */
  DBnormal(db) = dbn;				   /*                        */
 						   /*                        */
  for (type = parse_bib(master_record);		   /*                        */
       type != BIB_EOF;				   /*		             */
       type = parse_bib(master_record))		   /*                        */
  {						   /*                        */
    if (type < 0)				   /* Errors give rise to    */
    { SkipWarning; }				   /*  a warning.	     */
    else if (IsSpecialRecord(type))		   /* STRING/PREAMBLE/COMMENT*/
    { db_insert(db,				   /*                        */
		copy_record(master_record),	   /*                        */
		verbose);			   /*                        */
    }						   /*			     */
    else					   /*                        */
    { rec = copy_record(master_record);	   	   /* Make a private copy.   */
      RecordOldKey(rec) = *RecordHeap(rec);	   /*                        */
      db_insert(db,rec, verbose);		   /*                        */
      if (verbose) { ErrC('+'); FlushErr; }	   /*			     */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  if (verbose)			   	   	   /* If desired print a     */
  { VerbosePrint2("Done with ",file); }	   	   /*	close message.	     */
 						   /*                        */
  (void)seen();				   	   /* Close the file.	     */
 						   /*                        */
  return false;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	mark_string()
** Purpose:	
**		
**		
** Arguments:
**	rec	the record
**	s	the string
** Returns:	nothing
**___________________________________________________			     */
static void mark_string(Record rec, String s)			   /*                        */
{ int    d;					   /*                        */
  Record r;					   /*                        */
 						   /*                        */
  while (*s)					   /*                        */
  {						   /*                        */
    switch (*s)					   /*                        */
    { case '\0': return;			   /*                        */
      case '"':					   /*                        */
	d = 0;					   /*                        */
	while (*++s && (*s != '"' || d > 0))	   /*                        */
	{ switch (*s)				   /*                        */
	  { case '{': d++; break;		   /*                        */
	    case '}': d--; break;		   /*                        */
	    case '\\': if (s[1]) s++;		   /*                        */
	  }					   /*                        */
	}					   /*                        */
	if (*s) s++;				   /*                        */
	break;					   /*                        */
      case '{':					   /*                        */
	d = 1;					   /*                        */
	while (*++s && d > 0)			   /*                        */
	{ switch (*s)				   /*                        */
	  { case '{': d++; break;		   /*                        */
	    case '}': d--; break;		   /*                        */
	    case '\\': if (s[1]) s++;		   /*                        */
	  }					   /*                        */
	}					   /*                        */
	if (*s) s++;				   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	if (is_allowed(*s))			   /*                        */
	{ Symbol mac = sym_extract(&s, false);	   /*                        */
 						   /*                        */
	  for (r = rec; r; r = NextRecord(r))	   /*                        */
	  { if (*RecordHeap(r) == mac)	   	   /*                        */
	    { SetRecordMARK(r);			   /*                        */
	      break;		   		   /*                        */
	    }					   /*                        */
	  }					   /*                        */
	}					   /*                        */
	else s++;				   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	print_segment()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	the file
**	 db	the database
**	 rec	the record
**	allp	the indicator for printing all
** Returns:	nothing
**___________________________________________________			     */
static void print_segment(FILE *file, DB db, Record rec, bool allp)	   /*                        */
{						   /*                        */
  if (rec == RecordNULL) return;		   /*                        */
 						   /*                        */
  while (PrevRecord(rec) != RecordNULL)		   /* Rewind to beginning.   */
  { rec = PrevRecord(rec); }		   	   /*                        */
 						   /*                        */
  for ( ; rec != RecordNULL; rec = NextRecord(rec))/*                        */
  {						   /*                        */
    if (!RecordIsDELETED(rec))		   	   /*                        */
    { if (allp || RecordIsMARKED(rec))	   	   /*                        */
      { fput_record(file, rec, db, (String)"@");   /*                        */
      }					   	   /*                        */
    }					   	   /*                        */
    else if (rsc_del_q)			   	   /*                        */
    { fput_record(file, rec,db, rsc_del_pre); }	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	preprint_string()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	the file
**	db	the database
**	strings	the string definition
**	rec	the record
** Returns:	nothing
**___________________________________________________			     */
static void preprint_string(FILE *file, DB db, Record strings, Record rec)/*                        */
{ int    i, d;					   /*                        */
  Record r;					   /*                        */
 						   /*                        */
  for (i = 0; i < RecordFree(rec); i += 2)   	   /*                        */
  { if (RecordHeap(rec)[i] != NO_SYMBOL)	   /*                        */
    { String s = SymbolValue(RecordHeap(rec)[i+1]);/*                        */
 						   /*                        */
      while(*s)					   /*                        */
      {						   /*                        */
	switch (*s)				   /*                        */
	{ case '\0': return;			   /*                        */
	  case '"':				   /*                        */
	    d = 0;				   /*                        */
	    while (*++s && (*s != '"' || d > 0))   /*                        */
	    { switch (*s)			   /*                        */
	      { case '{': d++; break;		   /*                        */
		case '}': d--; break;		   /*                        */
		case '\\': if (s[1]) s++;	   /*                        */
	      }					   /*                        */
	    }					   /*                        */
	    if (*s) s++;			   /*                        */
	    break;				   /*                        */
	  case '{':				   /*                        */
	    d = 1;				   /*                        */
	    while (*++s && d > 0)		   /*                        */
	    { switch (*s)			   /*                        */
	      { case '{': d++; break;		   /*                        */
		case '}': d--; break;		   /*                        */
		case '\\': if (s[1]) s++;	   /*                        */
	      }					   /*                        */
	    }					   /*                        */
	    if (*s) s++;			   /*                        */
	    break;				   /*                        */
	  default:				   /*                        */
	    if (is_allowed(*s))		   	   /*                        */
	    { Symbol mac = sym_extract(&s, false); /*                        */
 						   /*                        */
	      for (r = strings;			   /*                        */
		   r != RecordNULL;		   /*                        */
		   r = NextRecord(r))		   /*                        */
	      { if (*RecordHeap(r) == mac &&	   /*                        */
		    RecordIsMARKED(r))	   	   /*                        */
	        { ClearRecordMARK(r);		   /*                        */
		  fput_record(file,		   /*                        */
			      r,		   /*                        */
			      db,		   /*                        */
			      (String)"@");	   /*                        */
 						   /*                        */
		  preprint_string(file,		   /*                        */
				  db,		   /*                        */
				  strings,	   /*                        */
				  r);		   /*                        */
		}				   /*                        */
	      }					   /*                        */
	    }					   /*                        */
	    else s++;				   /*                        */
        }					   /*                        */
      }						   /*                        */
    }					   	   /*                        */
  }					   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	print_strings()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	the target file
**	db	the database
**	allp	the indicator to include all
** Returns:	nothing
**___________________________________________________			     */
static void print_strings(FILE *file, DB db, bool allp)	   /*                        */
{ Record strings = DBstring(db);		   /*                        */
  Record rec;					   /*                        */
    						   /*                        */
  if (strings == RecordNULL) return;		   /*                        */
 						   /*                        */
  while (PrevRecord(strings)) 			   /* find beginning         */
  { strings = PrevRecord(strings); }		   /*  of strings            */
 						   /*                        */
  if (allp)					   /*                        */
  {						   /*                        */
    for (rec = strings;				   /*                        */
	 rec != RecordNULL;			   /*                        */
	 rec = NextRecord(rec))			   /*                        */
    { SetRecordMARK(rec); }			   /*                        */
  }						   /*                        */
  else						   /*                        */
  { int i;					   /*                        */
 						   /*                        */
    for (rec = strings;				   /* reset all marks        */
	 rec != RecordNULL;			   /*                        */
	 rec = NextRecord(rec))			   /*                        */
    { ClearRecordMARK(rec); }			   /*                        */
 						   /*                        */
    if ((rec=DBnormal(db)) != RecordNULL)	   /*                        */
    { 						   /*                        */
      while (PrevRecord(rec)) rec = PrevRecord(rec);/*                       */
						   /*                        */
      for ( ;					   /*                        */
	   rec != RecordNULL;			   /*                        */
	   rec = NextRecord(rec))		   /*                        */
      {						   /*                        */
	if (!RecordIsDELETED(rec))		   /*                        */
	{					   /*                        */
	  for (i = 2; i < RecordFree(rec); i += 2) /*                        */
	  { if (RecordHeap(rec)[i] != NULL)	   /*                        */
	    { mark_string(strings,		   /*                        */
			  SymbolValue(RecordHeap(rec)[i+1]));/*              */
	    }					   /*                        */
	  }					   /*                        */
	}					   /*                        */
      }						   /*                        */
 						   /*                        */
      for (rec = strings;			   /* mark the dependencies  */
	   rec != RecordNULL;			   /*  from within strings   */
	   rec = NextRecord(rec))		   /*                        */
      {						   /*                        */
	if (RecordIsMARKED(rec))		   /*                        */
	{					   /*                        */
	  for (i = 1; i < RecordFree(rec); i++)    /*                        */
	  { if (RecordHeap(rec)[i] != NULL)	   /*                        */
            { mark_string(strings,		   /*                        */
			  SymbolValue(RecordHeap(rec)[i]));/*                */
	    }					   /*                        */
	  }					   /*                        */
	}					   /*                        */
      }			   			   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  for (rec = strings;				   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = NextRecord(rec))			   /*                        */
  {						   /*                        */
    if (!RecordIsDELETED(rec) &&		   /*                        */
	RecordIsMARKED(rec))	   	   	   /*                        */
    { preprint_string(file, db, strings, rec); }   /*                        */
  }						   /*                        */
 						   /*                        */
  print_segment(file, db, strings, false);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	print_db()
** Purpose:	Print a database to a file in a way which is readable by
**		\BibTeX. The spec determines which parts should be
**		printed and the order of this parts. The spec is
**		processed from left to right. Each unknown character
**		is silently ignored. The following characters
**		correspond to parts of the database:
**		\begin{description}
**		\item [p] The preamble.
**		\item [\$] All strings (macros) contained in the database.
**		\item [S] The strings (macros) which are used in the
**			  database.
**		\item [s] The strings (macros) contained in the database
**			  where the resource print.all.strings determines
**			  whether all strings should be printed or the used
**			  strings only. 
**		\item [n] The normal records.
**		\item [c] The comments.
**		\item [i] The includes.
**		\item [a] The aliases.
**		\item [m] The modifies.
**		\end{description}
**		Upper-case letters which are not mentioned are silently folded
**		to their lower-case counterparts.
** Arguments:
**	file	The file handle for printing.
**	db	The database to print
**	spec	String containing the specification of the parts to print.
** Returns:	nothing
**___________________________________________________			     */
void print_db(FILE *file, DB db, char *spec)			   /*                        */
{						   /*                        */
  while (*spec)				   	   /*                        */
  { switch (*(spec++))			   	   /*                        */
    { case 'p': case 'P':			   /*                        */
	print_segment(file, db, DBpreamble(db), true);/*                     */
	break;					   /*                        */
      case 'n': case 'N':			   /*                        */
	print_segment(file, db, DBnormal(db), true);/*                       */
	break;					   /*                        */
      case 's':					   /*                        */
	print_strings(file, db, rsc_all_macs);	   /*                        */
	break;					   /*                        */
      case '$':					   /*                        */
	print_strings(file, db, true);		   /*                        */
	break;					   /*                        */
      case 'S':					   /*                        */
	print_strings(file, db, false);		   /*                        */
	break;					   /*                        */
      case 'c': case 'C':			   /*                        */
	print_segment(file, db, DBcomment(db), true);/*                      */
	break;					   /*                        */
      case 'i': case 'I':			   /*                        */
	print_segment(file, db, DBinclude(db), true);/*                      */
	break;					   /*                        */
      case 'a': case 'A':			   /*                        */
	print_segment(file, db, DBalias(db), true);/*                        */
	break;					   /*                        */
      case 'm': case 'M':			   /*                        */
	print_segment(file, db, DBmodify(db), true);/*                       */
	break;					   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	delete_record()
** Purpose:	Delete a record from a database.
**		It is not checked, that the record really is part of the
**		database. The record is just unlinked from its
**		list. Just in case the record should be the first one
**		the database record is modified.
** Arguments:
**	db	Database containing |rec|.
**	rec	Record to delete.
** Returns:	nothing
**___________________________________________________			     */
void delete_record(DB db, Record rec)			   /*                        */
{ Record *rp;					   /*                        */
 						   /*                        */
  switch (RecordType(rec))			   /*                        */
  { case BIB_PREAMBLE: rp = &DBpreamble(db); break;/*                        */
    case BIB_STRING:   rp = &DBstring(db);   break;/*                        */
    case BIB_COMMENT:  rp = &DBcomment(db);  break;/*                        */
    case BIB_MODIFY:   rp = &DBmodify(db);   break;/*                        */
    case BIB_INCLUDE:  rp = &DBinclude(db);  break;/*                        */
    case BIB_ALIAS:    rp = &DBalias(db);    break;/*                        */
    default:           rp = &DBnormal(db);   break;/*                        */
  }						   /*                        */
  if (rec == *rp)				   /*                        */
  { if (NextRecord(rec) != RecordNULL)	   	   /*                        */
    { *rp = NextRecord(rec); }			   /*                        */
    else if (PrevRecord(rec) != RecordNULL)	   /*                        */
    { *rp = PrevRecord(rec); }			   /*                        */
    else 					   /*                        */
    { *rp = RecordNULL; }			   /*                        */
  }						   /*                        */
  if (PrevRecord(rec) != RecordNULL)		   /*                        */
  { NextRecord(PrevRecord(rec)) = NextRecord(rec); }/*                       */
  if (NextRecord(rec) != RecordNULL)		   /*                        */
  { PrevRecord(NextRecord(rec)) = PrevRecord(rec); }/*                       */
  free_1_record(rec);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_forall()
** Purpose:	Visit all normal records in the data base and apply the given
**		function |fct| to each.
**		If this function returns |true| then no more records need to
**		be visited.
**		No special order can be assumed in which the records are seen.
** Arguments:
**	fct	Boolean valued function determining the end of the
**		processing. It takes two arguments a |DB| and a |Record|.
** Returns:	nothing
**___________________________________________________			     */
void db_forall(DB db, bool (*fct)_ARG((DB,Record)))				   /*                        */
{ register Record rec, next;			   /*                        */
						   /*                        */
  if (DBnormal(db) == RecordNULL) return;	   /*                        */
						   /*                        */
  for (rec = DBnormal(db);			   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = next)			   	   /*                        */
  { next = NextRecord(rec);			   /*                        */
    if (!RecordIsDELETED(rec) && 		   /*                        */
	(*fct)(db,rec)) return;		   	   /*                        */
  }		   				   /*                        */
 						   /*                        */
  for (rec = PrevRecord(DBnormal(db));		   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = next)			   	   /*                        */
  { next = PrevRecord(rec);			   /*                        */
    if (!RecordIsDELETED(rec) && 		   /*                        */
	(*fct)(db,rec)) return;		   	   /*                        */
  }		   				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_find()
** Purpose:	Search the database for a record with a given key.
**		If |RecordOldKey| is set for the record then use this value.
**		Otherwise use |*Heap|. |*Heap| contains the reference
**		key of normal records.
**
**		Deleted records are ignored. An arbitrary matching
**		record is returned. Thus if more than one record have
**		the same key then the behavior is nondeterministic.
** Arguments:
**	db	Database to search in.
**	key	the key to search for
** Returns:	the record found or |NULL| if none is found
**___________________________________________________			     */
Record db_find(DB db, Symbol key)				   /*                        */
{ register Record rec;				   /*                        */
						   /*                        */
  DebugPrint2("Finding... ", SymbolValue(key));	   /*                        */
 						   /*                        */
  if (DBnormal(db) == RecordNULL) return RecordNULL;/*                       */
						   /*                        */
  for (rec = DBnormal(db);			   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = NextRecord(rec))			   /*                        */
  {						   /*                        */
    if (!RecordIsDELETED(rec))		   	   /*                        */
    { if (RecordOldKey(rec) != NULL)		   /*                        */
      { if (RecordOldKey(rec) == key) return rec;  /*                        */
      }						   /*                        */
      else if (*RecordHeap(rec) == key) return rec;/*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  for (rec = PrevRecord(DBnormal(db));		   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = PrevRecord(rec))			   /*                        */
  {						   /*                        */
    if (!RecordIsDELETED(rec))		   	   /*                        */
    { if (RecordOldKey(rec) != NULL)		   /*                        */
      { if (RecordOldKey(rec) == key) return rec;  /*                        */
      }						   /*                        */
      else if (*RecordHeap(rec) == key) return rec;/*                        */
    }						   /*                        */
  }		   				   /*                        */
  return RecordNULL;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_search()
** Purpose:	Search the database for a record with a given key.
**		If |RecordOldKey| is set for the record then use this value.
**		Otherwise use |*Heap|. |*Heap| contains the reference
**		key of normal records.
**
**		Deleted records are not ignored! An arbitrary matching
**		record is returned. Thus if more than one record have
**		the same key then the behavior is nondeterministic.
** Arguments:
**	db	Database to search in.
**	key	the key to search for
** Returns:	the record found or |NULL| if none is found
**___________________________________________________			     */
Record db_search(DB db, Symbol key)			   /*                        */
{ register Record rec;				   /*                        */
						   /*                        */
  if (DBnormal(db) == RecordNULL) return RecordNULL;/*                       */
						   /*                        */
  for (rec = DBnormal(db);			   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = NextRecord(rec))			   /*                        */
  { if (RecordOldKey(rec) != NO_SYMBOL)	   	   /*                        */
    { if (RecordOldKey(rec) == key) return rec; }  /*                        */
    else if (*RecordHeap(rec) == key) return rec;  /*                        */
  }						   /*                        */
 						   /*                        */
  for (rec = PrevRecord(DBnormal(db));		   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = PrevRecord(rec))			   /*                        */
  { if (RecordOldKey(rec) != NULL)		   /*                        */
    { if (RecordOldKey(rec) == key) return rec; }  /*                        */
    else if (*RecordHeap(rec) == key) return rec;  /*                        */
  }		   				   /*                        */
  return RecordNULL;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_new_key()
** Purpose:	Search the database for a record with a given old key and
**		return the new one.
** Arguments:
**	db	Database to search in.
**	key	Key to find.
** Returns:	nothing
**___________________________________________________			     */
Symbol db_new_key(DB db, Symbol key)			   /*                        */
{ register Record rec;				   /*                        */
						   /*                        */
  if (DBnormal(db) == RecordNULL) return NULL;     /*                        */
						   /*                        */
  for (rec = DBnormal(db);			   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = NextRecord(rec))			   /*                        */
  {						   /*                        */
    if (RecordOldKey(rec) != NULL &&		   /*                        */
	RecordOldKey(rec) == key)		   /*                        */
    return *RecordHeap(rec); 			   /*                        */
  }						   /*                        */
 						   /*                        */
  for (rec = PrevRecord(DBnormal(db));		   /*                        */
       rec != RecordNULL;			   /*                        */
       rec = PrevRecord(rec))			   /*                        */
  {						   /*                        */
    if (RecordOldKey(rec) != NULL &&		   /*                        */
	RecordOldKey(rec) == key)		   /*                        */
    return *RecordHeap(rec); 			   /*                        */
  }						   /*                        */
  return NULL;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_rewind()
** Purpose:	Rewind the normal records of a database to point to the first
**		record if at least one records exists. Otherwise nothing is
**		done.
** Arguments:
**	db	Database to rewind.
** Returns:	nothing
**___________________________________________________			     */
void db_rewind(DB db)				   /*                        */
{					   	   /*                        */
  if (DBnormal(db) == RecordNULL) return;	   /*                        */
 						   /*                        */
  while (PrevRecord(DBnormal(db)) != RecordNULL)   /*                        */
  { DBnormal(db) = PrevRecord(DBnormal(db)); }	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	rec__sort()
** Purpose:	
**		
** Arguments:
**	rec	the record
**	less	the comparator
** Returns:	
**___________________________________________________			     */
static Record rec__sort(Record rec, int (*less)_ARG((Record,Record)))		   /*                        */
{ Record r;				   	   /*                        */
  Record new;		   		   	   /*                        */
 						   /*                        */
  if (rec == RecordNULL) return rec;	  	   /*                        */
  r = RecordNULL ;				   /*                        */
 						   /*                        */
  while (PrevRecord(rec) != RecordNULL)		   /*                        */
  { rec = PrevRecord(rec); }			   /*                        */
 						   /*                        */
  while (rec != RecordNULL)			   /*                        */
  { new = rec;					   /*                        */
    rec = NextRecord(rec);			   /*                        */
    r   = insert_record(new,r,less);		   /*                        */
  }						   /*                        */
  return r;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** The sorting uses a variant of insertion sort.
** Thus the major task is performed in this function, which is called to store
** a record.
** The Record structure contains two pointers to the same type. With those
** pointers a double linked list is established. sort_rec is either NULL ---
** if no record is stored --- or it is a pointer to some element in the
** ORDERED list:
** 
**    +------+	 +------+   +------+   +------+	  +------+   +------+	
** -->|Record|-->|Record|-->|Record|-->|Record|-->|Record|-->|Record|-->
** <--|	     |<--|	|<--|	   |<--|      |<--|	 |<--|	    |<--
**    +------+	 +------+   +------+   +------+	  +------+   +------+	
**			       ^
**		      db_______|
** 
** With this picture in mind it's obvious what's to be done.
** There are two major cases. To find the right position to insert the new
** record
** - either the pointer has to be moved leftward
** - or	    the pointer has to be moved rightward
** 
** Special cases have to be considered if the new record is to be inserted
** before the first or after the last element in the list.
** 
** The rest is simply leg work.
**
** Well, a word on the complexity.
** If the input is almost sorted (correct or in reverse order) then the 
** algorithm is linear.
** In the worst case the algorithm is quadratic. This worst case looks as
** follows:
** A record has to be inserted which is smaller than the least element in the
** list. Afterwards one which is greater than the largest.
** 
** NOTE: CURRENTLY THE ALGORITHM IS NOT STABLE:
**	 Records with the same key may get mixed in the sorted list.
**___________________________________________________			     */
static Record insert_record(register Record rec, register Record ptr, int (*less)_ARG((Record,Record)))	   /*			     */
{					   	   /*			     */
  if (ptr == RecordNULL) {	   		   /* List is empty	     */
    PrevRecord(rec) = RecordNULL;		   /*		             */
    NextRecord(rec) = RecordNULL;		   /*			     */
    return rec;					   /*                        */
  }						   /*                        */
						   /*			     */
  if ((*less)(rec,ptr))			   	   /*			     */
  {						   /*                        */
    while (PrevRecord(ptr) != RecordNULL)	   /* Move leftward.	     */
    { ptr = PrevRecord(ptr);			   /*			     */
      if (!(*less)(rec,ptr))			   /*			     */
      { PrevRecord(rec)		   = ptr;	   /* Insert		     */
	NextRecord(rec)		   = NextRecord(ptr);/*			     */
	PrevRecord(NextRecord(rec))= rec;	   /*			     */
	NextRecord(ptr)		   = rec;	   /*			     */
	return rec;				   /*			     */
      }						   /*			     */
    }						   /*			     */
    PrevRecord(ptr) = rec;			   /* Insert before the first*/
    NextRecord(rec) = ptr;			   /*			     */
    PrevRecord(rec) = RecordNULL;		   /*			     */
  }						   /*			     */
  else						   /*			     */
  {						   /*                        */
    while (NextRecord(ptr) != RecordNULL)	   /* Move rightward.	     */
    { ptr = NextRecord(ptr);			   /*			     */
      if ((*less)(rec,ptr))			   /*			     */
      { NextRecord(rec)		   = ptr;	   /* Insert		     */
	PrevRecord(rec)		   = PrevRecord(ptr);/*			     */
	NextRecord(PrevRecord(rec))= rec;	   /*			     */
	PrevRecord(ptr)		   = rec;	   /*			     */
	return rec;				   /*			     */
      }						   /*			     */
    }						   /*			     */
    NextRecord(ptr) = rec;			   /* Insert after the last. */
    PrevRecord(rec) = ptr;			   /*			     */
    NextRecord(rec) = RecordNULL;		   /*			     */
  }						   /*			     */
  return rec;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	cmp_heap()
** Purpose:	Compare the keys of two records. The keys are stored at the
**		top of the heap. 
** Arguments:
**	r1	First record to compare.
**	r2	Second record to compare.
** Returns:	1 if the first record is smaller than the second one.
**___________________________________________________			     */
static int cmp_heap(register Record r1, register Record r2)		   	   /*                        */
{						   /*                        */
  return symcmp(*RecordHeap(r1),		   /*                        */
		*RecordHeap(r2)) < 0;		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_mac_sort()
** Purpose:	Sort the macros of a database. The sorting uses
**		increasing lexicographic order according to the
**		character codes of the macro names. Note that this
**		might lead to different results on machines with
**		different character encodings, e.g.\ ASCII vs.\ EBCDIC.
** Arguments:
**	db	Database to sort.
**	less	comparison function to use.
** Returns:	nothing
**___________________________________________________			     */
void db_mac_sort(DB db)			   	   /*                        */
{						   /*                        */
  DBstring(db) = rec__sort(DBstring(db), cmp_heap);/*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_sort()
** Purpose:	Sort the normal records of a database. As a side effect the
**		records are kept in sorted order in the database.
**		The sorting order can be determined by the argument |less|
**		which is called to compare two records.
** Arguments:
**	db	Database to sort.
**	less	Comparison function to use. This boolean function
**		takes two records and returns -1 if the first one
**		is less than the second one.
** Returns:	nothing
**___________________________________________________			     */
void db_sort(DB db, int (*less)_ARG((Record,Record)))				   /*                        */
{						   /*                        */
  DBnormal(db) = rec__sort(DBnormal(db), less);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_string()
** Purpose:	Try to find the definition of a macro.
**		First, the local values in the database |db| are considered.
**		If this fails and |localp| is |false| then the global list
**		is searched aswell. If all fails |NULL| is returned.
** Arguments:
**	db	Database
**	sym	Name of the \BibTeX{} macro to expand.
**	localp	Boolean determining whether the search is only local to the db.
** Returns:	The macro expansion or |NULL| upon failure.
**___________________________________________________			     */
Symbol db_string(DB db, Symbol sym, bool localp)		   /*                        */
{ Record rec;					   /*                        */
 						   /*                        */
  if ((rec=DBstring(db)))			   /*                        */
  {						   /*                        */
    for (; rec; rec=NextRecord(rec))		   /*                        */
    { if (RecordHeap(rec)[0] == sym)		   /*                        */
      { return RecordHeap(rec)[1]; }		   /*                        */
    }						   /*                        */
    for (rec = PrevRecord(DBstring(db));	   /*                        */
	 rec;					   /*                        */
	 rec = PrevRecord(rec))		   	   /*                        */
    { if (RecordHeap(rec)[0] == sym)		   /*                        */
      { return RecordHeap(rec)[1]; }		   /*                        */
    }						   /*                        */
  }						   /*                        */
  						   /*                        */
  return (localp ? NO_SYMBOL : look_macro(sym, 0));/*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_count()
** Purpose:	Count all entries in a database. This includes normal
**		as well as special records. The result is stored in a
**		static array which is reused by |db_count()|. A
**		pointer to this array is returned. The indices
**		correspond to the entry types defined with
**		|add_entry_type()| or declared as symbolic constants
**		in |entry.h|. 
**
**		The end of the array is marked by an element
**		containing a negative number. In addition the argument
**		|lp| can point to an integer where the number of valid
**		elements is stored. If |lp| is |NULL| this step is
**		omitted. 
** Arguments:
**	db	Database to count.
**	lp	pointer to an integer for the length.
** Returns:	Static array containing the statistics.
**___________________________________________________			     */
int * db_count(DB db, int *lp)				   /*                        */
{ static int *count;				   /*                        */
  static int len = 0;				   /*                        */
  int        i;					   /*                        */
  Record     rec;				   /*                        */
 						   /*                        */
  for (i = 5; get_entry_type(i) != NULL; i++) ;	   /*                        */
  if (lp) *lp = i;				   /*                        */
  i++;						   /*                        */
 						   /*                        */
  if (len == 0)					   /*                        */
  { len = i;					   /*                        */
    count = (int*)malloc(len*sizeof(int));	   /*                        */
  }						   /*                        */
  else if (len != i)				   /*                        */
  { len = i;					   /*                        */
    count = (int*)realloc(count,len*sizeof(int));  /*                        */
  }						   /*                        */
  if (count == NULL)				   /*                        */
  { OUT_OF_MEMORY("count"); }		   	   /*                        */
						   /*                        */
  for (i = 0; i < len; i++) count[i] = 0;	   /*                        */
  count[len-1] = -1;				   /*                        */
						   /*                        */
  if ((rec=DBstring(db)) != RecordNULL)		   /*                        */
  { while (PrevRecord(rec) != RecordNULL) rec = PrevRecord(rec);/*           */
    while (rec != RecordNULL)			   /*                        */
    { count[BIB_STRING]++;			   /*                        */
      rec = NextRecord(rec);			   /*                        */
    }						   /*                        */
  }						   /*                        */
  if ((rec=DBcomment(db)) != RecordNULL)	   /*                        */
  { while (PrevRecord(rec) != RecordNULL) rec = PrevRecord(rec);/*           */
    while (rec != RecordNULL)			   /*                        */
    { count[BIB_COMMENT]++;			   /*                        */
      rec = NextRecord(rec);			   /*                        */
    }						   /*                        */
  }						   /*                        */
  if ( (rec=DBpreamble(db)) != RecordNULL)	   /*                        */
  { while (PrevRecord(rec) != RecordNULL) rec = PrevRecord(rec);/*           */
    while (rec != RecordNULL)			   /*                        */
    { count[BIB_PREAMBLE]++;			   /*                        */
      rec = NextRecord(rec);			   /*                        */
    }						   /*                        */
  }						   /*                        */
  if ((rec=DBalias(db)) != RecordNULL)		   /*                        */
  { while (PrevRecord(rec) != RecordNULL) rec = PrevRecord(rec);/*           */
    while (rec != RecordNULL)			   /*                        */
    { count[BIB_ALIAS]++;			   /*                        */
      rec = NextRecord(rec);			   /*                        */
    }						   /*                        */
  }						   /*                        */
  if ((rec=DBmodify(db)) != RecordNULL)		   /*                        */
  { while (PrevRecord(rec) != RecordNULL) rec = PrevRecord(rec);/*           */
    while (rec != RecordNULL)			   /*                        */
    { count[BIB_MODIFY]++;			   /*                        */
      rec = NextRecord(rec);			   /*                        */
    }						   /*                        */
  }						   /*                        */
  if ((rec=DBinclude(db)) != RecordNULL)	   /*                        */
  { while (PrevRecord(rec) != RecordNULL) rec = PrevRecord(rec);/*           */
    while (rec != RecordNULL)			   /*                        */
    { count[BIB_INCLUDE]++;			   /*                        */
      rec = NextRecord(rec);			   /*                        */
    }						   /*                        */
  }						   /*                        */
  if ((rec=DBnormal(db)) != RecordNULL)		   /*                        */
  { while (PrevRecord(rec) != RecordNULL)	   /*                        */
    { rec = PrevRecord(rec); }			   /*                        */
    while (rec != RecordNULL)			   /*                        */
    { if (!RecordIsDELETED(rec))		   /*                        */
      { count[RecordType(rec)]++; }		   /*                        */
      rec = NextRecord(rec);			   /*                        */
    }						   /*                        */
  }						   /*                        */
						   /*                        */
  return count;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_xref_undelete()
** Type:	void
** Purpose:	Scan through the database and undelete all entries
**		which are in the transitive closure wrt the crossref
**		relation. Initially all not deleted entries are in the
**		set to consider.
** Arguments:
**	db	Database to treat
** Returns:	nothing
**___________________________________________________			     */
void db_xref_undelete(DB db)			   /*                        */
{ Record rec = DBnormal(db);			   /*                        */
  if (rec == RecordNULL) return;		   /* No entries left anyhow.*/
 						   /*                        */
  while (PrevRecord(rec) != RecordNULL)	   	   /* Rewind                 */
  { rec = PrevRecord(rec); }			   /*                        */
 						   /*                        */
  for (;				   	   /* Phase:                 */
       rec != RecordNULL;			   /*  For all marked entries*/
       rec = NextRecord(rec))		   	   /*  which have a xref and */
  {						   /*  mark all xrefs.       */
    if (RecordIsXREF(rec)   &&		   	   /*                        */
	!RecordIsDELETED(rec))			   /*                        */
    { Symbol key = sym_qqq;	   		   /*                        */
      int    count;				   /*                        */
      Record r = rec;				   /*                        */
 						   /*                        */
      for (count=rsc_xref_limit;		   /* Prevent infinite loop  */
	   count >= 0 && RecordIsXREF(r);	   /*                        */
	   count--)				   /*                        */
      {					   	   /*                        */
	if ((key = get_field(db,	   	   /*                        */
			     r,		   	   /*                        */
			     sym_crossref)) == NULL)/*                       */
	{ count = -1;				   /*                        */
	}			   	   	   /*                        */
	else					   /*                        */
	{					   /*                        */
	  key = expand_rhs(key,	   		   /*                        */
			   sym_empty, 		   /*                        */
			   sym_empty, 		   /*                        */
			   db,			   /*                        */
			   true);     	   	   /*                        */
	  if ((r=db_search(db,key)) == RecordNULL) /*                        */
	  { ErrPrintF("*** BibTool: Crossref `%s' not found.\n",/*           */
		      SymbolValue(key));	   /*                        */
	    count = -1;			   	   /*                        */
	  }					   /*                        */
	  else if (!RecordIsDELETED(r))	   	   /*                        */
	  { count = -1; }			   /*                        */
	  else					   /*                        */
	  { ClearRecordDELETED(r);		   /*                        */
	  }					   /*                        */
	}			   		   /*                        */
      }			   		   	   /*                        */
      if (count == -1)				   /*                        */
      { ErrPrintF("*** BibTool: Crossref limit exceeded; `%s' possibly looped.\n",
		  SymbolValue(key));		   /*                        */
      }						   /*                        */
    }    					   /*                        */
  }						   /*                        */
}						   /*------------------------*/
