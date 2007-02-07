/******************************************************************************
** $Id: stack.h,v 1.1 2007-02-07 21:31:59 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-1997 Gerd Neugebauer
** 
** Net: gerd@informatik.uni-koblenz.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This module provides access to the functions defined in the
**	module |stack.c|. The the documentation of this module for
**	details.
** 
******************************************************************************/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 char * pop_string _ARG((void));		   /* stack.c                */
 void push_string _ARG((char * s));		   /* stack.c                */
