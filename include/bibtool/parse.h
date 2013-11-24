/******************************************************************************
** $Id: parse.h,v 1.9 2013-11-24 22:07:53 gene Exp $
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
**	This header file contains functions which deal with the
**	parsing of \BibTeX{} files. They are defined in |parse.c| and
**	declared in this file.
**	
******************************************************************************/

#include <bibtool/record.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int parse_bib _ARG((Record rec));		   /* parse.c                */
 int read_rsc _ARG((Uchar *name));		   /* parse.c                */
 int see_bib _ARG((Uchar * fname));		   /* parse.c                */
 int seen _ARG((void));				   /* parse.c                */
 void init_read _ARG((void));			   /* parse.c                */
 void set_rsc_path _ARG((Uchar * val));		   /* parse.c                */
