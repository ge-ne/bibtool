/*** print.c ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2020 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2, or (at your option)
** any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
**-----------------------------------------------------------------------------
** Description:
**	This module provides also access to the functions and
**	variables defined in |entry.c|. Consult also the documentation
**	of this file for details.
**
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/print.h>
#include <bibtool/entry.h>
#include <bibtool/rsc.h>
#include <bibtool/macros.h>
#include <bibtool/sbuffer.h>
#include <bibtool/expand.h>
#include <bibtool/error.h>

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 char * sput_record _ARG((Record rec,DB db,String start));/* print.c         */
 static int fput_char _ARG((int c));		   /* print.c                */
 static int sput_char _ARG((int c));		   /* print.c                */
 static void indent _ARG((int col,int (*fct)_ARG((int))));/* print.c         */
 static void line_breaking _ARG((String t,int align,int (*fct)_ARG((int))));/* print.c*/
 static void print_equation _ARG((String pre,Symbol s,Symbol t,int align,int (*fct)_ARG((int))));/* print.c*/
 static void puts_in _ARG((String s,int in,int (*fct)_ARG((int))));/* print.c */
 void fput_record _ARG((FILE *file,Record rec,DB db,String start));/* print.c*/
 void put_record _ARG((int (*fct)_ARG((int)),Record rec,DB db,String start));/* print.c*/
 void rsc_align _ARG((String s));	   	   /* print.c                */
 void set_key_type _ARG((String  s));		   /* print.c                */
 void set_symbol_type _ARG((String  s));	   /* print.c                */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

#define TAB_WIDTH 8

 static int symbol_type = SYMBOL_TYPE_LOWER;	   /*                        */

 static String s_upper = (String)"upper";	   /*                        */
 static String s_lower = (String)"lower";	   /*                        */
 static String s_cased = (String)"cased";	   /*                        */

