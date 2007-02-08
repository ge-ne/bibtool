/******************************************************************************
** $Id: database.c,v 1.2 2007-02-08 05:27:32 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2001 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This module contains functions which deal with databases.
**	Databases are stored in an abstract datatype |DB| which is defined
**	in |database.h|. Methods are provided to query and modify a database.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/database.h>
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
 DB new_db _ARG((void));			   /* database.c             */
 Record db_find _ARG((DB db,Uchar *key));	   /* database.c             */
 Uchar * db_new_key _ARG((DB db,Uchar *key));	   /* database.c             */
 Uchar * db_string _ARG((DB db,Uchar *s,int localp));/* database.c           */
 int *db_count _ARG((DB db,int *lp));		   /* database.c             */
 int read_db _ARG((DB db,char *file,int (*fct)_ARG((DB,Record)),int verbose));/* database.c*/
 static Record insert_record _ARG((Record rec,Record ptr,int (*less)_ARG((Record,Record))));/* database.c*/
 static Record rec__sort _ARG((Record rec,int (*less)_ARG((Record,Record))));/* database.c*/
 static int cmp_heap _ARG((Record r1,Record r2));  /* database.c             */
 static void mark_string _ARG((Record rec,Uchar *s));/* database.c           */
 void db_add_record _ARG((DB db,Record rec));	   /* database.c             */
 void db_forall _ARG((DB db,int (*fct)_ARG((DB,Record))));/* database.c      */
 void db_mac_sort _ARG((DB db));		   /* database.c             */
 void db_rewind _ARG((DB db));			   /* database.c             */
 void db_sort _ARG((DB db,int (*less)_ARG((Record,Record))));/* database.c   */
 void delete_record _ARG((DB db,Record rec));	   /* database.c             */
 void free_db _ARG((DB db));			   /* database.c             */
 void print_db _ARG((FILE *file,DB db,char *spec));/* database.c             */

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/

