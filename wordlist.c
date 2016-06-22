/*** wordlist.c ***************************************************************
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
**	This module contains functions which deal with lists of
**	words. Those words are in fact simple strings. Thus this
**	module provides a very general functionality, namely a list of
**	strings and the associated methods.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/error.h>
#include <bibtool/symbols.h>
#include <bibtool/wordlist.h>

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Function:	add_word()
** Purpose:	Put a string into a word list. The string itself is
**		\emph{not} copied. Thus it is highly recommended to
**		use symbols as words nevertheless this is not
**		required as long as the string |s| persists as long as
**		the word list exists. 
**
**		The second argument is a pointer to a |WordList|. This
**		destination is modified by adding a new node. The use
**		of a pointer allows a uniform treatment of empty and
**		not empty word lists.
**
**		If no memory is left then an error is raised and the program
**		is terminated.
** Arguments:
**	s	String to add to the wordlist.
**	wlp	Pointer to a wordlist.
** Returns:	nothing
**___________________________________________________			     */
void add_word(sym, wlp)				   /*			     */
  register Symbol   sym;			   /*			     */
  register WordList *wlp;			   /*			     */
{ register WordList wl;				   /*			     */
  register int	    cmp = 1;			   /*			     */
						   /*			     */
  while (*wlp != WordNULL			   /*			     */
	 && (cmp=symcmp(ThisWord(*wlp),	sym)) < 0) /*			     */
  { wlp = & NextWord(*wlp); }			   /*			     */
						   /*			     */
  if ( cmp == 0 ) return;			   /*			     */
						   /*			     */
  if ( (wl=(WordList)malloc(sizeof(SWordList))) == WordNULL )/*		     */
  { OUT_OF_MEMORY("WordList"); }   		   /*                        */
						   /*			     */
  ThisWord(wl) = sym;				   /*			     */
  NextWord(wl) = *wlp;				   /*			     */
  *wlp	       = wl;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	delete_word()
** Purpose:	Remove a word from a |WordList|. Only the first
**		appearance of such a word is removed. I a word is
**		found which contains the same string as |s| then the
**		associated node is removed from the list and the
**		function |fct| is called to free the memory of the
**		string in the |WordList| node if the function is not
**		|NULL|. In this case the function returns
**		|0|. Otherwise |1| is returned. 
** Arguments:
**	s	Word to remove.
**	wlp	Pointer to the word list to modify.
**	fct	Function to call to free the memory occupied by the word.
** Returns:	|0| if the word was not found. |1| otherwise.
**___________________________________________________			     */
int delete_word(sym, wlp, fct)			   /*                        */
  Symbol   sym;					   /*                        */
  WordList *wlp;				   /*                        */
  void    (*fct)_ARG((String));			   /*                        */
{ WordList wl;				   	   /*			     */
  int cmp = 1;					   /*                        */
  while ( *wlp != WordNULL			   /*			     */
	  && (cmp=symcmp(ThisWord(*wlp), sym)) < 0 )/*		             */
  { wlp = & NextWord(*wlp); }			   /*			     */
  						   /*                        */
  if ( cmp == 0 ) return 0;			   /*			     */
 						   /*                        */
  wl   = *wlp;					   /*                        */
  *wlp = NextWord(wl);				   /*                        */
  if ( fct != NULL ) { (*fct)(SymbolValue(ThisWord(wl))); }/*                */
  free(wl);					   /*                        */
  return 1;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_words()
** Purpose:	Release the memory allocated for a list of words.
**		All nodes in the list are freed. The function |fct| is
**		called to free the memory occupied by the string
**		component if it is not |NULL|.
** Arguments:
**	wlp	Pointer to the |WordList|.
**	fct	Function to be called to free the memory of the word itself.
**		If it is |NULL| then no function is called.
** Returns:	nothing
**___________________________________________________			     */
void free_words(wlp, fct)			   /*                        */
  WordList *wlp;				   /*                        */
  void    (*fct)_ARG((Symbol));			   /*                        */
{ WordList wl, next;				   /*                        */
 						   /*                        */
  if (wlp == NULL) return;			   /*                        */
 						   /*                        */
  if (fct != NULL)				   /*                        */
  { for ( wl = *wlp; wl; wl = next)		   /*                        */
    { next = NextWord(wl);			   /*                        */
      (*fct)(ThisWord(wl));   			   /*                        */
      (void)free(wl);				   /*                        */
    }						   /*                        */
  }						   /*                        */
  else						   /*                        */
  { for ( wl = *wlp; wl; wl = next)		   /*                        */
    { next = NextWord(wl);			   /*                        */
      (void)free(wl);				   /*                        */
    }						   /*                        */
  }						   /*                        */
  *wlp = WordNULL;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	foreach_word()
** Purpose:	Applies the given function |fct| to all elements in
**		the |WordList| as long as the function does not return
**		0. Thus it can be used to search for a specified word
**		-- e.g. determined by matching against a
**		template. Another application the the processing of
**		all elements in the |WordList|. In this case |fct|
**		must always return |TRUE|.
** Arguments:
**	wl	WordList to traverse.
**	fct	function to apply.
** Returns:	return value of last function or 1.
**___________________________________________________			     */
int foreach_word(wl, fct)			   /*                        */
  WordList wl;					   /*                        */
  int (*fct)_ARG((Symbol));			   /*                        */
{ int ret = 1;					   /*                        */
  while ( wl && (ret=(fct)(ThisWord(wl))) )	   /*                        */
  { wl = NextWord(wl); }			   /*                        */
  return ret;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	find_word()
** Purpose:	Look up a word in a word list. The comparison is done
**		case insensitive. 
** Arguments:
**	s	String to find.
**	wl	Word list to search in.
** Returns:	|FALSE| iff the word does not occur in the word list.
**___________________________________________________			     */
int find_word(s, wl)				   /*			     */
  register String   s;				   /*			     */
  register WordList wl;				   /*			     */
{					   	   /*			     */
  while ( wl != WordNULL )			   /*                        */
  {						   /*                        */
    if ( case_cmp(SymbolValue(ThisWord(wl)),	   /*                        */
		  s) )   		   	   /*                        */
    { return 1; } 				   /*			     */
    wl = NextWord(wl);				   /*                        */
  }			   			   /*			     */
					   	   /*			     */
  return 0;				   	   /*			     */
}						   /*------------------------*/
