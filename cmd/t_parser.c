/*** t_parser.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <bibtool/sbuffer.h>
#include <bibtool/symbols.h>
#include "term.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

 SymDef scan();
 int parse_term();
 static Term read_cmd();
 static Term read_expr();
 static Term yylval;

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


static Term yylval;
static FILE * in_file;
static int linenum;
static SymDef sd_look_ahead = 0L;
static Term look_ahead = NIL;

#define unscan(S,T) (sd_look_ahead = S, look_ahead = T)

#define GETC fgetc(in_file)
#define UNGETC(C) ungetc(C, in_file)

/*-----------------------------------------------------------------------------
** Function:	scan()
** Type:	SymDef
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
SymDef scan()					   /*                        */
{					   	   /*                        */
  int c;					   /*                        */
 						   /*                        */
#ifdef DEBUG
  printf("--- scan\n");
#endif
  if (sd_look_ahead)			   	   /*                        */
  { SymDef sd	  = sd_look_ahead;		   /*                        */
    sd_look_ahead = SymDefNull;			   /*                        */
    yylval	  = look_ahead;			   /*                        */
    look_ahead	  = NIL;			   /*                        */
#ifdef DEBUG
    printf("--- repeat %s\n", SymName(sd));
#endif
    return sd;			   		   /*                        */
  }						   /*                        */
  yylval = term_eof;				   /*                        */
    						   /*                        */
  for (c = GETC; c >= 0; c = GETC)	   	   /*                        */
  {						   /*                        */
    switch (c) {				   /*                        */
      case '\n':				   /*                        */
	linenum++;				   /*                        */
      case ' ':					   /*                        */
      case '\f':				   /*                        */
      case '\r':				   /*                        */
      case '\b':				   /*                        */
	continue;				   /*                        */
      case '"':					   /*                        */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  for (c = GETC; c && c != '"'; c = GETC)  /*                        */
	  { if ( c == '\\')			   /*                        */
	    { c = GETC;				   /*                        */
	      switch (c)			   /*                        */
	      { case 0:				   /*                        */
		  break;			   /*                        */
		case 'n':			   /*                        */
		  sbputc('\n', sb);		   /*                        */
		  break;			   /*                        */
		case 'r':			   /*                        */
		  sbputc('\r', sb);		   /*                        */
		  break;			   /*                        */
		case 'f':			   /*                        */
		  sbputc('\f', sb);		   /*                        */
		  break;			   /*                        */
		case 'b':			   /*                        */
		  sbputc('\b', sb);		   /*                        */
		  break;			   /*                        */
		default:			   /*                        */
		  sbputc(c, sb);		   /*                        */
	      }					   /*                        */
	    } else {				   /*                        */
	      sbputc(c, sb);			   /*                        */
	    }					   /*                        */
	  }					   /*                        */
	  					   /*                        */
	  yylval = new_t_string(sym_string, 	   /*                        */
				symbol((String)sbflush(sb)));/*              */
	  sbclose(sb);				   /*                        */
	  return sym_string;			   /*                        */
	}					   /*                        */
      case '\'':				   /*                        */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  for (c = GETC; c && c != '\''; c = GETC) /*                        */
	  { sbputc(c, sb); }			   /*                        */
	  					   /*                        */
	  yylval = new_term(sym_field,		   /*                        */
			    symbol((String)sbflush(sb)));/*                  */
	  sbclose(sb);				   /*                        */
	  return sym_field;			   /*                        */
	}					   /*                        */
      case '{':					   /*                        */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  int n = 1;				   /*                        */
	  for (c = GETC; c; c = GETC)		   /*                        */
	  { if (c == '{')			   /*                        */
	    { n++;				   /*                        */
	    } else if (c == '}')		   /*                        */
	    { if (--n < 1) { break; }		   /*                        */
	    }					   /*                        */
	    sbputc(c, sb);			   /*                        */
	  }					   /*                        */
	  					   /*                        */
	  yylval = new_t_string(sym_block,	   /*                        */
				symbol((String)sbflush(sb)));/*              */
	  sbclose(sb);				   /*                        */
	  return sym_block;			   /*                        */
	}					   /*                        */
      case '0':					   /*                        */
	yylval = new_term_num(0);		   /*                        */
	c = GETC;				   /*                        */
	if (c == 0)				   /*                        */
	{ return sym_number;			   /*                        */
	} else if (c == 'x')			   /*                        */
	{ for (c = GETC; c; c = GETC)		   /*                        */
	  { if (c >= '0' && c <= '9')		   /*                        */
	    { TNumber(yylval) = TNumber(yylval) * 16 + c - '0';/*            */
	    } else if (c >= 'a' && c <= 'f')	   /*                        */
	    { TNumber(yylval) = TNumber(yylval) * 16 + c - 'a';/*            */
	    } else if (c >= 'A' && c <= 'F')	   /*                        */
	    { TNumber(yylval) = TNumber(yylval) * 16 + c - 'A';/*            */
	    } else 				   /*                        */
	    { break; }				   /*                        */
	  }					   /*                        */
	} else if (c >= '0' && c <= '7')	   /*                        */
	{ for (c = GETC; c >= '0' && c <= '7'; c = GETC)/*                   */
	  { TNumber(yylval) = TNumber(yylval) * 8 + c - '0';/*               */
	  }					   /*                        */
	}					   /*                        */
	UNGETC(c);				   /*                        */
	return sym_number;			   /*                        */
      case '1':					   /*                        */
      case '2':					   /*                        */
      case '3':					   /*                        */
      case '4':					   /*                        */
      case '5':					   /*                        */
      case '6':					   /*                        */
      case '7':					   /*                        */
      case '8':					   /*                        */
      case '9':					   /*                        */
	yylval = new_term_num(c - '0');		   /*                        */
	for (c = GETC; c >= '0' && c <= '9'; c = GETC)/*                     */
	{ TNumber(yylval) = 			   /*                        */
	    TNumber(yylval) * 10 + c - '0';	   /*                        */
	}					   /*                        */
	UNGETC(c);				   /*                        */
	return sym_number;			   /*                        */
      case ';':					   /*                        */
	yylval = term_semicolon;
	return TSym(yylval);
      case '!':					   /*                        */
	if ((c=GETC) == '=') {
	  yylval = new_term(sym_ne, NIL, NIL);
	  return sym_ne;
	}
	UNGETC(c);
	break;
      case '>':					   /*                        */
	if ((c=GETC) == '=') {
	  yylval = new_term(sym_ge, NIL, NIL);
	  return sym_ge;
	}
	UNGETC(c);
	yylval = new_term(sym_gt, NIL, NIL);
	return sym_gt;
      case '<':					   /*                        */
	if ((c=GETC) == '=') {
	  yylval = new_term(sym_le, NIL, NIL);
	  return sym_le;
	}
	UNGETC(c);
	yylval = new_term(sym_lt, NIL, NIL);
	return sym_lt;
      case '=':					   /*                        */
	if ((c=GETC) == '=') {
	  yylval = new_term(sym_eq, NIL, NIL);
	  return sym_eq;
	}
	UNGETC(c);
	yylval = new_term(sym_setq, NIL, NIL);
	return sym_setq;
      default:					   /*                        */
	if ((c >= 'a' && c <= 'z') ||		   /*                        */
	    (c >= 'A' && c <= 'Z') ||		   /*                        */
	    c == '$' || c == '@' || c == '_' || c == '.')/*                  */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  String s;				   /*                        */
	  sbputc((char)c ,sb);			   /*                        */
	  for (c = GETC;			   /*                        */
	       isalpha(c) || c == '_' || c == '.'; /*                        */
	       c = GETC) 			   /*                        */
	  { sbputc((char)c ,sb); }		   /*                        */
	  UNGETC(c);				   /*                        */
	  s = symbol((String)sbflush(sb));	   /*                        */
	  sbclose(sb);				   /*                        */
 						   /*                        */
