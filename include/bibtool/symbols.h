/*** symbols.h ****************************************************************
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
** Macro:	UnlinkSymbol()
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
#define UnlinkSymbol(SYM) if (--SymbolCount(SYM) == 0) sym_del(SYM)
#else
#ifdef COMPLEX_SYMBOL
#define UnlinkSymbol(SYM) --SymbolCount(SYM)
#else
#define UnlinkSymbol(SYM)
#endif
#endif

/*****************************************************************************/
/***									   ***/
/*****************************************************************************/

#ifdef COMPLEX_SYMBOL

typedef struct
 { String sy_value;
   int sy_count;
 } sSymbol, *Symbol;
#define SymbolValue(X) ((X)->sy_value)
#define SymbolCount(X) ((X)->sy_count)

#define LinkSymbol(SYM) SymbolCount(SYM)++

#else

typedef String Symbol;
#define SymbolValue(X) (X)
#define LinkSymbol(SYM)

#endif

#define SetSym(VAR,SYM)			\
  if (VAR) { UnlinkSymbol(VAR); }	\
  VAR = SYM;				\
  if (VAR) { LinkSymbol(VAR); }

#define symlen(SYM) strlen((char*)SymbolValue(SYM))
#define symcmp(S,T) strcmp((char*)SymbolValue(S),(char*)SymbolValue(T))

/*-----------------------------------------------------------------------------
** Constant:	NO_SYMBOL
** Type:	Symbol
** Purpose:	The NULL pointer for Symbols
**___________________________________________________			     */
#define NO_SYMBOL (Symbol)NULL

/*-----------------------------------------------------------------------------
** Variable:	s_empty
** Type:	String 
** Purpose:	Unmodifiable value containing the empty string. This
**		variable needs |init_symbols()| to be called first.
**___________________________________________________			     */
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
** Variable:	sym_star
** Type:	Symbol
** Purpose:	The symbol with a single star character. This variable needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_star;

 extern Symbol sym_qqq;

/*-----------------------------------------------------------------------------
** Variable:	sym_comma
** Type:	Symbol
** Purpose:	The symbol with a single comma character. This variable needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_comma;

/*-----------------------------------------------------------------------------
** Variable:	sym_double_quote
** Type:	Symbol
** Purpose:	The symbol with a single double quote character (").
**		This variable needs |init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_double_quote;

/*-----------------------------------------------------------------------------
** Variable:	sym_open_brace
** Type:	Symbol
** Purpose:	The symbol with a single open brace character. This
**		variable needs |init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_open_brace;

/*-----------------------------------------------------------------------------
** Variable:	sym_close_brace
** Type:	Symbol
** Purpose:	The symbol with a single close brace character. This
**		variable needs |init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_close_brace;

/*-----------------------------------------------------------------------------
** Variable:	sym_et
** Type:	Symbol
** Purpose:	The symbol with a single et character (\&). This
**		variable needs |init_symbols()| to be called first.
**___________________________________________________			     */
 extern Symbol sym_et;

 extern Symbol sym_key;

 extern Symbol sym_sortkey;

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
 Symbol  symbol _ARG((String s));	   	   /* symbols.c              */
 Symbol  sym_extract _ARG((String *sp,bool lowercase));/* symbols.c          */
 char * new_string _ARG((char * s));		   /* symbols.c              */
 void init_symbols _ARG((void));		   /* symbols.c              */
 void sym_dump _ARG((void));			   /* symbols.c              */
 void sym_del _ARG((Symbol sym));		   /* symbols.c              */
 void sym_gc _ARG((void));			   /* symbols.c              */
 void sym_unlink _ARG((Symbol s));		   /* symbols.c              */
 void free_sym_array _ARG((Symbol *sym_arr));	   /*                        */

#endif /* SYMBOLS_H_LOADED */
