/*** rsc.h ********************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2020 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2, or (at your option)
** any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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

#include <bibtool/symbols.h>

#ifdef RSC_INIT
#define RscNumeric(SYM,S,V,I) int    V = I;
#define RscString(SYM,S,V,I)  String V = (String)I;
#define RscBoolean(SYM,S,V,I) bool   V = I;
#define RscByFct(SYM,S,FCT)   
#define DECLARE(TYPE,VAR,VAL) TYPE VAR = VAL
#else
#define RscNumeric(SYM,S,V,I) extern int    V;
#define RscString(SYM,S,V,I)  extern String V;
#define RscBoolean(SYM,S,V,I) extern bool   V;
#define RscByFct(SYM,S,FCT)   
#define DECLARE(TYPE,VAR,VAL) extern TYPE VAR
#endif

#include <bibtool/resource.h>

DECLARE( int   , rsc_select        , FALSE  			);

DECLARE( char* , rsc_e_rsc         , RSC_BIBTOOL		);
DECLARE( String, rsc_v_rsc , (String)(RSC_BIBTOOL_DEFAULT)	);

/*---------------------------------------------------------------------------*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 bool load_rsc _ARG((String name));
 bool search_rsc _ARG((void));
 bool resource _ARG((String name));
 bool set_rsc _ARG((Symbol name, Symbol val));
 bool use_rsc _ARG((String s));
 void rsc_print _ARG((String s));

/*---------------------------------------------------------------------------*/
