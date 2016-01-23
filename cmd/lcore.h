/*** symdef.h ******************************************************************
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

#include "lreader.h"

#ifndef Declare

#include <stdio.h>
#include <bibtool/type.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

#define Declare(SYM,VAL) extern SymDef SYM

/*---------------------------------------------------------------------------*/

extern void init_symdef();
extern SymDef symdef();
extern unsigned int hash();
extern Term g_version();
extern Term g_field();
extern void print_quoted();			   /*                        */
extern Term eval_bool _ARG((Binding b, Term t));   /*                        */

extern SymDef* sym_char;			   /*                        */

#endif
/*---------------------------------------------------------------------------*/
#define SYMDEF(S,N,G) symdef((String)S,N,G)

Declare(sym_group,  SYMDEF("group",    L_GROUP,		NULL));
Declare(sym_list,   SYMDEF("list",     L_LIST,		NULL));
Declare(sym_fct,    SYMDEF("function", L_FUNCTION,	NULL));

Declare(sym_string, SYMDEF("string",   L_STRING,	NULL));
Declare(sym_block,  SYMDEF("block",    L_BLOCK,		NULL));
Declare(sym_number, SYMDEF("number",   L_NUMBER,	NULL));

Declare(sym_field,  SYMDEF("field",    L_FIELD,		NULL));
Declare(sym_true,   SYMDEF("true",     L_TRUE,		g_self));
Declare(sym_false,  SYMDEF("false",    L_FALSE,		g_self));

Declare(sym_set,    SYMDEF("=",	       L_SET,		g_setq));

Declare(sym_quote,  SYMDEF("quote",    L_QUOTE,		NULL));

Declare(sym_plus,   SYMDEF("+",	       L_PLUS,		g_plus));
Declare(sym_minus,  SYMDEF("-",	       L_MINUS,		g_minus));
Declare(sym_times,  SYMDEF("*",	       L_TIMES,		g_times));
Declare(sym_div,    SYMDEF("/",	       L_DIV,		g_div));
Declare(sym_mod,    SYMDEF("%",	       L_MOD,		g_mod));

Declare(sym_and,    SYMDEF("&&",       L_AND,		g_and));
Declare(sym_or,	    SYMDEF("||",       L_OR,		g_or));
Declare(sym_not,    SYMDEF("!",	       L_NOT,		g_not));
Declare(sym_eq,	    SYMDEF("==",       L_EQ,		g_eq));
Declare(sym_ne,	    SYMDEF("!=",       L_NE,		g_ne));
Declare(sym_ge,	    SYMDEF(">=",       L_GE,		NULL));
Declare(sym_gt,	    SYMDEF(">",	       L_GT,		NULL));
Declare(sym_le,	    SYMDEF("<=",       L_LE,		NULL));
Declare(sym_lt,	    SYMDEF("<",	       L_LT,		NULL));

Declare(sym_like,   SYMDEF("like",     L_LIKE,		NULL));
Declare(sym_ilike,  SYMDEF("ilike",    L_ILIKE,		NULL));

Declare(sym_if,	    SYMDEF("if",       L_IF,		NULL));
Declare(sym_while,  SYMDEF("while",    L_WHILE,		NULL));
Declare(sym_with,   SYMDEF("with",     L_WITH,		NULL));

/*---------------------------------------------------------------------------*/
#undef Declare
