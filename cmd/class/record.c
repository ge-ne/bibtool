/*** record.c ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2017 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/error.h>
#include <bibtool/type.h>
#include <bibtool/sbuffer.h>
#include <bibtool/entry.h>
#include "../binding.h"
#include "../lcore.h"

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


static Term c_record;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	m_class()
** Type:	Term
** Purpose:	Getter for the class.
** Arguments:
**	binding	the binding
**	rec	the record term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_class(binding, rec, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term rec;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "class");	   	   	   /*                        */
  LinkTerm(c_record);				   /*                        */
  return c_record;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_type()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	rec	the record term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_type(binding, record, args)	   /*                        */
  Binding binding;				   /*                        */
  Term record;					   /*                        */
  Term args;					   /*                        */
{ no_args(args, "type");	   	   	   /*                        */
 						   /*                        */
  return StringTerm(EntryName(RecordType(TRecord(record))));/*               */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_get()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	rec	the record term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_get(binding, record, args)	   /*                        */
  Binding binding;				   /*                        */
  Term record;					   /*                        */
  Term args;					   /*                        */
{ String key = str_arg(binding, &args, "get");	   /*                        */
  String val = record_get(TRecord(record), key);   /*                        */
  no_args(args, "get");	   	   	   	   /*                        */
 						   /*                        */
  return val ? StringTerm(val) : NIL;		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	a_set()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	rec	the record term
**	value	the value term
** Returns:	
**___________________________________________________			     */
static Term a_set(binding, record, value)	   /*                        */
  Binding binding;				   /*                        */
  Term record;					   /*                        */
  Term value;				   	   /*                        */
{ Term args = Cddr(record);			   /*                        */
  String key = str_arg(binding, &args, "field");   /*                        */
  String val;					   /*                        */
  no_args(args, "field");			   /*                        */
 						   /*                        */
  val = eval_str(binding, value);		   /*                        */
  push_to_record(TRecord(record),		   /*                        */
		 key,				   /*                        */
		 val);			   	   /*                        */
  return StringTerm(val);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_has()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	rec	the record term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_has(binding, record, args)	   /*                        */
  Binding binding;				   /*                        */
  Term record;					   /*                        */
  Term args;					   /*                        */
{ String key = str_arg(binding, &args, "has");	   /*                        */
  String val = record_get(TRecord(record), key);   /*                        */
  no_args(args, "has");	   	   	   	   /*                        */
 						   /*                        */
  return val ? term_true : term_false;		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_sort()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	rec	the record term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_sort(binding, record, args)	   /*                        */
  Binding binding;				   /*                        */
  Term record;					   /*                        */
  Term args;					   /*                        */
{ no_args(args, "sort");			   /*                        */
 						   /*                        */
  sort_record(TRecord(record));			   /*                        */
  LinkTerm(record);				   /*                        */
  return record;		   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_key()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	rec	the record term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_key(binding, record, args)	   /*                        */
  Binding binding;				   /*                        */
  Term record;					   /*                        */
  Term args;					   /*                        */
{ no_args(args, "key");	   	   	   	   /*                        */
 						   /*                        */
  return StringTerm(*RecordHeap(TRecord(record))); /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	a_key()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	record	the record
**	val	the value
** Returns:	
**___________________________________________________			     */
static Term a_key(binding, record, val)	   	   /*                        */
  Binding binding;				   /*                        */
  Term record;					   /*                        */
  Term val;				   	   /*                        */
{ StringBuffer* sb = sbopen();			   /*                        */
  char *cp = (char*)eval_str(binding, Car(val));   /*                        */
  String s;		   			   /*                        */
 						   /*                        */
  for (; *cp; cp++)	   			   /*                        */
  { if (is_allowed(*cp)) sbputc(*cp, sb);  }	   /*                        */
  s = symbol((String)sbflush(sb));		   /*                        */
  sbclose(sb);					   /*                        */
 						   /*                        */
  *RecordHeap(TRecord(record)) = s;		   /*                        */
  return StringTerm(s); 			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_sortkey()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	rec	the record term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_sortkey(binding, record, args)	   /*                        */
  Binding binding;				   /*                        */
  Term record;					   /*                        */
  Term args;					   /*                        */
{ no_args(args, "sort.key");			   /*                        */
 						   /*                        */
  return StringTerm(*RecordHeap(TRecord(record))); /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_length()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	rec	the record term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_length(binding, rec, args)	   /*                        */
  Binding binding;				   /*                        */
  Term rec;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "length");	   	   	   /*                        */
  return NumberTerm(count_record(TRecord(rec)));   /*                        */
}						   /*------------------------*/

#define Bind(NAME,GET)		Bind2(NAME,GET, NULL)
#define Bind2(NAME,GET, SET)	bind(b,					\
				     symdef(symbol((String)NAME),	\
					    0, 0, GET, SET));

/*-----------------------------------------------------------------------------
** Function:	class_record()
** Type:	Term
** Purpose:	Initialize the class methods for <RECORD>
**		
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
Term class_record()				   /*                        */
{ Binding b;					   /*                        */
 						   /*                        */
  if (c_record == NIL)			   	   /*                        */
  { c_record = new_class(StringTerm("Entry"));	   /*                        */
    b = TBinding(c_record);		   	   /*                        */
 						   /*                        */
    Bind("as.number", m_as_number);		   /*                        */
    Bind("as.string", m_as_string);		   /*                        */
    Bind("class", m_class);		   	   /*                        */
    Bind2("field", m_get, a_set);		   /*                        */
    Bind("has", m_has);		   	   	   /*                        */
    Bind2("key", m_key, a_key);			   /*                        */
    Bind("length", m_length);		   	   /*                        */
    Bind("sort", m_sort);			   /*                        */
    Bind("sort.key", m_sortkey);		   /*                        */
    Bind("type", m_type);			   /*                        */
  }						   /*                        */
						   /*                        */
  return c_record;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
