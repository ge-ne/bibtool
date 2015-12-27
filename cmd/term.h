/*** term.h ********************************************************************
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

#include "symdef.h"

/*---------------------------------------------------------------------------*/

typedef struct S_TERM {
  SymDef sym;
  union {
    struct S_TERM * car;
    unsigned char * string;
    long number;
  } a;
  struct S_TERM * cdr;
} STerm, *Term;

#define NIL ((Term)0)

#define TSym(T)    ((T)->sym)
#define Car(T)     ((T)->a.car)
#define Cdr(T)     ((T)->cdr)
#define TString(T) ((T)->a.string)
#define TNumber(T) ((T)->a.number)

#define TermIsNumber(T)	(TSym(T) == sym_number)
#define TermIsEOF(T)	(TSym(T) == SymDefNull)

#define Cons(CAR, CDR) new_term(sym_cons, CAR, CDR)


/*---------------------------------------------------------------------------*/

extern Term term_eof;
extern Term term_true;
extern Term term_false;
extern Term term_mod;

extern Term new_term();
extern Term new_term_num();
extern Term new_t_string _ARG((SymDef symdef, unsigned char* s));
extern void free_term();
extern void print_term();

extern int parse_term _ARG((char* file, int(*action)(Term t)));

/*---------------------------------------------------------------------------*/
