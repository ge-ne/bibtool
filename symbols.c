/*** symbols.c ****************************************************************
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
**	This module contains functions which deal with symbols and
**	general memory management. 
**	This module implements a single symbol table.
**
**	This module required initialization before all functions can
**	be used. Especially the symbol table does not exist before
**	initialization. 
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/error.h>
#include "config.h"

/*-----------------------------------------------------------------------------
** Typedef*:	StringTab
** Purpose:	This is the pointer type representing an entry in the symbol
**		table. It contains a string and some integers.
**		
**___________________________________________________			     */
 typedef struct STAB		/*                                           */
  { Symbol	st_name;	/* The string representation of the symbol   */
    int		st_count;	/* 			                     */
    int		st_flags;	/* Bits of certain flags.                    */
    int		st_used; 	/* Counter for determining the number of uses*/
    struct STAB *st_next;	/* Pointer to the next item.                 */
  } *StringTab;

/*-----------------------------------------------------------------------------
** Macro*:	NextSymbol()
** Type:	StringTab
** Purpose:	The next |StringTab| of the argument. This macro
**		can also be used as lvalue.
** Arguments:
**	ST	Current |StringTab|
** Returns:	The next |StringTab| or |NULL|.
**___________________________________________________			     */
#define NextSymbol(ST)	((ST)->st_next)

/*-----------------------------------------------------------------------------
** Macro*:	SymbolCount()
** Type:	int
** Purpose:	The count slot of a |StringTab|. This macro
**		can also be used as lvalue.
** Arguments:
**	ST	Current |StringTab|
** Returns:	The count slot of |ST|.
**___________________________________________________			     */
#define SymbolCount(ST)	((ST)->st_count)

/*-----------------------------------------------------------------------------
** Macro*:	SymbolUsed()
** Type:	int
** Purpose:	The used slot of a |StringTab|. This macro
**		can also be used as lvalue.
** Arguments:
**	ST	Current |StringTab|
** Returns:	The used slot of |ST|.
**___________________________________________________			     */
#define SymbolUsed(ST)	((ST)->st_used)

/*-----------------------------------------------------------------------------
** Macro*:	SymbolName()
** Type:	Symbol
** Purpose:	The name slot of a |StringTab|, i.e.\ the string
**		representation. This macro can also be used as lvalue.
** Arguments:
**	ST	Current |StringTab|
** Returns:	The name slot of |ST|.
**___________________________________________________			     */
#define SymbolName(ST)	((ST)->st_name)

/*-----------------------------------------------------------------------------
** Macro*:	SymbolFlags()
** Type:	int
** Purpose:	The flags slot of a |StringTab|. This macro
**		can also be used as lvalue.
** Arguments:
**	ST	Current |StringTab|
** Returns:	The flags slot of |ST|.
**___________________________________________________			     */
#define SymbolFlags(ST)	((ST)->st_flags)

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Symbol  sym_add _ARG((String s, int count));	   /* symbols.c              */
 Symbol  sym_extract _ARG((String *sp, int lowercase));/* symbols.c          */
 char * new_string _ARG((char * s));		   /* symbols.c              */
 int sym_flag _ARG((Symbol  s));		   /* symbols.c              */
 static StringTab new_string_tab _ARG((Symbol name,int count,int flags));/* symbols.c*/
 static int hashindex _ARG((String s));		   /* symbols.c              */
 void init_symbols _ARG((void));		   /* symbols.c              */
#ifdef SYMBOL_DUMP
 void sym_dump _ARG((void));			   /* symbols.c              */
#endif
 void sym_gc _ARG((void));			   /* symbols.c              */
 void sym_set_flag _ARG((Symbol s, int flags));	   /* symbols.c              */
 void sym_unlink _ARG((Symbol s));		   /* symbols.c              */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

#ifdef HASH_TABLE_SIZE
#define HASHMAX HASH_TABLE_SIZE
#else
#define HASHMAX 307
#endif



 String  s_empty          = (String)"";

 Symbol  sym_empty        = NO_SYMBOL;		   /*                        */
 Symbol  sym_space        = NO_SYMBOL;		   /*                        */
 Symbol  sym_crossref     = NO_SYMBOL;		   /*                        */
 Symbol  sym_xdata        = NO_SYMBOL;		   /*                        */
 Symbol  sym_xref         = NO_SYMBOL;		   /*                        */
 Symbol  sym_qqq          = NO_SYMBOL;		   /*                        */
 Symbol  sym_comma        = NO_SYMBOL;		   /*                        */
 Symbol  sym_double_quote = NO_SYMBOL;		   /*                        */
 Symbol  sym_open_brace   = NO_SYMBOL;		   /*                        */
 Symbol  sym_close_brace  = NO_SYMBOL;		   /*                        */


