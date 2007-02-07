/******************************************************************************
** $Id: version.h,v 1.1 2007-02-07 21:32:04 gene Exp $
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
******************************************************************************/

 extern char * bibtool_version;

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 void show_version _ARG((void));		   /* version.c		     */

/*---------------------------------------------------------------------------*/
