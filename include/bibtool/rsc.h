/******************************************************************************
** $Id: rsc.h,v 1.7 2011-06-07 20:01:06 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2011 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This header file provides definitions for all resource
**	variables, i.e.\ the variables defined in the header file
**	|resource.h|. 
**
**	In addition the functions defined in |resource.c| are made
**	accessible to those modules including this header file.
******************************************************************************/

#include <bibtool/type.h>

#ifdef RSC_INIT
#define RscNumeric(SYM,S,V,I) int    V = I;
#define RscString(SYM,S,V,I)  Uchar * V = (Uchar*)I;
#define RscBoolean(SYM,S,V,I) int    V = I;
#define RscByFct(SYM,S,FCT)   
#define DECLARE(TYPE,VAR,VAL) TYPE VAR = VAL
#else
#define RscNumeric(SYM,S,V,I) extern int    V;
#define RscString(SYM,S,V,I)  extern Uchar * V;
#define RscBoolean(SYM,S,V,I) extern int    V;
#define RscByFct(SYM,S,FCT)   
#define DECLARE(TYPE,VAR,VAL) extern TYPE VAR
#endif

#include <bibtool/resource.h>

DECLARE( int   , rsc_select       , FALSE  			);

DECLARE( char* , rsc_e_rsc        , RSC_BIBTOOL			);
DECLARE( char* , rsc_v_rsc        , RSC_BIBTOOL_DEFAULT		);


#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int load_rsc _ARG((char *name));
 int resource _ARG((char *name));
 int search_rsc _ARG((void));
 int set_rsc _ARG((Uchar *name,Uchar *val));
 int use_rsc _ARG((Uchar *s));
 void rsc_print _ARG((char *s));
