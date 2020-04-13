/*** sbuffer.h ****************************************************************
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
 extern bool    sbclose(
#ifdef __STDC__
		       StringBuffer*
#endif
		      );
 extern bool    sbputs(
#ifdef __STDC__
		       char *,
		       StringBuffer*
#endif
		      );
 extern bool    sbputc(
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
 extern int     sbtell(
#ifdef __STDC__
		       StringBuffer*
#endif
		      );
 extern void   sbrewind(
#ifdef __STDC__
		       StringBuffer*
#endif
		      );
 extern bool   sbseek(
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