#define RSC_FIRST(C)	    case C:
#define RSC_NEXT(C)	    break; case C:
#define ON(A)		    if (strcmp((char*)s, A) == 0)
#define RscNumeric(A,B,C,D) ON(A) {yylval = new_t_string(sym_builtin, s);}
#define RscString(A,B,C,D)  ON(A) {yylval = new_t_string(sym_builtin, s);}
#define RscBoolean(A,B,C,D) ON(A) {yylval = new_t_string(sym_builtin, s);}
#define RscByFct(A,B,C)     ON(A) {yylval = new_t_string(sym_builtin, s);}
	  switch (*s) {				   /*                        */
#include <bibtool/resource.h>
	  }					   /*                        */
	  if (yylval == term_eof)		   /*                        */
	  { ON("true")				   /*                        */
	    { yylval = term_true;		   /*                        */
	    } else ON("false")			   /*                        */
	    { yylval = term_false;		   /*                        */
	    } else {				   /*                        */
	      yylval = new_t_string(sym_field, s); /*                        */
	    }					   /*                        */
	  }					   /*                        */
	  return TSym(yylval);			   /*                        */
	}					   /*                        */
    }						   /*                        */
#ifdef DEBUG
    printf("--- scanned: %c\n", c);
#endif
    return c < 0 ? SymDefNull : sym_char[c & 0xff];/*                        */
  }						   /*                        */
  return SymDefNull;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_expr()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
