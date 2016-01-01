/*** symdef.h ******************************************************************
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

#endif
/*---------------------------------------------------------------------------*/

Declare(SymDef, sym_group  , sym_def("group",  -10, NIL, NULL, p_cons));
Declare(SymDef, sym_cons   , sym_def("cons",   -10, NIL, NULL, p_cons));

Declare(SymDef, sym_string , sym_def("string", -11, NIL, eval_self, p_term_str));
Declare(SymDef, sym_block  , sym_def("block",  -11, NIL, eval_self, p_term_block));
Declare(SymDef, sym_number , sym_def("number", -12, NIL, eval_self, p_term_num));

Declare(SymDef, sym_field  , sym_def("field",   -1, NIL, NULL, p_term_field));
Declare(SymDef, sym_true   , sym_def("true",    -1, NIL, eval_self, p_sym_name));
Declare(SymDef, sym_false  , sym_def("false",   -1, NIL, eval_self, p_sym_name));
Declare(SymDef, sym_builtin, sym_def("builtin", -1, NIL, NULL, p_term_field));

Declare(SymDef, sym_and    , sym_def("and",     10, NIL, NULL, p_sym_name));
Declare(SymDef, sym_or     , sym_def("or",      10, NIL, NULL, p_sym_name));
Declare(SymDef, sym_not    , sym_def("not",     21, NIL, NULL, p_sym_name));
Declare(SymDef, sym_eq     , sym_def("==",      30, NIL, NULL, p_sym_name));
Declare(SymDef, sym_ge     , sym_def(">=",      30, NIL, NULL, p_sym_name));
Declare(SymDef, sym_le     , sym_def("<=",      30, NIL, NULL, p_sym_name));
Declare(SymDef, sym_ne     , sym_def("!=",      30, NIL, NULL, p_sym_name));

Declare(SymDef, sym_mod    , sym_def("mod",     60, NIL, NULL, p_sym_name));
Declare(SymDef, sym_like   , sym_def("like",   22, NIL, NULL, p_sym_name));
Declare(SymDef, sym_ilike  , sym_def("ilike",  22, NIL, NULL, p_sym_name));

Declare(SymDef*, sym_char  , (SymDef*)calloc(256, sizeof(SymDef)));

/*---------------------------------------------------------------------------*/
#undef Declare
