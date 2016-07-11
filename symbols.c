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
** Typedef*:	SymTab
** Purpose:	This is the pointer type representing an entry in the symbol
**		table. It contains a string and some integers.
**		
**___________________________________________________			     */
 typedef struct STAB		/*                                           */
  { Symbol	st_name;	/* The symbol itself			     */
#ifndef COMPLEX_SYMBOL
    int		st_count;	/* 			                     */
#endif
    struct STAB *st_next;	/* Pointer to the next item.                 */
  } *SymTab;

/*-----------------------------------------------------------------------------
** Macro*:	NextSymTab()
** Type:	SymTab
** Purpose:	The next |SymTab| of the argument. This macro
**		can also be used as lvalue.
** Arguments:
**	ST	Current |SymTab|
** Returns:	The next |SymTab| or |NULL|.
**___________________________________________________			     */
#define NextSymTab(ST)	((ST)->st_next)

/*-----------------------------------------------------------------------------
** Macro*:	SymTabCount()
** Type:	int
** Purpose:	The count slot of a |SymTab|. This macro
**		can also be used as lvalue.
** Arguments:
**	ST	Current |SymTab|
** Returns:	The count slot of |ST|.
**___________________________________________________			     */
#ifdef COMPLEX_SYMBOL
#define SymTabCount(SYMTAB)  SymbolCount(SymTabSymbol(SYMTAB))
#define SymCount(SYM,SYMTAB) SymbolCount(SymTabSymbol(SYMTAB))
#else
#define SymTabCount(SYMTAB)  ((SYMTAB)->st_count)
#define SymCount(SYM,SYMTAB) SymTabCount(SYMTAB)
#endif

/*-----------------------------------------------------------------------------
** Macro*:	SymTabSymbol()
** Type:	Symbol
** Purpose:	The name slot of a |SymTab|, i.e.\ the string
**		representation. This macro can also be used as lvalue.
** Arguments:
**	ST	Current |SymTab|
** Returns:	The name slot of |ST|.
**___________________________________________________			     */
#define SymTabSymbol(ST) ((ST)->st_name)

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Symbol  symbol _ARG((String s));	   	   /* symbols.c              */
 Symbol  sym_extract _ARG((String *sp, bool lowercase));/* symbols.c         */
 char * new_string _ARG((char * s));		   /* symbols.c              */
 static SymTab new_sym_tab _ARG((String value));   /* symbols.c              */
 static int hashindex _ARG((String s));		   /* symbols.c              */
 void init_symbols _ARG((void));		   /* symbols.c              */
 void sym_del _ARG((Symbol sym));		   /* symbols.c              */
#ifdef SYMBOL_DUMP
 void sym_dump _ARG((void));			   /* symbols.c              */
#endif
 void sym_gc _ARG((void));			   /* symbols.c              */
 void sym_unlink _ARG((Symbol s));		   /* symbols.c              */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

#ifdef HASH_TABLE_SIZE
#define HASHMAX HASH_TABLE_SIZE
#else
#define HASHMAX 307
#endif



 String s_empty		  = (String)"";

 Symbol sym_empty	  = NO_SYMBOL;		   /*			     */
 Symbol sym_space	  = NO_SYMBOL;		   /*			     */
 Symbol sym_star	  = NO_SYMBOL;		   /*			     */
 Symbol sym_crossref	  = NO_SYMBOL;		   /*			     */
 Symbol sym_xdata	  = NO_SYMBOL;		   /*			     */
 Symbol sym_xref	  = NO_SYMBOL;		   /*			     */
 Symbol sym_qqq		  = NO_SYMBOL;		   /*			     */
 Symbol sym_comma	  = NO_SYMBOL;		   /*			     */
 Symbol sym_double_quote  = NO_SYMBOL;		   /*			     */
 Symbol sym_open_brace	  = NO_SYMBOL;		   /*			     */
 Symbol sym_close_brace	  = NO_SYMBOL;		   /*			     */
 Symbol sym_et		  = NO_SYMBOL;		   /*			     */


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
  if ( (t=malloc((size_t)strlen(s) + 1)) == NULL ) /*			     */
  { OUT_OF_MEMORY("string"); }	   		   /*			     */
  (void)strcpy(t, s);				   /*			     */
  return t;					   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***			     Symbol Table Section			   ***/
/*****************************************************************************/

