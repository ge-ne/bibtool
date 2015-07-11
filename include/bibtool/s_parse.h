/*** s_parse.h ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
** 
******************************************************************************/


#define StringParseSkip		    256
#define StringParseNext		    257
#define StringParseNumber	    258
#define StringParseSymbol	    259
#define StringParseString	    260
#define StringParseUnquotedString   261
#define StringParseBraces	    262
#define StringParseUnquotedBraces   263
#define StringParseEOS		    264
#define StringParseValue	    265

#define SParseSymbol(SP)	    s_parse(StringParseSymbol	     ,SP,-1)
#define SParseOptionalSymbol(SP)    s_parse(StringParseSymbol	     ,SP, 0)
#define SParseString(SP)	    s_parse(StringParseString	     ,SP,-1)
#define SParseUnquotedString(SP)    s_parse(StringParseUnquotedString,SP,-1)
#define SParseEOS(SP)		    s_parse(StringParseEOS   	     ,SP,-1)
#define SParseSkip(SP)		    s_parse(StringParseSkip  	     ,SP,-1)
#define SParseNext(SP)		    s_parse(StringParseNext  	     ,SP,-1)
#define SParseValue(SP)		    s_parse(StringParseValue 	     ,SP,-1)
#define SParseExpect(C,SP)	    s_parse(C&0xff           	     ,SP,-1)


#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 String s_parse _ARG((int type, String *sp, int errp));/* s_parse.c          */
 int sp_open _ARG((String  s));			   /* s_parse.c              */
 void sp_close _ARG((void));			   /* s_parse.c              */
 void sp_error _ARG((String s, char *a, char *b)); /* s_parse.c              */
