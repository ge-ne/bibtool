/******************************************************************************
** $Id: stack.h,v 1.8 2013-11-24 22:07:53 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2013 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This module provides access to the functions defined in the
**	module |stack.c|. The the documentation of this module for
**	details.
** 
******************************************************************************/

#include <bibtool/type.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Uchar * pop_string _ARG((void));		   /* stack.c                */
 void push_string _ARG((Uchar * s));		   /* stack.c                */
