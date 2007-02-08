/******************************************************************************
** $Id: symbols.h,v 1.2 2007-02-08 05:27:32 gene Exp $
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
**	This header file contains definitions dealing with symbols.
**
**	\BibTool{} uses symbols as the basic representation for
**	strings.  Symbols are stored in a symbol table and shared
**	amoung different instances. Thus the same string occurring at
**	different places has to be stored only once.
**
**	Another advantage of symbols is that once you have got two
**	symbols at hand it is rather easy to compare them for
**	equality.  A simple pointer comparison is enough. It is not
**	neccesary to compare them character by character.
**
**	The disadvantage of a symbol is that you can not simply modify
**	it temporarily since it is part of the symbol table. This
**	symbol table would be in an insane state otherwise. Thus you
**	always have to make a copy if you want to modify a symbol.
**
**	The functions defined in |symbols.c| are exported with this
**	header file aswell.
**
******************************************************************************/

#ifndef SYMBOLS_H_LOADED
#define SYMBOLS_H_LOADED

#include <bibtool/type.h>

/*-----------------------------------------------------------------------------
** Macro:	symbol()
** Type:	char *
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

#define SYMBOL_STATIC	1

/*-----------------------------------------------------------------------------
** Variable:	sym_empty
** Type:	Uchar *
** Purpose:	The empty symbol. This is a symbol pointing
**		immediately to a |\0| byte.  This needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Uchar * sym_empty;

/*-----------------------------------------------------------------------------
** Variable:	sym_crossref
** Type:	Uchar *
** Purpose:	The symbol |crossref|. This variable needs
**		|init_symbols()| to be called first.
**___________________________________________________			     */
 extern Uchar * sym_crossref;


#define new_Ustring(S) (Uchar*)new_string((char*)(S))


#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Uchar * sym_add _ARG((Uchar *s,int count));	   /* symbols.c              */
 Uchar * sym_extract _ARG((Uchar *ap,Uchar *ep,int count));/* symbols.c      */
 char * new_string _ARG((char * s));		   /* symbols.c              */
 int sym_flag _ARG((Uchar * s));		   /* symbols.c              */
 void init_symbols _ARG((void));		   /* symbols.c              */
 void sym_dump _ARG((void));			   /* symbols.c              */
 void sym_gc _ARG((void));			   /* symbols.c              */
 void sym_set_flag _ARG((Uchar *s,int flags));	   /* symbols.c              */
 void sym_unlink _ARG((Uchar *s));		   /* symbols.c              */

#endif /* SYMBOLS_H_LOADED */
