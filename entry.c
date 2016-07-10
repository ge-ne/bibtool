/*** entry.c ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2016 Gerd Neugebauer
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
 static bool match _ARG((String s, String t));	   /* entry.c                */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*****************************************************************************/
/***									   ***/
/*****************************************************************************/

 int type_xdata = -1;				   /*                        */

#define EntrySizeIncrement 8

 Symbol	    *entry_type;
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
**		  before the bibliography environment.
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
  def_entry_type(symbol((String)"STRING")  );	   /*			     */
  def_entry_type(symbol((String)"PREAMBLE"));	   /*			     */
  def_entry_type(symbol((String)"COMMENT") );	   /*			     */
  def_entry_type(symbol((String)"ALIAS")   );	   /*			     */
  def_entry_type(symbol((String)"MODIFY")  );	   /*			     */
  def_entry_type(symbol((String)"INCLUDE") );	   /*			     */
#ifdef INITIALIZE_BIBTEX_ENTRIES
  for ( wp = word_list; *wp != NULL; ++wp )	   /* add compiled in types. */
  { def_entry_type(symbol((String)(*wp))); }	   /*			     */
#endif
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	def_entry_type()
** Purpose:	Dynamically define an entry type. If the entry type
**		already exists then a new printing representation is
**		stored. 
**
**		If no memory is left then an error is raised and the
**		program is terminated
** Arguments:
**	s	String containing the name of the entry.
** Returns:	nothing
**___________________________________________________			     */
void def_entry_type(sym)			   /*			     */
  Symbol sym;				   	   /*			     */
{ int  i;				   	   /*                        */
  String s = SymbolValue(sym);			   /*                        */
 						   /*                        */
  for (i = 0; i < entry_ptr; ++i)		   /*			     */
  { 						   /*                        */
    if (case_eq(s, SymbolValue(EntryName(i))))	   /*			     */
    { 
      EntryName(i) = sym; 		   	   /*			     */
      return;				   	   /*			     */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  if ( entry_ptr <= entry_size )		   /*			     */
  { entry_size += EntrySizeIncrement;		   /*			     */
    entry_type = ( entry_ptr == 0		   /*			     */
		  ? (Symbol*)malloc((size_t)(entry_size * sizeof(Symbol)))
		  : (Symbol*)realloc((void*)entry_type,
				     (size_t)(entry_size * sizeof(Symbol)))
		  );				   /*			     */
    if ( entry_type == (Symbol*)NULL )		   /*			     */
    { OUT_OF_MEMORY("entry type"); }		   /*                        */
  }						   /*			     */
 						   /*                        */
  if (case_eq(s, (String)"xdata"))		   /*                        */
  { type_xdata = entry_ptr; }			   /*                        */
 						   /*                        */
  entry_type[entry_ptr++] = sym;	   	   /*		             */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	match()
** Purpose:	Compare two strings ignoring case.
** Arguments:
**	s	First string
**	t	Second string
** Returns:	|true| iff the arguments are identical or the second
**		string is a substring not followed by a letter or digit.
**___________________________________________________			     */
static bool match(s,t)				   /*			     */
  register String s;				   /*			     */
  register String t;				   /*			     */
{						   /*			     */
  while (*t)					   /*			     */
  { if ( ToLower(*s) != ToLower(*t) ) return false;/*			     */
    s++; t++;					   /*			     */
  }						   /*			     */
  return (is_alpha(*s) || is_digit(*s)		   /*                        */
	  ? false				   /*                        */
	  : true);				   /*		             */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	find_entry_type()
** Purpose:	Look up an entry type in the array of defined entries.
** Arguments:
**	s	String of the potential entry name.
** Returns:	The index in the array or |NOOP|.
**___________________________________________________			     */
int find_entry_type(s)			   	   /*			     */
  String s;				   	   /*			     */
{ int i;				   	   /*			     */
						   /*			     */
  for (i = 0; i < entry_ptr; ++i)		   /*			     */
  { if (match(s, SymbolValue(EntryName(i))))	   /*			     */
    { return i; }				   /*			     */
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
Symbol  get_entry_type(idx)			   /*                        */
  int idx;				   	   /*                        */
{						   /*                        */
  return (idx < 0 || idx >= entry_ptr		   /*                        */
	  ? NO_SYMBOL				   /*                        */
	  : EntryName(idx));			   /*                        */
}						   /*------------------------*/
