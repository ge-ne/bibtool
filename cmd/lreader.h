/*** lreader.h *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#ifndef LREADER_H
#define LREADER_H

#include <stdio.h>
#include "term.h"

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

extern void init_lreader();

#define Error(X,Y,Z)						\
	error(ERR_ERROR|ERR_FILE|ERR_EXIT,(String)X,		\
	      (String)Y,(String)Z,(String)0,(String)0,linenum,filename)
#define ErrorNF(X,Y)						\
	error(ERR_ERROR|ERR_EXIT,(String)X,			\
	      (String)Y,(String)0,(String)0,(String)0,0,NULL)

#endif
