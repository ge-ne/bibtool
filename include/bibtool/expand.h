/******************************************************************************
** $Id: expand.h,v 1.4 2007-02-08 05:43:31 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2003 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
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
 Uchar * expand_rhs _ARG((Uchar *s,char *pre,char *post, DB db));/* expand.c */
