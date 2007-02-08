/******************************************************************************
** $Id: print.c,v 1.5 2007-02-08 19:47:16 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2004 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
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
 char * sput_record _ARG((Record rec,DB db,Uchar *start));/* print.c          */
 static int fput_char _ARG((int c));		   /* print.c                */
 static int sput_char _ARG((int c));		   /* print.c                */
 static void indent _ARG((int col,int (*fct)_ARG((int))));/* print.c         */
 static void line_breaking _ARG((char *t,int align,int (*fct)_ARG((int))));/* print.c*/
 static void print_equation _ARG((Uchar *pre,Uchar *s,Uchar *t,int align,int (*fct)_ARG((int))));/* print.c*/
 static void puts_in _ARG((char *s,int in,int (*fct)_ARG((int))));/* print.c */
 void fput_record _ARG((FILE *file,Record rec,DB db,Uchar *start));/* print.c*/
 void put_record _ARG((int (*fct)_ARG((int)),Record rec,DB db,Uchar *start));/* print.c*/
 void set_key_type _ARG((char * s));		   /* print.c                */
 void set_symbol_type _ARG((char * s));		   /* print.c                */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

#define TAB_WIDTH 8

 static int symbol_type = SYMBOL_TYPE_LOWER;

 static char * s_upper = "upper";
 static char * s_lower = "lower";
 static char * s_cased = "cased";

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
**		This function is called from |rsc.c|.
** Arguments:
**	s	String description of the value.
** Returns:	nothing
**___________________________________________________			     */
void set_symbol_type(s)				   /*			     */
  register char * s;				   /*			     */
{ if ( case_cmp(s,s_upper) )			   /*			     */
  { symbol_type = SYMBOL_TYPE_UPPER; }		   /*			     */
  else if ( case_cmp(s,s_cased) )		   /*			     */
  { symbol_type = SYMBOL_TYPE_CASED; }		   /*			     */
  else if ( case_cmp(s,s_lower) )		   /*			     */
  { symbol_type = SYMBOL_TYPE_LOWER; }		   /*			     */
  else						   /*			     */
  { Err("Unknown symbol type ignored.\n"); }	   /*			     */
}						   /*------------------------*/


#ifdef MAYBE_IN_THE_NEXT_RELEASE

 static int key_type = SYMBOL_TYPE_LOWER;

/*-----------------------------------------------------------------------------
** Function*:	set_key_type()
** Purpose:	Wrapper function to set the static variable key_type.
**		This function is called from rsc.c
** Arguments:
**	s	String description of the value.
** Returns:	nothing
**___________________________________________________			     */
void set_key_type(s)				   /*			     */
  register char * s;				   /*			     */
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

						   /*------------------------*/
 static int column = 0;				   /* The current column of  */
						   /*  the output stream is  */
						   /*  kept in this variable.*/

#define NL	(void)(*fct)('\n'),column=0
#define PUTC(C) (void)((*fct)(C),++column)
#define PUTS(S) puts_in(S,0,fct)

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
  register char *s;				   /*			     */
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
        if ( in > 0 ) indent(in,fct);		   /*                        */
        break;  				   /*			     */
      default:	 ++column;			   /*			     */
    }						   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	indent()
