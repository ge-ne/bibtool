/*** term.c ********************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "term.h"
#include "commands.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

Term new_term _ARG((int op, Term a, Term b));
void free_term _ARG((Term t));

static void dump_t();

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	new_term()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	op	
**	 a1	
**	 a2	
** Returns:	
**___________________________________________________			     */
Term new_term(op, a1, a2)			   /*                        */
  int op;					   /*                        */
  Term a1;					   /*                        */
  Term a2;					   /*                        */
{						   /*                        */
  Term t = (Term)malloc(sizeof(STerm));		   /*                        */
 						   /*                        */
  TermOp(t) = op;				   /*                        */
  TermTerm(t) = a1;				   /*                        */
  TermTerm2(t) = a2;				   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_term_num()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	n	
** Returns:	
**___________________________________________________			     */
Term new_term_num(n)				   /*                        */
  long n;					   /*                        */
{						   /*                        */
  Term t = (Term)malloc(sizeof(STerm));		   /*                        */
  TermOp(t) = NUMBER;				   /*                        */
  TermNumber(t) = n;				   /*                        */
  TermTerm2(t) = TermNULL;			   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_term_string()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	op	
**	 s	
** Returns:	
**___________________________________________________			     */
Term new_term_string(op, s)			   /*                        */
  int op;					   /*                        */
  char * s;					   /*                        */
{						   /*                        */
  Term t = (Term)malloc(sizeof(STerm));		   /*                        */
  TermOp(t) = op;				   /*                        */
  TermString(t) = s;				   /*                        */
  TermTerm2(t) = TermNULL;			   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_term()
** Type:	void
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	nothing
**___________________________________________________			     */
void free_term(t)				   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  switch (TermOp(t))				   /*                        */
  { case STRING:				   /*                        */
    case FIELD:				   	   /*                        */
    case NUMBER:				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      if (TermTerm(t)) { free_term(TermTerm(t)); } /*                        */
  }						   /*                        */
  if (TermTerm2(t)) { free_term(TermTerm2(t)); }   /*                        */
  free(t);					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_list()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	stream	
**	 t	
**	 in	
**	 s	
** Returns:	nothing
**___________________________________________________			     */
static void dump_list(stream, t, in, s)		   /*                        */
  FILE * stream;				   /*                        */
  Term t;					   /*                        */
  int in;					   /*                        */
{						   /*                        */
  for (; t && TermOp(t) == PAIR; t = TermTerm2(t)) /*                        */
  { putchar(' ');				   /*                        */
    dump_t(stream, TermTerm(t), 0);		   /*                        */
  }						   /*                        */
  if (t) dump_t(stream, t, in);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_cmd()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	stream	
**	 t	
**	 in	
**	 s	
** Returns:	nothing
**___________________________________________________			     */
static void dump_cmd(stream, t, in, s)		   /*                        */
  FILE * stream;				   /*                        */
  Term t;					   /*                        */
  int in;					   /*                        */
  char * s;					   /*                        */
{						   /*                        */
  fprintf(stream, "(%s",s);			   /*                        */
  dump_list(stream, TermTerm(t), in + 1);	   /*                        */
  fputc(')', stream);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_t()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	t	
**	 in	
** Returns:	nothing
**___________________________________________________			     */
static void dump_t(stream, t, in)		   /*                        */
  FILE * stream;				   /*                        */
  Term t;					   /*                        */
  int in;					   /*                        */
{ int i;					   /*                        */
  if (in > 0 )					   /*                        */
  { fputc('\n', stream);			   /*                        */
    for (i = 0; i < in; i++) fputc(' ', stream);   /*                        */
  }						   /*                        */
						   /*                        */
  switch (t == TermNULL ? -1 : TermOp(t))	   /*                        */
  { case -1:					   /*                        */
      fputs("nil", stream);			   /*                        */
      return;					   /*                        */
    case PAIR:					   /*                        */
      putchar('(');				   /*                        */
      dump_list(stream, t, ++in);		   /*                        */
      putchar(')');				   /*                        */
      return;					   /*                        */
    case FIELD:					   /*                        */
      fprintf(stream, "'%s'",TermString(t));	   /*                        */
      return;					   /*                        */
    case STRING:				   /*                        */
      fprintf(stream, "\"%s\"",TermString(t));	   /*                        */
      return;					   /*                        */
    case BLOCK:					   /*                        */
      fprintf(stream, "{%s}",TermString(t));	   /*                        */
      return;					   /*                        */
    case NUMBER:				   /*                        */
      fprintf(stream, "%ld",TermNumber(t));	   /*                        */
      return;					   /*                        */
    case NOT:					   /*                        */
      fputc('(', stream);			   /*                        */
      dump_t(TermTerm(t), in + 1);		   /*                        */
      fputc(' ', stream);			   /*                        */
      return;					   /*                        */
#define CMD(S) dump_cmd(stream, t, in, S); return
    case ADD_FIELD:
      CMD("add.field"); 
    case APPLY_ALIAS:
      CMD("apply.alias"); 
    case APPLY_MODIFY:
      CMD("apply.modify"); 
    case APPLY_INCLUDE:
      CMD("apply.include"); 
    case BIBTEX_ENV_NAME:
      CMD("bibtex.env.name"); 
    case BIBTEX_SEARCH_PATH:
      CMD("bibtex.search.path"); 
    case CHECK_DOUBLE:
      CMD("check.double"); 
    case CHECK_DOUBLE_DELETE:
      CMD("check.double.delete"); 
    case CHECK_RULE:
      CMD("check.rule"); 
    case CHECK_CASE_SENSITIVE:
      CMD("check.case.sensitive"); 
    case CLEAR_IGNORED_WORDS:
      CMD("clear.ignored.words"); 
    case COUNT_ALL:
      CMD("count.all"); 
    case COUNT_USED:
      CMD("count.used"); 
    case CROSSREF_LIMIT:
      CMD("crossref.limit"); 
    case DEFAULT_KEY:
      CMD("default.key"); 
    case DELETE_FIELD:
      CMD("delete.field"); 
    case DIR_FILE_SEPARATOR:
      CMD("dir.file.separator"); 
    case DUMP_SYMBOLS:
      CMD("dump.symbols"); 
    case ENV_SEPARATOR:
      CMD("env.separator"); 
    case EXTRACT_FILE:
      CMD("extract.file"); 
    case EXTRACT_REGEX:
      CMD("extract.regex"); 
    case EXPAND_MACROS:
      CMD("expand.macros"); 
    case EXPAND_CROSSREF:
      CMD("expand.crossref"); 
    case FMT_INTER_NAME:
      CMD("fmt.inter.name"); 
    case FMT_NAME_PRE:
      CMD("fmt.name.pre"); 
    case FMT_NAME_NAME:
      CMD("fmt.name.name"); 
    case FMT_NAME_TITLE:
      CMD("fmt.name.title"); 
    case FMT_TITLE_TITLE:
      CMD("fmt.title.title"); 
    case FMT_ET_AL:
      CMD("fmt.et.al"); 
    case FMT_WORD_SEPARATOR:
      CMD("fmt.word.separator"); 
    case FIELD_TYPE:
      CMD("field.type"); 
    case INPUT:
      CMD("input"); 
    case IGNORED_WORD:
      CMD("ignored.word"); 
    case KEY_GENERATION:
      CMD("key.generation"); 
    case KEY_BASE:
      CMD("key.base"); 
    case KEY_FORMAT:
      CMD("key.format"); 
    case KEY_MAKE_ALIAS:
      CMD("key.make.alias"); 
    case KEY_NUMBER_SEPARATOR:
      CMD("key.number.separator"); 
    case KEY_EXPAND_MACROS:
      CMD("key.expand.macros"); 
    case MACRO_FILE:
      CMD("macro.file"); 
    case NEW_ENTRY_TYPE:
      CMD("new.entry.type"); 
    case NEW_FIELD_TYPE:
      CMD("new.field.type"); 
    case NEW_FORMAT_TYPE:
      CMD("new.format.type"); 
    case OUTPUT_FILE:
      CMD("output.file"); 
    case PASS_COMMENTS:
      CMD("pass.comments"); 
    case PRESERVE_KEY_CASE:
      CMD("preserve.key.case"); 
    case PRESERVE_KEYS:
      CMD("preserve.keys"); 
    case PRINT:
      CMD("print"); 
    case PRINT_ALIGN_STRING:
      CMD("print.align.string"); 
    case PRINT_ALIGN_COMMENT:
      CMD("print.align.comment"); 
    case PRINT_ALIGN_PREAMBLE:
      CMD("print.align.preamble"); 
    case PRINT_ALIGN_KEY:
      CMD("print.align.key"); 
    case PRINT_ALIGN:
      CMD("print.align"); 
    case PRINT_ALL_STRINGS:
      CMD("print.all.strings"); 
    case PRINT_ENTRY_TYPES:
      CMD("print.entry.types"); 
    case PRINT_EQUAL_RIGHT:
      CMD("print.equal.right"); 
    case PRINT_BRACES:
      CMD("print.braces"); 
    case PRINT_COMMA_AT_END:
      CMD("print.comma.at.end"); 
    case PRINT_DELETED_PREFIX:
      CMD("print.deleted.prefix"); 
    case PRINT_DELETED_ENTRIES:
      CMD("print.deleted.entries"); 
    case PRINT_INDENT:
      CMD("print.indent"); 
    case PRINT_LINE_LENGTH:
      CMD("print.line.length"); 
    case PRINT_NEWLINE:
      CMD("print.newline"); 
    case PRINT_PARENTHESES:
      CMD("print.parentheses"); 
    case PRINT_TERMINAL_COMMA:
      CMD("print.terminal.comma"); 
    case PRINT_USE_TAB:
      CMD("print.use.tab"); 
    case PRINT_WIDE_EQUAL:
      CMD("print.wide.equal"); 
    case QUIET:
      CMD("quiet"); 
    case REGEXP_SYNTAX:
      CMD("regexp.syntax"); 
    case RENAME_FIELD:
      CMD("rename.field"); 
    case RESOURCE:
      CMD("resource"); 
    case RESOURCE_SEARCH_PATH:
      CMD("resource.search.path"); 
    case REWRITE_RULE:
      CMD("rewrite.rule"); 
    case REWRITE_CASE_SENSITIVE:
      CMD("rewrite.case.sensitive"); 
    case REWRITE_LIMIT:
      CMD("rewrite.limit"); 
    case SELECT:
      CMD("select"); 
    case SELECT_BY_STRING:
      CMD("select.by.string"); 
    case SELECT_BY_NON_STRING:
      CMD("select.by.non.string"); 
    case SELECT_BY_STRING_IGNORED:
      CMD("select.by.string.ignored"); 
    case SELECT_CASE_SENSITIVE:
      CMD("select.case.sensitive"); 
    case SELECT_FIELDS:
      CMD("select.fields"); 
    case SELECT_NON:
      CMD("select.non"); 
    case SELECT_CROSSREFS:
      CMD("select.crossrefs"); 
    case SORT:
      CMD("sort"); 
    case SORT_CASED:
      CMD("sort.cased"); 
    case SORT_MACROS:
      CMD("sort.macros"); 
    case SORT_REVERSE:
      CMD("sort.reverse"); 
    case SORT_ORDER:
      CMD("sort.order"); 
    case SORT_FORMAT:
      CMD("sort.format"); 
    case SUPPRESS_INITIAL_NEWLINE:
      CMD("suppress.initial.newline"); 
    case SYMBOL_TYPE:
      CMD("symbol.type"); 
    case TEX_DEFINE:
      CMD("tex.define"); 
    case VERBOSE:
      CMD("verbose"); 
    case VERSION:
      CMD("version"); 
  }
  fputc('(', stream);
  switch(TermOp(t))
  {
    case EQ:     fputs("=", stream); break;
    case NE:     fputs("!=", stream); break;
    case LT:     fputs("<", stream); break;
    case LE:     fputs("<=", stream); break;
    case GT:     fputs(">", stream); break;
    case GE:     fputs(">=", stream); break;
    case LIKE:   fputs("like", stream); break;
    case ILIKE:  fputs("ilike", stream); break;
    case PLUS:   fputs("+", stream); break;
    case MINUS:  fputs("-", stream); break;
    case TIMES:  fputs("*", stream); break;
    case DIVIDE: fputs("/", stream); break;
    case AND:    fputs("and", stream); break;
    case OR:     fputs("or", stream); break;
    case FCT_LOWERCASE: fputs("lowercase", stream); break;
    case FCT_UPPERCASE: fputs("uppercase", stream); break;
    case FCT_SUBSTRING: fputs("substring", stream); break;
    case FCT_TRIM:      fputs("trim", stream); break;
    default:
      fprintf(stderr, "*** UNKNOWN OP CODE: %d\n", TermOp(t));
      return;
  }						   /*                        */
  dump_list(stream, TermTerm(t), ++in);		   /*                        */
  fputc(')', stream);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_term()
** Type:	void
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	nothing
**___________________________________________________			     */
void dump_term(t) 				   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  dump_t(stdout, t, 0);				   /*                        */
  fputc('\n', stdout);				   /*                        */
}						   /*------------------------*/
