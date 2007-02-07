/******************************************************************************
** $Id: expand.h,v 1.1 2007-02-07 21:31:49 gene Exp $
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
**	This header file makes available the function defined in
**	|expand.c|. This file includes the header file |database.h|.
******************************************************************************/

#include <bibtool/database.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 char * expand_rhs _ARG((char *s,char *pre,char *post, DB db));/* expand.c   */
