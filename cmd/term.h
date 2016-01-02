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
  short int op;					   /*                        */
  struct S_TERM * term;	   			   /*                        */
  void (*print)();				   /*                        */
} SSymDef, *SymDef;				   /*------------------------*/

#define SymDefNull ((SymDef)0)

#define SymName(T)   ((T)->name)
#define SymOp(T)     ((T)->op)
#define SymTerm(T)   ((T)->term)
#define SymPrint(T)  ((T)->print)

#define BinarySym(S) ((SymOp(S) & 1) == 0)
#define UnarySym(S) ((SymOp(S) & 1) != 0)

#define SymIsNumber(S) ((S) == sym_number) 
#define SymIsOperator(S) (SymOp(S) > 0) 
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
#define TermIsEOF(T)	(TSym(T) == SymDefNull)

#define Cons(CAR, CDR) new_term(sym_cons, CAR, CDR)

#define BlockTerm(S) new_t_string(sym_block, symbol(S))
#define FieldTerm(S) new_t_string(sym_field, symbol(S))

/*-----------------------------------------------------------------------------
** Typedef:	BJunk
** Purpose:	
**		
**		
**___________________________________________________			     */
typedef struct S_BJUNK				   /*                        */
{ String key;					   /*                        */
  Term value;					   /*                        */
  Term (*get)();				   /*                        */
  void (*set)();				   /*                        */
  struct S_BJUNK * next;			   /*                        */
} SBJunk, *BJunk;				   /*------------------------*/

#define JKey(BJ)	((BJ)->key)
#define JValue(BJ)	((BJ)->value)
#define JGet(BJ)	((BJ)->get)
#define JSet(BJ)	((BJ)->set)
#define NextJunk(BJ)	((BJ)->next)

/*-----------------------------------------------------------------------------
** Typedef:	Binding
** Purpose:	
**		
**		
**___________________________________________________			     */
typedef struct S_BINDING			   /*                        */
{ int junk_size;				   /*                        */
  BJunk *junks;					   /*                        */
  struct S_BINDING *next;			   /*                        */
} SBinding, *Binding;				   /*------------------------*/

#define BindingNULL ((Binding)NULL)

#define BSize(B)	((B)->junk_size)
#define BJunks(B)	((B)->junks)
#define NextBinding(B)	((B)->next)

/*---------------------------------------------------------------------------*/

extern Term term_eof;
extern Term term_true;
extern Term term_false;
extern Term term_mod;
extern Term term_and;
extern Term term_or;
extern Term term_not;
extern Term term_like;
extern Term term_ilike;

extern Term new_term();
extern Term new_term_num();
extern Term new_t_string _ARG((SymDef symdef, unsigned char* s));
extern void free_term();
extern void print_term();

extern int parse_term _ARG((char* file, int(*action)(Term t)));

/*---------------------------------------------------------------------------*/
#endif
