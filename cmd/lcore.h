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

extern SymDef* sym_char;

#endif
/*---------------------------------------------------------------------------*/
#define SYMDEF(S,N,P,G) symdef((String)S,N,P,G)

Declare(sym_group , SYMDEF("group",  L_GROUP,  p_cons,       NULL));
Declare(sym_list  , SYMDEF("list",   L_LIST,   p_cons,       g_self));
Declare(sym_cons  , SYMDEF("cons",   L_CONS,   p_cons,       g_fct));

Declare(sym_string, SYMDEF("string", L_STRING, p_term_str,   g_self));
Declare(sym_block , SYMDEF("block",  L_BLOCK,  p_term_block, g_self));
Declare(sym_number, SYMDEF("number", L_NUMBER, p_term_num,   g_self));

Declare(sym_field , SYMDEF("field",  L_FIELD,  p_term_field, NULL));
Declare(sym_true  , SYMDEF("true",   L_TRUE,   p_sym_name,   g_self));
Declare(sym_false , SYMDEF("false",  L_FALSE,  p_sym_name,   g_self));

Declare(sym_set   , SYMDEF("=",      L_SET,    p_sym_name,   NULL));

Declare(sym_quote , SYMDEF("quote",  L_QUOTE,  p_sym_name,   NULL));

Declare(sym_plus  , SYMDEF("+",      L_PLUS,   p_sym_name,   g_plus));
Declare(sym_minus , SYMDEF("-",      L_MINUS,  p_sym_name,   g_minus));
Declare(sym_times , SYMDEF("*",      L_TIMES,  p_sym_name,   g_times));
Declare(sym_div   , SYMDEF("/",      L_DIV,    p_sym_name,   g_div));
Declare(sym_mod   , SYMDEF("mod",    L_MOD,    p_sym_name,   g_mod));

Declare(sym_and   , SYMDEF("and",    L_AND,    p_sym_name,   g_and));
Declare(sym_or    , SYMDEF("or",     L_OR,     p_sym_name,   g_or));
Declare(sym_not   , SYMDEF("not",    L_NOT,    p_sym_name,   g_not));
Declare(sym_eq    , SYMDEF("==",     L_EQ,     p_sym_name,   g_eq));
Declare(sym_ne    , SYMDEF("!=",     L_NE,     p_sym_name,   g_ne));
Declare(sym_ge    , SYMDEF(">=",     L_GE,     p_sym_name,   NULL));
Declare(sym_gt    , SYMDEF(">",      L_GT,     p_sym_name,   NULL));
Declare(sym_le    , SYMDEF("<=",     L_LE,     p_sym_name,   NULL));
Declare(sym_lt    , SYMDEF("<",      L_LT,     p_sym_name,   NULL));

Declare(sym_like  , SYMDEF("like",   L_LIKE,   p_sym_name,   NULL));
Declare(sym_ilike , SYMDEF("ilike",  L_ILIKE,  p_sym_name,   NULL));

Declare(sym_if    , SYMDEF("if",     L_IF,     p_sym_name,   NULL));
Declare(sym_while , SYMDEF("while",  L_WHILE,  p_sym_name,   NULL));

/*---------------------------------------------------------------------------*/
#undef Declare
