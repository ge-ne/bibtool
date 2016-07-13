/*** rewrite.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2016 Gerd Neugebauer
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
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/entry.h>
#include <bibtool/error.h>
#include <bibtool/macros.h>
#include <bibtool/rsc.h>
#include <bibtool/key.h>
#include <bibtool/s_parse.h>
#include <bibtool/sbuffer.h>
#include <bibtool/rewrite.h>
#include <bibtool/symbols.h>

#ifdef REGEX
#include <bibtool/regex.h>
#endif

 typedef struct rULE
 { Symbol	rr_field;
   Symbol	rr_goal;
   Symbol	rr_value;
   Symbol	rr_frame;
   int		rr_flag;
   struct rULE	*rr_next;
#ifdef REGEX
   struct re_pattern_buffer rr_pat_buff;
#endif
 } SRule, *Rule;

#define RuleNULL	(Rule)0

#define RuleField(X)	((X)->rr_field)
#define RuleGoal(X)	((X)->rr_goal)
#define RuleValue(X)	((X)->rr_value)
#define RulePattern(X)	((X)->rr_pat_buff)
#define RuleFrame(X)	((X)->rr_frame)
#define NextRule(X)	((X)->rr_next)
#define RuleFlag(X)	((X)->rr_flag)

#define RULE_NONE	0x00
#define RULE_ADD	0x01
#define RULE_REGEXP	0x02
#define RULE_NOT	0x04
#define RULE_RENAME	0x08
#define RULE_DELETE	0x10
#define RULE_KEEP	0x20

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 bool is_selected _ARG((DB db,Record rec));	   /*                        */
 int set_regex_syntax _ARG((char* name));	   /*                        */
 static Rule new_rule _ARG((Symbol field,Symbol value,Symbol pattern,Symbol frame,int flags,int casep));
 static String  check_regex _ARG((Symbol field,Symbol value,Rule rule,DB db,Record rec));
 static String  repl_regex _ARG((Symbol field,Symbol value,Rule rule,DB db,Record rec));
 static bool s_match _ARG((String  p,String  s));  /*                        */
 static bool s_search _ARG((String  pattern,String  s));/*                    */
 static void add_rule _ARG((String s,Rule *rp,Rule *rp_end,int flags,int casep));/**/
#ifdef UNUSED
 static void free_rule _ARG((Rule rule));	   /*                        */
#endif
 static void init_s_search _ARG((String  ignored));/*                        */
 static void rewrite_1 _ARG((String frame,StringBuffer *sb,String match,DB db,Record rec));/**/
 void add_check_rule _ARG((String s));		   /*                        */
 void add_extract _ARG((Symbol s,int regexp,int notp));/*                    */
 void add_field _ARG((String spec));		   /*                        */
 void add_rewrite_rule _ARG((String s));	   /*                        */
 void clear_addlist _ARG((void));		   /*                        */
 void remove_field _ARG((Symbol field,Record rec));/*                        */
 void rename_field _ARG((Symbol spec));		   /*                        */
 void rewrite_record _ARG((DB db,Record rec));	   /*                        */
 void save_regex _ARG((String s));		   /*                        */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/


/*---------------------------------------------------------------------------*/

 static String s_if = (String)"if";


/*****************************************************************************/
/***			  Field Add/Delete Section			   ***/
/*****************************************************************************/

 static Macro addlist = MacroNULL;

