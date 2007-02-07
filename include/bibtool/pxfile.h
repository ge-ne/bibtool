/******************************************************************************
** $Id: pxfile.h,v 1.1 2007-02-07 21:32:00 gene Exp $
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
**	This module provides access to the functions and
**	variables defined in |pxfile.c|. Consult also the documentation
**	of this file for details.
**
**	This header file automatically includes |bibtool.h| and |<stdio.h>|.
**
******************************************************************************/

#include <stdio.h>

extern char * px_filename;


extern FILE * px_fopen(
#ifdef __STDC__
	char  * name,
	char  * mode,
	char  **pattern,
	char  **path,
	int   (*show)()
#endif
	);

extern char **px_s2p(
#ifdef __STDC__
	char  * s,
	int   sep
#endif
	);

