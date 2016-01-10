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

Declare(sym_group , symdef("group",  L_GROUP,  NIL, p_cons,       NULL));
Declare(sym_cons  , symdef("cons",   L_LIST,   NIL, p_cons,       g_fct));

Declare(sym_string, symdef("string", L_STRING, NIL, p_term_str,   g_self));
Declare(sym_block , symdef("block",  L_BLOCK,  NIL, p_term_block, g_self));
Declare(sym_number, symdef("number", L_NUMBER, NIL, p_term_num,   g_self));

Declare(sym_field , symdef("field",  L_FIELD,  NIL, p_term_field, NULL));
Declare(sym_true  , symdef("true",   L_TRUE,   NIL, p_sym_name,   g_self));
Declare(sym_false , symdef("false",  L_FALSE,  NIL, p_sym_name,   g_self));

Declare(sym_set   , symdef("=",      L_SET,    NIL, p_sym_name,   NULL));

Declare(sym_quote , symdef("quote",  L_QUOTE,  NIL, p_sym_name,   NULL));

Declare(sym_plus  , symdef("+",      L_PLUS,   NIL, p_sym_name,   NULL));
Declare(sym_minus , symdef("-",      L_MINUS,  NIL, p_sym_name,   g_minus));
Declare(sym_times , symdef("*",      L_TIMES,  NIL, p_sym_name,   NULL));
Declare(sym_div   , symdef("/",      L_DIV,    NIL, p_sym_name,   NULL));

Declare(sym_and   , symdef("and",    L_AND,    NIL, p_sym_name,   g_and));
Declare(sym_or    , symdef("or",     L_OR,     NIL, p_sym_name,   g_or));
Declare(sym_not   , symdef("not",    L_NOT,    NIL, p_sym_name,   g_not));
Declare(sym_eq    , symdef("==",     L_EQ,     NIL, p_sym_name,	  g_eq));
Declare(sym_ne    , symdef("!=",     L_NE,     NIL, p_sym_name,	  g_ne));
Declare(sym_ge    , symdef(">=",     L_GE,     NIL, p_sym_name,   NULL));
Declare(sym_gt    , symdef(">",      L_GT,     NIL, p_sym_name,   NULL));
Declare(sym_le    , symdef("<=",     L_LE,     NIL, p_sym_name,   NULL));
Declare(sym_lt    , symdef("<",      L_LT,     NIL, p_sym_name,   NULL));

Declare(sym_mod   , symdef("mod",    L_MOD,    NIL, p_sym_name,   NULL));
Declare(sym_like  , symdef("like",   L_LIKE,   NIL, p_sym_name,   NULL));
Declare(sym_ilike , symdef("ilike",  L_ILIKE,  NIL, p_sym_name,   NULL));

/*---------------------------------------------------------------------------*/
#undef Declare