** Purpose:	Add spaces or tabs to indent to the given column.
**		the current column is beyond col nothing happens.
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
    { (void)(*fct)(' ');			   /*  write a singe space   */
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
static void line_breaking(t,align,fct)		   /*			     */
  register char *t;				   /* string to print.	     */
  int		align;				   /* alignment column	     */
  int (*fct)_ARG((int));			   /*                        */
{ register char *s;				   /* intermediate pointer   */
  char		end_c;				   /* temp. character.	     */
  int		brace,				   /* brace counter	     */
		len,				   /* length of rem. output  */
		first = TRUE;			   /* indicator for #	     */
						   /*			     */
  while ( is_space(*t) ) ++t;			   /* skip leading spaces    */
						   /*			     */
  indent(align,fct);				   /* goto alignment column  */
						   /*			     */
  while ( *t )					   /* as long as sth to print*/
  { s = t;					   /*			     */
						   /*			     */
    switch( *t )				   /*			     */
    { case '"':					   /* QUOTED PART	     */
	for ( len=2,++t;			   /*			     */
	     *t && *t != '\"';			   /* Search terminating "   */
	     ++t,++len )			   /*			     */
	{ if ( *t == '\\' && *(t+1) != '\0' )	   /* skip over quoted and   */
	  { ++t; ++len; }			   /*  similar constructs.   */
	}					   /*			     */
	if ( *t ) ++t;				   /* skip after end, if poss*/
	if ( *t ) { end_c = *++t; *t = '\0'; }	   /* save char and mark end.*/
	else	  { end_c = *t; }		   /*			     */
	break;					   /*			     */
      case '{':					   /* BRACED PART	     */
	brace = 1;				   /*			     */
	for ( len=2,++t;			   /* find matching brace.   */
	     *t && brace>0;			   /*			     */
	     ++t,++len )			   /*			     */
	{ switch ( *t )				   /*			     */
	  { case '\\': if ( *(t+1) ) ++t; break;   /* ignore \{ \} etc	     */
	    case '{': ++brace; break;		   /*			     */
	    case '}': brace--; break;		   /*			     */
	  }					   /*			     */
	}					   /*			     */
	if ( *t ) { end_c = *++t; *t = '\0'; }	   /* save char and mark end.*/
	else	  { end_c = *t; }		   /*			     */
	break;					   /*			     */
      default:					   /* Now we should have a   */
	while ( is_allowed(*t) ) ++t;		   /*	SYMBOL		     */
	end_c = *t; *t = '\0';			   /*			     */
	s = (char*)get_item(symbol(s),symbol_type);/*			     */
	len = strlen(s);			   /*			     */
    }						   /*			     */
						   /* Now s is a single	     */
						   /*  string to print.	     */
						   /* t points to the closing*/
						   /*  '\0' of s	     */
						   /* end_c is the old *t    */
    while ( *s )				   /*			     */
    { if ( len + (first?0:3) <= rsc_linelen - column)/* Is there enough space*/
      { if ( !first ) PUTS(" # ");		   /* Maybe add separator    */
	puts_in(s,align,fct);			   /* write it out	     */
	s = t;					   /* and we are done	     */
      }						   /*			     */
      else if ( !first )			   /* If sth has been before */
      { puts_in("\n# ",align-2,fct);	   	   /*  start a new line	     */
	first = TRUE;				   /*			     */
      }						   /* Now we have to break   */
      else					   /*  a single entry	     */
      { char save_c,				   /*                        */
	     *save_ptr,				   /*                        */
	     *ptr;			   	   /*			     */
						   /*			     */
        if ( 0 <= rsc_linelen - column )	   /*                        */
	  save_ptr = s + rsc_linelen - column;	   /* Potential end	     */
	else					   /*                        */
	  save_ptr = s;				   /*                        */
 						   /*                        */
	for(ptr=s;				   /* Search next newline    */
	    ptr <= save_ptr && *ptr != '\n';	   /*  or end of region      */
	    ptr++) {}				   /*                        */
 						   /*                        */
	if ( *ptr == '\n' )			   /*                        */
	{ save_ptr = ptr;			   /*                        */
	  *save_ptr = '\0';	   		   /* Save and mark end.     */
	  puts_in(s,align,fct);			   /*                        */
	  NL;					   /*                        */
	  indent(align,fct);	   		   /*			     */
	  *save_ptr = '\n';			   /* Restore end	     */
	  len += s - save_ptr - 1;		   /* Update the length	     */
	  s = save_ptr+1;			   /*			     */
	}					   /*                        */
	else					   /*                        */
	{					   /*                        */
	  while ( save_ptr != s && *save_ptr != ' ' )/*                      */
	  { save_ptr--; }			   /* Find a  SPC  backward  */
	  					   /*			     */
	  if ( save_ptr == s  )			   /* If no SPC found then   */
	  { while ( *save_ptr && *save_ptr != ' ' )/*  search one forward.   */
	    { ++save_ptr; }	   		   /*                        */
	  }					   /*                        */
	  len += s - save_ptr;			   /* Update the length	     */
	  save_c = *save_ptr; *save_ptr = '\0';	   /* Save and mark end.     */
	  puts_in(s,align,fct);			   /*                        */
	  NL;					   /*                        */
	  indent(align,fct);	   		   /*			     */
	  *save_ptr = save_c;			   /* Restore end	     */
	  s = save_ptr;	   			   /*			     */
	  while ( is_space(*s) ) { ++s; len--; }   /* Skip spaces	     */
	}					   /*                        */
      }						   /*			     */
    }						   /*			     */
    *t = end_c;					   /* Restore the end	     */
						   /*			     */
    while ( *t && *t != '#' ) ++t;		   /* Search next #	     */
    if ( *t ) ++t;				   /* Skip beyond the #	     */
    while ( is_space(*t) ) ++t;			   /* Ignore following spaces*/
    first = FALSE;				   /*			     */
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
static void print_equation(pre,s,t,align,fct)	   /*			     */
  Uchar *pre;					   /*                        */
  Uchar *s;				   	   /*			     */
  Uchar *t;				   	   /*			     */
  int  align;				   	   /*			     */
  int (*fct)_ARG((int));			   /*                        */
{						   /*			     */
  if ( align < 0 )				   /*			     */
  { PUTS(pre);		   			   /*			     */
    PUTS(get_item(s,symbol_type));		   /*			     */
    if ( rsc_print_we )				   /*                        */
    { PUTS(" = "); }				   /*                        */
    else					   /*                        */
    { PUTC('='); }				   /*                        */
    PUTS(t);					   /*			     */
  }						   /*			     */
  else						   /*			     */
  { indent(rsc_indent,fct);			   /*			     */
    PUTS(pre);		   			   /*			     */
    PUTS(get_item(s,symbol_type));		   /*			     */
    if ( column>=align-2 && rsc_print_we )	   /*                        */
    { PUTC(' '); }				   /*                        */
    else if ( rsc_eq_right )			   /*                        */
    { indent(align-2,fct); }			   /*			     */
    else if ( column<align || rsc_print_we )	   /*                        */
    { PUTC(' '); }	   			   /*                        */
    PUTC('=');					   /*			     */
    if ( rsc_print_we )	{ PUTC(' '); }		   /*                        */
    line_breaking(t,align,fct);			   /*			     */
  }						   /*			     */
}						   /*------------------------*/

 static FILE * ofile=NULL;

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
{ return fputc(c,ofile);			   /*                        */
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
void fput_record(file,rec,db,start)	   	   /*			     */
  FILE	 *file;			   		   /*                        */
  DB	 db;			   		   /*                        */
  Record rec;			   		   /* record to print	     */
  Uchar	 *start;		   	   	   /* initial string = "@"   */
{						   /*                        */
  ofile = file;					   /*                        */
  put_record(fput_char,rec,db,start);		   /*                        */
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
{ return sbputchar(c,osb);			   /*                        */
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
char * sput_record(rec,db,start)	   	   /*			     */
  DB	 db;			   		   /*                        */
  Record rec;			   		   /* record to print	     */
  Uchar	 *start;		   	   	   /* initial string = "@"   */
{						   /*                        */
  if ( osb == NULL ) osb = sbopen();		   /*                        */
  sbrewind(osb);				   /*                        */
  put_record(sput_char,rec,db,start);		   /*                        */
  return sbflush(osb);
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	put_record()
** Purpose:	Format and print a complete record.
**		The record type and several resources are taken into
**		account. The following external variables (from
**		|rsc.c|) are taken into account:
**		\begin{description}
**		\item[rsc\_parentheses] If this boolean variable is
**		  |TRUE| then |(| and |)| are used to delimit the
**		  record. Otherwise |{| and |}| are used.
**		\item[rsc\_col\_p] This integer variable controlls the
**		  indentation of preamble records.
**		\item[rsc\_col\_s] This integer variable controlls the
**		  indentation of string records.
**
**		\item[rsc\_expand\_macros] If this boolean variable is
**		  set then macros are expanded before the record is
**		  printed. This does not effect the internal
**		  representation. 
**		\item[rsc\_col] This integer variable controlls the
**		  indentation of normal records.
**		\item[rsc\_col\_key] This integer variable controlls the
**		  indentation of the key in a normal record.
**		\item[rsc\_newlines] This integer variable controlls
**		  the number of newlines printed after a normal record.
**
**		\item[rsc\_linelen] This integer variable controlls
**		  the length of the line. The line breaking algorithm
**		  is applied if this column is about to be violated.
**		\item[rsc\_indent] This integer variable controlls the
**		  indentation of equations.
**		\item[rsc\_eq\_right] This boolean variable controlls
**		  the alignment of the |=| in equations. It it is set
**		  then the equality sign is flused right. Otherwise it
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
void put_record(fct,rec,db,start)		   /*                        */
  int	       (*fct)_ARG((int));		   /*                        */
  Record       rec;				   /*                        */
  DB	       db;				   /*                        */
  Uchar	       *start;		   	   	   /* initial string = "@"   */
{ Uchar	       **hp;			   	   /* heap pointer	     */
  unsigned int i;			   	   /*			     */
  char	       open_brace, close_brace;		   /*			     */
  static int   first = 1;
  						   /*                        */
  sort_record(rec);				   /*                        */
 						   /*                        */
  hp = RecordHeap(rec);				   /*			     */
  if ( rsc_no_nl && first ) { first = 0; }
  else if ( IsNormalRecord(RecordType(rec)) ) { NL; }/*			     */
 						   /*                        */
  if ( *RecordComment(rec) )		   	   /*                        */
  { PUTS(RecordComment(rec));			   /*                        */
    NL;						   /*                        */
  }						   /*                        */
 						   /*                        */
  if ( rsc_parentheses )			   /*                        */
  { open_brace  = '(';			   	   /*                        */
    close_brace = ')';			   	   /*                        */
  }						   /*                        */
  else						   /*                        */
  { open_brace  = '{';			   	   /*                        */
    close_brace = '}';			   	   /*                        */
  }						   /*                        */
 						   /*                        */
  switch ( RecordType(rec) )			   /*			     */
  { case BIB_COMMENT:				   /*			     */
#ifdef OLD
      indent(rsc_col_c,fct);			   /*			     */
      PUTS(*hp);				   /*			     */
      PUTC(' ');				   /*                        */
      NL;				   	   /*			     */
#endif
      break;					   /*			     */
    case BIB_PREAMBLE:				   /*			     */
      PUTS(start);				   /*			     */
      PUTS(EntryName(RecordType(rec)));	   	   /*			     */
      PUTC(open_brace);				   /*			     */
      indent(rsc_col_p,fct);			   /*			     */
      line_breaking(*hp,rsc_col_p,fct);		   /*			     */
      PUTC(' ');				   /*                        */
      PUTC(close_brace);			   /*                        */
      NL;				   	   /*			     */
      break;					   /*			     */
    case BIB_STRING:				   /*			     */
      PUTS(start);				   /*			     */
      PUTS(EntryName(RecordType(rec)));	   	   /*			     */
      PUTC(open_brace);				   /*			     */
      print_equation(sym_empty,*hp,*(hp+1),rsc_col_s,fct);/*		     */
      PUTC(' ');				   /*                        */
      PUTC(close_brace);			   /*                        */
      NL;				   	   /*			     */
      break;					   /*			     */
    case BIB_ALIAS:				   /*			     */
      PUTS(start);				   /*			     */
      PUTS(EntryName(RecordType(rec)));	   	   /*			     */
      PUTC(open_brace);				   /*			     */
      print_equation(sym_empty,*hp,*(hp+1),rsc_col_s,fct);/*		     */
      PUTC(' ');				   /*                        */
      PUTC(close_brace);			   /*                        */
      NL;				   	   /*			     */
      break;					   /*			     */
    case BIB_MODIFY:				   /*			     */
    case BIB_INCLUDE:				   /*			     */
      NL;				   	   /*			     */
      break;					   /*			     */
    default:					   /*			     */
      PUTS(start);				   /*			     */
      PUTS(EntryName(RecordType(rec)));	   	   /*			     */
      PUTC(open_brace);				   /*			     */
      { Uchar *comma1 = sym_empty,		   /*                        */
	      *comma2 = (Uchar*)",";		   /*                        */
 						   /*                        */
        if (rsc_print_ce)			   /*                        */
	{ comma1 = comma2;			   /*                        */
	  comma2 = sym_empty;			   /*                        */
	}					   /*                        */
 						   /*                        */
        for ( i=RecordFree(rec); i>0; i-=2 )	   /*			     */
	{		   			   /* No deleted or          */
	  if ( *hp && is_allowed(**hp) )	   /*   private entry        */
	  { 					   /*                        */
	    if ( *(hp+1) )			   /* If equation	     */
	    { PUTS(comma1);			   /*                        */
	      NL;			   	   /*                        */
	      print_equation(comma2,		   /*                        */
			     *hp,		   /*                        */
			     (rsc_expand_macros	   /*                        */
			      ? expand_rhs(*(hp+1),/*                        */
					   (rsc_braces?"{":"\""),/*          */
					   (rsc_braces?"}":"\""),/*          */
					   db)	   /*                        */
			      : *(hp+1) ),	   /*                        */
			     rsc_col,		   /*                        */
			     fct);		   /*                        */
	    }					   /*			     */
	    else				   /* Otherwise print a key  */
	    { indent(rsc_col_key,fct);		   /*			     */
	      PUTS(get_key_name(*hp));      	   /*			     */
	    }					   /*			     */
	  }					   /*			     */
	  hp += 2;				   /* Goto next pair.	     */
	}					   /*                        */
      }						   /*			     */
      NL;					   /*                        */
      PUTC(close_brace);	   	   	   /*                        */
      for ( i=rsc_newlines; i>0; --i ) { NL; }	   /*                        */
  }						   /*			     */
}						   /*------------------------*/
