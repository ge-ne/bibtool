/*** s_parse.h ****************************************************************
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
** Description: This header file contains definitions and declarations for the
**		string parser.
** 
******************************************************************************/

#ifndef S_PARSE_H_LOADED
#define S_PARSE_H_LOADED

#include <bibtool/general.h>
#include <bibtool/symbols.h>

#define StringParseNext		    257
#define StringParseNumber	    258
#define StringParseSymbol	    259
#define StringParseString	    260
#define StringParseUnquotedString   261
#define StringParseBraces	    262
#define StringParseUnquotedBraces   263
#define StringParseValue	    265

#define SParseSymbol(SP)	    s_parse(StringParseSymbol	     ,SP, true)
#define SParseOptionalSymbol(SP)    s_parse(StringParseSymbol	     ,SP, false)
#define SParseString(SP)	    s_parse(StringParseString	     ,SP, true)
#define SParseUnquotedString(SP)    s_parse(StringParseUnquotedString,SP, true)
#define SParseNext(SP)		    s_parse(StringParseNext  	     ,SP, true)
#define SParseValue(SP)		    s_parse(StringParseValue 	     ,SP, true)
#define SParseExpect(C,SP)	    s_parse((C)&0xff           	     ,SP, true)

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Symbol s_parse _ARG((int type, String *sp, bool errp));/* s_parse.c         */
 void sp_close _ARG((void));			   /* s_parse.c              */
 void sp_open _ARG((String  s));		   /* s_parse.c              */
 void sp_skip _ARG((String *sp));		   /*                        */
 bool sp_expect _ARG((String *sp, String expect, bool verbose));/* s_parse.c */
 Symbol* sp_symbols _ARG((String *sp));		   /* s_parse.c              */
 String sp_eos _ARG((String *sp));		   /*                        */

/*---------------------------------------------------------------------------*/
#endif