static Term read_expr()				   /*                        */
{ SymDef s;					   /*                        */
  Term t = term_eof;				   /*                        */
 						   /*                        */
  for (s = scan(); s; s = scan())		   /*                        */
  {						   /*                        */
    if (s == sym_builtin) {
      Term *tp;
      t	 = new_list(yylval, NIL);
      tp = &TArg(t);

      for (s = scan(); s; s = scan())
      {
	if (   SymIs(s, '#')
	    || s == sym_setq) {
	} else if (   SymIs(s, ';')
		   || SymIs(s, ')')
		   || SymIs(s, ']')) {
	  unscan(s, yylval);
	  return t;
	} else {
	  unscan(s, yylval);
	  yylval = read_expr();
	  *tp = new_list(yylval, NIL);
	  tp = &(TArg(*tp));
	}
      }
      return t;
      
    } else if (SymIs(s, '-')) {
      t	= read_expr();
      if (TIsEOF(t)) { return t; }
      if (TIsNumber(t))
      { TNumber(t) = -TNumber(t);
	return t;
      }
      
      return new_list(term_minus, new_list(t, NIL));

    } else if (s == sym_field
	       || s == sym_string
	       || s == sym_number) {

      t = yylval;
      s	= scan();
      if (s == NULL) { return t; }
      unscan(s, yylval);
					   /* TODO*/
      return t;
    } else if (SymOp(s) > 0
	       || s == sym_true
	       || s == sym_false) {
      return yylval;
    } else if (SymIs(s, ';')) {
      return term_semicolon;
    } else {
#ifdef DEBUG
      char c = *SymName(s);
      fprintf(stderr,"\n::: %c %d\n", c, c);
#endif
      return term_eof;				   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_cmd()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
static Term read_cmd()				   /*                        */
{ SymDef s;					   /*                        */
  Term t = read_expr();				   /*                        */
  if (TIsEOF(t)) return t;		   	   /*                        */
  						   /*                        */
  s = scan();					   /*                        */
  if (s != sym_char[';'])			   /*                        */
  { fprintf(stderr,				   /*                        */
	    "Semicolon expected instead of %s\n",  /*                        */
	    (s ? (char*)SymName(s) : "EOF"));	   /*                        */
    return term_eof;				   /*                        */
  }						   /*                        */
   						   /*                        */
  return t;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_term()
** Type:	int
** Purpose:	
**		
** Arguments:
**	filename	
** Returns:	
**___________________________________________________			     */
int parse_term(file, action)			   /*                        */
  char * file;				   	   /*                        */
  int (*action)_ARG((Term t));			   /*                        */
{ Term t;					   /*                        */
 						   /*                        */
  if (file == NULL) {			   	   /*                        */
    fprintf(stderr, "No input file given\n");	   /*                        */
    return -2;					   /*                        */
  }						   /*                        */
  linenum  = 1;					   /*                        */
  look_ahead = NIL;				   /*                        */
  in_file  = fopen(file, "r");		   	   /*                        */
  if (in_file == NULL) {			   /*                        */
    fprintf(stderr,				   /*                        */
	    "%s: File could not be opened\n",	   /*                        */
	    file);				   /*                        */
    return -1;					   /*                        */
  }						   /*                        */
   						   /*                        */
  for (t = read_cmd();				   /*                        */
       t != term_eof;				   /*                        */
       t = read_cmd())				   /*                        */
  { (*action)(t); }				   /*                        */
 						   /*                        */
  fclose(in_file);				   /*                        */
 						   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/
