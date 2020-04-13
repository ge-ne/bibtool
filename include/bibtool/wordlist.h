/*** wordlist.h ***************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2020 Gerd Neugebauer
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
******************************************************************************/

#ifndef WordNULL

#include <bibtool/type.h>

/*-----------------------------------------------------------------------------
** Typedef:	WordList
** Purpose:	This data type represents a node in a list of
**		strings. This list only provides a next pointer. and
**		is pretty generic.
**________________________________________________   			     */
 typedef struct wORDlIST			   /*                        */
 { Symbol	   wl_word;			   /* String value of	     */
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
** Type:	String
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
 bool find_word _ARG((String s, WordList wl));	   /* wordlist.c             */
 bool foreach_word _ARG((WordList wl,bool (*fct)_ARG((Symbol))));/* wordlist.c*/
 void free_words _ARG((WordList *wlp,void (*fct)_ARG((Symbol))));/* wordlist.c*/
 void add_word _ARG((Symbol s,WordList *wlp));	   /* wordlist.c             */

/*---------------------------------------------------------------------------*/
#endif
