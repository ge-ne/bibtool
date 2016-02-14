/*** term.c ********************************************************************
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

#include <bibtool/general.h>
#include <bibtool/error.h>
#include "term.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

Term new_term _ARG((short int type, Term car, Term cdr));
Term new_term_num _ARG((long value));
Term new_t_string _ARG((short int type, unsigned char* s));
void free_term _ARG((Term term));
void print_term _ARG((FILE* file, Term term));
String token_type _ARG((int c));

static void prn_args _ARG((FILE * file, Term term, char* sep, int in, int q));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

#define DEBUG_MEM
#undef DEBUG_MEM

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	token_type()
** Type:	String
** Purpose:	
**		
** Arguments:
**	c	
** Returns:	
**___________________________________________________			     */
String token_type(c)			   	   /*                        */
  int c;					   /*                        */
{ static Uchar buffer[2];			   /*                        */
						   /*                        */
  switch (c)					   /*                        */
  { case 0:					   /*                        */
    case EOF:        return (String)"end of file"; /*                        */
    case L_AND:      return (String)"and";	   /*                        */
    case L_CONS:     return (String)"cons";	   /*                        */
    case L_DEFUN:    return (String)"defun";	   /*                        */
    case L_DIV:      return (String)"/";	   /*                        */
    case L_EACH:     return (String)"each";	   /*                        */
    case L_EQ:       return (String)"==";	   /*                        */
    case L_FALSE:    return (String)"false";	   /*                        */
    case L_VAR:	     return (String)"var";	   /*                        */
    case L_FIELD:    return (String)"field";	   /*                        */
    case L_FUNCALL:  return (String)"funcall";	   /*                        */
    case L_FUNCTION: return (String)"function";	   /*                        */
    case L_GE:       return (String)">=";	   /*                        */
    case L_GROUP:    return (String)"group";	   /*                        */
    case L_GT:       return (String)">";	   /*                        */
    case L_IF:       return (String)"if";	   /*                        */
    case L_ILIKE:    return (String)"ilike";	   /*                        */
    case L_LE:       return (String)"<=";	   /*                        */
    case L_LIKE:     return (String)"like";	   /*                        */
    case L_LT:       return (String)"<";	   /*                        */
    case L_MINUS:    return (String)"-";	   /*                        */
    case L_MOD:      return (String)"mod";	   /*                        */
    case L_NE:       return (String)"!=";	   /*                        */
    case L_NOT:      return (String)"not";	   /*                        */
    case L_NUMBER:   return (String)"number";	   /*                        */
    case L_OR:       return (String)"or";	   /*                        */
    case L_PLUS:     return (String)"+";	   /*                        */
    case L_QUOTE:    return (String)"'";	   /*                        */
    case L_RETURN:   return (String)"return";	   /*                        */
    case L_SET:      return (String)"=";	   /*                        */
    case L_STRING:   return (String)"string";	   /*                        */
    case L_TIMES:    return (String)"*";	   /*                        */
    case L_TRUE:     return (String)"true";	   /*                        */
    case L_UMINUS:   return (String)"-";	   /*                        */
    case L_WHILE:    return (String)"while";	   /*                        */
    case L_WITH:     return (String)"with";	   /*                        */
  }						   /*                        */
  buffer[0] = c;				   /*                        */
  buffer[1] = 0;				   /*                        */
  return buffer;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	term_type()
** Type:	String
** Purpose:	
**		
** Arguments:
**	term	
** Returns:	
**___________________________________________________			     */
String term_type(term)				   /*                        */
  Term term;					   /*                        */
{ return term == NIL				   /*                        */
    ? (String)"[]"				   /*                        */
    : token_type(TType(term));			   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/


 static Term terms = NIL;			   /*                        */

#ifdef DEBUG_MEM
 static Term *t_map = NULL;
 static size_t t_map_size = 0;
 static size_t t_map_ptr = 0;
#endif

/*-----------------------------------------------------------------------------
** Function:	new_term()
** Type:	Term
** Purpose:	Allocate a new term and initialize it.
**		
** Arguments:
**	type	the term type
**	cdr	the cdr
** Returns:	
**___________________________________________________			     */
static Term new__t(type, cdr)			   /*                        */
  short int type;				   /*                        */
  Term cdr;					   /*                        */
{ register Term t = terms;			   /*                        */
  						   /*                        */
  if (t) { terms = Car(t); }			   /*                        */
  else						   /*                        */
  { t = (Term)malloc(sizeof(STerm));		   /*                        */
    if (t == NIL) OUT_OF_MEMORY("term");	   /*                        */
  }	   					   /*                        */
  TType(t)     = type;			   	   /*                        */
  Cdr(t)       = cdr;			   	   /*                        */
  TRefCount(t) = 1L;				   /*                        */
#ifdef DEBUG_MEM
  if (t_map_ptr >= t_map_size)
  { t_map_size += 8192;
    t_map	= (t_map
		   ? calloc(t_map_size, sizeof(Term))
		   : malloc(t_map_size*sizeof(Term)));
  }
  t_map[t_map_ptr++] = t;
#endif
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_terms()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	the output file
** Returns:	nothing
**___________________________________________________			     */
void dump_terms(file)				   /*                        */
  FILE* file;					   /*                        */
{						   /*                        */
#ifdef DEBUG_MEM
  size_t i;					   /*                        */
  register int c;				   /*                        */
 						   /*                        */
  for (i = 0; i < t_map_ptr; i++)		   /*                        */
  { c = TType(t_map[i]);			   /*                        */
    fputc(c ? *token_type(c) : '_', file);	   /*                        */
    if (i%64 == 63) fputc('\n', file);		   /*                        */
  }						   /*                        */
  fputc('\n', file);				   /*                        */
#endif
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_term()
** Type:	Term
** Purpose:	Allocate a new term and initialize it.
** Arguments:
**	type	the term type
**	car	the initial car
**	cdr	the initial cdr
** Returns:	the new term
**___________________________________________________			     */
Term new_term(type, car, cdr)			   /*                        */
  short int type;				   /*                        */
  Term car;					   /*                        */
  Term cdr;					   /*                        */
{ register Term t = new__t(type, cdr);		   /*                        */
  Car(t) = car;			   	   	   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_term_num()
** Type:	Term
** Purpose:	Allocate a new term and initialize it as number.
** Arguments:
**	n	the numeric value
** Returns:	
**___________________________________________________			     */
Term new_term_num(n)				   /*                        */
  long n;					   /*                        */
{ register Term t = new__t(L_NUMBER, NIL);	   /*                        */
  TNumber(t) = n;				   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_t_string()
** Type:	Term
** Purpose:	Allocate a new term and initialize it as string type.
** Arguments:
**	sym	the symdef
**	s	the string value, i.e. a symbol
** Returns:	the new term
**___________________________________________________			     */
Term new_t_string(type, s)		   	   /*                        */
  short int type;				   /*                        */
  String s;					   /*                        */
{ register Term t = new__t(type, NIL);		   /*                        */
  TString(t) = s;				   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_t_db()
** Type:	Term
** Purpose:	Allocate a new databse term.
** Arguments:
**	db	the database
** Returns:	the new database term
**___________________________________________________			     */
Term new_t_db(db)				   /*                        */
  DB db;					   /*                        */
{ register Term t = new__t(L_DB, NIL);	   	   /*                        */
  TDB(t) = db;				   	   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_t_rec()
** Type:	Term
** Purpose:	Allocate a new reacord term.
** Arguments:
**	rec	the record
** Returns:	the new record term
**___________________________________________________			     */
Term new_t_rec(rec)				   /*                        */
  Record rec;					   /*                        */
{ register Term t = new__t(L_RECORD, NIL);	   /*                        */
  TRecord(t) = rec;				   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_term()
** Type:	void
** Purpose:	Free the memory of a term and arrange for reuse.
**		The term odes are linked into the |terms| list to be reused.
**		This happens only for those term nodes which are not locked.
** Arguments:
**	t	the term be freed
** Returns:	nothing
**___________________________________________________			     */
void free_term(t)				   /*                        */
  register Term t;				   /*                        */
{ Term cdr;					   /*                        */
 						   /*                        */
  if (t == NIL					   /*                        */
      || TRefCount(t) > 0			   /*                        */
      || TType(t) <= 0			   	   /*                        */
      || TType(t) == L_FALSE			   /*                        */
      || TType(t) == L_TRUE) return;	   	   /*                        */
 						   /*                        */
#ifdef DEBUG_MEM
  print_term(stderr, t);			   /*                        */
  fputs(stderr, "");				   /*                        */
#endif
 						   /*                        */
  cdr = Cdr(t);					   /*                        */
 						   /*                        */
  switch (TType(t))				   /*                        */
  { case L_TRUE:				   /*                        */
    case L_FALSE:				   /*                        */
      return;					   /*                        */
    case L_VAR:					   /*                        */
    case L_FIELD:				   /*                        */
    case L_STRING:				   /*                        */
    case L_FUNCALL:				   /*                        */
 						   /*                        */
    case L_DB:				   	   /*                        */
    case L_RECORD:				   /*                        */
    case L_NUMBER:				   /*                        */
      Car(t) = NIL;				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      if (Car(t)) free_term(Car(t));		   /*                        */
      break;					   /*                        */
  }						   /*                        */
 						   /*                        */
  Car(t) = terms;				   /*                        */
  terms = t;					   /*                        */
 						   /*                        */
  if (cdr)					   /*                        */
  { free_term(cdr);			   	   /*                        */
    Cdr(t) = NIL;				   /*                        */
  }						   /*                        */
  TType(t) = 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	prn_quoted()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	the output stream
**	c	the delimiting character
**	s	the string to be printed
** Returns:	nothing
**___________________________________________________			     */
static void prn_quoted(file, c, s)		   /*                        */
  FILE * file;					   /*                        */
  char c;					   /*                        */
  String s;					   /*                        */
{ if (c) fputc(c, file);			   /*                        */
  for (; *s; s++)				   /*                        */
  { switch (*s)					   /*                        */
    { case '\n': fputs("\\n", file);  break;	   /*                        */
      case '\r': fputs("\\r", file);  break;	   /*                        */
      case '\t': fputs("\\t", file);  break;	   /*                        */
      case '\b': fputs("\\b", file);  break;	   /*                        */
      case '\f': fputs("\\f", file);  break;	   /*                        */
      case '"':	 fputs("\\\"", file); break;	   /*                        */
      case '`':  fputs("\\`", file);  break;	   /*                        */
      case '\'': fputs("\\'", file);  break;	   /*                        */
      case '\\': fputs("\\\\", file); break;	   /*                        */
      default:	 fputc((char)*s, file);		   /*                        */
    }						   /*                        */
  }						   /*                        */
  if (c) fputc(c, file);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	prn_field()
** Type:	int
** Purpose:	
**		
** Arguments:
**	file	the output file
**	t	the term
** Returns:	
**___________________________________________________			     */
static void prn_field(file, t, quoted)		   /*                        */
  FILE * file;					   /*                        */
  Term t;					   /*                        */
  int quoted;					   /*                        */
{ char q   = 0;				   	   /*                        */
  String s = TString(t);			   /*                        */
  if (*s >= '0' && *s <= '9') {			   /*                        */
    q = '`';					   /*                        */
  } else {					   /*                        */
    for (; *s; s++)				   /*                        */
    { if (!(   (*s >='a' && *s <='z') 		   /*                        */
	    || (*s >='A' && *s <='Z')		   /*                        */
	    || (*s >='0' && *s <='9')		   /*                        */
	    || *s == '@'			   /*                        */
	    || *s == '$'			   /*                        */
	    || *s == '_'			   /*                        */
	    || *s == '.'))			   /*                        */
      { q = '`';				   /*                        */
	break;					   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
  prn_quoted(file, q, TString(t));	   	   /*                        */
 						   /*                        */
  if (Cdr(t))					   /*                        */
  { fputs(": ", file);				   /*                        */
    prn_term(file, Cdr(t), 0, quoted);		   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	indent()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	the outptu file
**	s	the inital string to print
**	in	the indentation level
** Returns:	nothing
**___________________________________________________			     */
static void indent(file, s, in)			   /*                        */
  FILE * file;					   /*                        */
  char * s;					   /*                        */
  int in;					   /*                        */
{ fputs(s, file);				   /*                        */
  while (in-- > 0) fputs("  ", file);	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	prn_args()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	
**	term	
**	sep	
**	in	
** Returns:	nothing
**___________________________________________________			     */
static void prn_args(file, term, sep, in, quote)   /*                        */
  FILE * file;					   /*                        */
  Term term;					   /*                        */
  char * sep;					   /*                        */
  int in;					   /*                        */
  int quote;					   /*                        */
{						   /*                        */
  if (term == NIL) return;			   /*                        */
 						   /*                        */
  prn_term(file, Car(term), in, quote);	   	   /*                        */
  for (term = Cdr(term); term; term = Cdr(term))   /*                        */
  { indent(file, sep, in);			   /*                        */
    prn_term(file, Car(term), in, quote);	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	prn_function()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	
**	 prefix	
**	 term	
**	 in	
** Returns:	nothing
**___________________________________________________			     */
static void prn_function(file, prefix, term, in, quote)/*                    */
  FILE *file;					   /*                        */
  char * prefix;				   /*                        */
  Term term;					   /*                        */
  int in;					   /*                        */
  int quote;					   /*                        */
{						   /*                        */
  fputs(prefix, file);		   		   /*                        */
  prn_args(file, Car(term), ", ", 0, quote);	   /*                        */
  fputs(") ", file);			   	   /*                        */
  if (Cddr(term))				   /*                        */
    prn_term(file, Cdr(term), in, quote);	   /*                        */
  else						   /*                        */
    fputs("{}", file);			   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	prn_term()
** Type:	void
** Purpose:	Produce a printed representation of a term and write it to
**		the output stream.
** Arguments:
**	file	the output stream
**	t	the term to print
** Returns:	nothing
**___________________________________________________			     */
void prn_term(file, term, in, quote)		   /*                        */
  FILE * file;					   /*                        */
  Term term;					   /*                        */
  int in;					   /*                        */
  int quote;					   /*                        */
{ char * key;					   /*                        */
  if (term == NIL) {				   /*                        */
    fputs("[]", file);				   /*                        */
    return;					   /*                        */
  }						   /*                        */
  switch (TType(term))				   /*                        */
  { case 0:					   /*                        */
    case EOF:					   /*                        */
      return;	   			   	   /*                        */
						   /*                        */
    case L_CONS:				   /*                        */
      fputs("[", file);			   	   /*                        */
      prn_args(file, term, ", ", 0, quote);	   /*                        */
      fputs("]", file);			   	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_DB:				   	   /*                        */
      fputs("<DB>", file);			   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_DEFUN:			   	   /*                        */
      fputs("defun ", file);			   /*                        */
      fputs((char*)TString(term), file);	   /*                        */
      prn_function(file, "(", Cdr(term), in);  	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_EACH:			   	   /*                        */
      fputs("each (", file);			   /*                        */
      prn_field(file, Car(term), quote);	   /*                        */
      fputs(") ", file);			   /*                        */
      prn_term(file, Cdr(term), in, quote);	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_FALSE:				   /*                        */
      fputs("false", file);			   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_VAR:				   	   /*                        */
    case L_FIELD:				   /*                        */
      prn_field(file, term, quote);		   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_FUNCTION:			   	   /*                        */
      prn_function(file, "function (", term, in);  /*                        */
      return;					   /*                        */
						   /*                        */
    case L_GROUP:				   /*                        */
      if (Cdr(term))				   /*                        */
      { indent(file, "{\n", in + 1);		   /*                        */
	prn_args(file, Cdr(term), ";\n", in + 1, quote);/*                   */
	indent(file, "\n", in);	   		   /*                        */
      } else {					   /*                        */
	fputs("{\n", file);			   /*                        */
      }						   /*                        */
      fputs("}", file);			   	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_IF:				   	   /*                        */
      fputs("if (", file);			   /*                        */
      prn_args(file, Cdar(term), "", in + 1, quote);/*                       */
      fputs(") ", file);			   /*                        */
      prn_term(file, Cadr(term), in, quote);	   /*                        */
      if (Cddr(term))				   /*                        */
      { fputs(" else ", file);			   /*                        */
	prn_term(file, Cddr(term), in, quote);	   /*                        */
      }						   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_NUMBER:				   /*                        */
      fprintf(file, "%ld", TNumber(term));	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_RECORD:				   /*                        */
      fputs("<REC>", file);			   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_RETURN:				   /*                        */
      fputs("return ", file);			   /*                        */
      prn_term(file, Cdr(term), in, quote);	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_STRING:				   /*                        */
      if (quote)				   /*                        */
      { prn_quoted(file, '"', TString(term)); }	   /*                        */
      else					   /*                        */
      { fputs((char*)TString(term), file); }	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_TRUE:				   /*                        */
      fputs("true", file);			   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_UMINUS:				   /*                        */
      fputs("-", file);			   	   /*                        */
      prn_term(file, Cadr(term), in, quote);	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_WHILE:				   /*                        */
      fputs("while (", file);			   /*                        */
      prn_args(file, Cdar(term), "", in + 1, quote);/*                       */
      fputs(") ", file);			   /*                        */
      prn_term(file, Cdr(term), in, quote);	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_WITH:			   	   /*                        */
      fputs("with (", file);			   /*                        */
      prn_args(file, Car(term), ",", in + 1, quote);/*                       */
      fputs(") ", file);			   /*                        */
      prn_term(file, Cdr(term), in, quote);	   /*                        */
      return;					   /*                        */
						   /*                        */
    case L_FUNCALL:  key = (char*)TString(term);break;/*                     */
    case L_QUOTE:    key = "'";		     break;/*                        */
    case L_MINUS:    key = " - ";	     break;/*                        */
    case L_PLUS:     key = " + ";	     break;/*                        */
    case L_TIMES:    key = " * ";	     break;/*                        */
    case L_DIV:      key = " / ";	     break;/*                        */
    case L_MOD:      key = " mod ";          break;/*                        */
    case L_SET:      key = " = ";	     break;/*                        */
    case L_LIKE:     key = " like ";         break;/*                        */
    case L_ILIKE:    key = " ilike ";        break;/*                        */
    case L_EQ:       key = " == ";           break;/*                        */
    case L_NE:       key = " != ";           break;/*                        */
    case L_GT:       key = " > ";	     break;/*                        */
    case L_GE:       key = " >= ";           break;/*                        */
    case L_LT:       key = " < ";	     break;/*                        */
    case L_LE:       key = " <= ";           break;/*                        */
    case L_NOT:      key = "not";            break;/*                        */
    case L_AND:      key = " and ";          break;/*                        */
    case L_OR:       key = " or ";           break;/*                        */
    default:					   /*                        */
      fprintf(file, "?0x%x?", TType(term));	   /*                        */
      return;					   /*                        */
  }						   /*                        */
 						   /*                        */
  if (L_IS_BINARY(TType(term)) )		   /*                        */
  { term = Cdr(term);				   /*                        */
    if (term == NIL) return;			   /*                        */
    fputc('(', file);				   /*                        */
    prn_term(file, Car(term), in, quote);	   /*                        */
    fputs(key, file);		   		   /*                        */
    prn_term(file, Cadr(term), in, quote);	   /*                        */
  } else {					   /*                        */
    fputs(key, file);		   		   /*                        */
    fputc('(', file);				   /*                        */
    if (term)					   /*                        */
      prn_args(file, Cdr(term), ", ", in, quote);  /*                        */
  }						   /*                        */
  fputc(')', file);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	print_term()
** Type:	void
** Purpose:	Produce a printed representation of a term and write it to
**		the output stream.
** Arguments:
**	file	the output stream
**	t	the term to print
** Returns:	nothing
**___________________________________________________			     */
void print_term(file, term)			   /*                        */
  register FILE * file;				   /*                        */
  register Term term;				   /*                        */
{ prn_term(file, term, 0, TRUE);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	list_length()
** Type:	int
** Purpose:	Determine the length of a list, i.e. a cons sequence.
** Arguments:
**	list	the list
** Returns:	the length
**___________________________________________________			     */
int list_length(list)				   /*                        */
  register Term list;				   /*                        */
{ register int i = 0;				   /*                        */
  while (list && TermIsList(list))		   /*                        */
  { i++;					   /*                        */
    list = Cdr(list);				   /*                        */
  }						   /*                        */
  return i;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	hash()
** Type:	int
** Purpose:	Compute the has value of a string as sum of shifted characters.
** Arguments:
**	s	the string
** Returns:	the hash value
**___________________________________________________			     */
unsigned int hash(s)			   	   /*                        */
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
** Function:	symdef()
** Type:	SymDef
** Purpose:	Allocate a new SymDef and fill it with initial values.
** Arguments:
**	name	the name of the symdef
**	op	the op code
**	flags	the flags
**	get	the getter function
**	set	the setter function
** Returns:	the new SymDef
**___________________________________________________			     */
SymDef symdef(name, op, flags, get, set)	   /*                        */
  String name;					   /*                        */
  short int op;					   /*                        */
  short int flags;				   /*                        */
  Term (*get)_ARG((Binding, Term));		   /*                        */
  Term (*set)_ARG((Binding, Term));		   /*                        */
{						   /*                        */
  SymDef sym    = (SymDef) malloc(sizeof(SSymDef));/*                        */
  if (sym == SymDefNULL) OUT_OF_MEMORY("symdef");  /*                        */
  SymName(sym)  = name;				   /*                        */
  SymOp(sym)    = op;				   /*                        */
  SymFlags(sym) = flags;			   /*                        */
  SymHash(sym)  = hash(name);			   /*                        */
  SymTerm(sym)  = NIL;				   /*                        */
  SymValue(sym) = NIL;				   /*                        */
  SymGet(sym)   = get;			   	   /*                        */
  SymSet(sym)   = set;			   	   /*                        */
  return sym;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_sym()
** Type:	void
** Purpose:	Release the memory occupied by a symbol definition.
** Arguments:
**	sym	the symbol definition
** Returns:	nothing
**___________________________________________________			     */
void free_sym(sym)				   /*                        */
  SymDef sym;					   /*                        */
{						   /*                        */
  if (SymValue(sym)) free_term(SymValue(sym));	   /*                        */
  free(sym);					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
