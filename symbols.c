/******************************************************************************
** $Id: symbols.c,v 1.3 2007-02-08 05:35:57 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2002 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
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
 typedef struct STAB				   /*                        */
  { Uchar	*st_name;	/* The string representation of the symbol   */
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
** Type:	Uchar *
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
 Uchar * sym_add _ARG((Uchar *s,int count));	   /* symbols.c              */
 Uchar * sym_extract _ARG((Uchar *ap,Uchar *ep,int count));/* symbols.c      */
 char * new_string _ARG((char * s));		   /* symbols.c              */
 int sym_flag _ARG((Uchar * s));		   /* symbols.c              */
 static StringTab new_string_tab _ARG((Uchar *name,int count,int flags));/* symbols.c*/
 static int hashindex _ARG((Uchar *s));		   /* symbols.c              */
 void init_symbols _ARG((void));		   /* symbols.c              */
 void sym_dump _ARG((void));			   /* symbols.c              */
 void sym_gc _ARG((void));			   /* symbols.c              */
 void sym_set_flag _ARG((Uchar *s,int flags));	   /* symbols.c              */
 void sym_unlink _ARG((Uchar *s));		   /* symbols.c              */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

#ifdef HASH_TABLE_SIZE
#define HASHMAX HASH_TABLE_SIZE
#else
#define HASHMAX 307
#endif



 Uchar * sym_empty    = NULL;
 Uchar * sym_crossref = NULL;


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
  return(t);					   /*			     */
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
** Returns:	Pointer to a new inbstance of a |StringTab|.
**___________________________________________________			     */
static StringTab new_string_tab(name,count,flags)  /*			     */
  Uchar		     *name;			   /*			     */
  int		     count;			   /*			     */
  int		     flags;			   /*			     */
{ register StringTab new;			   /*			     */
						   /*			     */
  if ( (new=(StringTab)malloc(sizeof(struct STAB))) == 0L )/*		     */
  { OUT_OF_MEMORY("StringTab"); }   		   /*			     */
  SymbolName(new)  = name;			   /*			     */
  SymbolCount(new) = count;			   /*			     */
  SymbolFlags(new) = flags;			   /*			     */
  SymbolUsed(new)  = 0;				   /*			     */
  NextSymbol(new)  = (StringTab)0;		   /*			     */
  return(new);					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	hashindex()
** Purpose:	Compute the sum of ASCII values modulo |HASHMAX|
**		to be used as an hashindex.
** Arguments:
**	s	string to be analyzed.
** Returns:	hashindex
**___________________________________________________			     */
static int hashindex(s)				   /*                        */
  Uchar *s;					   /*                        */
{ int	index=0;				   /*                        */
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
**		symbol comparison assumtion. Thus this case is caught
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
  if ( sym_empty != NULL ) return;		   /*                        */
  for ( i=0; i<HASHMAX; i++ ) sym_tab[i] = NULL;   /*			     */
  sym_empty    = sym_add((Uchar*)"",-1);	   /*                        */
  sym_crossref = sym_add((Uchar*)"crossref",-1);   /*                        */
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
  Uchar * s;					   /*                        */
{						   /*                        */
  if ( last_stp == NULL || SymbolName(last_stp) != s )/*                     */
  { s = sym_add(s,0); }				   /*                        */
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
  register Uchar *s;				   /*			     */
  register int  flags;				   /*			     */
{ 						   /*                        */
  if ( last_stp == NULL || SymbolName(last_stp) != s )/*                     */
  { s = sym_add(s,0); }				   /*                        */
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
**		symbol will never bee deleted from the symbol
**		table. Static can be used at places where one does not
**		care about the memory occupied.
**
**		If no more memory is available then an error is raised
**		and the program is terminated.
**
**		See also the macro |symbol()| in |symbols.h| for a
**		convenient alternative to this function.
** Arguments:
**	s	String which should be translated into a symbol.
**	count	The use count which should be added t the symbol
** Returns:	The new symbol.
**___________________________________________________			     */
Uchar * sym_add(s,count)			   /*			     */
  register Uchar     *s;		   	   /*			     */
  register int	     count;			   /*			     */
{ register StringTab *stp;			   /*			     */
						   /*			     */
  if ( s == (Uchar*)NULL ) return (Uchar*)NULL;	   /* ignore dummies.	     */
 						   /*                        */
  for ( stp = &sym_tab[hashindex(s)];		   /*			     */
       *stp != NULL;		   		   /*			     */
        stp = &NextSymbol(*stp) )		   /*			     */
  {						   /*                        */
    if ( strcmp((char*)s,(char*)SymbolName(*stp)) == 0 )/*		     */
    { if ( count>0 ) SymbolCount(*stp) += count;   /*			     */
      last_stp = *stp;			   	   /*			     */
      if ( s != SymbolName(*stp) )		   /*                        */
      { SymbolUsed(*stp)++; }			   /*                        */
      return SymbolName(*stp);			   /*			     */
    }						   /*			     */
  }						   /*			     */
  if ( count<0 )				   /*                        */
  { count = 0;					   /*                        */
    SymbolFlags(*stp) != SYMBOL_STATIC;		   /*                        */
  }	   					   /*			     */
  else						   /*                        */
  { s = new_Ustring(s); }		   	   /*			     */
  *stp	   = new_string_tab(s,count,0);		   /*			     */
  last_stp = *stp;				   /*			     */
  SymbolUsed(*stp)++;				   /*                        */
  return SymbolName(*stp);			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sym_unlink()
** Purpose:	Free a symbol since it is no longer used.
**		This does not mean that the memory is also freed. The
**		symbol can be static or used at other places. The real
**		free operation requires that the garbage collector
**		|sym_gc()| to be called.
**
**		If the argument is |NULL| or an arbitrary string (no
**		symbol) then this case is also dealt with.
** Arguments:
**	s	Symbol to be released.
** Returns:	nothing
**___________________________________________________			     */
void sym_unlink(s)				   /*			     */
  register Uchar     *s;			   /*			     */
{ register StringTab st;			   /*			     */
						   /*			     */
  if ( s == NULL ) return;		   	   /* ignore dummies.	     */
 						   /*                        */
  for ( st = sym_tab[hashindex(s)];		   /*			     */
        st != NULL;		   		   /*			     */
        st = NextSymbol(st) )		   	   /*			     */
  { if ( s == SymbolName(st) )	   		   /*			     */
    { SymbolUsed(st)--;				   /* reduce reference count */
      return;			   		   /*			     */
    }						   /*			     */
  }						   /*			     */
#ifdef DEBUG
  ErrPrintF("*** Attempt to free an undefined symbol: %s\n",s);/*            */
#endif
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	sym_gc()
** Purpose:	This is the garbade collector. It analyzes the symbol
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
{						   /*                        */
  register StringTab st, st2;			   /*			     */
  register int i;				   /*                        */
  						   /*                        */
  for ( i=0;i<HASHMAX;i++ )			   /*			     */
  {						   /*                        */
    while (sym_tab[i] && SymbolUsed(sym_tab[i])<=0)
    { st = sym_tab[i];
      sym_tab[i] = NextSymbol(st);
      if ( (SymbolFlags(st) & SYMBOL_STATIC) == 0 )
      { free(SymbolName(st)); }
      free(st);
    }
    st = sym_tab[i];
    if ( st )
    {
      while ( (st2=NextSymbol(st)) != NULL &&
	      SymbolUsed(st) <= 0 )
      { NextSymbol(st) = NextSymbol(st2);
        if ( (SymbolFlags(st2) & SYMBOL_STATIC) == 0 )
	{ free(SymbolName(st2)); }
	free(st2);
      }						   /*                        */
    }						   /*                        */
  }						   /*			     */
}						   /*------------------------*/

#ifdef New
/*-----------------------------------------------------------------------------
** Function*:	sym_extract()
** Purpose:	Extract a symbol from a string.
** Arguments:
**	ap
**	ep
**	count
** Returns:	
**___________________________________________________			     */
Uchar * sym_extract(ap,ep,count)		   /*			     */
  register Uchar *ap;				   /* pointer to first char  */
  register Uchar *ep;				   /* pointer after last char*/
  register int	count;				   /*			     */
{ Uchar c;					   /*			     */
						   /*			     */
  c   = *ep;					   /*			     */
  *ep = '\0';					   /*			     */
  ap  = sym_add(ap,count<0?0:count);		   /*			     */
  *ep = c;					   /*			     */
  return ap;					   /*			     */
}						   /*------------------------*/
#endif

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
  for ( i=0;i<HASHMAX;i++ )			   /*			     */
  { for ( st = sym_tab[i]; st; st=NextSymbol(st) ) /*			     */
    { ErrPrintF2("--- BibTool symbol %4d %s\n",	   /*			     */
		 (int)SymbolCount(st),		   /*			     */
		 SymbolName(st));		   /*			     */
      l     = strlen(SymbolName(st))+1;		   /*			     */
      len  += l;				   /*			     */
      used += l*SymbolCount(st);		   /*                        */
      ++cnt;					   /*			     */
    }						   /*			     */
  }						   /*			     */
  ErrPrintF2("--- BibTool symbol table: %ld bytes for %ld symbols\n",/*	     */
	     len, cnt);				   /*			     */
  ErrPrintF("--- BibTool symbol table emulates %ld bytes\n",/*		     */
	     used);				   /*			     */
}						   /*------------------------*/
#endif

