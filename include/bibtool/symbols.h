/*** symbols.h ****************************************************************
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
**	This header file contains definitions dealing with symbols.
**
**	\BibTool{} uses symbols as the basic representation for
**	strings.  Symbols are stored in a symbol table and shared
**	among different instances. Thus the same string occurring at
**	different places has to be stored only once.
**
**	Another advantage of symbols is that once you have got two
**	symbols at hand it is rather easy to compare them for
**	equality.  A simple pointer comparison is enough. It is not
**	necessary to compare them character by character.
**
**	The disadvantage of a symbol is that you can not simply modify
**	it temporarily since it is part of the symbol table. This
**	symbol table would be in an insane state otherwise. Thus you
**	always have to make a copy if you want to modify a symbol.
**
**	The functions defined in |symbols.c| are exported with this
**	header file as well.
**
******************************************************************************/

#ifndef SYMBOLS_H_LOADED
#define SYMBOLS_H_LOADED

#include <bibtool/type.h>

/*-----------------------------------------------------------------------------
** Macro:	symbol()
** Type:	Symbol
** Purpose:	Translate a string into a symbol.
**		The symbol returned is either created or an existing
**		symbol is returned.
** Arguments:
**	STR	String to translate into a symbol.
** Returns:	The symbol corresponding to the argument.
**___________________________________________________			     */
#define symbol(STR) sym_add(STR,1)

/*-----------------------------------------------------------------------------
** Macro:	ReleaseSymbol()
** Type:	void
** Purpose:	The symbol given as argument is released. In fact the
**		memory is not really freed but one instance is marked
**		as not used any more. At other places the symbol might
**		be still required. The freeing of memory is performed
**		by the garbage collector |sym_gc()|.
** Arguments:
**	SYM	Symbol to release.
** Returns:	nothing
**___________________________________________________			     */
#ifdef FREE_MEMORY
#define ReleaseSymbol(SYM) sym_del(SYM)
#else
#define ReleaseSymbol(SYM)
#endif

/*****************************************************************************/
/***									   ***/
/*****************************************************************************/

typedef String Symbol;

#define NO_SYMBOL (Symbol)NULL

#define SYMBOL_STATIC	1

extern String s_empty;

/*-----------------------------------------------------------------------------
** Variable:	sym_empty
** Type:	Symbol 
** Purpose:	The empty symbol. This is a symbol pointing
**		immediately to a |\0| byte.  This needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_empty;

/*-----------------------------------------------------------------------------
** Variable:	sym_crossref
** Type:	Symbol
** Purpose:	The symbol |crossref|. This variable needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_crossref;

/*-----------------------------------------------------------------------------
** Variable:	sym_xref
** Type:	Symbol
** Purpose:	The symbol |xref|. This variable needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_xref;

/*-----------------------------------------------------------------------------
** Variable:	sym_xdata
** Type:	Symbol
** Purpose:	The symbol |xdata|. This variable needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_xdata;

/*-----------------------------------------------------------------------------
** Variable:	sym_space
** Type:	Symbol
** Purpose:	The symbol with a single space character. This variable needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_space;

/*-----------------------------------------------------------------------------
** Macro:	newString()
** Type:	String
** Purpose:	Create a copy of a given String.
** Arguments:
**	S	the source of the bytes	
** Returns:	a newly allocated byte array containing the content of
**		the source
**___________________________________________________			     */
#define newString(S) (String)new_string((char*)(S))

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Symbol  sym_add _ARG((String s,int count));	   /* symbols.c              */
 Symbol  sym_extract _ARG((String *sp,int lowercase));/* symbols.c           */
 char * new_string _ARG((char * s));		   /* symbols.c              */
 int sym_flag _ARG((Symbol  s));		   /* symbols.c              */
 void init_symbols _ARG((void));		   /* symbols.c              */
 void sym_dump _ARG((void));			   /* symbols.c              */
 void sym_gc _ARG((void));			   /* symbols.c              */
 void sym_set_flag _ARG((Symbol s,int flags));	   /* symbols.c              */
 void sym_unlink _ARG((Symbol s));		   /* symbols.c              */

#endif /* SYMBOLS_H_LOADED */
