/******************************************************************************
** $Id: wordlist.h,v 1.8 2013-11-24 22:07:53 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2013 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#ifndef WordNULL

#include <bibtool/type.h>

/*-----------------------------------------------------------------------------
** Typedef:	WordList
** Purpose:	This data type represents a node in a list of
**		strings. This list only provides a next pointer. and
**		is prety generic.
**________________________________________________   			     */
 typedef struct wORDlIST			   /*                        */
 { Uchar	   *wl_word;			   /* String value of	     */
 						   /*  this node.            */
   struct wORDlIST *wl_next;			   /* Pointer to the next    */
 						   /*  node.                 */
 } SWordList, *WordList;			   /*                        */

/*-----------------------------------------------------------------------------
** Constant:	WordNULL()
** Type:	WordList
** Purpose:	This is the |NULL| value for a |WordList|. It
**		terminates the list and represents the empty node.
** Returns:	|NULL| of appropriate type.
**___________________________________________________			     */
#define WordNULL    ((WordList)0)

/*-----------------------------------------------------------------------------
** Macro:	ThisWord()
** Type:	Uchar *
** Purpose:	This macro returns the string of a |WordList| node.
** Arguments:
**	WL	|WordList| to consider which is not |WordNULL|.
** Returns:	The word stored in this node.
**___________________________________________________			     */
#define ThisWord(WL) ((WL)->wl_word)

/*-----------------------------------------------------------------------------
** Macro:	NextWord()
** Type:	WordList
** Purpose:	This macro returns the next |WordList| node of a given
**		|WordList| if this is not |WordNULL|.
** Arguments:
**	WL	|WordList| to consider which is not |WordNULL|.
** Returns:	The next |WordList|.
**___________________________________________________			     */
#define NextWord(WL) ((WL)->wl_next)

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int find_word _ARG((Uchar *s,WordList wl));	   /* wordlist.c             */
 int foreach_word _ARG((WordList wl,int (*fct)_ARG((Uchar*))));/* wordlist.c */
 void free_words _ARG((WordList *wlp,void (*fct)_ARG((Uchar*))));/* wordlist.c*/
 void add_word _ARG((Uchar *s,WordList *wlp));	   /* wordlist.c             */

#endif
