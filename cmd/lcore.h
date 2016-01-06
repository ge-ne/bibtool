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

#define Declare(T,N,V) extern T N

/*---------------------------------------------------------------------------*/

extern void init_symdef();
extern SymDef symdef();
extern unsigned int hash();

#endif
/*---------------------------------------------------------------------------*/

Declare(SymDef, sym_group  , symdef("group",  L_GROUP,  NIL, p_cons));
Declare(SymDef, sym_cons   , symdef("cons",   L_LIST,   NIL, p_cons));

Declare(SymDef, sym_string , symdef("string", L_STRING, NIL, p_term_str));
Declare(SymDef, sym_block  , symdef("block",  L_BLOCK,  NIL, p_term_block));
Declare(SymDef, sym_number , symdef("number", L_NUMBER, NIL, p_term_num));

Declare(SymDef, sym_field  , symdef("field",  L_FIELD,  NIL, p_term_field));
Declare(SymDef, sym_true   , symdef("true",   L_TRUE,   NIL, p_sym_name));
Declare(SymDef, sym_false  , symdef("false",  L_FALSE,  NIL, p_sym_name));

Declare(SymDef, sym_set    , symdef("=",      L_SET,    NIL, p_sym_name));

Declare(SymDef, sym_quote  , symdef("quote",  L_QUOTE,  NIL, p_sym_name));

Declare(SymDef, sym_plus   , symdef("+",      L_PLUS,   NIL, p_sym_name));
Declare(SymDef, sym_minus  , symdef("-",      L_MINUS,  NIL, p_sym_name));
Declare(SymDef, sym_times  , symdef("*",      L_TIMES,  NIL, p_sym_name));
Declare(SymDef, sym_div    , symdef("/",      L_DIV,    NIL, p_sym_name));

Declare(SymDef, sym_and    , symdef("and",    L_AND,    NIL, p_sym_name));
Declare(SymDef, sym_or     , symdef("or",     L_OR,     NIL, p_sym_name));
Declare(SymDef, sym_not    , symdef("not",    L_NOT,    NIL, p_sym_name));
Declare(SymDef, sym_eq     , symdef("==",     L_EQ,     NIL, p_sym_name));
Declare(SymDef, sym_ge     , symdef(">=",     L_GE,     NIL, p_sym_name));
Declare(SymDef, sym_gt     , symdef(">",      L_GT,     NIL, p_sym_name));
Declare(SymDef, sym_le     , symdef("<=",     L_LE,     NIL, p_sym_name));
Declare(SymDef, sym_lt     , symdef("<",      L_LT,     NIL, p_sym_name));
Declare(SymDef, sym_ne     , symdef("!=",     L_NE,     NIL, p_sym_name));

Declare(SymDef, sym_mod    , symdef("mod",    L_MOD,    NIL, p_sym_name));
Declare(SymDef, sym_like   , symdef("like",   L_LIKE,   NIL, p_sym_name));
Declare(SymDef, sym_ilike  , symdef("ilike",  L_ILIKE,  NIL, p_sym_name));

Declare(SymDef*, sym_char  , (SymDef*)calloc(256, sizeof(SymDef)));

/*---------------------------------------------------------------------------*/
#undef Declare
