/******************************************************************************
** $Id: entry.c,v 1.2 2007-02-08 05:27:32 gene Exp $
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
**	This module contains functions which deal with entry types. 
**	Right from the beginning only the special record types are
**	known. Those special record types are |@Comment|, |@Preamble|,
**	|@String|, |@Include|, |@Modify|, and |@Alias|.
**
**	In addition to those special records the user can define
**	additional record types which are denoted as ``normal''. E.g.\
**	usually |@Article| and |@Book| are defined which are
**	``normal'' record types.
**
**	The record types are are managed in this module. In the other
**	modules only numerical representations are used. This module
**	provides means to map those numerical ids to the string
**	representation and back. It is also possible to define
**	additional record types.
**
**	Part of this module is likely to be integrated into databases.
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/entry.h>
#include <bibtool/error.h>
#include "config.h"

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 static int match _ARG((Uchar *s,Uchar *t));	   /* entry.c                */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*****************************************************************************/
/***									   ***/
/*****************************************************************************/

#define EntrySizeIncrement 8

 Uchar	    **entry_type;
 static int entry_ptr	= 0;
 static int entry_size  = 0;

/*-----------------------------------------------------------------------------
** Function:	init_entries()
** Purpose:	Predefine some entry types which are stored at startup time
**		in an array. The following entry types are predefined
**		because they are considered special by \BibTeX:
**		\begin{description}
**		\item [BIB\_STRING] denotes a \BibTeX{} macro definition.
**		\item [BIB\_PREAMBLE] denotes a preamble item which goes
**		  before the bibligraphy environment.  
**		\item [BIB\_COMMENT] denotes a comment entry which is
**		  passed to the output file.
**		\item [BIB\_ALIAS] denotes an alias entry which renames an
**		  existing entry.
**		\item [BIB\_MODIFY] denotes a modification request which
**		  alters an existing entry.
**		\item [BIB\_INCLUDE] denotes an include request which reads
**		  in another \BibTeX{} file.
**		\end{description}
**		Note that this function is for internal purposes
**		only. The normal user should call |init_bibtool()|
**		instead.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void init_entries()				   /*			     */
{						   /*			     */
#ifdef INITIALIZE_BIBTEX_ENTRIES
  static char *word_list[] =			   /* default entry types.   */
  { INITIALIZE_BIBTEX_ENTRIES, NULL };		   /* Mark the end with NULL */
  register char**wp;				   /*			     */
#endif
						   /*			     */
  def_entry_type((Uchar*)"STRING"  );		   /*			     */
  def_entry_type((Uchar*)"PREAMBLE");		   /*			     */
  def_entry_type((Uchar*)"COMMENT" );		   /*			     */
  def_entry_type((Uchar*)"ALIAS"   );		   /*			     */
  def_entry_type((Uchar*)"MODIFY"  );		   /*			     */
  def_entry_type((Uchar*)"INCLUDE" );		   /*			     */
#ifdef INITIALIZE_BIBTEX_ENTRIES
  for ( wp=word_list; *wp!=NULL; ++wp )		   /* add compiled in types. */
  { def_entry_type((Uchar*)(*wp)); }		   /*			     */
#endif
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	def_entry_type()
** Purpose:	Dynamically define an entry type. If the entry type
**		already exists then a new printing representation is
**		stored. 
**
**		If no memory is left then an error is raised and the
**		program is termined
** Arguments:
**	s	String containing the name of the entry.
** Returns:	nothing
**___________________________________________________			     */
void def_entry_type(s)				   /*			     */
  Uchar *s;				   	   /*			     */
{ int  i;				   	   /*                        */
 						   /*                        */
  for (i=0; i<entry_ptr; ++i)			   /*			     */
  { 						   /*                        */
    if ( case_cmp(s,EntryName(i)) )		   /*			     */
    { free(EntryName(i));			   /*                        */
      EntryName(i) = new_Ustring(s); 		   /*			     */
      return;				   	   /*			     */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  if ( entry_ptr <= entry_size )		   /*			     */
  { entry_size += EntrySizeIncrement;		   /*			     */
    entry_type = ( entry_ptr == 0		   /*			     */
		  ? (Uchar**)malloc((size_t)(entry_size*sizeof(Uchar*)))
		  : (Uchar**)realloc((char*)entry_type,
				     (size_t)(entry_size*sizeof(Uchar*)))
		  );				   /*			     */
    if ( entry_type == (Uchar**)NULL )		   /*			     */
    { OUT_OF_MEMORY("entry type"); }		   /*                        */
  }						   /*			     */
  entry_type[entry_ptr++] = new_Ustring(s);	   /*		             */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	match()
** Purpose:	Compare two strings ignoring case.
**		Return TRUE iff they are identical or the second string is a
**		substring not followed by a letter or digit.
** Arguments:
**	s	First string
**	t	Second string
** Returns:	
**___________________________________________________			     */
static int match(s,t)				   /*			     */
  register Uchar *s;				   /*			     */
  register Uchar *t;				   /*			     */
{						   /*			     */
  while( *t )					   /*			     */
  { if ( ToLower(*s) != ToLower(*t) ) return(FALSE);/*			     */
    s++; t++;					   /*			     */
  }						   /*			     */
  return( is_alpha(*s) || is_digit(*s) ? FALSE : TRUE );/*		     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	find_entry_type()
** Purpose:	Look up an entry type in the array of defined entries.
** Arguments:
**	s	String of the potential entry name.
** Returns:	The index in the array or |NOOP|.
**___________________________________________________			     */
int find_entry_type(s)				   /*			     */
  Uchar *s;				   	   /*			     */
{ int i;				   	   /*			     */
						   /*			     */
  for (i=0; i<entry_ptr; ++i)			   /*			     */
  { if ( match(s,EntryName(i)) )		   /*			     */
    { return(i); }				   /*			     */
  }						   /*			     */
  return BIB_NOOP;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_entry_type()
** Purpose:	Get the printable string representation corresponding
**		to the numerical entry type given as argument. If no
**		entry type is defined for the given index then |NULL|
**		is returned.
** Arguments:
**	idx	Index of entry type.
** Returns:	Print representation of the entry type or |NULL|.
**___________________________________________________			     */
Uchar * get_entry_type(idx)			   /*                        */
  int idx;				   	   /*                        */
{						   /*                        */
  return (idx<0||idx>=entry_ptr ? NULL : EntryName(idx));/*                  */
}						   /*------------------------*/
