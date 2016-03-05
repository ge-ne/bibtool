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
#include <bibtool/database.h>
#include <bibtool/record.h>

/*---------------------------------------------------------------------------*/

#define L_TRUE		0x100
#define L_FALSE		0x101

#define L_VAR		0x210
#define L_FIELD		0x211
#define L_STRING	0x212
#define L_FUNCALL	0x213
#define L_FUNCALL2	0x214
#define L_DEFUN		0x215
#define L_EACH		0x216
#define L_METHOD	0x217

#define L_NUMBER	0x220

#define L_DB		0x230
#define L_RECORD	0x240

#define L_CONS		0x200
#define L_CLASS		0x201
#define L_GROUP		0x202

#define L_FUNCTION	0x205
#define L_IF		0x206
#define L_ELSE		0x207
#define L_WHILE		0x208
#define L_WITH		0x209

#define L_QUOTE		0x401
#define L_UMINUS	0x403
#define L_RETURN	0x405
#define L_MINUS		0x412
#define L_PLUS		0x414
#define L_TIMES		0x416
#define L_DIV		0x418
#define L_MOD		0x420
#define L_SET		0x422
#define L_LIKE		0x424
#define L_ILIKE		0x426
#define L_EQ		0x428
#define L_NE		0x430
#define L_GT		0x432
#define L_GE		0x434
#define L_LT		0x436
#define L_LE		0x438
#define L_AND		0x440
#define L_OR		0x442
#define L_NOT		0x451

#define L_IS_OPERATOR(C) ((C) >= 0x400)
#define L_IS_BINARY(C)   (((C) & 0x401) == 0x400)

/*---------------------------------------------------------------------------*/

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
    struct S_BINDING *binding;			   /*                        */
    DB db;					   /*                        */
    Record record;				   /*                        */
  } a;						   /*                        */
  struct S_TERM * cdr;				   /*                        */
  long ref_count;				   /*                        */
} STerm, *Term;					   /*------------------------*/

#define NIL ((Term)0)

#define TType(T)		((T)->type)
#define Car(T)			((T)->a.car)
#define Cdr(T)			((T)->cdr)
#define TString(T)		((T)->a.string)
#define TNumber(T)		((T)->a.number)
#define TBinding(T)		((T)->a.binding)
#define TDB(T)			((T)->a.db)
#define TRecord(T)		((T)->a.record)
#define TRefCount(T)		((T)->ref_count)

#define LinkTerm(T)		if (T) TRefCount(T)++
#define UnlinkTerm(T)		if ((T) && --TRefCount(T) <= 0) free_term(T)

#define Caar(T)			Car(Car(T))
#define Cdar(T)			Cdr(Car(T))
#define Cadr(T)			Car(Cdr(T))
#define Cddr(T)			Cdr(Cdr(T))

#define IsNumber(T)		(TType(T) == L_NUMBER)
#define IsString(T)		(TType(T) == L_STRING)
#define IsList(T)		(TType(T) == L_CONS)
#define IsField(T)		(TType(T) == L_FIELD)
#define IsVar(T)		(TType(T) == L_VAR)
#define IsRecord(T)		(TType(T) == L_RECORD)
#define IsTrue(T)		(TType(T) == L_TRUE)
#define IsFalse(T)		(TType(T) == L_FALSE)

#define Cons(CAR, CDR)		new_term(L_CONS, CAR, CDR)
#define Cons1(CAR)		Cons(CAR, NIL)

#define StringTerm(S)		new_t_string(L_STRING, symbol((String)S))
#define FieldTerm(S)		new_t_string(L_FIELD, symbol((String)S))
#define VarTerm(S)		new_t_string(L_VAR, symbol((String)S))
#define NumberTerm(N)		new_term_num(N)
#define NewTerm(N)		new_term(N, NIL, NIL)
#define DBTerm(DB)		new_t_db(DB)
#define RecordTerm(REC)		new_t_rec(REC)

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Typedef:	SymDef
** Purpose:	
**		
**___________________________________________________			     */
typedef struct S_SYMDEF {			   /*                        */
  String name;				   	   /*                        */
  short int op;				   	   /*                        */
  short int flags;				   /*                        */
  short int hash;				   /*                        */
  struct S_SYMDEF * next;			   /*                        */
  Term term;	   			   	   /*                        */
  Term value;			   		   /*                        */
  Term (*get)();			   	   /*                        */
  Term (*set)();			   	   /*                        */
} SSymDef, *SymDef;				   /*------------------------*/

#define SymDefNULL	((SymDef)0)

#define SymName(SYM)	((SYM)->name)
#define SymOp(SYM)	((SYM)->op)
#define SymFlags(SYM)	((SYM)->flags)
#define SymHash(SYM)	((SYM)->hash)
#define SymTerm(SYM)	((SYM)->term)
#define SymKey(SYM)	((SYM)->key)
#define SymValue(SYM)	((SYM)->value)
#define SymGet(SYM)	((SYM)->get)
#define SymSet(SYM)	((SYM)->set)
#define NextJunk(SYM)	((SYM)->next)

#define SYM_NONE	0x00
#define SYM_BUILTIN	0x01
#define SYM_LOCKED	0x02

/*---------------------------------------------------------------------------*/

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

extern void free_sym _ARG((SymDef s));

extern Term new_class(Term name);		   /*                        */
extern Term new_term _ARG((short int type, Term car, Term cdr ));
extern Term new_term_num _ARG((long value));
extern Term new_t_string _ARG((short int type, unsigned char* s));
extern Term new_t_db _ARG((DB db));
extern Term new_t_rec _ARG((Record rec));
extern void free_term _ARG((Term term));
extern void print _ARG((FILE* file, Term term));
extern void prn_term _ARG((FILE* file, Term term, int in, int q, int o));
extern String token_type _ARG((int c));
extern String term_type _ARG((Term t));

extern int list_length _ARG((Term t));
extern int parse_term _ARG((char* file, int(*action)(Term t)));
extern void dump_terms _ARG((FILE*file));
extern unsigned int hash _ARG((String s));

extern SymDef symdef _ARG((String name,
			   short int op,
			   short int flags,
			   Term(*get)(),
			   Term(*set)()));

/*---------------------------------------------------------------------------*/
#endif
