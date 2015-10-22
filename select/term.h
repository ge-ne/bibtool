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

#define TermNULL (Term)0

#define TermOp(T)     ((T)->op)
#define TermArg1(T)   ((T)->arg1)
#define TermTerm(T)   ((T)->arg1.term)
#define TermString(T) ((T)->arg1.str)
#define TermNumber(T) ((T)->arg1.num)
#define TermArg2(T)   ((T)->arg2)


extern Term new_term();
extern Term new_term_num();
extern Term new_term_string();
extern void free_term();
extern void dump_term();

#define T_EOF 0

#define T_FIELD    1000
#define T_NUMBER   1001
#define T_STRING   1002
#define T_BLOCK    1003

#define T_PAIR     1010

#define T_EQ       1020
#define T_NE       1021
#define T_LT       1022
#define T_LE       1023
#define T_GT       1024
#define T_GE       1025
#define T_LIKE     1026
#define T_ILIKE    1027

#define T_UMINUS   1030
#define T_PLUS     1031
#define T_MINUS    1032
#define T_TIMES    1033
#define T_DIVIDE   1034

#define T_NOT      1035
#define T_AND      1036
#define T_OR       1037

#define T_FCT_LOWERCASE	 2001
#define T_FCT_UPPERCASE	 2002
#define T_FCT_SUBSTRING	 2003
#define T_FCT_TRIM	 2004

/*---------------------------------------------------------------------------*/
