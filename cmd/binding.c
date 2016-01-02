/*** binding.c *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <bibtool/error.h>
#include "binding.h"
#include "term.h"
#include "symdef.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
Binding binding _ARG((unsigned int size));
Term eval_term _ARG((Binding binding, Term term));
Term eval_self _ARG((Binding binding, Term term));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

#define Error(X,Y)					\
	error(ERR_ERROR|ERR_EXIT,(String)X,		\
	      (String)Y,(String)0,(String)0,(String)0,0,NULL)
/*-----------------------------------------------------------------------------
** Function:	binding()
** Type:	Binding
** Purpose:	
**		
** Arguments:
**	term	
** Returns:	
**___________________________________________________			     */
Binding binding(size)			   	   /*                        */
  unsigned int size;				   /*                        */
{						   /*                        */
  Binding bind = (Binding) malloc(sizeof(SBinding));/*                       */
  if (bind == BindingNULL) OUT_OF_MEMORY("binding");/*                       */
 						   /*                        */
  BJunks(bind) = (BJunk*) calloc(size, sizeof(BJunk));/*                     */
  if (BJunks(bind) == NULL) OUT_OF_MEMORY("binding");/*                      */
 						   /*                        */
  BSize(bind) = size;				   /*                        */
  NextBinding(bind) = BindingNULL;		   /*                        */
  return bind;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_bind()
** Type:	BJunk
** Purpose:	
**		
** Arguments:
**	binding	
**	 key	
** Returns:	
**___________________________________________________			     */
BJunk get_bind(binding, key)			   /*                        */
  Binding binding;				   /*                        */
  String key;					   /*                        */
{ unsigned int h = hash(key) % BSize(binding);	   /*                        */
  BJunk junk;					   /*                        */
  						   /*                        */
  for (;;)					   /*                        */
  {						   /*                        */
    for (junk = BJunks(binding)[h];		   /*                        */
	 junk;					   /*                        */
	 junk = NextJunk(junk))			   /*                        */
    { if (strcmp((char*)JKey(junk), (char*)key) == 0)/*                      */
      { return junk; }				   /*                        */
    }						   /*                        */
    binding = NextBinding(binding);		   /*                        */
    if (binding == BindingNULL) return NULL;	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bind()
** Type:	void
** Purpose:	
**		
** Arguments:
**	b	
**	key	
**	term	
**	get	
**	set	
** Returns:	nothing
**___________________________________________________			     */
void bind(b, key, term, get, set)		   /*                        */
  Binding b;				   	   /*                        */
  String key;					   /*                        */
  Term term;					   /*                        */
  Term (*get)();				   /*                        */
  void (*set)();				   /*                        */
{ unsigned int h = hash(key) % BSize(b);	   /*                        */
  BJunk junk;					   /*                        */
  
  for (junk = BJunks(b)[h]; junk; junk = NextJunk(junk))
  { if (strcmp((char*)JKey(junk), (char*)key) == 0)
    {
      JValue(junk) = term;
      JGet(junk)   = get;
      JSet(junk)   = set;
      return;
    }
  }

  junk = (BJunk) malloc(sizeof(SBJunk));	   /*                        */
  if (junk == NULL) OUT_OF_MEMORY("binding");	   /*                        */
  JKey(junk)     = key;				   /*                        */
  JValue(junk)   = term;			   /*                        */
  JGet(junk)     = get;				   /*                        */
  JSet(junk)     = set;				   /*                        */
  NextJunk(junk) = BJunks(b)[h];		   /*                        */
  BJunks(b)[h]   = junk;			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_print()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_print(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  print_term(stdout, Cdr(term));		   /*                        */
  return NIL;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	def_binding()
** Type:	Binding
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
Binding def_binding()				   /*                        */
{ Binding b = binding(511);			   /*                        */

  bind(b, "add.field"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "apply.alias"			, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "apply.modify"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "apply.include"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "and"				, NIL, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "bibtex.env.name"		, NIL, NULL, NULL);   /* RscString	*/ 	
  bind(b, "bibtex.search.path"		, NIL, NULL, NULL);   /* RscString	*/ 	
  bind(b, "check.double"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "check.double.delete"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "check.rule"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "check.case.sensitive"	, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "clear.ignored.words"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "count.all"			, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "count.used"			, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "crossref.limit"		, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "default.key"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "delete.field"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "dir.file.separator"		, NIL, NULL, NULL);   /* RscString	*/ 	
  bind(b, "dump.symbols"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "env.separator"		, NIL, NULL, NULL);   /* RscString	*/ 	
  bind(b, "extract.file"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "extract.regex"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "expand.macros"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "expand.crossref"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "fmt.inter.name"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "fmt.name.pre"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "fmt.name.name"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "fmt.name.title"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "fmt.title.title"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "fmt.et.al"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "fmt.word.separator"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "field.type"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "false"			, term_false, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "input"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "ignored.word"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "ilike"			, NIL, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "key.generation"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "key.base"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "key.format"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "key.make.alias"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "key.number.separator"	, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "key.expand.macros"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "like"			, NIL, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "macro.file"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "mod"				, NIL, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "new.entry.type"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "new.field.type"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "new.format.type"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "not"				, NIL, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "nil"				, NIL, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "output.file"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "or"				, NIL, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "pass.comments"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "preserve.key.case"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "preserve.keys"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print"			, NIL, g_print, NULL);   /* RscByFct	*/ 	
  bind(b, "print.align.string"		, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "print.align.comment"		, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "print.align.preamble"	, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "print.align.key"		, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "print.align"			, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "print.all.strings"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print.entry.types"		, NIL, NULL, NULL);   /* RscString	*/ 	
  bind(b, "print.equal.right"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print.braces"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print.comma.at.end"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print.deleted.prefix"	, NIL, NULL, NULL);   /* RscString	*/ 	
  bind(b, "print.deleted.entries"	, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print.indent"		, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "print.line.length"		, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "print.newline"		, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "print.parentheses"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print.terminal.comma"	, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print.use.tab"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "print.wide.equal"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "quiet"			, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "regexp.syntax"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "rename.field"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "resource"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "resource.search.path"	, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "rewrite.rule"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "rewrite.case.sensitive"	, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "rewrite.limit"		, NIL, NULL, NULL);   /* RscNumeric	*/ 	
  bind(b, "select"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "select.by.string"		, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "select.by.non.string"	, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "select.by.string.ignored"	, NIL, NULL, NULL);   /* RscString	*/ 	
  bind(b, "select.case.sensitive"	, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "select.fields"		, NIL, NULL, NULL);   /* RscString	*/ 	
  bind(b, "select.non"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "select.crossrefs"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "sort"			, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "sort.cased"			, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "sort.macros"			, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "sort.reverse"		, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "sort.order"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "sort.format"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "suppress.initial.newline"	, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "symbol.type"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "tex.define"			, NIL, NULL, NULL);   /* RscByFct	*/ 	
  bind(b, "true"			, term_true, NULL, NULL);   /* RscTerm	*/ 	
  bind(b, "verbose"			, NIL, NULL, NULL);   /* RscBoolean	*/ 	
  bind(b, "version"			, NIL, NULL, NULL);   /* RscByFct	*/ 	

  return b;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_term()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term eval_term(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ BJunk junk;					   /*                        */
 						   /*                        */
  if (term == NIL) return NIL;			   /*                        */
 						   /*                        */
  junk = get_bind(binding, TermName(term));	   /*                        */
 						   /*                        */
  if (junk == NULL)	   			   /*                        */
  { Error("Undefined function ", TermName(term)); }/*                        */
  if (JGet(junk) == NULL)	   		   /*                        */
  { Error("Undefined getter for ", TermName(term)); }/*                      */
 						   /*                        */
  return (*JGet(junk))(binding, term);	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_self()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term eval_self(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  register Term term;				   /*                        */
{						   /*                        */
  return term;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_cons()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term eval_builtin(binding, term)		   /*                        */
  Binding binding;				   /*                        */
  register Term term;				   /*                        */
{						   /*                        */

  if (strcmp((char*)TString(term), "print") == 0) {
    print_term(stdout,
	       eval_term(binding, Cdr(term)));
  }

  return NIL;					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
