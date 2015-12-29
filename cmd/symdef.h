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
  int op;					   /*                        */
  struct S_TERM * term;	   			   /*                        */
  struct S_TERM * (*parse)_ARG((FILE*));	   /*                        */
  void (*print)_ARG((FILE*, struct S_TERM *));	   /*                        */
} SSymDef, *SymDef;				   /*------------------------*/

#define SymDefNull ((SymDef)0)

#define SymName(T)   ((T)->name)
#define SymOp(T)     ((T)->op)
#define SymTerm(T)   ((T)->term)
#define SymParse(T)  ((T)->parse)
#define SymPrint(T)  ((T)->print)

#define BinarySym(S) ((SymOp(S) & 1) == 0)
#define UnarySym(S) ((SymOp(S) & 1) != 0)

#define SymIsNumber(S) ((S) == sym_number) 
#define SymIs(S,C) ((S) == sym_char[C]) 

#define SymChar(C) sym_char[C]
#define SymCharName(C) SymName(sym_char[C])
#define SymCharTerm(C) SymTerm(sym_char[C])

#define Declare(T,N,V) extern T N

/*---------------------------------------------------------------------------*/

extern void init_symdef();

#endif
/*---------------------------------------------------------------------------*/

Declare(SymDef, sym_number , sym_def("number", -1, NIL, NULL, p_term_num));
Declare(SymDef, sym_string , sym_def("string", -2, NIL, NULL, p_term_str));
Declare(SymDef, sym_block  , sym_def("block",  -3, NIL, NULL, NULL));
Declare(SymDef, sym_field  , sym_def("field",  -4, NIL, NULL, p_term_field));
Declare(SymDef, sym_builtin, sym_def("builtin",-5, NIL, NULL, p_term_field));
Declare(SymDef, sym_group  , sym_def("group",  -6, NIL, NULL, NULL));

Declare(SymDef, sym_true   , sym_def("true", -100, NIL, NULL, p_sym_name));
Declare(SymDef, sym_false  , sym_def("false",-101, NIL, NULL, p_sym_name));

Declare(SymDef, sym_cons   , sym_def(".",      90, NIL, NULL, p_cons));
Declare(SymDef, sym_and    , sym_def("and",    10, NIL, NULL, p_sym_name));
Declare(SymDef, sym_or     , sym_def("or",     10, NIL, NULL, p_sym_name));
Declare(SymDef, sym_not    , sym_def("not",    21, NIL, NULL, p_sym_name));
Declare(SymDef, sym_eq     , sym_def("==",     30, NIL, NULL, p_sym_name));
Declare(SymDef, sym_ge     , sym_def(">=",     30, NIL, NULL, p_sym_name));
Declare(SymDef, sym_le     , sym_def("<=",     30, NIL, NULL, p_sym_name));
Declare(SymDef, sym_ne     , sym_def("!=",     30, NIL, NULL, p_sym_name));

Declare(SymDef, sym_mod    , sym_def("mod",    60, NIL, NULL, p_sym_name));

Declare(SymDef*, sym_char  , (SymDef*)calloc(256, sizeof(SymDef)));

/*---------------------------------------------------------------------------*/
#undef Declare
