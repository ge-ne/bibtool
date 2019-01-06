/*** error.c ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2019 Gerd Neugebauer
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
**	To ensure a consistent appearence of error messages \BibTool{}
**	provides one generic error reporting routine. This routine is
**	controlled by several arguments to allow maximum flexibility.
**
**	Usually it is awkward to fill out all those arguments. To
**	avoid this trouble the header file |error.h| provides some
**	macros which cover the most common situation and hide
**	unneccesary details.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/error.h>

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

 extern bool rsc_quiet;

/*---------------------------------------------------------------------------*/

 char  *err_format = "*** BibTool: %s";
 String err_point  = (String)".";
 String err_oom    = (String)"Out of memory for ";

 FILE * err_file = NULL;

/*-----------------------------------------------------------------------------
** Function:	init_error()
** Type:	void
** Purpose:	
**		Initialize the error reporting.
** Arguments:
**	file	the output file to write error messages to
** Returns:	nothing
**___________________________________________________			     */
void init_error(file)				   /*                        */
  FILE * file;					   /*                        */
{						   /*                        */
  err_file = file;				   /*                        */
}						   /*------------------------*/

#define ErrNL		(void)fputc('\n',err_file)
#define ErrChar(C)	(void)fputc(C,err_file)
#define ErrS(S)		(void)fputs(S,err_file)

/*-----------------------------------------------------------------------------
** Function:	err_location()
** Type:	void
** Purpose:	Print the error location to the error stream.
**		
** Arguments:
**	lineno	the line number
**	fname	the file name
**	s1	the optional postfix string
** Returns:	nothing
**___________________________________________________			     */
void err_location(lineno,fname,s1)		   /*                        */
  int    lineno;				   /*                        */
  String fname;					   /*                        */
  char*  s1;					   /*                        */
{						   /*                        */
  (void)fprintf(err_file,			   /*			     */
		" (line %d in %s)",		   /*			     */
		lineno,				   /*			     */
		*fname ? (char*)fname : "<STDIN>");/*			     */
  if ( s1 ) { ErrS(s1); }		   	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	error()
** Purpose:	This is the generic error printing routine.
**		It prints an error message together with an optional filename,
**		the line number, the erroneous line and a pointer to the
**		problematic position.
**
**		All parts of an error message are optional and can be
**		suppressed under certain conditions.  The error type
**		determines which parts are actually shown. It is a
**		boolean combination of the following flags which are
**		defined in |error.h|:
**		\begin{description}
**		\item[ERR\_ERROR] If this bit is set then the error
**		message is marked as ``error''. The flag |ERR_WARNING|
**		is ignored in this case. This kind of messages can not
**		be suppressed.
**		\item[ERR\_WARNING]  If this bit is set and
**		|ERR_ERROR| is not set then the error message is
**		marked as ``warning''. |ERR_WARNING| is ignored 
**		in this case.
**		\item[ERR\_POINT] If this bit is set then the line |line| is
**		shown together with a pointer to the byte pointed to
**		by |err_pos|. Otherwise the line is not shown.
**		\item[ERR\_FILE] If this bit is set then the name of
**		the file |file_name| and the line number |lineno| are
**		shown. Otherwise the file name and the line number are
**		suppressed.
**		\item[ERR\_EXIT] If this bit is set then the error
**		routine calls |exit(-1)| at the end. This implicitly
**		sets the |ERR_ERROR| bit as well.
**		\end{description}
**
**		The error message itself can be split in up to three
**		strings |s1|, |s2|, and |s3|. Those strings are
**		concatenated. They can also be |NULL| in which case
**		they are ignored.
**
**		The error message is written to the stream determined
**		by the variable |err_file|. This variable refers to
**		the |stderr| stream initially but can be redirected to
**		any other destination.
**
** Arguments:
**	type	Error type: boolean combination of the error bits as
**		defined in |error.h|. 
**	s1	1$^\mathrm{st}$ error message or |NULL|.
**	s2	2$^\mathrm{nd}$ error message or |NULL|.
**	s3	3$^\mathrm{rd}$ error message or |NULL|.
**	line	Current line when error occured (for reading errors).
**	err_pos	Error position in line |line|.
**	line_no	The line number where the error occurred.
**	fname	The file name where the error occurred.
** Returns:	nothing
**___________________________________________________			     */
void error(type, s1, s2, s3, line, err_pos, line_no, fname)/*		     */
  int	  type;			   	   	   /* defined in error.h     */
  String  s1;			   	   	   /* 1st error message	     */
  String  s2;			   	   	   /* 2nd error message	     */
  String  s3;			   	   	   /* 3rd error message	     */
  String  line;				   	   /* line_no string.	     */
  String  err_pos;				   /* error position in line */
  int	  line_no;		   	   	   /* line number	     */
  Symbol  fname;		   	   	   /* file name		     */
{						   /*			     */
  if ( (type&ERR_WARNING)			   /* anything less than an  */
       && rsc_quiet ) return;			   /*  error is ignored.     */
						   /*			     */
  if (!(type&ERR_NO_NL)) { ErrNL; }		   /*			     */
  if ( (type&ERR_POINT) && line != NULL )	   /*			     */
  { ErrS((char*)line);				   /* print the error line.  */
    if (line[strlen((char*)line)-1] != '\n') ErrNL;/*			     */
    for ( ; line < err_pos; ++line ) ErrChar('_'); /*  and a pointer to the  */
    ErrChar('^'); ErrNL;			   /*  error position.	     */
  }						   /*			     */
						   /*			     */
  ErrS("*** BibTool");				   /*                        */
  if	  ( type&ERR_ERROR ) ErrS(" ERROR"  );	   /*		             */
  else if ( type&ERR_WARN  ) ErrS(" WARNING");	   /*		             */
  if (type&ERR_FILE)			   	   /*			     */
  { err_location(line_no,fname, NULL); }	   /*			     */
  ErrS(": ");					   /*                        */
  if ( s1 ) { ErrS((char*)s1); }		   /*			     */
  if ( s2 ) { ErrS((char*)s2); }		   /*			     */
  if ( s3 ) { ErrS((char*)s3); }		   /*			     */
  if (!(type&ERR_NO_NL)) { ErrNL; }		   /*			     */
  if ( type&ERR_EXIT ) exit(-1);		   /*			     */
}						   /*------------------------*/
