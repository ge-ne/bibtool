/*** sbuffer.h ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This header file makes accessible the functions to treat
**	strings like streams In addition to the functions defined in
**	|sbuffer.c| one macro is defined here.
**
******************************************************************************/

#ifndef  sbputchar

 typedef struct 
 { char *sb__string;
   int  sb__size;
   int  sb__ptr;
 } StringBuffer;

#define StringBufferIncrement 256


 extern StringBuffer* sbopen(
#ifdef __STDC__
		       void
#endif
		      );
 extern int     sbclose(
#ifdef __STDC__
		       StringBuffer*
#endif
		      );
 extern int      sbputs(
#ifdef __STDC__
		       char *,
		       StringBuffer*
#endif
		      );
 extern int      sbputc(
#ifdef __STDC__
		       int,
		       StringBuffer*
#endif
		      );
 extern char*   sbflush(
#ifdef __STDC__
		       StringBuffer*
#endif
		      );
 extern int      sbtell(
#ifdef __STDC__
		       StringBuffer*
#endif
		      );
 extern void   sbrewind(
#ifdef __STDC__
		       StringBuffer*
#endif
		      );
 extern int      sbseek(
#ifdef __STDC__
		       StringBuffer*,
		       int
#endif
		      );

/*-----------------------------------------------------------------------------
** Macro:	sbputchar()
** Purpose:	Put the character |C| into the string buffer |SB|.
**		
**		This macro is not sane. The arguments are expanded
**		several times. Thus they must not contain side
**		effects. 
** Arguments:
**	C	Character to put.
**	SB	Destination string buffer.
** Returns:	nothing
**___________________________________________________			     */
#define sbputchar(C,SB) ((SB)->sb__ptr < (SB)->sb__size		\
			? (SB)->sb__string[(SB)->sb__ptr++] = C	\
			: sbputc(C,SB))

#endif
