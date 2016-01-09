/*** lcore.c ******************************************************************
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bibtool/error.h>
#include <ctype.h>
#include "term.h"
#include "binding.h"
#include "lcore.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


#define Declare(T,N,V) T N
#include "lcore.h"

/*-----------------------------------------------------------------------------
** Function:	print_quoted()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	file	
**	 s	
** Returns:	nothing
**___________________________________________________			     */
void print_quoted(file, s)		   	   /*                        */
  FILE * file;					   /*                        */
  String s;					   /*                        */
{						   /*                        */
  for (; *s; s++)				   /*                        */
  { switch (*s)					   /*                        */
    { case '\n':				   /*                        */
	fputs("\\n", file);			   /*                        */
	break;					   /*                        */
      case '\r':				   /*                        */
	fputs("\\r", file);			   /*                        */
	break;					   /*                        */
      case '\b':				   /*                        */
	fputs("\\b", file);			   /*                        */
	break;					   /*                        */
      case '\f':				   /*                        */
	fputs("\\f", file);			   /*                        */
	break;					   /*                        */
      case '"':					   /*                        */
	fputs("\\\"", file);			   /*                        */
	break;					   /*                        */
      case '\'':				   /*                        */
	fputs("\\'", file);			   /*                        */
	break;					   /*                        */
      case '\\':				   /*                        */
	fputs("\\\\", file);			   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	fputc((char)*s, file);			   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_sym_name()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
void p_sym_name(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (t == NIL)					   /*                        */
  { fputs("??",file);				   /*                        */
    return;					   /*                        */
  }						   /*                        */
  print_quoted(file, SymName(TSym(t)));		   /*                        */
  if (Car(t)) { print_term(Car(t)); }	   	   /*                        */
  if (Cdr(t)) { print_term(Cdr(t)); }		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_term_num()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
void p_term_num(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  fprintf(file, "%ld", TNumber(t));		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_term_str()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
void p_term_str(file, t)			   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  fputc('"', file);				   /*                        */
  print_quoted(file, TString(t));		   /*                        */
  fputc('"', file);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_term_str()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
static void p_term_block(file, t)		   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  fputc('{', file);				   /*                        */
  fputs((char*)TString(t), file);		   /*                        */
  fputc('}', file);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_term_field()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
void p_term_field(file, t)		   	   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{ int q	 = 0;					   /*                        */
  String s = TString(t);			   /*                        */
  if (*s >= '0' && *s <= '9') {			   /*                        */
    q = 1;					   /*                        */
  } else {					   /*                        */
    for (; *s; s++)				   /*                        */
    { if (!(   (*s >='a' && *s <='z') 		   /*                        */
	    || (*s >='A' && *s <='Z')		   /*                        */
	    || (*s >='0' && *s <='9')		   /*                        */
	    || *s == '@'			   /*                        */
	    || *s == '$'			   /*                        */
	    || *s == '_'			   /*                        */
	    || *s == '.'))			   /*                        */
      { q = 1;					   /*                        */
	break;					   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
  if (q) fputc('`', file);			   /*                        */
  print_quoted(file, TString(t));		   /*                        */
  if (q) fputc('`', file);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_builtin()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	nothing
**___________________________________________________			     */
void p_rsc(file, t)		   	   	   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (Cdr(t))					   /*                        */
  { fputc('(', file);			   	   /*                        */
    fputs((char*)TString(t), file);		   /*                        */
    fputc(' ', file);			   	   /*                        */
    print_term(file, Cdr(t));	   		   /*                        */
    fputc(')', file);			   	   /*                        */
  } else {					   /*                        */
    fputs((char*)TString(t), file);		   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	p_cons()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	file	
**	 t	
** Returns:	
**___________________________________________________			     */
void p_cons(file, t)			   	   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
{ fputc('(', file);				   /*                        */
  print_term(file, Car(t));			   /*                        */
  while (Cdr(t))				   /*                        */
  { t = Cdr(t);				   	   /*                        */
    if (t && TSym(t) == sym_cons)		   /*                        */
    { fputc(' ', file);			   	   /*                        */
      print_term(file, Car(t));		   	   /*                        */
    } else					   /*                        */
    { fputs(" . ", file);			   /*                        */
      print_term(file, Cdr(t));		   	   /*                        */
      break;					   /*                        */
    }						   /*                        */
  }						   /*                        */
  fputc(')', file);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_self()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_self(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ return term;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_fct()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the
** Returns:	
**___________________________________________________			     */
Term g_fct(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ SymDef sym;					   /*                        */
  Term f = Car(term);				   /*                        */
  if (f == NIL) ErrorNF("No function",0);	   /*                        */
  						   /*                        */
  if (TString(f))				   /*                        */
  { sym = get_bind(binding, TString(f));	   /*                        */
    if (sym && SymGet(sym))			   /*                        */
      return (*SymGet(sym))(binding, term);	   /*                        */
  }						   /*                        */
						   /*                        */
  sym = TSym(f);   				   /*                        */
  if (sym && SymGet(sym))			   /*                        */
    return (*SymGet(sym))(binding, term);	   /*                        */
 						   /*                        */
  ErrorNF("Undefined function ",
	  TString(f) ? TString(f) : SymName(sym)); /*                        */
  return NIL;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_eq()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
** Returns:	
**___________________________________________________			     */
Term g_eq(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ int val;					   /*                        */
  Term a, b;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { ErrorNF("Wrong number of arguments for ==",0); }/*                       */
  a = eval_term(binding, Car(term));
  b = eval_term(binding, Cadr(term));

  if (a	== NIL) { val = (b == NIL ? 1 : 0); }
  else if (TermIsNumber(a))
  { val = (b && TermIsNumber(b) && TNumber(a) == TNumber(b) ? 1 : 0);
  }
  else if (TermIsString(a))
  { val = (b
	   && TermIsString(b)
	   && strcmp((char*)TString(a), (char*)TString(b)) == 0 ? 1 : 0);
  }
  else if (TSym(a) == sym_true)
  { val = (TSym(b) == TSym(a)); }
  else if (TSym(a) == sym_false)
  { val = (TSym(b) == TSym(a)); }
  else val = 0;					   /*                        */
 						   /*                        */
  return SymTerm(val ? sym_true : sym_false );	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	hash()
** Type:	int
** Purpose:	
**		
** Arguments:
**	s	
**	 size	
** Returns:	
**___________________________________________________			     */
unsigned int hash(s)				   /*                        */
  register String s;				   /*                        */
{ register unsigned int hash = 0;		   /*                        */
  unsigned int i 	     = 0;		   /*                        */
 						   /*                        */
  while (*s)					   /*                        */
  { hash += (*s++) >> ((i++)&7); }		   /*                        */
  						   /*                        */
  return hash;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	init_symdef()
** Type:	void
** Purpose:	
**		
** Arguments:
**		
** Returns:	nothing
**___________________________________________________			     */
void init_lreader()				   /*                        */
{ int i;					   /*                        */
  char * s;					   /*                        */
 						   /*                        */
#define Declare(T,N,V) N = V
#include "lcore.h"
 						   /*                        */
#define InitSymChar(S,OP)				       \
  sym_char[i] = symdef(S, NIL, p_sym_name);		       \
  SymTerm(sym_char[i]) = new_term(sym_char[i], NIL, NIL)
 						   /*                        */
  for (i = 1; i < 256; i++) {			   /*                        */
 						   /*                        */
    switch (i)			   		   /*                        */
    { case ';':	InitSymChar( ";",    ';'); break;  /*                        */
      case '=':	InitSymChar( "=",  L_SET); break;  /*                        */
      case '<':	InitSymChar( "<",   L_LT); break;  /*                        */
      case '>':	InitSymChar( ">",   L_GT); break;  /*                        */
      case '#':	InitSymChar( "#",    '#'); break;  /*                        */
      case '+':	InitSymChar( "+", L_PLUS); break;  /*                        */
      case '-':	InitSymChar( "-",L_MINUS); break;  /*                        */
      case '*':	InitSymChar( "*",L_TIMES); break;  /*                        */
      case '/':	InitSymChar( "/",  L_DIV); break;  /*                        */
      case '%':	InitSymChar("mod", L_MOD); break;  /*                        */
      case '\'':InitSymChar("quote",L_QUOTE); break;/*                       */
      case '"':					   /*                        */
      case '_':					   /*                        */
      case '@':					   /*                        */
      case '$':					   /*                        */
      case '.':					   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	if (isalnum(i) || isspace(i)) break;	   /*                        */
 						   /*                        */
	s     = malloc(2 * sizeof(char));	   /*                        */
	if (s == NULL) OUT_OF_MEMORY("symdef");	   /*                        */
	*s     = (char)i;			   /*                        */
	*(s+1) = '\0';				   /*                        */
	sym_char[i] = symdef(s,		   	   /*                        */
			     i,		   	   /*                        */
			     NIL,		   /*                        */
			     p_sym_name, NULL);	   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  term_eof = SymdefTerm(NULL);	   		   /*                        */
 						   /*                        */
  MakeSymTerm(sym_quote);	   		   /*                        */
  MakeSymTerm(sym_mod);	   			   /*                        */
  MakeSymTerm(sym_and);	   			   /*                        */
  MakeSymTerm(sym_or);	   			   /*                        */
  MakeSymTerm(sym_not);	   			   /*                        */
  MakeSymTerm(sym_like);	   		   /*                        */
  MakeSymTerm(sym_ilike);	   		   /*                        */
  MakeSymTerm(sym_true);	   		   /*                        */
  MakeSymTerm(sym_false);	   		   /*                        */
 						   /*                        */
  SymGet(sym_true)  = g_self;			   /*                        */
  SymGet(sym_false) = g_self;			   /*                        */
  SymGet(sym_cons)  = g_fct;			   /*                        */
  SymGet(sym_eq)    = g_eq;			   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
