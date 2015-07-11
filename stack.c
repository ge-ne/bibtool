/*** stack.c ******************************************************************
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
**	This module provides a single stack of strings. There are two
**	operations on this stack, namely to push a string onto the
**	stack and a pop operation to get the topmost element from the
**	stack and remove it or to get a signal that the stack is
**	empty. 
**
**	The stack is implemented as an array which grows on demand.
**	Currently the memory of the stack is not returned to the
**	operating system. This seems to be not problemeatic since this
**	memory is not assumed to be really large. Normally just a few
**	strings are pushed to the stack at any time.
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/error.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 String  pop_string _ARG((void));		   /* stack.c                */
 void push_string _ARG((String  s));		   /* stack.c                */

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

 static String *stack;
 static size_t stack_size = 0;
 static size_t stack_ptr  = 0;

/*-----------------------------------------------------------------------------
** Function:	push_string()
** Purpose:	Push a string onto the stack. Only the memory for the
**		stack is allocated. The string is stored as pointer to
**		existing memory. No copy of the string is made.
**
**		If no memory is left then an error is raised and the program
**		is terminated.
** Arguments:
**	s	String to push to the stack.
** Returns:	nothing
**___________________________________________________			     */
void push_string(s)				   /*                        */
  register String s;				   /*                        */
{						   /*                        */
  if ( stack_ptr >= stack_size )		   /*                        */
  { stack_size += 16;		   		   /*                        */
    stack = (stack_ptr == 0			   /*                        */
	     ?(String*)malloc((size_t)(stack_size*sizeof(String)))/*         */
	     :(String*)realloc((char*)stack,	   /*                        */
			       (size_t)(stack_size*sizeof(String))));/*      */
    if ( stack == NULL )			   /*                        */
    { OUT_OF_MEMORY("stack"); }	   		   /*                        */
  }		   				   /*                        */
  stack[stack_ptr++] = s;   			   /*                        */
  DebugPrint2("pushing ",s);		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	pop_string()
** Purpose:	Pop a string from the stack. It the stack is empty
**		then |NULL| is returned. Thus the |NULL| value should
**		not be pushed to the stack since this can be confused
**		with the end of the stack.
** Arguments:	none
** Returns:	The old top element or |NULL| if the stack is empty.
**___________________________________________________			     */
String  pop_string()				   /*                        */
{						   /*                        */
  if ( stack_ptr <= 0 ) return NULL;		   /*                        */
 						   /*                        */
  DebugPrint2("poping ",stack[stack_ptr-1]);	   /*                        */
  return stack[--stack_ptr];			   /*                        */
}						   /*------------------------*/
