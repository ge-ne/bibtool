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

/*-----------------------------------------------------------------------------
** Typedef:	SSymDef
** Purpose:	
**		
**___________________________________________________			     */
typedef struct S_SYMDEF {			   /*                        */
  String name;				   	   /*                        */
  void * value;					   /*                        */
  int op;					   /*                        */
  struct S_TERM * (*parse)_ARG((FILE*));	   /*                        */
  int (*print)_ARG((FILE*, struct S_TERM *));	   /*                        */
} SSymDef, *SymDef;				   /*------------------------*/

#define SymDefNull ((SymDef)0)

#define SymName(T)   ((T)->name)
#define SymOp(T)     ((T)->op)
#define SymValue(T)  ((T)->value)
#define SymParse(T)  ((T)->parse)
#define SymPrint(T)  ((T)->print)

#define SymIs(S,C) ((S) == sym_char[C]) 

#define Declare(T,N,V) extern T N

/*---------------------------------------------------------------------------*/

extern void init_symdef();

#endif
/*---------------------------------------------------------------------------*/

Declare(SymDef, sym_number   , sym_def(NULL,     -1, NULL, p_term_num));
Declare(SymDef, sym_string   , sym_def(NULL,     -2, NULL, p_term_str));
Declare(SymDef, sym_field    , sym_def(NULL,     -3, NULL, p_term_field));
Declare(SymDef, sym_builtin  , sym_def(NULL,     -4, NULL, p_term_field));
Declare(SymDef, sym_block    , sym_def(NULL,     -6, NULL, NULL));

Declare(SymDef, sym_true     , sym_def("true", -100, NULL, p_sym_name));
Declare(SymDef, sym_false    , sym_def("false",-101, NULL, p_sym_name));

Declare(SymDef, sym_cons     , sym_def("cons", 1000, NULL, p_cons));
Declare(SymDef, sym_and      , sym_def("and",   100, NULL, p_sym_name));
Declare(SymDef, sym_or       , sym_def("or",    100, NULL, p_sym_name));
Declare(SymDef, sym_not      , sym_def("not",    90, NULL, p_sym_name));
Declare(SymDef, sym_eq       , sym_def("==",     80, NULL, p_sym_name));
Declare(SymDef, sym_gt       , sym_def(">",      80, NULL, p_sym_name));
Declare(SymDef, sym_ge       , sym_def(">=",     80, NULL, p_sym_name));
Declare(SymDef, sym_lt       , sym_def("<",      80, NULL, p_sym_name));
Declare(SymDef, sym_le       , sym_def("<=",     80, NULL, p_sym_name));
Declare(SymDef, sym_ne       , sym_def("!=",     80, NULL, p_sym_name));
Declare(SymDef, sym_setq     , sym_def("=",      80, NULL, p_sym_name));
Declare(SymDef, sym_plus     , sym_def("+",     200, NULL, p_sym_name));
Declare(SymDef, sym_minus    , sym_def("-",     200, NULL, p_sym_name));
Declare(SymDef, sym_times    , sym_def("*",     300, NULL, p_sym_name));
Declare(SymDef, sym_div      , sym_def("/",     300, NULL, p_sym_name));
Declare(SymDef, sym_mod      , sym_def("%",     300, NULL, p_sym_name));
Declare(SymDef, sym_hash     , sym_def("#",     100, NULL, p_sym_name));

Declare(SymDef*, sym_char    , (SymDef*)calloc(256, sizeof(SymDef)));

/*---------------------------------------------------------------------------*/
#undef Declare