/*-----------------------------------------------------------------------------
** Function*:	new_sym_tab()
** Purpose:	Allocate a new |SymTab| structure and fill it with initial
**		values.
**
**		If no more memory is available then an error is raised
**		and the program is terminated.
** Arguments:
**	value	String value of the |SymTab| node.
** Returns:	Pointer to a new instance of a |SymTab|.
**___________________________________________________			     */
static SymTab new_sym_tab(value)		   /*			     */
  String value;			   	   	   /*			     */
{ register SymTab new_symtab;		   	   /*			     */
  Symbol sym;					   /*                        */
 						   /*			     */
  if ((new_symtab=(SymTab)malloc(sizeof(struct STAB))) == 0L)/*              */
  { OUT_OF_MEMORY("SymTab"); }   		   /*			     */
 						   /*                        */
#ifdef COMPLEX_SYMBOL
  if ((sym=(Symbol)malloc(sizeof(sSymbol)))	   /*                        */
      == NO_SYMBOL)				   /*                        */
  { OUT_OF_MEMORY("Symbol"); }   		   /*			     */
  SymbolValue(sym) = newString(value);		   /*                        */
#else
  sym = newString(value);			   /*                        */
#endif
  SymTabSymbol(new_symtab)  = sym;		   /*			     */
  SymCount(sym, new_symtab) = 1;		   /*			     */
  NextSymTab(new_symtab)    = (SymTab)NULL;	   /*			     */
  return new_symtab;			   	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	hashindex()
** Purpose:	Compute the sum of ASCII values modulo |HASHMAX|
**		to be used as an hash index.
** Arguments:
**	s	string to be analyzed.
** Returns:	hash index
**___________________________________________________			     */
static int hashindex(s)				   /*                        */
  String s;					   /*                        */
{ int	index = 0;				   /*                        */
  while (*s) index = (index + *(s++)) % HASHMAX;   /*                        */
  return ( index < 0 ? -index : index );	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Variable*:	sym_tab
** Purpose:	
**		
**___________________________________________________			     */
 static SymTab sym_tab[HASHMAX];		   /*                        */

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
  sym_empty        = symbol((String)s_empty);	   /*                        */
  sym_space        = symbol((String)" ");	   /*                        */
  sym_star         = symbol((String)"*");	   /*                        */
  sym_crossref     = symbol((String)"crossref");   /*                        */
  sym_xref         = symbol((String)"xref");	   /*                        */
  sym_xdata        = symbol((String)"xdata");	   /*                        */
  sym_qqq          = symbol((String)"???");	   /*                        */
  sym_comma        = symbol((String)",");	   /*                        */
  sym_double_quote = symbol((String)"\"");	   /*                        */
  sym_open_brace   = symbol((String)"{");	   /*                        */
  sym_close_brace  = symbol((String)"}");	   /*                        */
  sym_et	   = symbol((String)"&");	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	get_sym_tab()
** Type:	SymTab
** Purpose:	
**		
** Arguments:
**	sym	the symbol to search for
** Returns:	
**___________________________________________________			     */
static SymTab* get_sym_tab(sym)			   /*			     */
  register Symbol sym;			   	   /*			     */
{ register SymTab *stp;			   	   /*			     */
						   /*			     */
  if (sym == NO_SYMBOL) return NULL;	   	   /* ignore dummies.	     */
 						   /*                        */
  for (stp = &sym_tab[hashindex(SymbolValue(sym))];/*			     */
       *stp != NULL;		   		   /*			     */
       stp = &NextSymTab(*stp) )		   /*			     */
  { if (sym == SymTabSymbol(*stp))	   	   /*		             */
    { DebugPrint2("Symbol found ",		   /*                        */
		  SymbolValue(sym));  		   /*                        */
      return stp;			   	   /*			     */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  return NULL;			   		   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	symbol()
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
** Returns:	The new symbol.
**___________________________________________________			     */
Symbol symbol(s)			   	   /*			     */
  String  s;				   	   /*			     */
{ register SymTab *stp;			   	   /*			     */
  Symbol sym;				   	   /*                        */
						   /*			     */
  if (s == StringNULL) return NO_SYMBOL;	   /* ignore dummies.	     */
 						   /*                        */
  DebugPrint2("Lookup symbol ", s);  		   /*                        */
 						   /*                        */
  for ( stp = &sym_tab[hashindex(s)];		   /*			     */
       *stp != NULL;		   		   /*			     */
        stp = &NextSymTab(*stp) )		   /*			     */
  { sym	= SymTabSymbol(*stp);			   /*                        */
    DebugPrintF3("\tlooking at '%s' == '%s'\n",	   /*                        */
	      (char*)s, (char*)SymbolValue(sym));  /*                        */
    if (strcmp((char*)s,			   /*                        */
	       (char*)SymbolValue(sym)) == 0 )	   /*		             */
    { DebugPrint2("Symbol found ",		   /*                        */
		  SymbolValue(sym));  		   /*                        */
      SymCount(sym,*stp)++; 		   	   /*			     */
      return sym;				   /*			     */
    }						   /*                        */
  }						   /*			     */
 						   /*                        */
  *stp = new_sym_tab(s);  		   	   /*			     */
  DebugPrint2("Symbol created ",		   /*                        */
	      SymbolValue(SymTabSymbol(*stp)));	   /*                        */
  return SymTabSymbol(*stp);			   /*			     */
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
**	sym	Symbol to be released.
** Returns:	nothing
**___________________________________________________			     */
void sym_unlink(sym)				   /*			     */
  register Symbol sym;			   	   /*			     */
{						   /*                        */
  if (sym == NO_SYMBOL) return;		   	   /* ignore dummies.	     */
#ifdef COMPLEX_SYMBOL
  if (--SymbolCount(sym) > 0) return;		   /* double check used.     */
#else
 						   /*                        */
#ifdef DEBUG
  if (get_sym_tab(sym) == NULL)		   	   /*                        */
  { ErrPrintF("*** Attempt to free an undefined symbol: %s\n",/*             */
	      SymbolValue(sym));		   /*                        */
  }						   /*                        */
#endif
#endif
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Constant:	SYM_PIPE_SIZE
** Type:	
** Purpose:	
**		
** Returns:	
**___________________________________________________			     */
#define SYM_PIPE_SIZE 32

#ifdef COMPLEX_SYMBOL
 static Symbol sym_pipe[SYM_PIPE_SIZE];
 static int sym_pipe_ptr = 0;
#endif

/*-----------------------------------------------------------------------------
** Function:	sym_del()
** Type:	void
** Purpose:	
**		
** Arguments:
**	sym	
** Returns:	nothing
**___________________________________________________			     */
void sym_del(sym)				   /*                        */
  Symbol sym;		   			   /*                        */
{						   /*                        */
#ifdef COMPLEX_SYMBOL
  SymTab *stp;					   /*                        */
  SymTab st;					   /*                        */
 						   /*                        */
  sym_pipe[sym_pipe_ptr] = sym;			   /*                        */
  if ( ++sym_pipe_ptr < SYM_PIPE_SIZE) return;	   /*                        */
 						   /*                        */
  while (--sym_pipe_ptr > 0)
  { sym = sym_pipe[sym_pipe_ptr];
    if (SymbolCount(sym) > 0) continue;

    stp = get_sym_tab(sym);
    if (stp == NULL) continue;
    st	 = *stp;
    *stp = NextSymTab(st);
    free(st);
    free(SymbolValue(sym));
    free(sym);
  }						   /*                        */
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
{
#ifdef COMPLEX_SYMBOL
#else
  register SymTab st, st2;			   /*			     */
  register int i;				   /*                        */
  						   /*                        */
  for ( i = 0; i < HASHMAX; i++ )		   /*			     */
  {						   /*                        */
    while (sym_tab[i] &&			   /*                        */
	   SymTabCount(sym_tab[i]) <= 0)	   /*                        */
    { st = sym_tab[i];				   /*                        */
      sym_tab[i] = NextSymTab(st);		   /*                        */
      free(SymTabSymbol(st));			   /*                        */
      free(st);					   /*                        */
    }						   /*                        */
    st = sym_tab[i];				   /*                        */
    if ( st )					   /*                        */
    {						   /*                        */
      while ( (st2=NextSymTab(st)) != NULL &&	   /*                        */
	      SymTabCount(st) <= 0 )		   /*                        */
      { NextSymTab(st) = NextSymTab(st2);	   /*                        */
        free(SymTabSymbol(st2));		   /*                        */
	free(st2);				   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*			     */
#endif
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
  bool   lowercase;				   /*                        */
{ Uchar  c;					   /*			     */
  String t = *sp;				   /*                        */
  Symbol sym;					   /*                        */
						   /*			     */
  while (is_allowed(**sp)) (*sp)++;		   /*                        */
  c    = **sp;					   /*			     */
  **sp = '\0';					   /*			     */
  if (lowercase)				   /*                        */
  { t	= lower(newString(t));	   		   /*                        */
    sym	= symbol(t);		   	   	   /*			     */
    free((void *)t);			   	   /*                        */
  } else {					   /*                        */
    sym  = symbol(t);			   	   /*			     */
  }						   /*                        */
  **sp = c;					   /*			     */
  return sym;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_sym_array()
** Type:	void
** Purpose:	
**		
** Arguments:
**	sym_arr	symbol array
** Returns:	nothing
**___________________________________________________			     */
void free_sym_array(sym_arr)			   /*                        */
  Symbol *sym_arr;				   /*                        */
{ Symbol *a;					   /*                        */
  for (a = sym_arr; *a; a++)			   /*                        */
  { if (*a) UnlinkSymbol(*a); }			   /*                        */
  free(sym_arr);				   /*                        */
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
{ register int	  i,l;			   	   /*			     */
  register SymTab st;			   	   /*			     */
  register long	  len  = 0l;			   /*			     */
  register long	  cnt  = 0l;			   /*			     */
  register long	  used = 0l;			   /*			     */
						   /*			     */
  for ( i = 0; i < HASHMAX; i++ )		   /*			     */
  { for ( st = sym_tab[i]; st; st=NextSymTab(st) ) /*			     */
    { ErrPrintF2("--- BibTool symbol %4d %s\n",	   /*			     */
		 SymTabCount(st),		   /*			     */
		 SymbolValue(SymTabSymbol(st)));   /*			     */
      l     = symlen(SymTabSymbol(st)) + 1;	   /*			     */
      len  += l;				   /*			     */
      used += l * SymTabCount(st);		   /*                        */
      ++cnt;					   /*			     */
    }						   /*			     */
  }						   /*			     */
  ErrPrintF2("--- BibTool symbol table: %ld bytes for %ld symbols\n",/*	     */
	     len, cnt);				   /*			     */
  ErrPrintF("--- BibTool symbol table emulates %ld bytes\n",/*		     */
	     used);				   /*			     */
}						   /*------------------------*/
#endif
