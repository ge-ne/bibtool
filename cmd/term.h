/*** term.h ********************************************************************
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

#ifndef TERM_H
#define TERM_H

#include <bibtool/type.h>

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Typedef:	SymDef
** Purpose:	
**		
**___________________________________________________			     */
typedef struct S_SYMDEF {			   /*                        */
  String name;				   	   /*                        */
  short int op;				   	   /*                        */
  short int hash;				   /*                        */
  struct S_SYMDEF * next;			   /*                        */
  struct S_TERM * term;	   			   /*                        */
  struct S_TERM * value;			   /*                        */
  struct S_TERM * (*get)();			   /*                        */
  void (*set)();				   /*                        */
  void (*print)();				   /*                        */
} SSymDef, *SymDef;				   /*------------------------*/

#define SymDefNULL ((SymDef)0)

#define SymName(SYM)	((SYM)->name)
#define SymOp(SYM)	((SYM)->op)
#define SymHash(SYM)	((SYM)->hash)
#define SymTerm(SYM)	((SYM)->term)
#define SymKey(SYM)	((SYM)->key)
#define SymValue(SYM)	((SYM)->value)
#define SymGet(SYM)	((SYM)->get)
#define SymSet(SYM)	((SYM)->set)
#define SymPrint(SYM)	((SYM)->print)
#define NextJunk(SYM)	((SYM)->next)

#define SymIsNumber(S) ((S) == sym_number) 
#define SymIs(S,C) ((S) == sym_char[C]) 

#define SymChar(C) sym_char[C]
#define SymCharName(C) SymName(sym_char[C])
#define SymCharTerm(C) SymTerm(sym_char[C])

/*-----------------------------------------------------------------------------
** Typedef:	Term
** Purpose:	
**		
**		
**___________________________________________________			     */
typedef struct S_TERM {				   /*                        */
  SymDef sym;					   /*                        */
  union {					   /*                        */
    struct S_TERM * car;			   /*                        */
    unsigned char * string;			   /*                        */
    long number;				   /*                        */
  } a;						   /*                        */
  struct S_TERM * cdr;				   /*                        */
} STerm, *Term;					   /*------------------------*/

#define NIL ((Term)0)

#define TSym(T)    ((T)->sym)
#define Car(T)     ((T)->a.car)
#define Cdr(T)     ((T)->cdr)
#define TString(T) ((T)->a.string)
#define TNumber(T) ((T)->a.number)

#define TermName(T)	SymName(TSym(T))
#define TermOp(T)	SymOp(TSym(T))
#define TermIsNumber(T)	(TSym(T) == sym_number)
#define TermIsString(T)	(TSym(T) == sym_string)
#define TermIsEOF(T)	(TSym(T) == SymDefNULL)

#define Cons(CAR, CDR) new_term(sym_cons, CAR, CDR)

#define SymdefTerm(S) new_term(S, NIL, NIL)
#define BlockTerm(S)  new_t_string(sym_block, symbol(S))
#define FieldTerm(S)  new_t_string(sym_field, symbol(S))

/*-----------------------------------------------------------------------------
** Typedef:	Binding
** Purpose:	
**		
**		
**___________________________________________________			     */
typedef struct S_BINDING			   /*                        */
{ unsigned int junk_size;			   /*                        */
  SymDef *junks;				   /*                        */
  struct S_BINDING *next;			   /*                        */
} SBinding, *Binding;				   /*------------------------*/

#define BindingNULL ((Binding)NULL)

#define BSize(B)	((B)->junk_size)
#define BJunks(B)	((B)->junks)
#define NextBinding(B)	((B)->next)

/*---------------------------------------------------------------------------*/

extern Term term_eof;

extern Term new_term();
extern Term new_term_num();
extern Term new_t_string _ARG((SymDef symdef, unsigned char* s));
extern void free_term();
extern void print_term();

extern int parse_term _ARG((char* file, int(*action)(Term t)));

extern SymDef symdef();

/*---------------------------------------------------------------------------*/
#endif
