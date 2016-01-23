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
#define NextJunk(SYM)	((SYM)->next)

#define SymIsNumber(S)	((S) == sym_number) 
#define SymIs(S,C)	((S) == sym_char[C]) 

#define SymChar(C)	sym_char[C]
#define SymCharName(C)  SymName(sym_char[C])
#define SymCharTerm(C)  SymTerm(sym_char[C])

/*-----------------------------------------------------------------------------
** Typedef:	Term
** Purpose:	
**		
**		
**___________________________________________________			     */
typedef struct S_TERM {				   /*                        */
  short int type;				   /*                        */
  union {					   /*                        */
    struct S_TERM * car;			   /*                        */
    unsigned char * string;			   /*                        */
    long number;				   /*                        */
  } a;						   /*                        */
  struct S_TERM * cdr;				   /*                        */
  long ref_count;
} STerm, *Term;					   /*------------------------*/

#define NIL ((Term)0)

#define TermOp(T)	((T)->type)
#define Car(T)		((T)->a.car)
#define Cdr(T)		((T)->cdr)
#define TString(T)	((T)->a.string)
#define TNumber(T)	((T)->a.number)
#define TermRefCount(T)	((T)->ref_count)

#define LinkTerm(T)	TermRefCount(T)++
#define UnlinkTerm(T)	TermRefCount(T)--

#define Cadr(T)		Car(Cdr(T))
#define Cddr(T)		Cdr(Cdr(T))

#define TermIsNumber(T)		(TermOp(T) == L_NUMBER)
#define TermIsString(T)		(TermOp(T) == L_STRING)
#define TermIsList(T)		(TermOp(T) == L_CONS)
#define TermIsFunction(T)	(TermOp(T) == L_FUNCTION)
#define TermIsEOF(T)		(TermOp(T) == L_EOF)
#define TermIsTrue(T)		(TermOp(T) == L_TRUE)
#define TermIsFalse(T)		(TermOp(T) == L_FALSE)

#define Cons(CAR, CDR)		new_term(L_CONS, CAR, CDR)
#define Cons1(CAR)		Cons(CAR, NIL)

#define MakeSymTerm(S)	SymTerm(S) = SymdefTerm(S)
#define SymdefTerm(S)	new_term(SymOp(S), NIL, NIL)
#define StringTerm(S)	new_t_string(L_STRING, symbol(S))
#define BlockTerm(S)	new_t_string(L_BLOCK, symbol(S))
#define FieldTerm(S)	new_t_string(L_FIELD, symbol(S))
#define NumberTerm(N)	new_term_num(N)
#define NewTerm(N)	new_term(N,NIL,NIL)

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

extern Term new_term _ARG((short int type, Term car, Term cdr ));
extern Term new_term_num _ARG((long value));
extern Term new_t_string _ARG((short int type, unsigned char* s));
extern void free_term _ARG((Term term));
extern void print_term _ARG((FILE* file, Term term));

extern int list_length _ARG((Term t));
extern int parse_term _ARG((char* file, int(*action)(Term t)));

extern SymDef symdef _ARG((String name, int op, Term(*get)()));

/*---------------------------------------------------------------------------*/
#endif
