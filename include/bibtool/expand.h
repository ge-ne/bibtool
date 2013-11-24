/******************************************************************************
** $Id: expand.h,v 1.9 2013-11-24 22:07:52 gene Exp $
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
**	This header file makes available the function defined in
**	|expand.c|. This file includes the header file |database.h|.
******************************************************************************/

#include <bibtool/database.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Uchar * expand_rhs _ARG((Uchar *s,Uchar *pre,Uchar *post, DB db));/* expand.c*/