/*****************************************************************************/
/***			Misc string allocation routine			   ***/
/*****************************************************************************/

/*-----------------------------------------------------------------------------
** Function:	new_string()
** Purpose:	Allocate a space for a string and copy the argument
**		there. Note this is just a new copy of the memory not
**		a symbol!
**
**		If no more memory is available then an error is raised
**		and the program is terminated.
** Arguments:
**	s	String to duplicate
** Returns:	Pointer to newly allocated memory containing a
**		duplicate of the argument string.
**___________________________________________________			     */
char * new_string(s)				   /*			     */
  register char * s;				   /*			     */
{ register char * t;				   /*			     */
  if ( (t=malloc((size_t)strlen(s)+1)) == NULL )   /*			     */
  { OUT_OF_MEMORY("string"); }	   		   /*			     */
  (void)strcpy(t,s);				   /*			     */
  return t;					   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***			     Symbol Table Section			   ***/
/*****************************************************************************/

/*-----------------------------------------------------------------------------
** Function:	new_string_tab()
** Purpose:	Allocate a new |StringTab| structure and fill it with initial
**		values.
**
**		If no more memory is available then an error is raised
**		and the program is terminated.
** Arguments:
**	name	String value of the |StringTab| node.
**	count	Initial use count of the |StringTab| node.
**	flags	Flags of the new |StringTab| node.
** Returns:	Pointer to a new instance of a |StringTab|.
**___________________________________________________			     */
static StringTab new_string_tab(name, count, flags)/*			     */
  Symbol	     name;			   /*			     */
  int		     count;			   /*			     */
  int		     flags;			   /*			     */
{ register StringTab new_string_tab;		   /*			     */
						   /*			     */
  if ( (new_string_tab=(StringTab)malloc(sizeof(struct STAB))) == 0L )/*     */
  { OUT_OF_MEMORY("StringTab"); }   		   /*			     */
 						   /*                        */
  SymbolName(new_string_tab)  = name;		   /*			     */
  SymbolCount(new_string_tab) = count;		   /*			     */
  SymbolFlags(new_string_tab) = flags;		   /*			     */
  SymbolUsed(new_string_tab)  = 0;		   /*			     */
  NextSymbol(new_string_tab)  = (StringTab)0;	   /*			     */
  return(new_string_tab);			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	hashindex()
** Purpose:	Compute the sum of ASCII values modulo |HASHMAX|
**		to be used as an hash index.
** Arguments:
**	s	string to be analyzed.
** Returns:	hash index
**___________________________________________________			     */
static int hashindex(s)				   /*                        */
  String s;					   /*                        */
{ int	index = 0;				   /*                        */
  while ( *s ) index = (index+*(s++)) % HASHMAX;   /*                        */
  return ( index < 0 ? -index : index );	   /*                        */
}						   /*------------------------*/

 static StringTab sym_tab[HASHMAX];

/*-----------------------------------------------------------------------------
** Function:	init_symbols()
** Purpose:	Initialize the symbols module.
**		The symbol table is cleared. This is not secure when
**		the symbols have already been initialized because it
**		would lead to a memory leak and a violation of the
**		symbol comparison assumption. Thus this case is caught
**		and nothing is done when the initialization seems to
**		be requested for the second time.
**
**		If no more memory is available then an error is raised
**		and the program is terminated.
**
**		Note that this function is for internal purposes
**		only. The normal user should call |init_bibtool()|
**		instead.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void init_symbols()				   /*			     */
{ register int i;				   /*			     */
						   /*			     */
  if (sym_empty) return;		   	   /*                        */
 						   /*                        */
  for (i = 0; i < HASHMAX; i++) sym_tab[i] = NULL; /*			     */
 						   /*                        */
  sym_empty    = sym_add(newString(s_empty), -1);  /*                        */
  sym_space    = sym_add(newString(" "), -1);	   /*                        */
  sym_crossref = sym_add(newString("crossref"),-1);/*                        */
  sym_xref     = sym_add(newString("xref"),-1);	   /*                        */
  sym_xdata    = sym_add(newString("xdata"),-1);   /*                        */
  sym_qqq      = sym_add(newString("???"),-1);     /*                        */
  sym_comma    = sym_add(newString(","),-1);       /*                        */
  sym_double_quote = sym_add(newString("\""),-1);  /*                        */
  sym_open_brace   = sym_add(newString("{"),-1);   /*                        */
  sym_close_brace  = sym_add(newString("}"),-1);   /*                        */
}						   /*------------------------*/

 static StringTab last_stp = NULL;	

/*-----------------------------------------------------------------------------
** Function:	sym_flag()
** Purpose:	Get the flags of the symbol given as argument.
** Arguments:
**	s	Symbol
** Returns:	The flags of the recently touched |StringTab|.
**___________________________________________________			     */
int sym_flag(s)					   /*			     */
  Symbol s;					   /*                        */
{						   /*                        */
  if (last_stp == NULL				   /*                        */
      || SymbolName(last_stp) != s)		   /*                        */
  { s = sym_add(SymbolValue(s), 0); }		   /*                        */
  return SymbolFlags(last_stp);		   	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sym_set_flag()
** Purpose:	Add the flags to the symbol corresponding to the
**		argument |s| by oring them together with the given
**		value. 
** Arguments:
**	s	Symbol to augment.
**	flags	New flags to add.
** Returns:	nothing
**___________________________________________________			     */
void sym_set_flag(s,flags)			   /*			     */
  register Symbol s;				   /*			     */
  register int    flags;			   /*			     */
{ 						   /*                        */
  if (last_stp == NULL				   /*                        */
      || SymbolName(last_stp) != s )		   /*                        */
  { s = sym_add(SymbolValue(s), 0); }		   /*                        */
  SymbolFlags(last_stp) |= flags;		   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sym_add()
** Purpose:	Add a symbol to the global symbol table. If the string
**		already has a symbol assigned to it then this symbol
**		is returned. If the symbol is not static then the use
**		count is incremented by |count|.
**
**		If the symbol does not exist already then a new symbol
**		is added to the symbol table and the use count is
**		initialized to |count|. A negative value for |count|
**		indicates that a static symbol is requested. A static
**		symbol will never be deleted from the symbol table.
**		Static can be used at places where one does not care
**		about the memory occupied.
**
**		If no more memory is available then an error is raised
**		and the program is terminated.
**
**		See also the macro |symbol()| in |symbols.h| for a
**		convenient alternative to this function.
** Arguments:
**	s	String which should be translated into a symbol.
**	count	The use count which should be added to the symbol
** Returns:	The new symbol.
**___________________________________________________			     */
Symbol sym_add(s, count)			   /*			     */
  register String    s;		   	   	   /*			     */
  register int	     count;			   /*			     */
{ register StringTab *stp;			   /*			     */
  Symbol sym;					   /*                        */
						   /*			     */
  if (s == StringNULL) return NO_SYMBOL;	   /* ignore dummies.	     */
 						   /*                        */
  for ( stp = &sym_tab[hashindex(s)];		   /*			     */
       *stp != NULL;		   		   /*			     */
        stp = &NextSymbol(*stp) )		   /*			     */
  {						   /*                        */
    if ( strcmp((char*)s,			   /*                        */
		(char*)SymbolValue(SymbolName(*stp))) == 0 )/*		     */
    { if ( count > 0 ) SymbolCount(*stp) += count; /*			     */
      last_stp = *stp;			   	   /*			     */
#ifdef QUESTIONABLE
      if ( s != SymbolName(*stp) )		   /*                        */
#endif
      { SymbolUsed(*stp)++; }			   /*                        */
 						   /*                        */
      DebugPrint2("Symbol found ",		   /*                        */
		  SymbolValue(SymbolName(*stp)));  /*                        */
      return SymbolName(*stp);			   /*			     */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  if (count >= 0) { s = newString(s); }	   	   /*			     */
  						   /*                        */
#ifdef COMPLEX_SYMBOL
  sym = (Symbol)malloc(sizeof(sSymbol));	   /*                        */
  SymbolValue(sym) = (count < 0 ? newString(s) : s);/*                       */
#else
  sym = (count < 0 ? newString(s) : s);		   /*                        */
#endif
  *stp = new_string_tab(sym,			   /*                        */
			count < 0 ? 0 : count, 	   /*                        */
			0);  		   	   /*			     */
 						   /*                        */
  last_stp = *stp;				   /*			     */
  SymbolUsed(*stp)++;				   /*                        */
  if (count < 0)				   /*                        */
  { SymbolFlags(*stp) ^= SYMBOL_STATIC; }	   /*			     */
  DebugPrint2("Symbol created ",		   /*                        */
	      SymbolValue(SymbolName(*stp)));	   /*                        */
  return SymbolName(*stp);			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sym_unlink()
** Purpose:	Free a symbol since it is no longer used.
**		This does not mean that the memory is also freed. The
**		symbol can be static or used at other places. The real
**		free operation requires the garbage collector
**		|sym_gc()| to be called.
**
**		If the argument is |NULL| or an arbitrary string (no
**		symbol) then this case is also dealt with.
** Arguments:
**	s	Symbol to be released.
** Returns:	nothing
**___________________________________________________			     */
void sym_unlink(s)				   /*			     */
  register Symbol    s;			   	   /*			     */
{ register StringTab st;			   /*			     */
						   /*			     */
  if (s == NO_SYMBOL) return;		   	   /* ignore dummies.	     */
 						   /*                        */
  for ( st = sym_tab[hashindex(SymbolValue(s))];   /*			     */
        st != NULL;		   		   /*			     */
        st = NextSymbol(st) )		   	   /*			     */
  { if ( s == SymbolName(st) )	   		   /*			     */
    { SymbolUsed(st)--;				   /* reduce reference count */
      return;			   		   /*			     */
    }						   /*			     */
  }						   /*			     */
#ifdef DEBUG
  ErrPrintF("*** Attempt to free an undefined symbol: %s\n",/*               */
	    SymbolValue(s));			   /*                        */
#endif
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	sym_gc()
** Purpose:	This is the garbage collector. It analyzes the symbol
**		table and releases all |SymbolTab| nodes not needed
**		any more.
**
**		Right now it is purely experimental. Better let your
**		hands off.
**
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void sym_gc()					   /*                        */
{ register StringTab st, st2;			   /*			     */
  register int i;				   /*                        */
  						   /*                        */
  for ( i = 0; i < HASHMAX; i++ )		   /*			     */
  {						   /*                        */
    while (sym_tab[i] &&			   /*                        */
	   SymbolUsed(sym_tab[i]) <= 0)		   /*                        */
    { st = sym_tab[i];				   /*                        */
      sym_tab[i] = NextSymbol(st);		   /*                        */
      if ( (SymbolFlags(st) & SYMBOL_STATIC) == 0 )/*                        */
      { free(SymbolName(st)); }			   /*                        */
      free(st);					   /*                        */
    }						   /*                        */
    st = sym_tab[i];				   /*                        */
    if ( st )					   /*                        */
    {						   /*                        */
      while ( (st2=NextSymbol(st)) != NULL &&	   /*                        */
	      SymbolUsed(st) <= 0 )		   /*                        */
      { NextSymbol(st) = NextSymbol(st2);	   /*                        */
        if ( (SymbolFlags(st2) & SYMBOL_STATIC) == 0 )/*                     */
	{ free(SymbolName(st2)); }		   /*                        */
	free(st2);				   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sym_extract()
** Purpose:	Extract a symbol from a string.
** Arguments:
**	sp	pointer to the string
**	lowercase	indicate that lowering is requested
** Returns:	
**___________________________________________________			     */
Symbol  sym_extract(sp, lowercase)		   /*			     */
  register String *sp;				   /* pointer to first char  */
  int lowercase;				   /*                        */
{ Uchar c;					   /*			     */
  String t = *sp;				   /*                        */
  Symbol sym;					   /*                        */
						   /*			     */
  while ( is_allowed(**sp) ) (*sp)++;		   /*                        */
  c    = **sp;					   /*			     */
  **sp = '\0';					   /*			     */
  if (lowercase)				   /*                        */
  { t	= lower(newString(t));	   		   /*                        */
    sym	= symbol(t);		   	   	   /*			     */
    (void)free((void *)t);			   /*                        */
  } else {					   /*                        */
    sym  = symbol(t);			   	   /*			     */
  }						   /*                        */
  **sp = c;					   /*			     */
  return sym;					   /*			     */
}						   /*------------------------*/

#ifdef SYMBOL_DUMP
/*-----------------------------------------------------------------------------
** Function:	sym_dump()
** Purpose:	Dump the symbol table to the error stream---see module
**		|error.c|. 
**		The symbols are printed according to their hash value
**		and the sequence they are occurring in the buckets.  A
**		summary of the memory used is also printed.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void sym_dump()					   /*			     */
{ register int	     i,l;			   /*			     */
  register StringTab st;			   /*			     */
  register long	     len  = 0l;			   /*			     */
  register long	     cnt  = 0l;			   /*			     */
  register long	     used = 0l;			   /*			     */
						   /*			     */
  for ( i = 0; i < HASHMAX; i++ )		   /*			     */
  { for ( st = sym_tab[i]; st; st=NextSymbol(st) ) /*			     */
    { ErrPrintF2("--- BibTool symbol %4d %s\n",	   /*			     */
		 (int)SymbolCount(st),		   /*			     */
		 SymbolName(st));		   /*			     */
      l     = symlen(st) + 1;	   		   /*			     */
      len  += l;				   /*			     */
      used += l * SymbolCount(st);		   /*                        */
      ++cnt;					   /*			     */
    }						   /*			     */
  }						   /*			     */
  ErrPrintF2("--- BibTool symbol table: %ld bytes for %ld symbols\n",/*	     */
	     len, cnt);				   /*			     */
  ErrPrintF("--- BibTool symbol table emulates %ld bytes\n",/*		     */
	     used);				   /*			     */
}						   /*------------------------*/
#endif
