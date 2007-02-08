/******************************************************************************
** $Id: error.c,v 1.5 2007-02-08 19:47:16 gene Exp $
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

 extern int rsc_quiet;

/*---------------------------------------------------------------------------*/

 char  *err_format = "*** BibTool: %s";
 Uchar *err_point  = (Uchar*)".";
 Uchar *err_oom    = (Uchar*)"Out of memory for ";

 FILE * err_file = NULL;

/*-----------------------------------------------------------------------------
** Function:	init_error()
** Type:	void
** Purpose:	
**		
** Arguments:
**		
** Returns:	nothing
**___________________________________________________			     */
void init_error(file)				   /*                        */
  FILE * file;					   /*                        */
{ err_file = file;
}						   /*------------------------*/


#define ErrNL		(void)fputc('\n',err_file)
#define ErrChar(C)	(void)fputc(C,err_file)
#define ErrS(S)		(void)fputs(S,err_file)

/*-----------------------------------------------------------------------------
** Function:	error()
** Purpose:	This is the generic error printing routine.
**		It prints an error message together with an optional filename,
**		the line number, the errorous line and a pointer to the
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
**		be suppresed.
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
**		routine calles |exit(-1)| at the end. This implicitly
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
void error(type,s1,s2,s3,line,err_pos,line_no,fname)/*			     */
  int	  type;			   	   	   /* defined in error.h     */
  Uchar	  *s1;			   	   	   /* 1st error message	     */
  Uchar	  *s2;			   	   	   /* 2nd error message	     */
  Uchar	  *s3;			   	   	   /* 3rd error message	     */
  Uchar   *line;				   /* line_no string.	     */
  Uchar   *err_pos;				   /* error position in line */
  int	  line_no;		   	   	   /* line number	     */
  char	  *fname;		   	   	   /* file name		     */
{						   /*			     */
  if ( (type&ERR_ERROR)==0 && rsc_quiet ) return;  /* anything less than an  */
						   /*  error is ignored.     */
  ErrNL;					   /*			     */
  if ( (type&ERR_POINT) && line != NULL )	   /*			     */
  { ErrS((char*)line);				   /* print the eror line.   */
    if ( line[strlen((char*)line)-1] != '\n' ) ErrNL;/*			     */
    for ( ; line<err_pos; ++line ) ErrChar('_');   /*  and a pointer to the  */
    ErrChar('^'); ErrNL;			   /*  error position.	     */
  }						   /*			     */
						   /*			     */
  ErrS("*** BibTool");				   /*                        */
  if	  ( type&ERR_ERROR ) ErrS(" ERROR"  );	   /*		             */
  else if ( type&ERR_WARN  ) ErrS(" WARNING");	   /*		             */
  ErrS(": ");					   /*                        */
  if ( type&ERR_FILE )			   	   /*			     */
  { (void)fprintf(err_file,			   /*			     */
		  " (line %d in %s): ",		   /*			     */
		  line_no,			   /*			     */
		  fname );			   /*			     */
  }						   /*			     */
  if ( s1 ) { ErrS((char*)s1); }		   /*			     */
  if ( s2 ) { ErrS((char*)s2); }		   /*			     */
  if ( s3 ) { ErrS((char*)s3); }		   /*			     */
  ErrNL;					   /*			     */
  if ( type&ERR_EXIT ) exit(-1);		   /*			     */
}						   /*------------------------*/
