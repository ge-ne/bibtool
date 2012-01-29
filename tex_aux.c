/******************************************************************************
** $Id: tex_aux.c,v 1.13 2012-01-29 17:17:07 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2012 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/expand.h>
#include <bibtool/sbuffer.h>
#include <bibtool/error.h>
#include <bibtool/rsc.h>
#include <bibtool/key.h>
#include <bibtool/symbols.h>
#include <bibtool/sbuffer.h>
#include <bibtool/wordlist.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#include <bibtool/tex_aux.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 static void save_ref _ARG((Uchar *s));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

 static StringBuffer* aux_sb = (StringBuffer*)0;

 static int cite_star        = TRUE;

 static WordList cite[32]    = 
 { WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL,
   WordNULL, WordNULL, WordNULL, WordNULL
 };

/*-----------------------------------------------------------------------------
** Function:	clear_aux()
** Purpose:	Reset the aux table to the initial state.
**		
**		
** Arguments:   none
** Returns:	nothing
**___________________________________________________			     */
void clear_aux()				   /*                        */
{ int i;					   /*                        */
  cite_star = TRUE;				   /*                        */
  for ( i=0; i<32; i++ )			   /*                        */
  { free_words(&cite[i],sym_unlink); }		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	foreach_aux()
** Purpose:	Apply the function to all words in the citation list of the
**		aux file.
**		
** Arguments:
**	fct	funtion to apply
** Returns:	|cite_star|
**___________________________________________________			     */
int foreach_aux(fct)				   /*                        */
  int (fct)_ARG((Uchar*));			   /*                        */
{ int i;					   /*                        */
  for ( i=0; i<32; i++ )			   /*                        */
  { foreach_word(cite[i],fct); }		   /*                        */
  return cite_star;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	save_ref()
** Purpose:	Store the cite key for selection.
**		If the cite key is "*" then all should be selected.
**		This is written e.g. by \nocite{*}
** Arguments:
**	s
** Returns:	nothing
**___________________________________________________			     */
static void save_ref(s)				   /*                        */
  register Uchar *s;				   /*                        */
{ 						   /*                        */
  if ( cite_star ) return;			   /*                        */
 						   /*                        */
  if ( *s == '*' && *(s+1) == '\0' )		   /*                        */
  { clear_aux(); }				   /*                        */
  else { add_word(symbol(s),&cite[*s&31]); }	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	aux_used()
** Purpose:	Check whether a reference key has been requested by the
**		previously read aux file. The request can either be expicit
**		or implicit if a * is used.
** Arguments:
**	s	reference key to check
** Returns:	
**___________________________________________________			     */
int aux_used(s)				   	   /*                        */
  Uchar * s;					   /*                        */
{						   /*                        */
  return (  cite_star				   /*                        */
	 || find_word(s,cite[*s&31])  );	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_aux()
** Purpose:	Analyze an aux file. If additional files are
**		requested, e.g. by |\include| instructions in the
**		original source file then those are read as well. Each
**		citation found is remembered and can be queried
**		afterwards. If a |\cite{*}| has been used then only a
**		flag is set and all citation keys are discarted.
**
**		The aux file contains also the information about the
**		\BibTeX{} files used. For each such file the function
**		|fct| is called with the file name as argument. This
**		function can arrange things that those \BibTeX{} files
**		are read into a database.
**
**		This function has only a very simple parser for the
**		aux file. Thus it can be confused by legal
**		contents. But a similar thing can happen to \BibTeX{}
**		aswell. 
** Arguments:
**	fname	The file name of the aux file.
**	fct	A function to be called for each \BibTeX{} file requested.
**	verbose	Boolean indicating whether messages should be produced
**		indicating the status of the operation.
** Returns:	|TRUE| iff the file could not be opened.
**___________________________________________________			     */
int read_aux(fname,fct,verbose)			   /*                        */
  Uchar 	*fname;			   	   /* aux file name          */
  void		(*fct)_ARG((char*));		   /*                        */
  int           verbose;			   /*                        */
{ FILE 	        *file;				   /*                        */
  int           c;                                 /*                        */
  register char *s;				   /*                        */
 						   /*                        */
  cite_star  = FALSE;				   /*                        */
  rsc_select = TRUE; 				   /*                        */
  					   	   /*                        */
  if ( (file=fopen((char*)fname,"r") ) == NULL )   /*                        */
  { StringBuffer *sb = sbopen();                   /*                        */
    sbputs((char*)fname,sb);			   /*                        */
    sbputs(".aux",sb);                             /*                        */
    file = fopen(sbflush(sb),"r");                 /*                        */
    sbclose(sb);                                   /*                        */
  }			   			   /*                        */
  if ( file == NULL )				   /*                        */
  { ERROR3("aux file ",fname," not found.");	   /*                        */
    return TRUE;				   /*                        */
  }						   /*                        */
 						   /*                        */
  rsc_del_q = FALSE;				   /*                        */
 						   /*                        */
  if ( verbose ) 				   /*                        */
  { VerbosePrint2("Analyzing ",fname); }	   /*                        */
 						   /*                        */
  if ( aux_sb == (StringBuffer*)0 )		   /*                        */
  { aux_sb = sbopen(); }			   /*                        */
 						   /*                        */
  for(c = getc(file); c != EOF; c = getc(file))    /*                        */
  { if ( c == '\\' ) 				   /*                        */
    { for(c = getc(file);                          /*                        */
          c != EOF && (is_alpha(c&0xff) || c == '@');/*                      */
          c = getc(file))			   /*                        */
      { (void)sbputchar(c, aux_sb); }              /*                        */
      s = sbflush(aux_sb);			   /*                        */
      sbrewind(aux_sb);				   /*                        */
 						   /*                        */
      if ( strcmp(s, "citation" ) == 0 )   	   /*                        */
      { do					   /* Save a cite key.       */
	{ switch ( c=getc(file) )		   /*                        */
	  { case EOF: break;			   /*                        */
	    case ',':				   /*                        */
	    case '}':		   	   	   /*                        */
	      s = sbflush(aux_sb);		   /*                        */
	      sbrewind(aux_sb);			   /*                        */
	      save_ref((Uchar*)s);		   /*                        */
	      break;				   /*                        */
	    default:				   /*                        */
	      (void)sbputchar(ToLower(c&0xff),aux_sb);/*                     */
	  }	   				   /*                        */
	} while ( c != '}' && c != EOF );	   /*                        */
      }						   /*                        */
      else if ( strcmp(s,"bibdata" ) == 0 )	   /*                        */
      { c = getc(file);				   /* Save a bib file name   */
	(void)sbputchar((Uchar)c, aux_sb);	   /*                        */
	while ( c != '}' && c != EOF )		   /*                        */
	{ c = getc(file);			   /*                        */
	  if ( c == ',' || c == '}' )		   /*                        */
	  { s = sbflush(aux_sb);		   /*                        */
	    sbrewind(aux_sb);			   /*                        */
	    (*fct)((char*)symbol((Uchar*)s));	   /*                        */
	  }					   /*                        */
	  else					   /*                        */
	  { (void)sbputchar(c,aux_sb); }	   /*                        */
	}					   /*                        */
      }						   /*                        */
      else if ( strcmp(s,"@input" )==0 )	   /* Read another aux file  */
      { while( (c=getc(file)) != '}' && c != EOF ) /*                        */
	{ (void)sbputchar(c,aux_sb); }		   /*                        */
	s = sbflush(aux_sb);			   /*                        */
	sbrewind(aux_sb);			   /*                        */
	    					   /*                        */
	read_aux((Uchar*)s,fct,verbose);	   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  (void)fclose(file);				   /*                        */
 						   /*                        */
#ifdef DEBUG
  { register int i;				   /*                        */
    WordList wl;				   /*			     */
						   /*			     */
    for ( i=0; i<32; ++i )			   /*                        */
    { ErrPrintF("--- BibTool: %d\n",i);	   	   /*                        */
      for ( wl=cite[i]; wl!=WordNULL; wl=NextWord(wl) )/*		     */
      { ErrPrintF("%s\n",ThisWord(wl)); }	   /*			     */
    }		   	   			   /*                        */
  }						   /*                        */
#endif
  return FALSE;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	apply_aux()
** Purpose:	This function deletes all entries which are not
**		requested by the recently read aux file. This means
**		that the entry to be kept is either mentioned directly,
**		it is crossreferenced, or all entries are requested
**		with the |\nocite{*}| feature.
**		
**		Note that the entries are in fact not deleted but only
**		marked as deleted. Thus they can be recovered if
**		necessary. 
** Arguments:
**	db	Database to clean.
** Returns:	|FALSE| iff all entries are kept because of an
**		explicit or implicit star (*).
**___________________________________________________			     */
int apply_aux(db)				   /*                        */
  DB     db;					   /*                        */
{ Record rec, rec1;				   /*                        */
 						   /*                        */
  if ( cite_star ) return FALSE;		   /* No selection desired.  */
 						   /*                        */
  rec = DBnormal(db);				   /*                        */
  if ( rec == RecordNULL ) return TRUE;		   /* No entries left anyhow.*/
 						   /*                        */
  while ( PrevRecord(rec) != RecordNULL )	   /* Rewind                 */
  { rec = PrevRecord(rec); }			   /*                        */
  rec1 = rec;					   /*                        */
 						   /*                        */
  for ( ;					   /* Phase 1:               */
	rec != RecordNULL;			   /*  Mark all entries      */
	rec = NextRecord(rec) )			   /*  contained in the aux  */
  { if ( *RecordHeap(rec) &&		   	   /*  file and unmark the   */
	 find_word(*RecordHeap(rec),	   	   /*  others.               */
		   cite[(**RecordHeap(rec))&31]) ) /*                        */
    { SetRecordMARK(rec); }			   /*                        */
    else					   /*                        */
    { ClearRecordMARK(rec); }			   /*                        */
  }						   /*                        */
 						   /*                        */
 						   /*                        */
  for ( rec = rec1;				   /* Phase 2:               */
	rec != RecordNULL;			   /*  For all marked entries*/
	rec = NextRecord(rec) )		   	   /*  which have a xref and */
  {						   /*  mark all xrefs.       */
    if ( RecordIsMARKED(rec) &&		   	   /*                        */
	 RecordIsXREF(rec)   &&		   	   /*                        */
	 !RecordIsDELETED(rec)		   	   /*                        */
       )					   /*                        */
    { Uchar  *key = (Uchar*)"???";		   /*                        */
      int    count;				   /*                        */
      Record r = rec;				   /*                        */
 						   /*                        */
      for ( count = rsc_xref_limit;		   /* Prevent infinite loop  */
	    count >= 0	      &&		   /*                        */
	      RecordIsXREF(r) &&		   /*                        */
	      !RecordIsDELETED(r);		   /*                        */
	    count-- )				   /*                        */
      {	key = get_field(db,r,sym_crossref);	   /*                        */
	if ( key == NULL )			   /*                        */
	{ count = -1; }			   	   /*                        */
	else					   /*                        */
	{ key = symbol(lower(expand_rhs(key,	   /*                        */
					sym_empty, /*                        */
					sym_empty, /*                        */
					db)));     /*                        */
	  if ( (r=db_find(db,key)) == RecordNULL ) /*                        */
	  { ErrPrintF("*** BibTool: Crossref `%s' not found.\n",key);/*      */
	    count = -1;			   	   /*                        */
	  }					   /*                        */
	  else				   	   /*                        */
	  {					   /*                        */
	    if ( RecordIsMARKED(r) )		   /*                        */
	    { count = -1; }			   /*                        */
	    SetRecordMARK(r);			   /*                        */
	    ClearRecordDELETED(r);		   /*                        */
	  }					   /*                        */
	}			   		   /*                        */
      }			   		   	   /*                        */
      if ( count == -1 )			   /*                        */
      { ErrPrintF("*** BibTool: Crossref limit exceeded; `%s' possibly looped.\n",
		  key);				   /*                        */
      }						   /*                        */
    }    					   /*                        */
  }						   /*                        */
 						   /*                        */
  for ( rec = rec1;				   /* Phase 3:               */
	rec != RecordNULL;			   /*  Delete unmarked       */
	rec = NextRecord(rec) )			   /*  entries.              */
  { if ( !RecordIsMARKED(rec) )			   /*                        */
    { SetRecordDELETED(rec); }			   /*                        */
  }						   /*                        */
 						   /*                        */
  return TRUE;					   /*                        */
}						   /*------------------------*/

