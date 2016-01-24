/*** binding.c *****************************************************************
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

#include <string.h>
#include <stdlib.h>
#include <bibtool/symbols.h>
#include <bibtool/error.h>
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
Binding binding _ARG((unsigned int size));
Term eval_term _ARG((Binding binding, Term term));
Term eval_self _ARG((Binding binding, Term term));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	binding()
** Type:	Binding
** Purpose:	
**		
** Arguments:
**	term	
** Returns:	
**___________________________________________________			     */
Binding binding(size)			   	   /*                        */
  unsigned int size;				   /*                        */
{						   /*                        */
  Binding b = (Binding) malloc(sizeof(SBinding));  /*                        */
  if (b == BindingNULL) OUT_OF_MEMORY("binding");  /*                        */
 						   /*                        */
  BJunks(b) = (SymDef*) calloc(size, sizeof(SymDef));/*                      */
  if (BJunks(b) == NULL) OUT_OF_MEMORY("binding"); /*                        */
 						   /*                        */
  BSize(b) = size;				   /*                        */
  NextBinding(b) = BindingNULL;		   	   /*                        */
  return b;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bind()
** Type:	void
** Purpose:	
**		
** Arguments:
**	b	the binding
**	sym	the symbol definition
** Returns:	nothing
**___________________________________________________			     */
void bind(b, sym)		   		   /*                        */
  Binding b;				   	   /*                        */
  SymDef sym;					   /*                        */
{ String key 	 = SymName(sym);		   /*                        */
  unsigned int h = hash(key) % BSize(b);	   /*                        */
  SymDef junk;					   /*                        */
   						   /*                        */
  for (junk = BJunks(b)[h]; junk; junk = NextJunk(junk))/*                   */
  { if (strcmp((char*)SymName(junk), (char*)key) == 0)/*                     */
    {						   /*                        */
      SymTerm(junk)  = SymTerm(sym);		   /*                        */
      SymValue(junk) = SymValue(sym);		   /*                        */
      SymGet(junk)   = SymGet(sym);		   /*                        */
      return;					   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  NextJunk(sym) = BJunks(b)[h];		   	   /*                        */
  BJunks(b)[h]  = sym;			   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	setq()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	b	the binding
**	key	the key
**	term	the term
** Returns:	
**___________________________________________________			     */
Term setq(b, key, term)		   		   /*                        */
  Binding b;				   	   /*                        */
  String key;					   /*                        */
  Term term;					   /*                        */
{ unsigned int h = hash(key) % BSize(b);	   /*                        */
  SymDef junk;					   /*                        */
   						   /*                        */
  for (junk = BJunks(b)[h]; junk; junk = NextJunk(junk))/*                   */
  { if (SymName(junk) == key)			   /*                        */
    { SymValue(junk) = term;		   	   /*                        */
      return term;				   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  junk           = symdef(key, L_FIELD, g_field);  /*                        */
  SymValue(junk) = term;		   	   /*                        */
  NextJunk(junk) = BJunks(b)[h];		   /*                        */
  BJunks(b)[h]   = junk;			   /*                        */
  return term;					   /*                        */
}						   /*------------------------*/

#undef DEBUG_BIND

/*-----------------------------------------------------------------------------
** Function:	get_bind()
** Type:	SymDef
** Purpose:	
**		
** Arguments:
**	b	
**	key	
** Returns:	
**___________________________________________________			     */
SymDef get_bind(b, key)			   	   /*                        */
  Binding b;				   	   /*                        */
  String key;					   /*                        */
{ SymDef s;					   /*                        */
  unsigned int h = hash(key) % BSize(b);	   /*                        */
  						   /*                        */
#ifdef DEBUG_BIND
  puts("BINDING");				   /*                        */
  dump_binding(b, stdout);			   /*                        */
  printf("--- lookup %s at %d\n", (char*)key, h);  /*                        */
#endif
  while (b)					   /*                        */
  {						   /*                        */
    for (s = BJunks(b)[h];		   	   /*                        */
	 s;					   /*                        */
	 s = NextJunk(s))			   /*                        */
    {						   /*                        */
#ifdef DEBUG_BIND
      printf("--- cmp %s\n",(char*)SymName(s));	   /*                        */
#endif
      if (strcmp((char*)SymName(s),		   /*                        */
		 (char*)key) == 0) {		   /*                        */
#ifdef DEBUG_BIND
	printf("--- found 0x%x\n",s ? SymOp(s):0); /*                        */
#endif
	return s; 	   			   /*                        */
      }						   /*                        */
    }						   /*                        */
    b = NextBinding(b);		   		   /*                        */
  }						   /*                        */
  return SymDefNULL; 	   			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_print()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_print(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ 					   	   /*                        */
  for (term = Cdr(term); term ; term = Cdr(term))  /*                        */
  { Term t = Car(term);				   /*                        */
    if (t == NIL) continue;			   /*                        */
    switch(TType(t))			   	   /*                        */
    { case L_STRING:				   /*                        */
      case L_BLOCK:				   /*                        */
	fputs((char*)TString(t), stdout);	   /*                        */
	break;					   /*                        */
      case L_NUMBER:				   /*                        */
	fprintf(stdout, "%ld", TNumber(t));	   /*                        */
	break;					   /*                        */
      case L_FIELD:				   /*                        */
	fputs((char*)TString(t), stdout);	   /*                        */
	break;					   /*                        */
      case L_TRUE:				   /*                        */
	fputs("true", stdout);			   /*                        */
	break;					   /*                        */
      case L_FALSE:				   /*                        */
	fputs("false", stdout);			   /*                        */
	break;					   /*                        */
#ifdef DEBUG
      default:					   /*                        */
	printf("--- 0x%x",TType(t));	   	   /*                        */
#endif
    }						   /*                        */
  }		   				   /*                        */
  return NIL;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_fct()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
** Returns:	
**___________________________________________________			     */
Term g_fct(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ String key;					   /*                        */
  SymDef sym;					   /*                        */
						   /*                        */
  if (term == NIL) return NIL;			   /*                        */
 						   /*                        */
  if (TermIsFunction(term))		   	   /*                        */
  { Term t = Car(term);				   /*                        */
 						   /*                        */
    if (t == NIL || TType(t) != L_FIELD)	   /*                        */
    { ErrorNF("Undefined function ",		   /*                        */
	      (String)"nil"); }  		   /*                        */
 						   /*                        */
    key = TString(t);				   /*                        */
 						   /*                        */
  } else {					   /*                        */
    ErrorNF("Unknown function", 0);		   /*                        */
  }						   /*                        */
  						   /*                        */
  sym = get_bind(binding, key);	   	   	   /*                        */
 						   /*                        */
  if (sym == NULL)	   			   /*                        */
  { ErrorNF("Undefined function ", key); }	   /*                        */
  if (SymGet(sym) == NULL)	   		   /*                        */
  { ErrorNF("Undefined getter for ", key); }	   /*                        */
 						   /*                        */
  return (*SymGet(sym))(binding, term);	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bool_rsc()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 name	
**	 term	
**	 rp	
** Returns:	
**___________________________________________________			     */
static Term bool_rsc(binding, name, term, rp)	   /*                        */
  Binding binding;				   /*                        */
  char * name;				   	   /*                        */
  Term term;					   /*                        */
  int * rp;					   /*                        */
{ switch (list_length(Cdr(term)))		   /*                        */
  { case 0:					   /*                        */
      break;					   /*                        */
    case 1:					   /*                        */
      term = eval_bool(binding, Cadr(term));	   /*                        */
      *rp  = (TermIsTrue(term) ? 1 : 0 );	   /*                        */
      UnlinkTerm(term);				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      ErrorNF("Too many arguments for ", name);	   /*                        */
  }						   /*                        */
  return SymTerm(*rp ? sym_true : sym_false);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	num_rsc()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 name	
**	 term	
**	 rp	
** Returns:	
**___________________________________________________			     */
static Term num_rsc(binding, name, term, rp)	   /*                        */
  Binding binding;				   /*                        */
  char * name;				   	   /*                        */
  Term term;					   /*                        */
  int * rp;					   /*                        */
{ switch (list_length(Cdr(term)))		   /*                        */
  { case 0:					   /*                        */
      break;					   /*                        */
    case 1:					   /*                        */
      term = eval_num(binding, Cadr(term));	   /*                        */
      *rp  = TNumber(term);	   		   /*                        */
      return term;				   /*                        */
    default:					   /*                        */
      ErrorNF("Too many arguments for ", name);	   /*                        */
  }						   /*                        */
  return NumberTerm(*rp);	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	str_rsc()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	
**	name	
**	term	
**	rp	
** Returns:	
**___________________________________________________			     */
static Term str_rsc(binding, name, term, rp)	   /*                        */
  Binding binding;				   /*                        */
  char *name;				   	   /*                        */
  Term term;					   /*                        */
  String *rp;					   /*                        */
{ switch (list_length(Cdr(term)))		   /*                        */
  { case 0:					   /*                        */
      break;					   /*                        */
    case 1:					   /*                        */
      term = eval_str(binding, Cadr(term));	   /*                        */
      *rp  = TString(term);	   		   /*                        */
      return term;				   /*                        */
    default:					   /*                        */
      ErrorNF("Too many arguments for ", name);	   /*                        */
  }						   /*                        */
   return StringTerm(*rp ? *rp : (String)"");	   /*                        */
}						   /*------------------------*/

#define Bind(NAME,OP,GET)
#define BindSym(NAME,SYM)
#define BindBool(NAME,GETTER,RSC)			\
  static Term GETTER (binding, term)			\
    Binding binding;					\
    Term term;						\
  { extern int RSC;					\
    return bool_rsc(binding, NAME, term, &RSC); }
#define BindNum(NAME,GETTER,RSC)			\
  static Term GETTER (binding, term)			\
    Binding binding;					\
    Term term;						\
  { extern int RSC;					\
    return num_rsc(binding, NAME, term, &RSC); }
#define BindBool(NAME,GETTER,RSC)			\
  static Term GETTER (binding, term)			\
    Binding binding;					\
    Term term;						\
  { extern int RSC;					\
    return bool_rsc(binding, NAME, term, &RSC); }
#define BindStr(NAME,GETTER,RSC)			\
  static Term GETTER (binding, term)			\
    Binding binding;					\
    Term term;						\
  { extern char* RSC;					\
    return str_rsc(binding, NAME, term, &RSC); }
#include "builtin.h"

#undef Bind
#undef BindSym
#undef BindBool
#undef BindNum
#undef BindStr

/*-----------------------------------------------------------------------------
** Function:	root_binding()
** Type:	Binding
** Purpose:	Create a new binding and initialize it with the BibTool
**		defaults.
**		
** Arguments:	none
** Returns:	the new binding
**___________________________________________________			     */
Binding root_binding()				   /*                        */
{ Binding b = binding(511);			   /*                        */
 						   /*                        */
#define BindBool(NAME,GET,R) Bind(NAME, L_FIELD, GET)
#define BindNum(NAME,GET,R)  Bind(NAME, L_FIELD, GET)
#define BindStr(NAME,GET,R)  Bind(NAME, L_FIELD, GET)
#define Bind(NAME,OP,GET)    bind(b, symdef(symbol((String)NAME),OP,GET))
#define BindSym(NAME,SYM)    bind(b, SYM)
 						   /*                        */
#include "builtin.h"
  return b;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_binding()
** Type:	void
** Purpose:	
**		
** Arguments:
**	b	
**	 file	
** Returns:	nothing
**___________________________________________________			     */
void dump_binding(b, file)			   /*                        */
  Binding b;					   /*                        */
  FILE* file;					   /*                        */
{ int i;					   /*                        */
  SymDef s;					   /*                        */
 						   /*                        */
  for (; b; b = NextBinding(b))			   /*                        */
  {						   /*                        */
#ifdef DEBUG
    fprintf(file, "--- 0x%lx [%d] ---\n", (unsigned long)b, BSize(b));/*     */
#endif
    for (i = 0; i < BSize(b); i++)		   /*                        */
    { s = BJunks(b)[i];				   /*                        */
      if (s) {					   /*                        */
	fprintf(file, "    #%d\n", i);		   /*                        */
	for (; s; s = NextJunk(s))		   /*                        */
	{ fprintf(file,				   /*                        */
		  "\t%s\n",			   /*                        */
		  SymName(s));			   /*                        */
	}					   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_term()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term to evaluate
** Returns:	the resulting term
**___________________________________________________			     */
Term eval_term(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ SymDef s;					   /*                        */
  String key = NULL;				   /*                        */
 						   /*                        */
  if (term == NIL) return NIL;			   /*                        */
 						   /*                        */
  switch (TType(term))				   /*                        */
  { case L_STRING:				   /*                        */
    case L_GROUP:				   /*                        */
    case L_NUMBER:				   /*                        */
    case L_TRUE:				   /*                        */
    case L_FALSE:				   /*                        */
    case L_CONS:				   /*                        */
      return term;				   /*                        */
    case 0:					   /*                        */
    case EOF:					   /*                        */
      return term_eof;	   			   /*                        */
    case L_FUNCTION:				   /*                        */
      key = TString(term);			   /*                        */
      s	  = get_bind(binding, key);	   	   /*                        */
      if (s == NULL || SymGet(s) == NULL)	   /*                        */
	ErrorNF("Undefined function ", key);	   /*                        */
      return (*SymGet(s))(binding, term);	   /*                        */
    case L_FIELD:				   /*                        */
      s = get_bind(binding, TString(term));	   /*                        */
      return s ? SymValue(s) : NIL;		   /*                        */
    case L_QUOTE:    key = (String)"'";	     break;/*                        */
    case L_MINUS:    key = (String)"-";	     break;/*                        */
    case L_PLUS:     key = (String)"+";	     break;/*                        */
    case L_TIMES:    key = (String)"*";	     break;/*                        */
    case L_DIV:      key = (String)"/";	     break;/*                        */
    case L_MOD:      key = (String)"mod";    break;/*                        */
    case L_SET:      key = (String)"=";	     break;/*                        */
    case L_LIKE:     key = (String)"like";   break;/*                        */
    case L_ILIKE:    key = (String)"ilike";  break;/*                        */
    case L_EQ:       key = (String)"==";     break;/*                        */
    case L_NE:       key = (String)"!=";     break;/*                        */
    case L_GT:       key = (String)">";	     break;/*                        */
    case L_GE:       key = (String)">=";     break;/*                        */
    case L_LT:       key = (String)"<";	     break;/*                        */
    case L_LE:       key = (String)"<=";     break;/*                        */
    case L_NOT:      key = (String)"!";	     break;/*                        */
    case L_AND:      key = (String)"&&";     break;/*                        */
    case L_OR:       key = (String)"||";     break;/*                        */
    default: ErrorNF("Undefined tag ", NULL);	   /*                        */
  }						   /*                        */
 						   /*                        */
   s = get_bind(binding, key);		   	   /*                        */
   if (s == SymDefNULL) 			   /*                        */
   { ErrorNF("Undefined function ", key); } 	   /*                        */
   return (*SymGet(s))(binding, term);		   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
