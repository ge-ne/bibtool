/*** sbuffer.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2016 Gerd Neugebauer
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
**	This module contains functions for dealing with strings of
**	aribtrary size. The allocation of memory is done automatically
**	when more characters are added.
**
**	The functions are modeled after the stream functions of C.
**	Currently a |printf|-like function is missing because one was
**	not needed yet and it is not so easy to implement---portably. 
** 
**	The functions in this module are very handy to deal with
**      strings of arbitrary length where the length is not known in
**      advance. E.g. consider the case that a line has to be read
**      from a file |file| and the line length should not be restricted by
**      some artificial boundry. This can be implemented as follows:
**	\\
**	|{ StringBuffer *sb = sb_open();|\Ccomment{Declare and
**      initialize a string buffer.}\\
**	|  int c;|\Ccomment{Variable to store a single character.}\\
**	|  char *s;|\Ccomment{Variable to hold the string at the end.}\\
**	|  while ( (c=fgetc(file) != EOF|\\
**	|          && c != '\n')|\\
**	|  { sbputchar(c,sb); }|\Ccomment{Store each character in the
**      string buffer.}\\
**	|  s = sbflush(sb);|\Ccomment{Get the string from the
**      string buffer.}\\
**	|  puts(s);|\Ccomment{Process the string; e.g. print it.}\\
**	|  sb_close(sb);|\Ccomment{Free the string buffer.}\\
**	|}|
**
**	Note that the flushing of the string buffer returns a C string
**      which is managed by the string buffer.  This memory is freed
**      or reused whenever the string buffer needs to. Thus you should
**      make a private copy of this string if it should survive the
**      next operation of the string buffer. Especially, after the
**      call to |sb_close()| this memory has been returned to the
**      operating system and is not available any more.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/sbuffer.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/


/*-----------------------------------------------------------------------------
** Function:	sbopen()
** Purpose:	Allocate a new string buffer.
**		Return a pointer to the new string buffer or |NULL| if
**		none was available.
** Arguments:	none.
** Returns:	pointer to new string buffer or NULL
**___________________________________________________			     */
StringBuffer* sbopen()				   /*                        */
{ register StringBuffer* sb;			   /*                        */
 						   /*                        */
  if ( (sb=(StringBuffer*)malloc(sizeof(StringBuffer))) == NULL )/*          */
  { return NULL; }				   /*                        */
  sb->sb__string = NULL;			   /*                        */
  sb->sb__ptr = sb->sb__size = 0;		   /*                        */
  return sb;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sbclose()
** Purpose:	Free an old string buffer.
** Arguments:
**	sb	Pointer to string buffer which should be closed
** Returns:	Return 0 upon failure.
**___________________________________________________			     */
int sbclose(sb)					   /*                        */
  StringBuffer* sb;				   /*                        */
{						   /*                        */
  if ( sb == NULL ) return 1;			   /*                        */
  if ( sb->sb__string != NULL ) free(sb->sb__string);/*                      */
  free((char*)sb);				   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sbputs()
** Purpose:	Push a whole string onto a string buffer.
** Arguments:
**	s	String to be pushed.
**	sb	Destination string buffer.
** Returns:	|FALSE| if something went wrong.
**___________________________________________________			     */
int sbputs(s,sb)				   /*                        */
  char         *s;				   /*                        */
  StringBuffer* sb;				   /*                        */
{						   /*                        */
  if ( sb == NULL ) return 1;			   /*                        */
 						   /*                        */
  while ( *s )					   /*                        */
  { (void)sbputchar(*s,sb); ++s;		   /*                        */
  }						   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sbputc()
** Purpose:	Push a single character onto a string buffer. In
**		contrast to the macro this function handles the
**		reallocation of the memory. For the user it should not
**		make a difference since the macros uses this function
**		when needed.
**
**		When no memory is left then the character is discarded
**		and this action is signaled via the return value.
** Arguments:
**	c	Character to put to the string buffer.
**	sb	Destination string buffer.
** Returns:	|FALSE| if no memory is left.
**___________________________________________________			     */
int sbputc(c,sb)				   /*                        */
  register int           c;			   /*                        */
  register StringBuffer* sb;			   /*                        */
{ register char         *cp;			   /*                        */
 						   /*                        */
  if ( sb->sb__ptr >= sb->sb__size )		   /*                        */
  { sb->sb__size += StringBufferIncrement;	   /*                        */
    if ( (cp=( sb->sb__ptr == 0		   	   /*                        */
	      ? malloc(sb->sb__size)		   /*                        */
	      : realloc(sb->sb__string,sb->sb__size))/*                      */
	 ) == NULL )				   /*                        */
    { sb->sb__size -= StringBufferIncrement;	   /*                        */
      return 1;					   /*                        */
    }						   /*                        */
    sb->sb__string = cp;			   /*                        */
  }						   /*                        */
 						   /*                        */
  sb->sb__string[sb->sb__ptr++] = c;		   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sbflush()
** Purpose:	Close a string buffer with a trailing |\0| and reset the
**		current pointer to the beginning.
**		The next write operation starts right at the end. Thus
**		additional write operations will overwrite the
**		terminating byte.
** Arguments:
**	sb	String buffer to close.
** Returns:	The string contained in the string buffer as a proper
**		C string.
**___________________________________________________			     */
char* sbflush(sb)				   /*                        */
  StringBuffer* sb;				   /*                        */
{ 						   /*                        */
  (void)sbputchar('\0',sb);			   /*                        */
  sb->sb__ptr--;				   /*                        */
  return sb->sb__string;			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sbrewind()
** Purpose:	Reset the string buffer pointer to the beginning.
**		The next write or read will operate there.
** Arguments:
**	sb	String buffer to consider.
** Returns:	nothing
**___________________________________________________			     */
void sbrewind(sb)				   /*                        */
  StringBuffer* sb;				   /*                        */
{ sb->sb__ptr = 0;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sbtell()
** Purpose:	Return the current pointer to the string buffer position.
**		This can be used with |sbseek()| to reset it.
** Arguments:
**	sb	String buffer to consider.
** Returns:	The relative byte position of the current writing
**		position. This is an integer offset from the beginning
**		of the string buffer.
**___________________________________________________			     */
int sbtell(sb)					   /*                        */
  StringBuffer* sb;				   /*                        */
{ return sb->sb__ptr;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sbseek()
** Purpose:	Reset the current pointer to the position given. If
**		the position is outside the valid region then |TRUE|
**		is returned and the position is left unchanged.
** Arguments:
**	sb	String buffer to reposition.
**	pos	New position of the string buffer.
** Returns:	|FALSE| if everything went right.
**___________________________________________________			     */
int sbseek(sb,pos)				   /*                        */
  StringBuffer* sb;				   /*                        */
  int           pos;				   /*                        */
{ 						   /*                        */
  if ( pos < 0 || pos > sb->sb__ptr ) return 1;	   /*                        */
  sb->sb__ptr = pos;				   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/
