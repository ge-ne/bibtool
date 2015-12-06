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

typedef struct S_TERM {
  int op;
  union {
    struct S_TERM * term;
    unsigned char * str;
    long num;
  } arg1;
  struct S_TERM * arg2;
} STerm, *Term;

#define NIL ((Term)0)

#define TermOp(T)     ((T)->op)
#define TermTerm(T)   ((T)->arg1.term)
#define TermString(T) ((T)->arg1.str)
#define TermNumber(T) ((T)->arg1.num)
#define TermTerm2(T)  ((T)->arg2)

extern Term new_term();
extern Term new_term_num();
extern Term new_term_string();
extern void free_term();
extern void dump_term();


/*---------------------------------------------------------------------------*/