/*-----------------------------------------------------------------------------
** Function:	set_symbol_type()
** Purpose:	Function to set the symbol type which is used by the
**		printing routine. The argument is a string describing
**		the value to use. Possible values are |"upper"|,
**		|"lower"|, and |"cased"|. The comparison of the values
**		is performed case insensitive.
**
**		If no appropriate value is found then an error message
**		is issued as the only action.
**		
**		This function is called from \File{rsc.c}.
** Arguments:
**	s	String description of the value.
** Returns:	nothing
**___________________________________________________			     */
void set_symbol_type(s)				   /*			     */
  register String  s;				   /*			     */
{ if ( case_eq(s, s_upper) )			   /*			     */
  { symbol_type = SYMBOL_TYPE_UPPER; }		   /*			     */
  else if ( case_eq(s, s_cased) )		   /*			     */
  { symbol_type = SYMBOL_TYPE_CASED; }		   /*			     */
  else if ( case_eq(s, s_lower) )		   /*			     */
  { symbol_type = SYMBOL_TYPE_LOWER; }		   /*			     */
  else						   /*			     */
  { Err("Unknown symbol type ignored.\n"); }	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_symbol_type()
** Type:	String
** Purpose:	Getter for the symbol type.
** Arguments:	none
** Returns:	one of the values SYMBOL\_TYPE\_UPPER, SYMBOL\_TYPE\_LOWER,
**		or SYMBOL\_TYPE\_CASED as defined in header \textsf{type.h}
**___________________________________________________			     */
String get_symbol_type()			   /*                        */
{ switch (symbol_type)				   /*                        */
  { case SYMBOL_TYPE_UPPER: return s_upper;	   /*                        */
    case SYMBOL_TYPE_LOWER: return s_lower;	   /*                        */
    case SYMBOL_TYPE_CASED: return s_cased;	   /*                        */
    default: return NULL;			   /*                        */
  }						   /*                        */
}						   /*------------------------*/

#ifdef MAYBE_IN_THE_NEXT_RELEASE

 static int key_type = SYMBOL_TYPE_LOWER;	   /*                        */

/*-----------------------------------------------------------------------------
** Function*:	set_key_type()
** Purpose:	Wrapper function to set the static variable key_type.
**		This function is called from rsc.c
** Arguments:
**	s	String description of the value.
** Returns:	nothing
**___________________________________________________			     */
void set_key_type(s)				   /*			     */
  register String  s;				   /*			     */
{ if ( case_cmp(s,s_upper) )			   /*			     */
  { key_type = SYMBOL_TYPE_UPPER; }		   /*			     */
  else if ( case_cmp(s,s_cased) )		   /*			     */
  { key_type = SYMBOL_TYPE_CASED; }		   /*			     */
  else if ( case_cmp(s,s_lower) )		   /*			     */
  { key_type = SYMBOL_TYPE_LOWER; }		   /*			     */
  else						   /*			     */
  { Err("Unknown key type ignored.\n"); }	   /*			     */
}						   /*------------------------*/
#endif


 static int align_value = 18;
 static bool align_auto = false;

/*-----------------------------------------------------------------------------
** Function:	rsc_align()
** Purpose:	Parse the value of the resource print.align and set the values
**		of the parameters accordingly.
**		Initial spaces are ignored. Then follows the keyword |auto| or
**		a (optionally negative) number.
** Arguments:
**	s	String description of the value.
** Returns:	nothing
**___________________________________________________			     */
void rsc_align(s)				   /*			     */
  String s;					   /*			     */
{						   /*			     */
  int val = 0;					   /*			     */
  while (*s && is_space(*s)) { s++; }		   /*			     */
						   /*			     */
  if (*s == '\0')				   /*			     */
  { Err("Missing value for print.align.\n");	   /*			     */
    return;					   /*			     */
  }						   /*			     */
  if (strcmp((char*)s, "auto") == 0)
  { align_auto = true;				   /*			     */
    return;					   /*			     */
  }						   /*			     */
  String sp = s;
  bool neg = false;
  if (*sp == '-')				   /*			     */
  { neg = true;					   /*			     */
    sp++;					   /*			     */
  }						   /*			     */
  while (*sp) {					   /*			     */
    if (!is_digit(*sp))
    { Err("Illegal print.align ignored.\n");
      return;					   /*			     */
    }						   /*			     */
    val = val*10 + *sp - '0';			   /*			     */
    sp++;					   /*			     */
  }						   /*			     */
  align_value = neg ? -val: val;		   /*			     */
  align_auto = false;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	adjust_align()
** Purpose:	Set the value of the |align_value| according to the width of the
**		labels of the current record.
** Arguments:
**	rec	the record
** Returns:	nothing
**___________________________________________________			     */
 static void adjust_align(rec)			   /*			     */
  Record rec;					   /*			     */
{ register int i;				   /*			     */
  register int len;				   /*			     */
  Symbol *hp = RecordHeap(rec);			   /*			     */
  align_value = 0;				   /*			     */
						   /*			     */
  for (i = RecordFree(rec); i > 0; i -= 2)	   /*			     */
  {		   				   /* Not a deleted or       */
    if (*hp && is_allowed(*SymbolValue(*hp))	   /*   private entry        */
        && *(hp+1) )				   /* and is a equation	     */
    { len = strlen(*hp);			   /*			     */
      if (len > align_value) align_value = len;	   /*			     */
    }						   /*			     */
    hp += 2;					   /*			     */
  }						   /*                        */
  align_value += rsc_indent + (rsc_print_we ? 3 : 1);/*                      */
}						   /*------------------------*/


						   /*------------------------*/
 static int column = 0;				   /* The current column of  */
						   /*  the output stream is  */
						   /*  kept in this variable.*/

#define NL	(void)(*fct)('\n'),column=0
#define PUTC(C) (void)((*fct)(C),++column)
#define PUTS(S) puts_in((String)(S), 0, fct)

/*-----------------------------------------------------------------------------
** Function:	puts_in()
** Purpose:	Print a string and update current column.
** Arguments:
**	s	string to be printed.
**	in	indentation. Alignment column.
**	fct	function to use for writing a character.
** Returns:	nothing
**___________________________________________________			     */
static void puts_in(s,in,fct)			   /*			     */
  register String s;				   /*			     */
  register int  in;				   /*                        */
  int (*fct)_ARG((int));			   /*                        */
{						   /*			     */
  while ( *s )					   /*			     */
  { (void)(*fct)(*s);			   	   /*                        */
    switch ( *(s++) )				   /*			     */
    { case '\t':				   /*                        */
	column += TAB_WIDTH - (column%TAB_WIDTH);  /*                        */
	break;					   /*	                     */
      case '\n':				   /*                        */
	column = 0;			   	   /*                        */
        if ( in > 0 ) indent(in, fct);		   /*                        */
        break;  				   /*			     */
      default: ++column;			   /*			     */
    }						   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	indent()
** Purpose:	Add spaces or tabs to indent to the given column.
**		If the current column is beyond col then nothing happens.
**		The resource use.tabs can be used to disable the use of TAB.
** Arguments:
**	col	Target column
**	fct	function to use for writing a character.
** Returns:	nothing
**___________________________________________________			     */
static void indent(col,fct)			   /*			     */
  register int col;				   /*			     */
  int (*fct)_ARG((int));			   /*                        */
{						   /*			     */
  if ( col > rsc_linelen ) col = rsc_linelen;	   /*                        */
  while ( column < col )			   /*			     */
  { if (   rsc_use_tabs				   /*	TAB is allowed and   */
	&& column+TAB_WIDTH-(column%TAB_WIDTH) <= col )/* enough space left  */
    { (void)(*fct)('\t');			   /*	then put a TAB and   */
      column += TAB_WIDTH - (column%TAB_WIDTH);	   /*	update column.	     */
    }						   /*			     */
    else					   /* otherwise		     */
    { (void)(*fct)(' ');			   /*  write a single space  */
      ++column;					   /*  and advance column.   */
    }						   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	line_breaking()
** Purpose:	Write out a right hand side of an equation.
**		If it does not fit break the line into several parts and
**		print them on successive lines.
**		Temporarily end marks are placed inside the string,
**		but the old contents has been restored at the end.
** Arguments:
**	t	string to print.
**	align	starting column for continuation lines.
**	fct	function to use for writing a character.
** Returns:	nothing
**___________________________________________________			     */
static void line_breaking(t, align, fct)	   /*			     */
  register String t;				   /* string to print.	     */
  int		 align;				   /* alignment column	     */
  int            (*fct)_ARG((int));		   /*                        */
{ register String s;			   	   /* intermediate pointer   */
  char		  end_c;			   /* temp. character.	     */
  int		  brace,			   /* brace counter	     */
		  len;				   /* length of rem. output  */
  bool		  first = true;			   /* indicator for #	     */
						   /*			     */
  while (is_space(*t)) ++t;			   /* skip leading spaces    */
						   /*			     */
  indent(align, fct);				   /* goto alignment column  */
						   /*			     */
  while (*t)					   /* as long as sth to print*/
  { s = t;					   /*			     */
						   /*			     */
    switch (*t)				   	   /*			     */
    { case '"':					   /* QUOTED PART	     */
	for ( len = 2, ++t;			   /*			     */
	     *t && *t != '\"';			   /* Search terminating "   */
	     ++t, ++len )			   /*			     */
	{ if ( *t == '\\' && *(t+1) != '\0' )	   /* skip over quoted and   */
	  { ++t; ++len; }			   /*  similar constructs.   */
	}					   /*			     */
	if ( *t ) ++t;				   /* skip after end, if poss*/
	if ( *t ) { end_c = *t; *t = '\0'; }	   /* save char and mark end.*/
	else	  { end_c = *t; }		   /*			     */
	break;					   /*			     */
      case '{':					   /* BRACED PART	     */
	brace = 1;				   /*			     */
	for ( len = 2, ++t;			   /* find matching brace.   */
	     *t && brace > 0;			   /*			     */
	     ++t, ++len )			   /*			     */
	{ switch ( *t )				   /*			     */
	  { case '\\': if ( *(t+1) ) ++t; break;   /* ignore \{ \} etc	     */
	    case '{': ++brace; break;		   /*			     */
	    case '}': brace--; break;		   /*			     */
	  }					   /*			     */
	}					   /*			     */
	if ( *t ) { end_c = *t; *t = '\0'; }	   /* save char and mark end.*/
	else	  { end_c = *t; }		   /*			     */
	break;					   /*			     */
      default:					   /* Now we should have a   */
	while ( is_allowed(*t) ) ++t;		   /*	SYMBOL		     */
	end_c = *t; *t = '\0';			   /*			     */
	s = SymbolValue(get_item(symbol(s),	   /*                        */
				 symbol_type));	   /*			     */
	len = strlen((char*)s);			   /*			     */
    }						   /*			     */
						   /* Now s is a single	     */
						   /*  string to print.	     */
						   /* t points to the closing*/
						   /*  '\0' of s	     */
						   /* end_c is the old *t    */
    while ( *s )				   /*			     */
    { if ( len + (first?0:3) <= rsc_linelen - column)/* Is there enough space*/
      { if ( !first ) PUTS(" # ");	   	   /* Maybe add separator    */
	puts_in(s, align, fct);			   /* write it out	     */
	s = t;					   /* and we are done	     */
      }						   /*			     */
      else if ( !first )			   /* If sth has been before */
      { puts_in((String)"\n# ", align - 2, fct);   /*  start a new line	     */
	first = true;				   /*			     */
      }						   /* Now we have to break   */
      else					   /*  a single entry	     */
      { Uchar  save_c;			   	   /*                        */
	String save_ptr,		   	   /*                        */
	       ptr;			   	   /*			     */
						   /*			     */
        if ( 0 <= rsc_linelen - column )	   /*                        */
	  save_ptr = s + rsc_linelen - column;	   /* Potential end	     */
	else					   /*                        */
	  save_ptr = s;				   /*                        */
 						   /*                        */
	for ( ptr = s;				   /* Search next newline    */
	      ptr < save_ptr && *ptr != '\n';	   /*  or end of region      */
	      ptr++ ) {}			   /*                        */
 						   /*                        */
	if ( *ptr == '\n' )			   /*                        */
	{ save_ptr = ptr;			   /*                        */
	  *save_ptr = '\0';	   		   /* Save and mark end.     */
	  puts_in(s, align, fct);		   /*                        */
	  NL;					   /*                        */
	  indent(align,fct);	   		   /*			     */
	  *save_ptr = '\n';			   /* Restore end	     */
	  len += s - save_ptr - 1;		   /* Update the length	     */
	  s = save_ptr + 1;			   /*			     */
	}					   /*                        */
	else					   /*                        */
	{					   /*                        */
	  while ( save_ptr != s && *save_ptr != ' ' )/*                      */
	  { save_ptr--; }			   /* Find a  SPC  backward  */
	  					   /*			     */
	  if ( save_ptr == s  )			   /* If no SPC found then   */
	  { while ( *save_ptr && *save_ptr != ' ' )/*  search one forward.   */
	    { save_ptr++; }	   		   /*                        */
	  }					   /*                        */
	  len += s - save_ptr;			   /* Update the length	     */
	  save_c = *save_ptr; *save_ptr = '\0';	   /* Save and mark end.     */
	  puts_in(s, align, fct);		   /*                        */
	  if (save_c != 0)			   /*                        */
	  { NL;					   /*                        */
	    indent(align, fct);	   		   /*			     */
	  }					   /*                        */
	  *save_ptr = save_c;			   /* Restore end	     */
	  s = save_ptr;	   			   /*			     */
	  while ( is_space(*s) ) { s++; len--; }   /* Skip spaces	     */
	}					   /*                        */
      }						   /*			     */
    }						   /*			     */
    *t = end_c;					   /* Restore the end	     */
						   /*			     */
    while ( *t && *t != '#' ) ++t;		   /* Search next #	     */
    if ( *t ) ++t;				   /* Skip beyond the #	     */
    while ( is_space(*t) ) ++t;			   /* Ignore following spaces*/
    first = false;				   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	print_equation()
** Purpose:	Print something of the form  s = t 
**		If desired it can be indented. t is broken if it doesn't fit
**		in one line.
** Arguments:
**	pre	string to be printed before s.
**	s	left hand side
**	t	right hand side
**	align	target column. If negative no indentation is performed.
**	fct	function to use for writing a character.
** Returns:	nothing
**___________________________________________________'			     */
static void print_equation(pre, lhs, rhs, align, fct)/*			     */
  String pre;					   /*                        */
  Symbol lhs;				   	   /*			     */
  Symbol rhs;				   	   /*			     */
  int  align;				   	   /*			     */
  int (*fct)_ARG((int));			   /*                        */
{						   /*			     */
  if ( align >= 0 ) indent(rsc_indent, fct);	   /*			     */
						   /*			     */
  PUTS(pre);		   			   /*			     */
  PUTS(SymbolValue(get_item(lhs, symbol_type)));   /*			     */
						   /*			     */
  if ( align < 0 ) {}				   /*			     */
  else if ( rsc_print_we && column > align - 2 )   /*                        */
  { PUTC(' '); }				   /*                        */
  else if ( rsc_eq_right )			   /*                        */
  { indent(align - ((rsc_print_we || !align_auto) ? 2 : 1), fct); }/*	     */
  else if ( column < align || rsc_print_we )	   /*                        */
  { PUTC(' '); }	   			   /*                        */
						   /*			     */
  PUTC('=');		   			   /*                        */
  if ( rsc_print_we && column > align )
  { PUTC(' '); }	   			   /*                        */
  line_breaking(SymbolValue(rhs), align, fct);     /*			     */
}						   /*------------------------*/

 static FILE * ofile = NULL;

/*-----------------------------------------------------------------------------
** Function:	fput_char()
** Purpose:	Output function which places the character on the |ofile| 
**		stream.
** Arguments:
**	c	Character to print.
** Returns:	The return status of |fputc()|.
**___________________________________________________			     */
static int fput_char(c)				   /*                        */
  int c;					   /*                        */
{ return fputc(c, ofile);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	fput_record()
** Purpose:	Format and print a complete record onto a given stream.
**		for further details see |put_record()|.
** Arguments:
**	file	Stream to print onto.
**	db	Database containing the record.
**	rec	Record to print.
**	start	Initial string used before the type. Should be "@" normally.
** Returns:	nothing
**___________________________________________________			     */
void fput_record(file, rec, db, start)	   	   /*			     */
  FILE	 *file;			   		   /*                        */
  DB	 db;			   		   /*                        */
  Record rec;			   		   /* record to print	     */
  String start;		   	   	   	   /* initial string = "@"   */
{						   /*                        */
  ofile = file;					   /*                        */
  put_record(fput_char, rec, db, start);	   /*                        */
}						   /*------------------------*/

 static StringBuffer *osb = NULL;

/*-----------------------------------------------------------------------------
** Function:	sput_char()
** Purpose:	Output function which places the character on the |osb| 
**		string buffer.
** Arguments:
**	c	Character to print.
** Returns:	The return status of |fputc()|.
**___________________________________________________			     */
static int sput_char(c)				   /*                        */
  int c;					   /*                        */
{ return sbputchar(c, osb);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sput_record()
** Purpose:	Format and print a complete record into a string and return it.
**		The string returned points to static memory which is
**		reused upon the next invocation of this function.
** Arguments:
**	file	Stream to print onto.
**	db	Database containing the record.
**	rec	Record to print.
**	start	Initial string used before the type. Should be "@" normally.
** Returns:	The string containing the printed representation.
**___________________________________________________			     */
char * sput_record(rec, db, start)	   	   /*			     */
  DB	 db;			   		   /*                        */
  Record rec;			   		   /* record to print	     */
  String start;		   	   	   	   /* initial string = "@"   */
{						   /*                        */
  if ( osb == NULL ) osb = sbopen();		   /*                        */
  sbrewind(osb);				   /*                        */
  put_record(sput_char, rec, db, start);	   /*                        */
  return sbflush(osb);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	put_record()
** Purpose:	Format and print a complete record.
**		The record type and several resources are taken into
**		account. The following external variables (from
**		|rsc.c|) are taken into account:
**		\begin{description}
**		\item[rsc\_parentheses] If this boolean variable is
**		  |true| then |(| and |)| are used to delimit the
**		  record. Otherwise |{| and |}| are used.
**		\item[rsc\_col\_p] This integer variable controls the
**		  indentation of preamble records.
**		\item[rsc\_col\_s] This integer variable controls the
**		  indentation of string records.
**		\item[rsc\_expand\_macros] If this boolean variable is
**		  set then macros are expanded before the record is
**		  printed. This does not effect the internal
**		  representation. 
**		\item[rsc\_col] This integer variable controls the
**		  indentation of normal records.
**		\item[rsc\_col\_key] This integer variable controls the
**		  indentation of the key in a normal record.
**		\item[rsc\_newlines] This integer variable controls
**		  the number of newlines printed after a normal record.
**		\item[rsc\_linelen] This integer variable controls
**		  the length of the line. The line breaking algorithm
**		  is applied if this column is about to be violated.
**		\item[rsc\_indent] This integer variable controls the
**		  indentation of equations.
**		\item[rsc\_eq\_right] This boolean variable controls
**		  the alignment of the |=| in equations. It it is set
**		  then the equality sign is flushed right. Otherwise it
**		  is flushed left.
**		\end{description}
**
**		The field in the record are sorted with
**		|sort_record()| before they are printed.
**
**		In normal records all fields not starting with an
**		allowed character are ignored. Thus it is possible to
**		store private and invisible information in a
**		field. Simply start the field name with an not allowed
**		character like |%|.
** Arguments:
**	fct	function to use for writing a character.
**	db	Database containing the record.
**	rec	Record to print.
**	start	Initial string used before the type. Should be "@" normally.
** Returns:	nothing
**___________________________________________________			     */
void put_record(fct, rec, db, start)		   /*                        */
  int	       (*fct)_ARG((int));		   /*                        */
  Record       rec;				   /*                        */
  DB	       db;				   /*                        */
  String       start;		   	   	   /* initial string = "@"   */
{ Symbol       *hp;			   	   /* heap pointer	     */
  unsigned int i;			   	   /*			     */
  char	       open_brace, close_brace;		   /*			     */
  static int   first = 1;			   /*                        */
  						   /*                        */
  sort_record(rec);				   /*                        */
 						   /*                        */
  hp = RecordHeap(rec);				   /*			     */
  if ( rsc_no_nl && first ) { first = 0; }	   /*                        */
  else if ( IsNormalRecord(RecordType(rec)) ) { NL; }/*			     */
 						   /*                        */
  if ( *SymbolValue(RecordComment(rec)) )	   /*                        */
  { PUTS(SymbolValue(RecordComment(rec)));	   /*                        */
    NL;						   /*                        */
  }						   /*                        */
 						   /*                        */
  if (rsc_parentheses)			   	   /*                        */
  { open_brace  = '(';			   	   /*                        */
    close_brace = ')';			   	   /*                        */
  }						   /*                        */
  else						   /*                        */
  { open_brace  = '{';			   	   /*                        */
    close_brace = '}';			   	   /*                        */
  }						   /*                        */
 						   /*                        */
  switch (RecordType(rec))			   /*			     */
  { case BIB_COMMENT:				   /*			     */
#ifdef OLD
      indent(rsc_col_c, fct);			   /*			     */
      PUTS(*hp);				   /*			     */
      PUTC(' ');				   /*                        */
      NL;				   	   /*			     */
#endif
      break;					   /*			     */
    case BIB_PREAMBLE:				   /*			     */
      PUTS(start);				   /*			     */
      PUTS(SymbolValue(EntryName(RecordType(rec))));/*			     */
      PUTC(open_brace);				   /*			     */
      indent(rsc_col_p,fct);			   /*			     */
      line_breaking(SymbolValue(*hp),		   /*                        */
		    rsc_col_p,			   /*                        */
		    fct);	   		   /*			     */
      PUTC(' ');				   /*                        */
      PUTC(close_brace);			   /*                        */
      NL;				   	   /*			     */
      break;					   /*			     */
    case BIB_STRING:				   /*			     */
      PUTS(start);				   /*			     */
      PUTS(SymbolValue(EntryName(RecordType(rec))));/*			     */
      PUTC(open_brace);				   /*			     */
      print_equation(s_empty,			   /*                        */
		     *hp,		   	   /*                        */
		     *(hp+1),	   		   /*                        */
		     rsc_col_s,			   /*                        */
		     fct);			   /*		             */
      PUTC(' ');				   /*                        */
      PUTC(close_brace);			   /*                        */
      NL;				   	   /*			     */
      break;					   /*			     */
    case BIB_ALIAS:				   /*			     */
      PUTS(start);				   /*			     */
      PUTS(SymbolValue(EntryName(RecordType(rec))));/*			     */
      PUTC(open_brace);				   /*			     */
      print_equation(s_empty,			   /*                        */
		     *hp,		   	   /*                        */
		     *(hp+1),	   		   /*                        */
		     rsc_col_s,			   /*                        */
		     fct);			   /*		             */
      PUTC(' ');				   /*                        */
      PUTC(close_brace);			   /*                        */
      NL;				   	   /*			     */
      break;					   /*			     */
    case BIB_INCLUDE:				   /*			     */
      PUTS(start);				   /*			     */
      PUTS(SymbolValue(EntryName(RecordType(rec))));/*			     */
      PUTC(open_brace);				   /*			     */
      PUTS(SymbolValue(*RecordHeap(rec)));	   /*			     */
      PUTC(close_brace);			   /*                        */
      NL;				   	   /*			     */
      break;					   /*			     */
    case BIB_MODIFY:				   /*			     */
    default:					   /*			     */
 						   /*                        */
      if (RecordType(rec) == type_xdata		   /*                        */
	  && rsc_expand_xdata) return;		   /*                        */
 						   /*                        */
      PUTS(start);				   /*			     */
      PUTS(SymbolValue(EntryName(RecordType(rec))));/*			     */
      PUTC(open_brace);				   /*			     */
      { String comma1 = s_empty,		   /*                        */
	       comma2 = (String)",";		   /*                        */
 						   /*                        */
        if (rsc_print_ce)			   /*                        */
	{ comma1 = comma2;			   /*                        */
	  comma2 = s_empty;			   /*                        */
	}					   /*                        */
 						   /*                        */
 	if (align_auto)				   /*                        */
	{ adjust_align(rec);			   /*                        */
	}					   /*                        */
 						   /*                        */
        for ( i = RecordFree(rec); i > 0; i -= 2 ) /*			     */
	{		   			   /* No deleted or          */
	  if (*hp && is_allowed(*SymbolValue(*hp)))/*   private entry        */
	  { 					   /*                        */
	    if ( *(hp+1) )			   /* If equation	     */
	    { PUTS(comma1);			   /*                        */
	      NL;			   	   /*                        */
	      print_equation(comma2,		   /*                        */
			     *hp,	   	   /*                        */
			     (rsc_expand_macros	   /*                        */
			      ? expand_rhs(*(hp+1),/*                        */
					   (rsc_braces/*                     */
					    ? sym_open_brace/*               */
					    : sym_double_quote),/*           */
					   (rsc_braces/*                     */
					    ? sym_close_brace/*              */
					    : sym_double_quote),/*           */
					   db,	   /*                        */
					   false)  /*                        */
			      : *(hp+1) ),	   /*                        */
			     align_value,	   /*                        */
			     fct);		   /*                        */
	    }					   /*			     */
	    else				   /* Otherwise print a key  */
	    { indent(rsc_col_key, fct);		   /*			     */
	      PUTS(SymbolValue(get_key(*hp)));	   /*			     */
	    }					   /*			     */
	  }					   /*			     */
	  hp += 2;				   /* Goto next pair.	     */
	}					   /*                        */
      }						   /*			     */
      if (rsc_print_tc) { PUTC(','); }		   /*                        */
      NL;					   /*                        */
      PUTC(close_brace);	   	   	   /*                        */
      for ( i = rsc_newlines; i > 0; --i ) { NL; } /*                        */
  }						   /*			     */
}						   /*------------------------*/
