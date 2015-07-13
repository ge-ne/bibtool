/*** type.c *******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** 
** Description:
**	This file contains functions to support a separate treatment of
**	character types. The normal functions and macros in |ctype.h| are 
**	replaced by those in |type.h|. This file contains an initialization
**	function which is required for the macros in |type.h| to work
**	properly. 
** 
**	See also the documentation of the header file |type.h| for
**	further information.
** 
******************************************************************************/

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#define INIT_TYPE
#include <bibtool/type.h>

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

#define to_lower(C)           ((C) + 'a'-'A')
#define to_upper(C)           ((C) + 'A'-'a')

/*-----------------------------------------------------------------------------
** Function:	init_type()
** Purpose:	This is the initialization routine for this file. This
**		has to be called before some of the macros in |type.h|
**		will work as described. It does no harm to call this
**		initialization more than once. It just takes some time.
**
**		Note that this function is for internal purposes
**		only. The normal user should call |init_bibtool()|
**		instead.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void init_type()				   /*                        */
{ register int i;				   /*                        */
 						   /*                        */
  for ( i = 0; i < 256; ++i )			   /*                        */
  { trans_lower[i] = is_upper(i)?to_lower(i):i;	   /*                        */
    trans_upper[i] = is_lower(i)?to_upper(i):i;	   /*                        */
    trans_id[i] = i;				   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	add_word_sep()
** Type:	void
** Purpose:	
**		Mark some characters as word separator.
** Arguments:
**	s	the allowed word separator characters
** Returns:	nothing
**___________________________________________________			     */
void add_word_sep(s)				   /*                        */
  register String s;				   /*                        */
{						   /*                        */
  if ( s == StringNULL ) return;		   /*                        */
  for ( ; *s ; s++ )				   /*                        */
  { type__allowed[*s] |= T__WordSep; }		   /*                        */
}						   /*------------------------*/

#ifdef DEBUG
#include <assert.h>
#endif

/*-----------------------------------------------------------------------------
** Function:	case_cmp()
** Purpose:	Compare two strings ignoring cases. If the strings are
**		identical up to differences in case then this function
**		returns |TRUE|.
** Arguments:
**	s	First string to consider.
**	t	Second string to consider.
** Returns:	|FALSE| iff the strings differ.
**___________________________________________________			     */
int case_cmp(s, t)				   /*                        */
  register String s;			   	   /*                        */
  register String t;			   	   /*                        */
{						   /*                        */
#ifdef DEBUG
  assert(s!=NULL);				   /*                        */
  assert(t!=NULL);				   /*                        */
#endif
  while ( *s )					   /*                        */
  { if ( ToLower(*(s++)) != ToLower(*(t++)) )	   /*                        */
      return 0;				   	   /*                        */
  }						   /*                        */
#ifdef DEBUG
  assert(t!=NULL);				   /*                        */
#endif
  return (*t=='\0'?1:0);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	lower()
** Purpose:	Function to translate all letters in a string to lower case.
** Arguments:
**	s	string to convert
** Returns:	The converted string.
**___________________________________________________			     */
String lower(s)					   /*                        */
  register String s;				   /*                        */
{ String t = s;					   /*                        */
  while ( *s ) { *s = ToLower(*s); ++s; }	   /*                        */
  return t;				   	   /*                        */
}						   /*------------------------*/
