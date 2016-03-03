/*** db.c *********************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/error.h>
#include <bibtool/type.h>
#include <bibtool/expand.h>
#include <bibtool/sbuffer.h>
#include "../binding.h"
#include "../lcore.h"
#include "../rec_sort.h"

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


static Term c_database;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	m_class()
** Type:	Term
** Purpose:	Getter for the class.
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_class(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "class");	   	   	   /*                        */
  LinkTerm(c_database);				   /*                        */
  return c_database;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_read()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	db	the database term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_read(binding, db, args)		   /*                        */
  Binding binding;				   /*                        */
  Term db;					   /*                        */
  Term args;					   /*                        */
{ Term t;					   /*                        */
  extern int rsc_verbose;			   /*                        */
 						   /*                        */
  if (args)				   	   /*                        */
  {						   /*                        */
    for ( ; args; args = Cdr(args))		   /*                        */
    { t = evaluate(binding, args);		   /*                        */
      if (t == NIL) continue;			   /*                        */
      if (IsString(t))			   	   /*                        */
      { if (read_db(TDB(db),			   /*                        */
		    TString(t),			   /*                        */
		    rsc_verbose))  		   /*                        */
	{ ErrorNF2("Database file not found: ",	   /*                        */
		   TString(t)); }		   /*                        */
      }	   					   /*                        */
      else if (IsList(t))			   /*                        */
      { for ( ; t; t = Cdr(t))			   /*                        */
	{ if (Car(t) == NIL) continue;		   /*                        */
	  if (IsString(Car(t)))		   	   /*                        */
	  { if (read_db(TDB(db),		   /*                        */
			TString(Car(t)),	   /*                        */
			rsc_verbose))		   /*                        */
	    { ErrorNF2("Database file not found: ",/*                        */
		       TString(Car(t))); }	   /*                        */
	  }					   /*                        */
	  else { ErrorNF2("read: illegal parameter ",/*                      */
			  term_type(Car(t))); }	   /*                        */
	}					   /*                        */
      }						   /*                        */
      else 					   /*                        */
      { ErrorNF2("read: illegal parameter ",	   /*                        */
		 term_type(t)); }		   /*                        */
    }						   /*                        */
  } 						   /*                        */
  LinkTerm(db);					   /*                        */
  return db;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_read()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_read(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term db = DBTerm(new_db());			   /*                        */
  m_read(binding, db, Cdr(term));		   /*                        */
  LinkTerm(db);				   	   /*                        */
  return db;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_rewind()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	db	the database term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_rewind(binding, db, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term db;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "rewind");	   	   	   /*                        */
  db_rewind(TDB(db));				   /*                        */
  LinkTerm(db);					   /*                        */
  return db;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_sort_macros()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	db	the database term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_sort_macros(binding, db, args)	   /*                        */
  Binding binding;				   /*                        */
  Term db;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "sort.macros");  	   	   /*                        */
  db_mac_sort(TDB(db));				   /*                        */
  LinkTerm(db);					   /*                        */
  return db;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_get()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	db	the database term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_get(binding, db, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term db;					   /*                        */
  Term args;					   /*                        */
{ Record rec;					   /*                        */
  String key = str_arg(binding, &args, "get");	   /*                        */
  no_args(args, "get");  	   	   	   /*                        */
 						   /*                        */
  rec = db_find(TDB(db), key);			   /*                        */
  return rec ? RecordTerm(rec) : NIL;		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_macro()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	db	the database term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_macro(binding, db, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term db;					   /*                        */
  Term args;					   /*                        */
{ String s = str_arg(binding, &args, "macro");     /*                        */
  no_args(args, "macro");  	   	   	   /*                        */
 						   /*                        */
  s = db_string(TDB(db), s, TRUE);		   /*                        */
  return s ? StringTerm(s) : NIL;		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sort_args()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	s	
**	casep	
**	descp	
** Returns:	nothing
**___________________________________________________			     */
static void sort_args(s, casep, descp)		   /*                        */
  String s;					   /*                        */
  int *casep;					   /*                        */
  int *descp;					   /*                        */
{						   /*                        */
  if (cmp(s, (String)"case") == 0)		   /*                        */
  { *casep = TRUE;	}			   /*                        */
  else if (cmp(s, (String)"ascending") == 0	   /*                        */
	   || cmp(s, (String)"asc") == 0)	   /*                        */
  { *descp = FALSE; }				   /*                        */
  else if (cmp(s, (String)"descending") == 0	   /*                        */
	   || cmp(s, (String)"desc") == 0)	   /*                        */
  { *descp = TRUE; }				   /*                        */
  else						   /*                        */
  { WARNING2("sort: Illegal argument ignored: ",   /*                        */
	     s);	   		   	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_sort()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	db	the database term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_sort(binding, db, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term db;					   /*                        */
  Term args;					   /*                        */
{ extern int rsc_sort_cased;			   /*                        */
  extern int rsc_sort_reverse;			   /*                        */
  Term t;					   /*                        */
  Term fct  = NIL;				   /*                        */
  int cased = rsc_sort_cased;			   /*                        */
  int desc  = rsc_sort_reverse;			   /*                        */
 						   /*                        */
  for ( ; args; args = Cdr(args))		   /*                        */
  { t = evaluate(binding, Car(args));		   /*                        */
    switch (t ? TType(t) : L_CONS)		   /*                        */
    { case L_VAR:				   /*                        */
      case L_STRING:				   /*                        */
	sort_args(TString(t), &cased, &desc);	   /*                        */
	break;					   /*                        */
      case L_CONS:				   /*                        */
	for ( ; t; t = Cdr(t))			   /*                        */
	{ switch (Car(t) ? TType(Car(t)) : L_CONS) /*                        */
	  { case L_VAR:			   	   /*                        */
	    case L_STRING:			   /*                        */
	      sort_args(TString(Car(t)), &cased, &desc);/*                   */
	      break;				   /*                        */
	    default:				   /*                        */
	      WARNING2("sort: Illegal argument ignored: ",/*                 */
		       token_type(Car(t) ? TType(Car(t)) : 0));/*            */
	  }					   /*                        */
	}					   /*                        */
	break;					   /*                        */
      case L_FUNCTION:				   /*                        */
	fct = t;				   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	WARNING2("sort: Illegal argument ignored: ",/*                       */
		 token_type(t ? TType(t) : 0));	   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  db_sort(TDB(db),				   /*                        */
	  get_sorter(cased, desc, binding, fct));  /*                        */
 						   /*                        */
  return db;		   			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_write()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	db	the database term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_write(binding, db, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term db;					   /*                        */
  Term args;					   /*                        */
{ extern char *rsc_print_et;			   /*                        */
  FILE *file;					   /*                        */
  char *f = (args != NIL			   /*                        */
	     ? (char*)str_arg(binding, &args, "write")/*                     */
	     : "");			   	   /*                        */
  char *spec = (args != NIL			   /*                        */
		? (char*)str_arg(binding, &args, "write")/*                  */
		: rsc_print_et);		   /*                        */
  no_args(args, "write");  	   	   	   /*                        */
 						   /*                        */
  file = *f ? fopen(f, "w") : stdout;	   	   /*                        */
  if (file == NULL)				   /*                        */
    ErrorNF2("write: file could not be opened: ",  /*                        */
	     f);				   /*                        */
  print_db(file, TDB(db), spec);		   /*                        */
 						   /*                        */
  if (*f) fclose(file);				   /*                        */
 						   /*                        */
  LinkTerm(db);					   /*                        */
  return db;	   				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_expand()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	db	the database term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_expand(binding, db, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term db;					   /*                        */
  Term args;					   /*                        */
{ String s = str_arg(binding, &args, "expand");    /*                        */
  no_args(args, "expand");  	   	   	   /*                        */
 						   /*                        */
  return StringTerm(expand_rhs(s,		   /*                        */
			       (String)"",	   /*                        */
			       (String)"",	   /*                        */
			       TDB(db)));	   /*                        */
}						   /*------------------------*/


#define Bind(NAME,GET)  bind(b, symdef(symbol((String)NAME),     \
				       0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	class_db()
** Type:	Term
** Purpose:	
**		
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
Term class_db()				   	   /*                        */
{ Binding b;					   /*                        */
 						   /*                        */
  if (c_database == NIL)			   /*                        */
  { c_database = new_class(StringTerm("Database"));/*                        */
    b = TBinding(c_database);		   	   /*                        */
 						   /*                        */
    Bind("as.string", m_as_string);		   /*                        */
    Bind("as.number", m_as_number);		   /*                        */
    Bind("class", m_class);			   /*                        */
    Bind("expand", m_expand);			   /*                        */
    Bind("entry", m_get);			   /*                        */
    Bind("macro", m_macro);			   /*                        */
    Bind("read", m_read);			   /*                        */
    Bind("rewind", m_rewind);		   	   /*                        */
    Bind("sort.macros", m_sort_macros);		   /*                        */
#ifdef TODO
#endif
    Bind("sort", m_sort);			   /*                        */
    Bind("write", m_write);		   	   /*                        */
  }						   /*                        */
 						   /*                        */
  return c_database;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