/*-----------------------------------------------------------------------------
** Function:	clear_addlist()
** Purpose:	Reset the addlist to the empty list.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void clear_addlist()				   /*                        */
{						   /*                        */
  free_macro(addlist);				   /*                        */
  addlist = MacroNULL;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	foreach_addlist()
** Type:	bool
** Purpose:	
**		
** Arguments:
**	fct	the function to be applied
** Returns:	
**___________________________________________________			     */
bool foreach_addlist(fct)			   /*                        */
  bool (*fct) _ARG((Symbol key, Symbol val));	   /*                        */
{ return each_macro(addlist, fct);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	add_field()
** Purpose:	Save a token and value for addition.
** Arguments:
**	spec	A string of the form
**		  | token=value|
** Returns:	nothing
**___________________________________________________			     */
void add_field(spec)				   /*			     */
  String spec;					   /*			     */
{ register Symbol field, value;		   	   /*			     */
						   /*			     */
  sp_open(spec);				   /*			     */
  if ((field = SParseSymbol(&spec)) == NO_SYMBOL)  /*		             */
    return;					   /*			     */
  sp_skip(&spec);			   	   /*			     */
  if ((value=SParseValue(&spec)) == NO_SYMBOL)     /*			     */
    return;					   /*			     */
  sp_eos(&spec);			   	   /*			     */
						   /*			     */
  addlist = new_macro(field, value, addlist, 0);   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	remove_field()
** Purpose:	Remove the given field from record.
** Arguments:
**	field	This is a symbol containing the name of the field to remove.
**	rec	Record in which the field should be removed.
** Returns:	nothing
**___________________________________________________			     */
void remove_field(field, rec)			   /*			     */
  register Symbol field;			   /*			     */
  Record	 rec;				   /*			     */
{ register int	 i;				   /*			     */
						   /*			     */
  for (i = 0; i < RecordFree(rec); i += 2 )	   /*			     */
  { if ( field == RecordHeap(rec)[i] )		   /* compare symbols	     */
    { RecordHeap(rec)[i] = NO_SYMBOL; }	   	   /*			     */
  }						   /*			     */
						   /*			     */
  while ( RecordFree(rec) > 0 &&		   /* Adjust Heap Length     */
	  RecordHeap(rec)[RecordFree(rec) - 2] == NULL )/*		     */
  { RecordFree(rec) -= 2;			   /*			     */
  }						   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***				 Rule Section				   ***/
/*****************************************************************************/

#ifdef REGEX
 static struct re_registers reg;		   /*			     */
#endif

/*-----------------------------------------------------------------------------
** Function*:	new_rule()
** Purpose:	Allocate a new Rule and fill some slots.
** Arguments:
**	field	The field to apply this rule to, or |NULL| for each field.
**	value	the value
**	pattern	the rule goal
**	frame	the rule frame
**	flags	The ored flag values
**	casep	Boolean; indicating case sensitive comparison.
** Returns:	A pointer to the allocated structure or |NULL| upon failure.
**___________________________________________________			     */
static Rule new_rule(field, value, pattern, frame, flags, casep)/*           */
  Symbol	field;				   /*			     */
  Symbol	value;			   	   /*			     */
  Symbol	pattern;			   /*			     */
  Symbol	frame;				   /*			     */
  int		flags;				   /*			     */
  int		casep;				   /*			     */
{ register Rule rule;				   /*			     */
  static int    init = 1;			   /*                        */
 						   /*                        */
#ifdef REGEX
  if ( init )					   /*                        */
  { init = 0;					   /*                        */
    reg.num_regs = 32;				   /*                        */
    reg.start = (regoff_t*)calloc(32,sizeof(regoff_t));/*                    */
    reg.end   = (regoff_t*)calloc(32,sizeof(regoff_t));/*                    */
    if ( reg.start == NULL || reg.end == NULL )	   /*                        */
    { OUT_OF_MEMORY("rewrite rule"); } 		   /*			     */
  }						   /*                        */
#endif
						   /*			     */
  if ( (rule=(Rule)malloc(sizeof(SRule))) == RuleNULL )/*		     */
  { OUT_OF_MEMORY("rewrite rule"); } 		   /*			     */
						   /*			     */
  RuleField(rule) = field;			   /*			     */
  if (field) { LinkSymbol(field); }		   /*                        */
  RuleValue(rule) = value;			   /*			     */
  if (value) { LinkSymbol(value); }		   /*                        */
  RuleFrame(rule) = frame;			   /*			     */
  if (frame) { LinkSymbol(frame); }		   /*                        */
  RuleFlag(rule)  = flags;			   /*			     */
  NextRule(rule)  = RuleNULL;			   /*			     */
  RuleGoal(rule)  = pattern;			   /*                        */
  if (pattern) { LinkSymbol(pattern); }		   /*                        */
					       	   /*                        */
#ifdef REGEX
  if ( pattern &&				   /*                        */
       *SymbolValue(pattern) &&			   /*                        */
       (flags&RULE_REGEXP) )			   /*                        */
  { char *msg;					   /*                        */
    if ( (RulePattern(rule).buffer = (String)malloc(16)) == NULL )/*         */
    { OUT_OF_MEMORY("pattern"); }		   /*			     */
    RulePattern(rule).allocated = 16;		   /*			     */
    RulePattern(rule).syntax    = RE_SYNTAX_EMACS; /*			     */
    RulePattern(rule).fastmap   = NULL;		   /*			     */
    RulePattern(rule).regs_allocated = REGS_FIXED; /*			     */
    RulePattern(rule).translate = (casep	   /*                        */
				  ? (char*)trans_lower/*                     */
				  : NULL);	   /*	                     */
						   /*			     */
    msg = (char*)re_compile_pattern((char*)SymbolValue(pattern),/*	     */
				    symlen(pattern),/*		             */
				    &RulePattern(rule) );/*	             */
    if (msg) {				   	   /*                        */
      Err(msg);					   /*                        */
      free(rule);				   /*                        */
      return NULL;				   /*                        */
    }	   					   /*			     */
  }						   /*                        */
  else						   /*                        */
  { RuleFlag(rule) = (flags & ~RULE_REGEXP);	   /*                        */
  }						   /*                        */
#endif
  DebugPrint2("pattern = ", SymbolValue(pattern)); /*			     */
  DebugPrint2("frame   = ", SymbolValue(frame));   /*			     */
  DebugPrintF1("+++ BibTool: flags   =");	   /*			     */
  DebugPrintF1(flags & RULE_NOT ? " NOT" : "");	   /*                        */
  DebugPrintF1(flags & RULE_ADD ? " ADD" : "");	   /*                        */
  DebugPrintF1(flags & RULE_RENAME ? " RENAME" : "");/*                      */
  DebugPrintF1(flags & RULE_KEEP ? " KEEP" : "");  /*                        */
  DebugPrintF1(flags & RULE_REGEXP ? " REGEXP" : "");/*                      */
  DebugPrintF1("\n");		   		   /*			     */
  DebugPrintF2("+++ BibTool: New rule = %lx\n",	   /*                        */
	       (long)rule);			   /*                        */
 						   /*                        */
  return rule;					   /*			     */
}						   /*------------------------*/

#ifdef UNUSED
/*-----------------------------------------------------------------------------
** Function*:	free_rule()
** Purpose:	Free a list of rules.
** Arguments:
**	rule	First rule in the list.
** Returns:	nothing
**___________________________________________________			     */
static void free_rule(rule)			   /*                        */
  Rule rule;					   /*                        */
{ Rule next;					   /*                        */
 						   /*                        */
  while (rule)				   	   /*                        */
  { next = NextRule(rule);			   /*                        */
#ifdef REGEX
    free(RulePattern(rule).buffer);		   /*                        */
#endif
    free(rule);					   /*                        */
    rule = next;				   /*                        */
  }						   /*                        */
}						   /*------------------------*/
#endif

/*-----------------------------------------------------------------------------
** Function*:	add_rule()
** Purpose:	Generic addition of a rule to a list of rules.
** Arguments:
**	s	the specification string
**	rp	the pointer to the first rule
**	rp_end	the pointer to the last rule
**	flags	the flags
**	casep	the indicator for cased matching
** Returns:	nothing
**___________________________________________________			     */
static void add_rule(s,rp,rp_end,flags,casep)	   /*			     */
  String	s;				   /*			     */
  Rule		*rp;				   /*			     */
  Rule		*rp_end;			   /*			     */
  int		flags;				   /*                        */
  int		casep;				   /*			     */
{ Symbol	field;				   /*			     */
  Symbol	pattern;			   /*			     */
  Symbol	frame;				   /*			     */
  Rule		rule;				   /*			     */
  int		sp;				   /*                        */
  int		stackp;				   /* stack pointer for the  */
  static Symbol	*stack;			   	   /* local stack of fields  */
  static int    stacksize = 0;			   /*                        */
 						   /*                        */
  if ( stacksize == 0 )				   /*                        */
  { stacksize++;				   /*                        */
    if ((stack=(Symbol*)malloc(sizeof(Symbol)))==(Symbol*)NULL)/*            */
    { OUT_OF_MEMORY("rule stack"); }		   /*                        */
  }						   /*                        */
  stackp = 0;					   /*                        */
						   /*			     */
  DebugPrint2("Adding rule: Parsing from: ", s);   /*			     */
  sp_open(s);				   	   /*			     */
  sp_skip(&s);				   	   /*			     */
						   /*			     */
  while (*s && *s != '"')			   /*                        */
  {						   /*                        */
    DebugPrint2("\tlooking for symbol in: ", s);   /*			     */
    field = SParseSymbol(&s);			   /*                        */
    if (field == NO_SYMBOL)			   /*                        */
    { DebugPrint2("\tno symbol found in: ", s);	   /*			     */
      return;					   /*                        */
    }					   	   /*                        */
    DebugPrint2("\tok ",s);			   /*                        */
    DebugPrint2("field   = ", SymbolValue(field)); /*			     */
    sp_skip(&s);			   	   /*                        */
						   /*			     */
    if (stackp >= stacksize)			   /*                        */
    { stacksize += 8;				   /*                        */
      if ( (stack=(Symbol*)realloc((void*)stack,   /*                        */
				   stacksize*sizeof(Symbol)))==NULL)/*       */
      { OUT_OF_MEMORY("rule stack"); }		   /*                        */
    }						   /*                        */
    stack[stackp++] = field;			   /*                        */
  }						   /*                        */
						   /*			     */
  if ( *s == '\0' )				   /*			     */
  { pattern = symbol((String)"."); }		   /*			     */
  else if ( (pattern=SParseUnquotedString(&s)) == NO_SYMBOL )/*		     */
  { DebugPrintF1("No pattern found");		   /*                        */
    return;					   /*			     */
  }						   /*                        */
						   /*			     */
  sp_skip(&s);				   	   /*			     */
						   /*			     */
  if (*s == '\0')				   /*			     */
  { frame = NO_SYMBOL; }			   /*			     */
  else if ((frame=SParseUnquotedString(&s)) == NO_SYMBOL)/*		     */
  { return; }					   /*			     */
  else						   /*			     */
  { sp_eos(&s); }			   	   /*			     */
						   /*			     */
  if (stackp == 0)				   /* No field specified.    */
  { rule = new_rule(NO_SYMBOL,			   /*                        */
		    NO_SYMBOL,			   /*                        */
		    pattern,			   /*                        */
		    frame,			   /*                        */
		    flags,			   /*                        */
		    casep);			   /*                        */
    if ( *rp == RuleNULL )			   /*                        */
    { *rp = *rp_end = rule; }			   /*			     */
    else					   /*                        */
    { NextRule(*rp_end) = rule; *rp_end = rule;}   /*			     */
    return;					   /*                        */
  }						   /*                        */
 						   /*                        */
  for (sp = 0; sp < stackp; sp++)		   /*                        */
  { rule = new_rule(stack[sp],			   /*                        */
		    NO_SYMBOL,			   /*                        */
		    pattern,			   /*                        */
		    frame,			   /*                        */
		    flags,			   /*                        */
		    casep);			   /*		             */
    if ( *rp == RuleNULL )			   /*                        */
    { *rp = *rp_end = rule; }			   /*			     */
    else					   /*                        */
    { NextRule(*rp_end) = rule; *rp_end = rule;}   /*			     */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	rewrite_1()
** Purpose:	
**		
**
** Arguments:
**	frame
**	sb
**	match
**	rec
** Returns:	nothing
**___________________________________________________			     */
static void rewrite_1(frame,sb,match,db,rec)	   /*			     */
  String	frame;			   	   /*			     */
  StringBuffer	*sb;			   	   /*			     */
  String	match;			   	   /*			     */
  DB		db;			   	   /*                        */
  Record	rec;			   	   /*			     */
{						   /*                        */
  for (; *frame; frame++)			   /*			     */
  { if (*frame == '%')			   	   /*	                     */
    { frame = fmt_expand(sb, frame, db, rec); }	   /*	                     */
    else if (*frame != '\\')			   /* Transfer normal	     */
    { (void)sbputchar(*frame,sb); }		   /*	characters.	     */
    else					   /*			     */
    {						   /*			     */
      switch (*++frame)			   	   /*			     */
      { case '1': case '2': case '3':		   /*			     */
	case '4': case '5': case '6':		   /*			     */
	case '7': case '8': case '9':		   /*			     */
#ifdef REGEX
	  { int i = *frame - '0';		   /* Look for register no   */
	    int e = reg.end[i];			   /* get end of match	     */
						   /*			     */
	    for (i = reg.start[i]; i < e; ++i)	   /* transfer from start    */
	    { (void)sbputchar(match[i],sb); }	   /*	to end of match.     */
	  }					   /*			     */
#endif
	  break;				   /*			     */
	case '$':				   /*			     */
	  (void)sbputs((char*)SymbolValue(*RecordHeap(rec)),/*               */
		       sb);			   /*			     */
	  break;				   /*			     */
	case '@':				   /*			     */
	  (void)sbputs((char*)SymbolValue(EntryName(RecordType(rec))),/*     */
		       sb);			   /*		             */
	  break;				   /*			     */
	case 'n':				   /*                        */
	  (void)sbputchar('\n', sb);		   /*                        */
	  break; 				   /*			     */
	case 't':				   /*                        */
	  (void)sbputchar('\t', sb);		   /*                        */
	  break; 				   /*			     */
	default:				   /*			     */
	  if (*frame) (void)sbputchar(*frame,sb);  /* Use '\\' as quote	     */
	  else --frame;				   /* or ignore at end of str*/
      }						   /*			     */
    }						   /*			     */
  }						   /*			     */
}						   /*------------------------*/

#ifdef REGEX

/*-----------------------------------------------------------------------------
** Function*:	selector_hits()
** Type:	bool
** Purpose:	
**		
** Arguments:
**	rule	the rule
**	 db	the database
**	 rec	the record
** Returns:	
**___________________________________________________			     */
static bool selector_hits(rule, db, rec)	   /*                        */
  Rule rule;					   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
{ Symbol field = RuleFrame(rule);		   /*                        */
  Symbol value;					   /*                        */
  int len;					   /*                        */
 						   /*                        */
  if (field == NO_SYMBOL) { return true; }	   /*                        */
 						   /*                        */
  value = get_field(db, rec, field);		   /*                        */
#ifdef REGEX
  len	= (value ? symlen(value) : 0) ;		   /*                        */
  return (value &&				   /*                        */
	  SymbolValue(value) &&			   /*			     */
	  re_search(&RulePattern(rule),	   	   /*			     */
		    (char*)SymbolValue(value),	   /*                        */
		    len,	   		   /*                        */
		    0,			   	   /*                        */
		    len - 1,		   	   /*                        */
		    &reg) >= 0 );	   	   /*			     */
#else
  return true;					   /*                        */
#endif
}						   /*------------------------*/
#endif

/*-----------------------------------------------------------------------------
** Function*:	repl_regex()
** Purpose:	
**		
**
** Arguments:
**	field	the field
**	value	the replacement value
**	rule	the rule
**	db	the database
**	rec	the record
** Returns:	
**___________________________________________________			     */
static String repl_regex(field, value, rule, db, rec)/*			     */
  Symbol field;				   	   /*			     */
  Symbol value;				   	   /*			     */
  Rule	 rule;			   	   	   /*			     */
  DB	 db;				   	   /*                        */
  Record rec;			   	   	   /*			     */
{						   /*			     */
#ifdef REGEX
  String        val = SymbolValue(value);	   /*                        */
  char		c;			   	   /*			     */
  int		len;			   	   /*			     */
  StringBuffer	*sp;			   	   /* intermediate pointer   */
  bool		once_more;		   	   /*                        */
  int		limit;			   	   /* depth counter to break */
 						   /*  out of infinite loops */
  static StringBuffer *s1 = NULL;		   /*			     */
  static StringBuffer *s2 = NULL;		   /*			     */
						   /*			     */
  if (rule == RuleNULL) return val; 		   /*			     */
						   /*			     */
  if (s1 == NULL) { s1 = sbopen(); s2 = sbopen(); }/*			     */
  else		  { sbrewind(s1);  sbrewind(s2);  }/*			     */
						   /*			     */
  (void)sbputs((char*)val, s1);		   	   /*			     */
  val       = (String)sbflush(s1);	   	   /*			     */
  len	    = strlen((char*)val);   		   /*			     */
  limit     = rsc_rewrite_limit;		   /*			     */
  once_more = true;				   /*                        */
    					   	   /*			     */
  while (once_more) 				   /*			     */
  {						   /*			     */
    once_more = false;				   /*                        */
    while (rule)			   	   /*                        */
    {						   /*                        */
#ifdef DEBUG
      printf("+++ BibTool: repl_regex rule:0x%lx flags:0x%x field:%s <> %s\n",
	     (long)rule,			   /*                        */
	     RuleFlag(rule),			   /*                        */
	     (char*)SymbolValue(RuleField(rule)),  /*                        */
	     (char*)SymbolValue(field));	   /*                        */
#endif
      if ((RuleFlag(rule) & RULE_RENAME) != 0)	   /*                        */
      {						   /*                        */
	if (RuleField(rule) == field &&		   /*                        */
	    selector_hits(rule, db, rec))	   /*                        */
	{ int i;				   /*                        */
	  Symbol *hp;				   /*                        */
	  for (i = RecordFree(rec), hp = RecordHeap(rec);/*		     */
	       i > 0;				   /*			     */
	       i -= 2, hp += 2)			   /*			     */
	  {					   /*			     */
	    if (*hp == field)	   		   /*			     */
	    { field = *hp = RuleValue(rule);	   /*                        */
	      break;				   /*                        */
	    }					   /*                        */
	  }					   /*                        */
	}					   /*                        */
	rule = NextRule(rule);			   /*                        */
	limit = rsc_rewrite_limit;		   /*			     */
      }						   /*                        */
      else if ((RuleField(rule) == NULL	   	   /*			     */
		|| RuleField(rule) == field ) &&   /*			     */
	       (RuleFlag(rule) & RULE_ADD) == 0 && /*                        */
	       re_search(&RulePattern(rule),	   /*			     */
			 (char*)val,		   /*                        */
			 len,			   /*                        */
			 0,			   /*                        */
			 len - 1,		   /*                        */
			 &reg) >= 0 )		   /*			     */
      {					   	   /*			     */
	if (--limit < 0)			   /*                        */
	{ ErrPrintF2("\n*** BibTool WARNING: Rewrite limit exceeded for field %s\n\t\t     in record %s\n",
		     (char*)SymbolValue(field),	   /*                        */
		     (*RecordHeap(rec)		   /*                        */
		      ? (char*)SymbolValue(*RecordHeap(rec))/*               */
		      : "") );			   /*                        */
	  once_more = false;			   /*                        */
	  break;				   /*                        */
	}					   /*                        */
	if (RuleFrame(rule) == NO_SYMBOL)	   /*			     */
	{ return StringNULL; }		   	   /*			     */
						   /*			     */
	if (reg.start[0] > 0)		   	   /*			     */
	{ c = val[reg.start[0]];		   /* Push initial segment   */
	  val[reg.start[0]] = '\0';		   /*			     */
	  (void)sbputs((char*)val, s2);		   /*		             */
	  val[reg.start[0]] = c;		   /*			     */
	}					   /*			     */
						   /*			     */
	rewrite_1(SymbolValue(RuleFrame(rule)),	   /*                        */
		  s2,				   /*                        */
		  val,			   	   /*                        */
		  db,				   /*                        */
		  rec);				   /*		             */
	(void)sbputs((char*)(val+reg.end[0]), s2); /* Transfer the end.	     */
						   /*			     */
	val = (String)sbflush(s2);		   /* update the value	     */
	len = strlen((char*)val);		   /*  and its length	     */
	sp  = s1; s1 = s2; s2 = sp;		   /* rotate the two string  */
	sbrewind(s2);				   /*  buffers and reset     */
						   /*  the destination.      */
	once_more = true;			   /*                        */
      }						   /*                        */
      else					   /*                        */
      { rule = NextRule(rule);			   /*                        */
	limit = rsc_rewrite_limit;		   /*			     */
      }						   /*                        */
    }						   /*                        */
  }						   /*			     */
#endif
  return val;					   /* return the result.     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	check_regex()
** Purpose:	
**		
** Arguments:
**	field	the field
**	value	the value
**	rule	the rule
**	rec	the record
** Returns:	
**___________________________________________________			     */
static String check_regex(field, value, rule, db, rec)/*		     */
  Symbol	field;			   	   /*			     */
  Symbol	value;			   	   /*			     */
  Rule		rule;			   	   /*			     */
  DB		db;			   	   /*                        */
  Record	rec;			   	   /*			     */
{						   /*			     */
#ifdef REGEX
  int			len;			   /*			     */
  static StringBuffer	*s2 = 0L;		   /*			     */
						   /*			     */
  if (rule == RuleNULL) return SymbolValue(value); /*			     */
						   /*			     */
  if ( s2 == NULL ) { s2 = sbopen(); }		   /*			     */
  else		    { sbrewind(s2);  }		   /*			     */
						   /*			     */
  for ( len  =	symlen(value);		   	   /* Loop through all rules */
	rule != RuleNULL;			   /*			     */
	rule =	NextRule(rule) )		   /*			     */
  {						   /*			     */
    if ( (   RuleField(rule) == NO_SYMBOL	   /*			     */
	  || RuleField(rule) == field )		   /*			     */
	&&					   /*                        */
	 (   (RuleFlag(rule)&RULE_REGEXP) == 0	   /*                        */
	  || re_search(&RulePattern(rule),	   /*			     */
		       (char*)SymbolValue(value),  /*                        */
		       len,0,len-1,&reg) >=0 	   /*			     */
	 )					   /*                        */
       )					   /*			     */
    { if ( RuleFrame(rule) == NO_SYMBOL )	   /*			     */
      { return StringNULL; }			   /*			     */
      rewrite_1(SymbolValue(RuleFrame(rule)),	   /*                        */
		s2,				   /*                        */
		SymbolValue(value),		   /*                        */
		db,				   /*                        */
		rec);  				   /*		             */
      return (String)sbflush(s2);		   /* TODO: update the value?*/
    }						   /*                        */
  }						   /*			     */
#endif
  return StringNULL;				   /* return the result.     */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
/*---			    Rewrite Rule Section			  ---*/
/*---------------------------------------------------------------------------*/

 static Rule r_rule = RuleNULL;
 static Rule r_rule_end	= RuleNULL;

/*-----------------------------------------------------------------------------
** Function:	rename_field()
** Type:	void
** Purpose:	
**		
** Arguments:
**	spec	the argument
** Returns:	nothing
**___________________________________________________			     */
void rename_field(spec)				   /*			     */
  Symbol spec;					   /*                        */
{ String s = SymbolValue(spec);			   /*                        */
  Symbol from;					   /*                        */
  Symbol to;					   /*                        */
  Symbol field 	 = NO_SYMBOL;			   /*                        */
  Symbol pattern = NO_SYMBOL;		   	   /*                        */
 						   /*                        */
  sp_open(s);				   	   /*			     */
  sp_skip(&s);			   	   	   /*			     */
  if ((from = SParseSymbol(&s)) == NO_SYMBOL)      /*		             */
    return;					   /*			     */
  sp_skip(&s);			   	   	   /*			     */
  if ((to = SParseSymbol(&s)) == NO_SYMBOL)        /*		             */
    return;					   /*			     */
 						   /*                        */
  if (sp_expect(&s, s_if, false))	   	   /*                        */
  { if ((field = SParseOptionalSymbol(&s)) != NO_SYMBOL)/*	             */
    { sp_skip(&s);			   	   /*			     */
      if ((pattern = SParseValue(&s)) == NO_SYMBOL)/*		             */
      { if (to)    UnlinkSymbol(to);		   /*                        */
	if (from)  UnlinkSymbol(from);		   /*                        */
	if (field) UnlinkSymbol(field);		   /*                        */
	return;					   /*			     */
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
  if (sp_eos(&s) != StringNULL )		   /*                        */
  { if (to)      UnlinkSymbol(to);		   /*                        */
    if (from)    UnlinkSymbol(from);		   /*                        */
    if (field)   UnlinkSymbol(field);		   /*                        */
    if (pattern) UnlinkSymbol(pattern);		   /*                        */
    return;					   /*			     */
  }						   /*                        */
 						   /*                        */
  Rule rule = new_rule(from,			   /*                        */
		       to,		   	   /*                        */
		       pattern,			   /*                        */
		       field, 	   		   /*                        */
		       RULE_RENAME | RULE_REGEXP,  /*                        */
		       rsc_case_rewrite);	   /*                        */
  if (r_rule == RuleNULL)			   /*                        */
  { r_rule = r_rule_end = rule;			   /*                        */
  }		   				   /*			     */
  else					   	   /*                        */
  { NextRule(r_rule_end) = rule;		   /*                        */
    r_rule_end = rule;				   /*                        */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	add_rewrite_rule()
** Purpose:	Save a rewrite rule for later use.
**		The main task is performed by |add_rule()|.
** Arguments:
**	s	Rule to save
** Returns:	nothing
**___________________________________________________			     */
void add_rewrite_rule(s)			   /*			     */
  String s;				   	   /*			     */
{						   /*			     */
  DebugPrintF1("add rewrite rule\n");		   /*			     */
 						   /*                        */
  add_rule(s,					   /*                        */
	   &r_rule,				   /*                        */
	   &r_rule_end,				   /*                        */
	   RULE_REGEXP,				   /*                        */
	   rsc_case_rewrite);			   /*			     */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
/*---			       Keep Rule Section			  ---*/
/*---------------------------------------------------------------------------*/

#define K_RULES_SIZE 37

static Rule *k_rules = (Rule*)NULL;

/*-----------------------------------------------------------------------------
** Function:	keep_field()
** Type:	void
** Purpose:	
**		
** Arguments:
**	spec	the specification
** Returns:	nothing
**___________________________________________________			     */
void keep_field(spec)				   /*			     */
  Symbol spec;					   /*                        */
{ String s = SymbolValue(spec);			   /*                        */
  Symbol* names;				   /*                        */
  Symbol* np;				   	   /*                        */
  Symbol field 	 = NO_SYMBOL;			   /*                        */
  Symbol pattern = NO_SYMBOL;		   	   /*                        */
  int i;					   /*                        */
 						   /*                        */
  sp_open(s);				   	   /*			     */
  if ((names = sp_symbols(&s)) == NULL)    	   /*		             */
    return;					   /*			     */
 						   /*                        */
  if (sp_expect(&s, s_if, false))	   	   /*                        */
  { if ((field = SParseOptionalSymbol(&s)) != NO_SYMBOL)/*	             */
    { sp_skip(&s);			   	   /*			     */
      if ((pattern = SParseValue(&s)) == NO_SYMBOL)/*		             */
      { free_sym_array(names);			   /*                        */
	UnlinkSymbol(field);			   /*                        */
	return;					   /*			     */
      }						   /*                        */
    }						   /*                        */
    else					   /*                        */
    { free_sym_array(names);			   /*                        */
      return;					   /*                        */
    }						   /*                        */
  }						   /*                        */
  if (sp_eos(&s) != StringNULL )	   	   /*			     */
  { free_sym_array(names);			   /*                        */
    if (field)   UnlinkSymbol(field);		   /*                        */
    if (pattern) UnlinkSymbol(pattern);		   /*                        */
    return;					   /*			     */
  }						   /*                        */
 						   /*                        */
  if (k_rules == NULL)				   /*                        */
  { if ((k_rules=calloc(K_RULES_SIZE, sizeof(Rule))) == NULL)/*              */
    { OUT_OF_MEMORY("keep rules"); }		   /*                        */
  }						   /*                        */
 						   /*                        */
  for (np = names; *np; np++)			   /*                        */
  { LinkSymbol(*np);				   /*                        */
    Rule rule = new_rule(*np,			   /*                        */
			 NULL,		   	   /*                        */
			 pattern,		   /*                        */
			 field,			   /*                        */
			 RULE_KEEP | RULE_REGEXP,  /*                        */
			 true);	   	   	   /*                        */
    i = (int)(*np) % K_RULES_SIZE;		   /*                        */
    if (i < 0) i = -i;				   /*                        */
 						   /*                        */
    NextRule(rule) = k_rules[i];		   /*                        */
    k_rules[i] = rule;				   /*                        */
  }						   /*                        */
  						   /*                        */
  free_sym_array(names);			   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
/*---			      Check Rule Section			  ---*/
/*---------------------------------------------------------------------------*/

 static Rule c_rule = RuleNULL;
 static Rule c_rule_end = RuleNULL;

/*-----------------------------------------------------------------------------
** Function:	add_check_rule()
** Purpose:	Save a check rule for later use.
** Arguments:
**	s	Rule to save.
** Returns:	nothing
**___________________________________________________			     */
void add_check_rule(s)				   /*			     */
  String s;				   	   /*			     */
{						   /*			     */
  DebugPrintF1("add check rule\n");		   /*			     */
  add_rule(s,					   /*                        */
	   &c_rule,				   /*                        */
	   &c_rule_end,				   /*                        */
	   RULE_REGEXP,				   /*                        */
	   rsc_case_check);  			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	dont_keep()
** Type:	static bool
** Purpose:	
**		
** Arguments:
**	sym	the symbol
**	rec	the record
**	db	the database
** Returns:	
**___________________________________________________			     */
static bool dont_keep(sym,rec,db)		   /*                        */
  Symbol sym;					   /*                        */
  Record rec;					   /*                        */
  DB     db;					   /*                        */
{ Rule   r;					   /*                        */
  int    idx = (int)(sym) % K_RULES_SIZE;	   /*                        */
  if (idx < 0) idx = -idx;			   /*                        */
 						   /*                        */
  for (r = k_rules[idx]; r; r = NextRule(r))	   /*                        */
  {						   /*                        */
    if (RuleField(r) == sym &&			   /*                        */
	selector_hits(r, db, rec))		   /*                        */
    { return false; }				   /*                        */
  }						   /*                        */
  return true;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rewrite_record()
** Purpose:	Apply deletions, checks, additions, and rewriting steps
**		in this order.
** Arguments:
**	rec	Actual record to apply things to.
**	db	The database record is belonging to.
** Returns:	nothing
**___________________________________________________			     */
void rewrite_record(db, rec)			   /*			     */
  DB		  db;				   /*                        */
  register Record rec;				   /*			     */
{ register int	  i;				   /*			     */
  register Symbol *hp;				   /* heap pointer	     */
  register Macro  mac;				   /*			     */
  String          cp;				   /*			     */
  static StringBuffer *sb = NULL;		   /*                        */
 						   /*                        */
  if (sb == NULL) sb = sbopen();		   /*                        */
						   /*			     */
  if (c_rule)			   		   /*			     */
  {						   /*                        */
    for (i = RecordFree(rec), hp = RecordHeap(rec);/*			     */
	 i > 0;				   	   /*			     */
	 i -= 2, hp +=2)			   /*			     */
    {						   /*			     */
      if (   *hp				   /*			     */
	  && *(hp+1)				   /*			     */
	  && StringNULL !=			   /*			     */
	     (cp=check_regex(*hp,	   	   /*                        */
			     *(hp+1), 		   /*                        */
			     c_rule,		   /*                        */
			     db,		   /*                        */
			     rec))		   /*		             */
	  )					   /*			     */
      { Err(cp); }				   /*			     */
    }						   /*			     */
  }						   /*			     */
						   /*			     */
  if (r_rule)			   		   /*			     */
  {   						   /*			     */
    for (i = RecordFree(rec), hp = RecordHeap(rec);/*			     */
	 i > 0;					   /*			     */
	 i -= 2, hp += 2)			   /*			     */
    {						   /*			     */
      if (*hp && *(hp+1))			   /*			     */
      {						   /*			     */
	cp = repl_regex(*hp,*(hp+1),r_rule,db,rec);/*			     */
	if (cp == StringNULL)		   	   /*			     */
	{ if (*hp) UnlinkSymbol(*hp);		   /*                        */
	  if (*(hp+1)) UnlinkSymbol(*(hp+1));	   /*                        */
	  *hp = *(hp+1) = NO_SYMBOL;		   /*                        */
	}					   /*                        */
	else if (strcmp((char*)cp,		   /*                        */
			(char*)SymbolValue(*(hp+1))))/*		             */
	{ if (*(hp+1)) UnlinkSymbol(*(hp+1));	   /*                        */
	  *(hp+1) = symbol(cp);			   /*                        */
	}		   			   /*			     */
      }						   /*			     */
    }						   /*			     */
  }						   /*			     */
						   /*                        */
  if (k_rules)			   		   /*			     */
  {						   /*                        */
    for (i = RecordFree(rec), hp = RecordHeap(rec);/*			     */
	 i > 0;					   /*			     */
	 i -= 2, hp += 2)			   /*			     */
    {						   /*			     */
      if (*hp &&				   /*                        */
	  *(hp+1) &&				   /*                        */
	  dont_keep(sym_star, rec, db) &&	   /*                        */
	  dont_keep(*hp, rec, db))		   /*                        */
      { if (*hp) UnlinkSymbol(*hp);		   /*                        */
	if (*(hp+1)) UnlinkSymbol(*(hp+1));	   /*                        */
	*hp = *(hp+1) = NO_SYMBOL;		   /*                        */
      }						   /*			     */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  for (mac = addlist;				   /* Add all items in the   */
       mac;					   /*  add list		     */
       mac = NextMacro(mac) )			   /*			     */
  { cp = SymbolValue(MacroValue(mac));		   /*                        */
    sbrewind(sb);				   /*                        */
    sbputc('{',sb);				   /*                        */
    while ( *cp )				   /*                        */
    {						   /*                        */
      if ( *cp == '%' )			   	   /*                        */
      { if ( *(cp+1) == '%' )			   /*                        */
        { sbputc(*cp,sb); cp+=2; }		   /*                        */
        else { cp = fmt_expand(sb,cp,db,rec); }    /*                        */
      }					   	   /*                        */
      else { sbputc(*cp,sb); cp++; }		   /*                        */
    }						   /*                        */
    sbputc('}', sb);				   /*                        */
    push_to_record(rec,			   	   /*                        */
		   MacroName(mac),		   /*                        */
		   symbol((String)sbflush(sb)));   /*                        */
  }						   /*			     */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
/*---			    Extract Rule Section			  ---*/
/*---------------------------------------------------------------------------*/

 static Rule x_rule = RuleNULL;
 static Rule x_rule_end = RuleNULL;

/*-----------------------------------------------------------------------------
** Function:	add_extract()
** Purpose:	Save an extraction rule for later use. The argument is
**		interpreted as regular expression to be matched
**		against the field value.
**
**		The value of |rsc_case_select| at the invocation of
**		this function determines whether the matching is
**		performed case sensitive or not.
** Arguments:
**	s	Rule to save.
**	regexp	Boolean value indicating whether regular expressions
**		should be used. If not set then plain string matching
**		is performed. 
**	notp	Boolean value indicating whether the result should be
**		negated. 
** Returns:	nothing
**___________________________________________________			     */
void add_extract(s,regexp,notp)			   /*			     */
  Symbol s;				   	   /*			     */
  int regexp;					   /*                        */
  int notp;					   /*                        */
{						   /*                        */
  add_rule(SymbolValue(s),			   /* The main task is       */
	   &x_rule,				   /*  performed by          */
	   &x_rule_end,				   /*  |add_rule()|.         */
	   (regexp?RULE_REGEXP:RULE_NONE) |	   /*                        */
	   (notp  ?RULE_NOT   :RULE_NONE) ,	   /*                        */
	   !rsc_case_select);			   /*			     */
  rsc_select = true;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	save_regex()
** Purpose:	Save an extraction rule for later use.
**		Only the regular expression of the rule is given as argument.
**		The fields are taken from the resource select.fields.
** Arguments:
**	s	Regular expression to search for.
** Returns:	nothing
**___________________________________________________			     */
void save_regex(s)				   /*                        */
  String s;				   	   /*                        */
{ String t = malloc( (size_t)strlen((char*)s)	   /*                        */
		   + (size_t)strlen((char*)rsc_sel_fields)/*                 */
		   + 4 );			   /*			     */
  if ( t == NULL ) { OUT_OF_MEMORY("string"); }	   /*			     */
 						   /*                        */
  (void)strcpy((char*)t, (char*)rsc_sel_fields);   /*			     */
  (void)strcat((char*)t, " \"");		   /*			     */
  (void)strcat((char*)t, (char*)s);		   /*			     */
  (void)strcat((char*)t, "\"");			   /*			     */
 						   /*                        */
  add_rule(t,				   	   /*                        */
	   &x_rule,				   /*                        */
	   &x_rule_end,				   /*                        */
	   RULE_REGEXP,				   /*                        */
	   !rsc_case_select);			   /*			     */
 						   /*                        */
  free((char*)t);				   /*                        */
  rsc_select = true;				   /*                        */
}						   /*------------------------*/


 static char s_class[256];			   /*                        */
 static String s_ignored = (String)NULL;	   /*                        */
 static int  s_cased    = -33;			   /*                        */

/*-----------------------------------------------------------------------------
** Function*:	init_s_search()
** Purpose:	
**		
**		
** Arguments:
**	ignored	the letters to be ignored
** Returns:	Nothing
**___________________________________________________			     */
static void init_s_search(ignored)		   /*                        */
  String ignored;				   /*                        */
{ int i;					   /*                        */
  for (i = 0; i < 256; i++) s_class[i] = i;	   /*                        */
 						   /*                        */
  if (!rsc_case_select) 			   /*                        */
  {						   /*                        */
    s_class['a'] = 'A';				   /*                        */
    s_class['b'] = 'B';				   /*                        */
    s_class['c'] = 'C';				   /*                        */
    s_class['d'] = 'D';				   /*                        */
    s_class['e'] = 'E';				   /*                        */
    s_class['f'] = 'F';				   /*                        */
    s_class['g'] = 'G';				   /*                        */
    s_class['h'] = 'H';				   /*                        */
    s_class['i'] = 'I';				   /*                        */
    s_class['j'] = 'J';				   /*                        */
    s_class['k'] = 'K';				   /*                        */
    s_class['l'] = 'L';				   /*                        */
    s_class['m'] = 'M';				   /*                        */
    s_class['n'] = 'N';				   /*                        */
    s_class['o'] = 'O';				   /*                        */
    s_class['p'] = 'P';				   /*                        */
    s_class['q'] = 'Q';				   /*                        */
    s_class['r'] = 'R';				   /*                        */
    s_class['s'] = 'S';				   /*                        */
    s_class['t'] = 'T';				   /*                        */
    s_class['u'] = 'U';				   /*                        */
    s_class['v'] = 'V';				   /*                        */
    s_class['w'] = 'W';				   /*                        */
    s_class['x'] = 'X';				   /*                        */
    s_class['y'] = 'Y';				   /*                        */
    s_class['z'] = 'Z';				   /*                        */
  }						   /*                        */
  while ( *ignored )				   /*                        */
  { s_class[(unsigned int)(*(ignored++))] = '\0'; }/*                        */
 						   /*                        */
  s_cased   = rsc_case_select;			   /*                        */
  s_ignored = rsc_sel_ignored;	   	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	s_match()
** Purpose:	
**		
**		
** Arguments:
**	pattern	the pattern
**	s	the string
** Returns:	
**___________________________________________________			     */
static bool s_match(p,s)			   /*                        */
  String  p;					   /*                        */
  String  s;					   /*                        */
{						   /*                        */
  while (*p && s_class[(unsigned int)*p] == '\0') p++;/*                     */
 						   /*                        */
  while (*p)					   /*                        */
  {						   /*                        */
    while (*s && s_class[(unsigned int)*s] == '\0') s++;/*                   */
 						   /*                        */
    if (s_class[(unsigned int)*s] != s_class[(unsigned int)*p]) return false;
    while (*p && s_class[(unsigned int)*p] == '\0') p++;/*                   */
    if (*s) s++;				   /*                        */
    if (*p) p++;				   /*                        */
  }						   /*                        */
  return true;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	s_search()
** Purpose:	Match a pattern against all positions in a string.
** Arguments:
**	pattern	the pattern
**	s	the string
** Returns:	If a match is found then |true| is returned. Otherwise
**		|false|.
**___________________________________________________			     */
static bool s_search(pattern,s)			   /*                        */
  String  pattern;				   /*                        */
  String  s;					   /*                        */
{						   /*                        */
  if ( s_cased != rsc_case_select ||		   /*                        */
       strcmp((char*)s_ignored,			   /*                        */
	      (char*)rsc_sel_ignored) != 0 )	   /*                        */
  { init_s_search(rsc_sel_ignored); }		   /*                        */
 						   /*                        */
  for ( ; *s; s++ )				   /*                        */
  { if (s_match(pattern,s)) return true;	   /*                        */
  }						   /*                        */
  return false;					   /*                        */
}						   /*------------------------*/

#define ReturnIf(COND)					\
  if ( COND )						\
  { if ( !(RuleFlag(rule) & RULE_NOT) ) return true; }	\
  else							\
  { if (  (RuleFlag(rule) & RULE_NOT) ) return true; }

/*-----------------------------------------------------------------------------
** Function:	is_selected()
** Purpose:	Boolean function to decide whether a record should be
**		considered. These selections are described by a set of
**		regular expressions which are applied. If none are
**		given then the match simply succeeds.
** Arguments:
**	db	Database containing the record.
**	rec	Record to look at.
** Returns:	|true| iff the record is seleced by a regexp or none is
**		given.
**___________________________________________________			     */
bool is_selected(db,rec)			   /*			     */
  DB     db;					   /*                        */
  Record rec;			   		   /*			     */
{						   /*			     */
  int	 len, i;				   /*			     */
  Symbol value;				   	   /*                        */
  Rule   rule;					   /*                        */
 						   /*                        */
  if ( (rule=x_rule) == RuleNULL ||		   /* If no rule is given or */
       !rsc_select	   			   /*  no selection is       */
     )				   		   /*  requested then        */
    return true;				   /*  select all records.   */
 						   /*                        */
  for ( ;			   		   /* Loop through all rules */
	rule != RuleNULL;			   /*			     */
	rule =	NextRule(rule) )		   /*			     */
  {						   /*			     */
    if ( RuleField(rule) == NULL )		   /* If no field is given   */
    {						   /*  then try all normal   */
      if ( RuleFlag(rule) & RULE_REGEXP )	   /*                        */
      {						   /*                        */
#ifdef REGEX
	if ( RecordHeap(rec)[0] )		   /*                        */
	{ len = symlen(RecordHeap(rec)[0]);	   /*                        */
	  ReturnIf(re_search(&RulePattern(rule),   /*			     */
			     (char*)SymbolValue(RecordHeap(rec)[0]),/*       */
			     len,		   /*                        */
			     0,		   	   /*                        */
			     len - 1,		   /*                        */
			     &reg) >= 0 );	   /*		             */
	}					   /*                        */
	for (i = 2; i < RecordFree(rec); i += 2 )  /*                        */
	{ if ( RecordHeap(rec)[i] )		   /*                        */
	  { len = symlen(RecordHeap(rec)[i+1]);	   /*                        */
	    ReturnIf(re_search(&RulePattern(rule), /*			     */
			       (char*)SymbolValue(RecordHeap(rec)[i+1]),/*   */
			       len,		   /*                        */
			       0,		   /*                        */
			       len - 1,		   /*                        */
			       &reg) >= 0 );	   /*		             */
	  }					   /*                        */
	}					   /*                        */
#endif
      }						   /*                        */
      else					   /*                        */
      {						   /*                        */
	if ( SymbolValue(RecordHeap(rec)[0]) )	   /*                        */
	{ ReturnIf(s_search(SymbolValue(RuleGoal(rule)),/*		     */
			    SymbolValue(RecordHeap(rec)[0])) );/*	     */
	}					   /*                        */
	for (i = 2; i < RecordFree(rec); i += 2 )  /*                        */
	{ if ( RecordHeap(rec)[i] )		   /*                        */
	  { ReturnIf(s_search(SymbolValue(RuleGoal(rule)),/*		     */
			      SymbolValue(RecordHeap(rec)[i+1])) );/*	     */
	  }					   /*                        */
	}					   /*                        */
      }						   /*                        */
    }						   /*                        */
    else if ( (value=get_field(db,		   /*                        */
			       rec,		   /*                        */
			       RuleField(rule)))   /*                        */
	     != NO_SYMBOL )			   /*                        */
    {						   /*                        */
      if ( RuleFlag(rule) & RULE_REGEXP )	   /*                        */
      {						   /*                        */
#ifdef REGEX
	len = symlen(value);   			   /*                        */
        ReturnIf(re_search(&RulePattern(rule),	   /*			     */
			   (char*)SymbolValue(value),/*                      */
			   len,			   /*                        */
			   0,			   /*                        */
			   len - 1,		   /*                        */
			   &reg) >=0 ) 		   /*			     */
#endif
      }						   /*                        */
      else ReturnIf(s_search(SymbolValue(RuleGoal(rule)),/*                  */
			     SymbolValue(value)))  /*                        */
    }						   /*			     */
    else if ( RuleFlag(rule) & RULE_NOT )	   /*                        */
    { return true;				   /*                        */
    }						   /*                        */
  }						   /*                        */
  return false;				   	   /* return the result.     */
}						   /*------------------------*/

#ifdef REGEX
#endif

/*-----------------------------------------------------------------------------
** Function:	set_regex_syntax()
** Type:	int
** Purpose:	experimental
**		
** Arguments:
**	name	
** Returns:	nothing
**___________________________________________________			     */
int set_regex_syntax(name)			   /*                        */
  char* name;					   /*                        */
{						   /*                        */
#ifdef REGEX
  if ( strcmp(name,"emacs")  == 0 )		   /*                        */
  { re_set_syntax(RE_SYNTAX_EMACS); }		   /*                        */
  else if ( strcmp(name,"awk") == 0 )		   /*                        */
  { re_set_syntax(RE_SYNTAX_AWK); }		   /*                        */
  else if ( strcmp(name,"grep") == 0 )		   /*                        */
  { re_set_syntax(RE_SYNTAX_GREP); }		   /*                        */
  else if ( strcmp(name,"egrep") == 0 )		   /*                        */
  { re_set_syntax(RE_SYNTAX_EGREP); }		   /*                        */
  else if ( strcmp(name,"posix_awk") == 0 )	   /*                        */
  { re_set_syntax(RE_SYNTAX_POSIX_AWK); }	   /*                        */
  else if ( strcmp(name,"posix_egrep") == 0 )	   /*                        */
  { re_set_syntax(RE_SYNTAX_POSIX_EGREP); }	   /*                        */
  else if ( strcmp(name,"ed") == 0 )		   /*                        */
  { re_set_syntax(RE_SYNTAX_ED); }		   /*                        */
  else if ( strcmp(name,"sed") == 0 )		   /*                        */
  { re_set_syntax(RE_SYNTAX_SED); }		   /*                        */
  else						   /*                        */
  { WARNING3("Unknown regexp syntax: ",name,"\n"); /*                        */
    return 1;					   /*                        */
  }						   /*                        */
#endif
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_regex_syntax()
** Type:	char*
** Purpose:	Getter for the regex syntax.
**		
** Arguments:	none
** Returns:	
**___________________________________________________			     */
char* get_regex_syntax()			   /*                        */
{						   /*                        */
#ifdef REGEX
  switch(re_syntax_options)			   /*                        */
  { case RE_SYNTAX_EMACS:       return "emacs";	   /*                        */
    case RE_SYNTAX_AWK:         return "awk";	   /*                        */
    case RE_SYNTAX_GREP:        return "grep";	   /*                        */
    case RE_SYNTAX_EGREP:       return "egrep";	   /*                        */
    case RE_SYNTAX_POSIX_AWK:   return "posix_awk";/*                        */
    case RE_SYNTAX_POSIX_EGREP: return "posix_egrep";/*                      */
    case RE_SYNTAX_SED:         return "sed";	   /*                        */
  }						   /*                        */
#endif
  return "";				   	   /*                        */
}						   /*------------------------*/