#define SkipWarning	      WARNING("*** Skiping to next '@'")

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
void free_db(db)				   /*                        */
  DB db;					   /*                        */
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
** Function:	add_db_record()
** Purpose:	Add a record to a database.
**		The record can be any kind of record. It is added to the
**		appropriate category.
** Arguments:
**	db	Database to insert the record into.
**	rec	Record to add to the database.
** Returns:	nothing
**___________________________________________________			     */
void db_add_record(db,rec)			   /*                        */
  DB     db;					   /*                        */
  Record rec;					   /*                        */
{ Record *rp;					   /*                        */
						   /*                        */
  switch ( RecordType(rec) )			   /*                        */
  { case BIB_STRING:   rp = &DBstring(db);   break;/*                        */
    case BIB_PREAMBLE: rp = &DBpreamble(db); break;/*                        */
    case BIB_COMMENT:  rp = &DBcomment(db);  break;/*                        */
    case BIB_MODIFY:   rp = &DBmodify(db);   break;/*                        */
    case BIB_INCLUDE:  rp = &DBinclude(db);  break;/*                        */
    case BIB_ALIAS:    rp = &DBalias(db);    break;/*                        */
    default:	       rp = &DBnormal(db);   break;/*                        */
  }						   /*                        */
						   /*                        */
  if ( *rp == RecordNULL )			   /* List is empty          */
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
**		called for each record. If this function returns |TRUE| then
**		the record is added to the database. Otherwise the record is
**		discarted. 
**
**		The progress of reading is reported to |stderr| if the
**		boolean argument |verbose| is |TRUE|.
** Arguments:
**	db	Database to augment.
**	file	File name to read from.
**	fct	Function to determine whether to store a given record.
**	verbose	Boolean to determine whether progress should be reported.
** Returns:	1 if the file can not be opened. 0 otherwise.
**___________________________________________________			     */
int read_db(db,file,fct,verbose)		   /*                        */
  DB		  db;				   /*                        */
  char		  *file;			   /*                        */
  int		  (*fct)_ARG((DB,Record));	   /* Function pointer	     */
  int		  verbose;			   /*                        */
{ register int	  type;				   /*			     */
  static Record	  master_record = RecordNULL;	   /*			     */
  Record	  rec;				   /*			     */
  register Record dbn;				   /*                        */
						   /*                        */
  if ( !see_bib(file) ) { return 1; }		   /*                        */
  if ( master_record == RecordNULL )		   /*                        */
  { master_record = new_record(0,32); }		   /*                        */
  RecordSource(master_record) = (file==NULL	   /*                        */
				 ?sym_empty	   /*                        */
				 :symbol((Uchar*)file));/*                   */
 						   /*                        */
  if ( file == NULL ) file = "<stdin>";		   /*                        */
  if ( verbose ) 			   	   /* If desired print an    */
  { VerbosePrint2("Reading ",file); }	   	   /*	open message.	     */
 						   /*                        */
  dbn = DBnormal(db);				   /*                        */
  if ( dbn != RecordNULL )			   /*                        */
  {						   /*                        */
    while ( NextRecord(dbn) != RecordNULL )	   /*                        */
    { dbn = NextRecord(dbn); }			   /*                        */
  }						   /*                        */
  DBnormal(db) = dbn;				   /*                        */
 						   /*                        */
  while ( (type=parse_bib(master_record)) != BIB_EOF )/*		     */
  {						   /*                        */
    if ( type < 0 )				   /* Errors give rise to    */
    { SkipWarning; }				   /*  a warning.	     */
    else if ( IsSpecialRecord(type) )		   /* STRING/PREAMBLE/COMMENT*/
    {						   /*                        */
      db_add_record(db,copy_record(master_record));/*                        */
    }						   /*			     */
    else					   /*			     */
    { if ( (*fct)(db,master_record) )		   /*                        */
      { rec = copy_record(master_record);	   /* Make a private copy.   */
	RecordOldKey(rec) = *RecordHeap(rec);	   /*                        */
	db_add_record(db,rec);			   /*                        */
	if ( verbose ) { ErrC('+'); FlushErr; }	   /*			     */
      }						   /*			     */
      else if ( verbose )			   /*			     */
      { ErrC('.'); FlushErr; }			   /* Just to see something. */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  if ( verbose )			   	   /* If desired print a     */
  { VerbosePrint2("Done with ",file); }	   	   /*	close message.	     */
 						   /*                        */
  (void)seen();				   	   /* Close the file.	     */
 						   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	mark_string()
** Purpose:	
**		
**		
** Arguments:
**	rec	
**	s	
** Returns:	nothing
**___________________________________________________			     */
static void mark_string(rec,s)			   /*                        */
  Record rec;					   /*                        */
  Uchar   *s;					   /*                        */
{ int    d;					   /*                        */
  Record r;					   /*                        */
 						   /*                        */
  FOREVER					   /*                        */
  {						   /*                        */
    switch (*s)
    { case '\0': return;
      case '"':
	d = 0;
	while ( *++s && (*s!='"' || d>0) )
	{ switch (*s)
	  { case '{': d++; break;
	    case '}': d--; break;
	    case '\\': if (s[1]) s++;
	  }
	}
	if ( *s ) s++;
	break;
      case '{':
	d = 1;
	while ( *++s && d>0 )
	{ switch (*s)
	  { case '{': d++; break;
	    case '}': d--; break;
	    case '\\': if (s[1]) s++;
	  }
	}
	if ( *s ) s++;
	break;
      default:
	if ( is_allowed(*s) )
	{ Uchar c, *t;
	  Uchar *mac = s;
	  while ( is_allowed(*s) ) s++;
	  c = *s;
	  *s ='\0';
	  t = new_Ustring(mac);
	  *s = c;
	  mac = sym_add(t,0);
	  free(t);
	  for ( r=rec; r; r=NextRecord(r) )
	  { if ( *RecordHeap(r) == mac )
	    { SetRecordMARK(r); break;
	    }
	  }
	}
	else s++;
    }						   /*                        */
  }						   /*                        */
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
**		Uppercase letters which are not mentioned are silently folded
**		to their lowercase counterparts. 
** Arguments:
**	file	The file handle for printing.
**	db	The database to print
**	spec	String containing the specification of the parts to print.
** Returns:	nothing
**___________________________________________________			     */
void print_db(file,db,spec)			   /*                        */
  FILE   *file;					   /*                        */
  DB     db;					   /*                        */
  char   *spec;					   /*                        */
{ Record rec;					   /*                        */
  int    allp;					   /* Boolean indicating     */
 						   /* whether all or only the*/
 						   /* marked records should  */
 						   /* be printed.            */
  if ( DBstring(db) != RecordNULL &&
       ( strchr(spec,'S') != NULL
	 || (strchr(spec,'s') != NULL && !rsc_all_macs)
       ) )
  { Record rec1;
    int    i;
 
    for ( rec = DBstring(db);
	  PrevRecord(rec);
	  rec = PrevRecord(rec) ) {}
    rec1 = rec;
    for ( ;
	  rec != RecordNULL;
	  rec = NextRecord(rec) )
    { ClearRecordMARK(rec); }

    if ( (rec=DBnormal(db)) != RecordNULL )
    { 
      while ( PrevRecord(rec) ) rec = PrevRecord(rec);
    }
						   /*                        */
    for ( ;					   /*                        */
	  rec != RecordNULL;			   /*                        */
	  rec = NextRecord(rec) )		   /*                        */
    { 						   /*                        */
      if ( !RecordIsDELETED(rec) )		   /*                        */
      {						   /*                        */
	for ( i=2; i < RecordFree(rec); i+=2 )	   /*                        */
	{ if ( RecordHeap(rec)[i] != NULL )	   /*                        */
	  { mark_string(rec1,RecordHeap(rec)[i+1]);/*                        */
	  }   					   /*                        */
	}					   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
						   /*                        */
  while ( *spec )				   /*                        */
  { switch ( *(spec++) )			   /*                        */
    { case 'p': case 'P': rec = DBpreamble(db); allp = TRUE; break;/*        */
      case 's':           rec = DBstring(db);   allp = rsc_all_macs; break;/**/
      case '$':           rec = DBstring(db);   allp = TRUE; break;/*        */
      case 'S':		  rec = DBstring(db);   allp = FALSE;break;/*        */
      case 'n': case 'N': rec = DBnormal(db);   allp = TRUE; break;/*        */
      case 'c': case 'C': rec = DBcomment(db);  allp = TRUE; break;/*        */
      case 'i': case 'I': rec = DBinclude(db);  allp = TRUE; break;/*        */
      case 'a': case 'A': rec = DBalias(db);    allp = TRUE; break;/*        */
      case 'm': case 'M': rec = DBmodify(db);   allp = TRUE; break;/*        */
      default:		  rec = RecordNULL;	   /*                        */
    }						   /*                        */
 						   /*                        */
    if ( rec != RecordNULL )			   /*                        */
    {						   /*                        */
      while ( PrevRecord(rec) != RecordNULL )	   /* Rewind to beginning.   */
      { rec = PrevRecord(rec); }		   /*                        */
 						   /*                        */
      while ( rec != RecordNULL )		   /*                        */
      {						   /*                        */
	if (!RecordIsDELETED(rec))		   /*                        */
	{					   /*                        */
	  if ( allp || RecordIsMARKED(rec) )	   /*                        */
	  {					   /*                        */
	    fput_record(file,rec,db,(Uchar*)"@");  /*                        */
	  }					   /*                        */
	}					   /*                        */
	else if ( rsc_del_q )			   /*                        */
	{ fput_record(file,rec,db,rsc_del_pre); }  /*                        */
	rec = NextRecord(rec);			   /*                        */
      }						   /*                        */
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
void delete_record(db,rec)			   /*                        */
  DB     db;					   /*                        */
  Record rec;					   /*                        */
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
  if ( rec == *rp )				   /*                        */
  { if ( NextRecord(rec) != RecordNULL )	   /*                        */
    { *rp = NextRecord(rec); }			   /*                        */
    else if ( PrevRecord(rec) != RecordNULL )	   /*                        */
    { *rp = PrevRecord(rec); }			   /*                        */
    else 					   /*                        */
    { *rp = RecordNULL; }			   /*                        */
  }						   /*                        */
  if ( PrevRecord(rec) != RecordNULL )		   /*                        */
  { NextRecord(PrevRecord(rec)) = NextRecord(rec); }/*                       */
  if ( NextRecord(rec) != RecordNULL )		   /*                        */
  { PrevRecord(NextRecord(rec)) = PrevRecord(rec); }/*                       */
  free_1_record(rec);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_forall()
** Purpose:	Visit all normal records in the data base and apply the given
**		function |fct| to each.
**		if this function returns |TRUE| then no more records need to
**		be visited.
**		No special order can be assumed in which the records are seen.
** Arguments:
**	fct	Boolean valued function determining the end of the
**		processing. It takes two arguments a |DB| and a |Record|.
** Returns:	nothing
**___________________________________________________			     */
void db_forall(db,fct)				   /*                        */
  DB              db;				   /*                        */
  int		  (*fct)_ARG((DB,Record));	   /* Function pointer	     */
{ register Record rec,next;			   /*                        */
						   /*                        */
  if ( DBnormal(db) == RecordNULL ) return;	   /*                        */
						   /*                        */
  for ( rec = DBnormal(db);			   /*                        */
	rec != RecordNULL;			   /*                        */
	rec = next )			   	   /*                        */
  { next = NextRecord(rec);			   /*                        */
    if ( (*fct)(db,rec) ) return;		   /*                        */
  }		   				   /*                        */
 						   /*                        */
  for ( rec = PrevRecord(DBnormal(db));		   /*                        */
	rec != RecordNULL;			   /*                        */
	rec = next )			   	   /*                        */
  { next = PrevRecord(rec);			   /*                        */
    if ( (*fct)(db,rec) ) return;		   /*                        */
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
**		the same key then the behaviour is nondeterministic. 
** Arguments:
**	db	Database to search in.
** Returns:	nothing
**___________________________________________________			     */
Record db_find(db,key)				   /*                        */
  DB              db;				   /*                        */
  Uchar		  *key;				   /*                        */
{ register Record rec;				   /*                        */
						   /*                        */
  if ( DBnormal(db) == RecordNULL ) return RecordNULL;/*                     */
						   /*                        */
  for ( rec = DBnormal(db);			   /*                        */
	rec != RecordNULL;			   /*                        */
	rec = NextRecord(rec) )			   /*                        */
  { if ( !RecordIsDELETED(rec) )
    { if ( RecordOldKey(rec) != NULL )
      { if ( RecordOldKey(rec) == key ) return rec; }
      else if ( *RecordHeap(rec) == key ) return rec; 
    }
  }
 						   /*                        */
  for ( rec = PrevRecord(DBnormal(db));		   /*                        */
	rec != RecordNULL;			   /*                        */
	rec = PrevRecord(rec) )			   /*                        */
  { if ( !RecordIsDELETED(rec) )
    { if ( RecordOldKey(rec) != NULL )
      { if ( RecordOldKey(rec) == key ) return rec; }
      else if ( *RecordHeap(rec) == key ) return rec; 
    }
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
Uchar * db_new_key(db,key)			   /*                        */
  DB              db;				   /*                        */
  Uchar		  *key;				   /*                        */
{ register Record rec;				   /*                        */
						   /*                        */
  if ( DBnormal(db) == RecordNULL ) return NULL;   /*                        */
						   /*                        */
  for ( rec = DBnormal(db);			   /*                        */
	rec != RecordNULL;			   /*                        */
	rec = NextRecord(rec) )			   /*                        */
  {
    if ( RecordOldKey(rec) != NULL &&		   /*                        */
	 RecordOldKey(rec) == key )		   /*                        */
    return *RecordHeap(rec); 			   /*                        */
  }						   /*                        */
 						   /*                        */
  for ( rec = PrevRecord(DBnormal(db));		   /*                        */
	rec != RecordNULL;			   /*                        */
	rec = PrevRecord(rec) )			   /*                        */
  {
    if ( RecordOldKey(rec) != NULL &&		   /*                        */
	 RecordOldKey(rec) == key )		   /*                        */
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
void db_rewind(db)				   /*                        */
  DB db;					   /*                        */
{					   	   /*                        */
  if ( DBnormal(db) == RecordNULL ) return;	   /*                        */
 						   /*                        */
  while ( PrevRecord(DBnormal(db)) != RecordNULL  )/*                        */
  { DBnormal(db) = PrevRecord(DBnormal(db));	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec__sort()
** Purpose:	
**		
**		
** Arguments:
**	rec	
**	less	
** Returns:	
**___________________________________________________			     */
static Record rec__sort(rec,less)		   /*                        */
  Record rec;					   /*                        */
  int	 (*less)_ARG((Record,Record));	   	   /* Function pointer	     */
{ Record r;				   	   /*                        */
  Record new;		   		   	   /*                        */
 						   /*                        */
  if ( rec == RecordNULL ) return rec;  	   /*                        */
  r = RecordNULL ;				   /*                        */
 						   /*                        */
  while ( PrevRecord(rec) != RecordNULL )	   /*                        */
  { rec = PrevRecord(rec); }			   /*                        */
 						   /*                        */
  while ( rec != RecordNULL )			   /*                        */
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
** The rest is simply legwork.
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
static Record insert_record(rec,ptr,less)	   /*			     */
  register Record rec;				   /*			     */
  register Record ptr;				   /*			     */
  int		  (*less)_ARG((Record,Record));	   /* Function pointer	     */
{					   	   /*			     */
  if ( ptr == RecordNULL ) {	   		   /* List is empty	     */
    PrevRecord(rec) = RecordNULL;		   /*		             */
    NextRecord(rec) = RecordNULL;		   /*			     */
    return rec;					   /*                        */
  }						   /*                        */
						   /*			     */
  if ( (*less)(rec,ptr) )			   /*			     */
  {						   /*                        */
    while ( PrevRecord(ptr) != RecordNULL )	   /* Move leftward.	     */
    { ptr = PrevRecord(ptr);			   /*			     */
      if ( !(*less)(rec,ptr) )			   /*			     */
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
    while ( NextRecord(ptr) != RecordNULL )	   /* Move rightward.	     */
    { ptr = NextRecord(ptr);			   /*			     */
      if ( (*less)(rec,ptr) )			   /*			     */
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
** Function:	cmp_heap()
** Purpose:	Compare the keys of two records. The keys are stored at the
**		top of the heap. 
** Arguments:
**	r1	First record to compare.
**	r2	Second record to compare.
** Returns:	|TRUE| iff the first record is smaller than the second one.
**___________________________________________________			     */
static int cmp_heap(r1,r2)		   	   /*                        */
  register Record r1;				   /*                        */
  register Record r2;				   /*                        */
{ return strcmp((char*)*RecordHeap(r1),		   /*                        */
		(char*)*RecordHeap(r2))<0;	   /*                        */
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
void db_mac_sort(db)			   	   /*                        */
  DB db;				   	   /*                        */
{						   /*                        */
  DBstring(db) = rec__sort(DBstring(db),cmp_heap); /*                        */
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
**		takes two records and returns |TRUE| iff the first one
**		is less than the second one.
** Returns:	nothing
**___________________________________________________			     */
void db_sort(db,less)				   /*                        */
  DB  db;				   	   /*                        */
  int (*less)_ARG((Record,Record));	   	   /* Function pointer	     */
{						   /*                        */
  DBnormal(db) = rec__sort(DBnormal(db),less);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_string()
** Purpose:	Try to find the definition of a macro.
**		First, the local values in the database |db| are considered.
**		If this fails and |localp| is |FALSE| then the global list
**		is searched aswell. If all fails |NULL| is returned.
** Arguments:
**	db	Database
**	s	Name of the \BibTeX{} macro to expand.
**	localp	Boolean determining whether the search is only local to the db.
** Returns:	The macro expansion or |NULL| upon failure.
**___________________________________________________			     */
Uchar * db_string(db,s,localp)			   /*                        */
  DB     db;					   /*                        */
  Uchar   *s;					   /*                        */
  int    localp;				   /*                        */
{ Record rec;					   /*                        */
 						   /*                        */
  if ( (rec=DBstring(db)) )			   /*                        */
  {						   /*                        */
    for ( ; rec; rec=NextRecord(rec) )		   /*                        */
    { if ( RecordHeap(rec)[0] == s )		   /*                        */
      { return RecordHeap(rec)[1]; }		   /*                        */
    }						   /*                        */
    for ( rec=PrevRecord(DBstring(db)) ; rec; rec=PrevRecord(rec) )/*        */
    { if ( RecordHeap(rec)[0] == s )		   /*                        */
      { return RecordHeap(rec)[1]; }		   /*                        */
    }						   /*                        */
  }						   /*                        */
  						   /*                        */
  return (localp?NULL:look_macro(s,0));		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	db_count()
** Purpose:	Count all entries in a database. This includes normal
**		aswell as special records. The result is stored in a
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
int *db_count(db,lp)				   /*                        */
  DB         db;				   /*                        */
  int        *lp;				   /*                        */
{ static int *count;				   /*                        */
  static int len = 0;				   /*                        */
  int        i;					   /*                        */
  Record     rec;				   /*                        */
 						   /*                        */
  for ( i=5; get_entry_type(i)!=NULL ; i++ ) ;	   /*                        */
  if ( lp ) *lp = i;				   /*                        */
  i++;						   /*                        */
 						   /*                        */
  if ( len == 0 )				   /*                        */
  { len = i;					   /*                        */
    count = (int*)malloc(len*sizeof(int));	   /*                        */
  }						   /*                        */
  else if ( len != i )				   /*                        */
  { len = i;					   /*                        */
    count = (int*)realloc(count,len*sizeof(int));  /*                        */
  }						   /*                        */
  if ( count == NULL )				   /*                        */
  { OUT_OF_MEMORY("count"); }		   	   /*                        */
						   /*                        */
  for ( i=0; i<len; i++ ) count[i] = 0;		   /*                        */
  count[len-1] = -1;				   /*                        */
						   /*                        */
  if ( (rec=DBstring(db)) != RecordNULL )
  { while ( PrevRecord(rec) != RecordNULL ) rec = PrevRecord(rec);
    while ( rec != RecordNULL )
    { count[BIB_STRING]++;
      rec = NextRecord(rec);
    }
  }
  if ( (rec=DBcomment(db)) != RecordNULL )
  { while ( PrevRecord(rec) != RecordNULL ) rec = PrevRecord(rec);
    while ( rec != RecordNULL )
    { count[BIB_COMMENT]++;
      rec = NextRecord(rec);
    }
  }
  if ( (rec=DBpreamble(db)) != RecordNULL )
  { while ( PrevRecord(rec) != RecordNULL ) rec = PrevRecord(rec);
    while ( rec != RecordNULL )
    { count[BIB_PREAMBLE]++;
      rec = NextRecord(rec);
    }
  }
  if ( (rec=DBalias(db)) != RecordNULL )
  { while ( PrevRecord(rec) != RecordNULL ) rec = PrevRecord(rec);
    while ( rec != RecordNULL )
    { count[BIB_ALIAS]++;
      rec = NextRecord(rec);
    }
  }
  if ( (rec=DBmodify(db)) != RecordNULL )
  { while ( PrevRecord(rec) != RecordNULL ) rec = PrevRecord(rec);
    while ( rec != RecordNULL )
    { count[BIB_MODIFY]++;
      rec = NextRecord(rec);
    }
  }
  if ( (rec=DBinclude(db)) != RecordNULL )
  { while ( PrevRecord(rec) != RecordNULL ) rec = PrevRecord(rec);
    while ( rec != RecordNULL )
    { count[BIB_INCLUDE]++;
      rec = NextRecord(rec);
    }
  }
  if ( (rec=DBnormal(db)) != RecordNULL )
  { while ( PrevRecord(rec) != RecordNULL ) rec = PrevRecord(rec);
    while ( rec != RecordNULL )
    { count[RecordType(rec)]++;
      rec = NextRecord(rec);
    }
  }
						   /*                        */
  return count;					   /*                        */
}						   /*------------------------*/
