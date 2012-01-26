/******************************************************************************
** $Id: rewrite.c,v 1.9 2012-01-26 19:54:21 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2012 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
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

#ifdef REGEX
#include <bibtool/regex.h>
#endif

 typedef struct rULE
 { Uchar		    *rr_field;
   Uchar		    *rr_goal;
   Uchar		    *rr_frame;
   int			    rr_flag;
   struct rULE		    *rr_next;
#ifdef REGEX
   struct re_pattern_buffer rr_pat_buff;
#endif
 } SRule, *Rule;

#define RuleNULL	(Rule)0

#define RuleField(X)	((X)->rr_field)
#define RuleGoal(X)	((X)->rr_goal)
#define RulePattern(X)	((X)->rr_pat_buff)
#define RuleFrame(X)	((X)->rr_frame)
#define NextRule(X)	((X)->rr_next)
#define RuleFlag(X)	((X)->rr_flag)

#define RULE_NONE	0x00
#define RULE_ADD	0x01
#define RULE_REGEXP	0x02
#define RULE_NOT	0x04

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int is_selected _ARG((DB db,Record rec));
 int set_regex_syntax _ARG((char* name));
 static Rule new_rule _ARG((Uchar *field,Uchar *pattern,Uchar *frame,int flags,int casep));
 static Uchar * check_regex _ARG((Uchar *field,Uchar *value,Rule rule,DB db,Record rec));
 static Uchar * repl_regex _ARG((Uchar *field,Uchar *value,Rule rule,DB db,Record rec));
 static int s_match _ARG((Uchar * p,Uchar * s));
 static int s_search _ARG((Uchar * pattern,Uchar * s));
 static void add_rule _ARG((Uchar *s,Rule *rp,Rule *rp_end,int flags,int casep));
 static void free_rule _ARG((Rule rule));
 static void init_s_search _ARG((char * ignored));
 static void rewrite_1 _ARG((Uchar *frame,StringBuffer *sb,Uchar *match,DB db,Record rec));
 void add_check_rule _ARG((Uchar *s));
 void add_extract _ARG((Uchar *s,int regexp,int notp));
 void add_field _ARG((Uchar *spec));
 void add_rewrite_rule _ARG((Uchar *s));
 void clear_addlist _ARG((void));
 void remove_field _ARG((Uchar *field,Record rec));
 void rewrite_record _ARG((DB db,Record rec));
 void save_regex _ARG((Uchar *s));

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/


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
** Function:	add_field()
** Purpose:	Save a token and value for addition.
** Arguments:
**	spec	A string of the form
**		  token=value
** Returns:	nothing
**___________________________________________________			     */
void add_field(spec)				   /*			     */
  Uchar *spec;					   /*			     */
{ register Uchar *field, *value;		   /*			     */
						   /*			     */
  (void)sp_open(spec);				   /*			     */
  if ( (field = SParseSymbol(&spec)) == (Uchar*)NULL )/*		     */
    return;					   /*			     */
  (void)SParseSkip(&spec);			   /*			     */
  if ( (value=SParseValue(&spec)) == (Uchar*)NULL )/*			     */
    return;					   /*			     */
  (void)SParseEOS(&spec);			   /*			     */
						   /*			     */
  addlist = new_macro(field,value,addlist,0);	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	remove_field()
** Purpose:	Remove the given field from record.
** Arguments:
**	field	This is a symbol containing the name of the field to remove.
**	rec	Record in which the field should be removed.
** Returns:	nothing
**___________________________________________________			     */
void remove_field(field,rec)			   /*			     */
  register Uchar *field;			   /*			     */
  Record	 rec;				   /*			     */
{ register int	 i;				   /*			     */
						   /*			     */
  for (i=0;i<RecordFree(rec);i+=2 )		   /*			     */
  { if ( field == RecordHeap(rec)[i] )		   /* compare symbols	     */
    { RecordHeap(rec)[i] = (Uchar*)NULL; }	   /*			     */
  }						   /*			     */
						   /*			     */
  while ( RecordFree(rec) > 0 &&		   /* Adjust Heap Length     */
	  RecordHeap(rec)[RecordFree(rec)-2] == NULL )/*		     */
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
** Function:	new_rule()
** Purpose:	Allocate a new Rule and fill some slots.
** Arguments:
**	field	The field to apply this rule to, or |NULL| for each field.
**	pattern	
**	frame	
**	flags	
**	casep	Boolean; indicating case sensitive comparison.
** Returns:	A pointer to the allocated structure or |NULL| upon failure.
**___________________________________________________			     */
static Rule new_rule(field,pattern,frame,flags,casep)/*			     */
  Uchar		*field;				   /*			     */
  Uchar		*pattern;			   /*			     */
  Uchar		*frame;				   /*			     */
  int		flags;				   /*			     */
  int		casep;				   /*			     */
{ register Rule new;				   /*			     */
  static int init = 1;				   /*                        */
 						   /*                        */
#ifdef REGEX
  if ( init )					   /*                        */
  { init = 0;					   /*                        */
    reg.num_regs = 32;				   /*                        */
    reg.start = (regoff_t*)calloc(32,sizeof(regoff_t));/*                    */
    reg.end   = (regoff_t*)calloc(32,sizeof(regoff_t));/*                    */
    if ( reg.start == NULL || reg.end == NULL )	   /*                        */
    { OUT_OF_MEMORY("rewite rule"); } 		   /*			     */
  }						   /*                        */
#endif
						   /*			     */
  if ( (new=(Rule)malloc(sizeof(SRule))) == RuleNULL )/*		     */
  { OUT_OF_MEMORY("rewite rule"); } 		   /*			     */
						   /*			     */
  RuleField(new) = field;			   /*			     */
  RuleFrame(new) = frame;			   /*			     */
  RuleFlag(new)  = flags;			   /*			     */
  NextRule(new)	 = RuleNULL;			   /*			     */
  RuleGoal(new)  = pattern;			   /*                        */
					       	   /*                        */
#ifdef REGEX
  if ( *pattern && (flags&RULE_REGEXP) )   	   /*                        */
  { char *msg;					   /*                        */
    if ( (RulePattern(new).buffer = (unsigned char *)malloc(16)) == NULL )/* */
    { OUT_OF_MEMORY("pattern"); }		   /*			     */
    RulePattern(new).allocated = 16;		   /*			     */
    RulePattern(new).syntax    = RE_SYNTAX_EMACS;  /*			     */
    RulePattern(new).translate = (casep?trans_lower:NULL);/*		     */
    RulePattern(new).fastmap   = NULL;		   /*			     */
    RulePattern(new).regs_allocated = REGS_FIXED;  /*			     */
						   /*			     */
    msg = (char*)re_compile_pattern((char*)pattern,/*			     */
				    strlen((char*)pattern),/*		     */
				    &RulePattern(new) );/*	             */
						   /*			     */
    if ( msg ) { Err(msg); return NULL; }	   /*			     */
  }						   /*                        */
  else						   /*                        */
  {						   /*                        */
    RuleFlag(new) = (flags&~RULE_REGEXP);	   /*                        */
  }						   /*                        */
#endif
  return new;					   /*			     */
}						   /*------------------------*/

#ifdef UNUSED
/*-----------------------------------------------------------------------------
** Function:	free_rule()
** Purpose:	Free a list of rules.
**		
**		
** Arguments:
**	rule	First rule in the list.
** Returns:	nothing
**___________________________________________________			     */
static void free_rule(rule)			   /*                        */
  Rule rule;					   /*                        */
{ Rule next;					   /*                        */
 						   /*                        */
  while ( rule )				   /*                        */
  { next = NextRule(rule);			   /*                        */
#ifdef REGEX
    free (RulePattern(rule).buffer);		   /*                        */
#endif
    free(rule);					   /*                        */
    rule = next;				   /*                        */
  }						   /*                        */
}						   /*------------------------*/
#endif

/*-----------------------------------------------------------------------------
** Function:	add_rule()
** Purpose:	Generic addition of a rule to a list of rules.
** Arguments:
**	s	
**	rp	
**	rp_end	
**	flags	
**	casep	
** Returns:	nothing
**___________________________________________________			     */
static void add_rule(s,rp,rp_end,flags,casep)	   /*			     */
  Uchar		*s;				   /*			     */
  Rule		*rp;				   /*			     */
  Rule		*rp_end;			   /*			     */
  int		flags;				   /*                        */
  int		casep;				   /*			     */
{ Uchar		*field;				   /*			     */
  Uchar		*pattern;			   /*			     */
  Uchar		*frame;				   /*			     */
  Rule		rule;				   /*			     */
  int		sp;				   /*                        */
  int		stackp;				   /* stack pointer for the  */
  static Uchar	**stack;			   /* local stack of fields  */
  static int    stacksize = 0;			   /*                        */
 						   /*                        */
  if ( stacksize == 0 )				   /*                        */
  { stacksize++;				   /*                        */
    if ((stack=(Uchar**)malloc(sizeof(Uchar*)))==(Uchar**)NULL)/*            */
    { OUT_OF_MEMORY("rule stack"); }		   /*                        */
  }						   /*                        */
  stackp = 0;					   /*                        */
						   /*			     */
  DebugPrint2("Adding rule: Parsing from: ",s);	   /*			     */
  (void)sp_open(s);				   /*			     */
  (void)SParseSkip(&s);				   /*			     */
						   /*			     */
  while (*s && *s != '"')			   /*                        */
  {
    DebugPrint2("\tlooking for symbol in: ",s);	   /*			     */
    field = SParseSymbol(&s);			   /*                        */
    DebugPrint2("\tok ",s);
    if ( field == NULL)	   			   /*                        */
    {						   /*                        */
      DebugPrint2("\tno symbol found in: ",s);	   /*			     */
      return; }					   /*                        */
    DebugPrint1("\tok ");
    DebugPrint2("field   = ",field);	   	   /*			     */
    (void)SParseSkip(&s);			   /*                        */
						   /*			     */
    if ( stackp > stacksize )			   /*                        */
    { stacksize += 8;				   /*                        */
      if ( (stack=(Uchar**)realloc((char*)stack,   /*                        */
				  stacksize*sizeof(char*)))==NULL)/*         */
      { OUT_OF_MEMORY("rule stack"); }		   /*                        */
    }						   /*                        */
    stack[stackp++] = field;			   /*                        */
  }						   /*                        */
						   /*			     */
  if ( *s == '\0' )				   /*			     */
  { pattern = symbol((Uchar*)"."); }		   /*			     */
  else if ( (pattern=SParseUnquotedString(&s)) == NULL )/*		     */
  { DebugPrintF1("No pattern found");		   /*                        */
    return;					   /*			     */
  }						   /*                        */
						   /*			     */
  DebugPrint2("pattern = ",pattern);		   /*			     */
  (void)SParseSkip(&s);				   /*			     */
						   /*			     */
  if ( *s == '\0' )				   /*			     */
  { frame = (Uchar*)NULL; }			   /*			     */
  else if ( (frame=SParseUnquotedString(&s)) == NULL )/*		     */
  { return; }					   /*			     */
  else						   /*			     */
  { (void)SParseEOS(&s); }			   /*			     */
  DebugPrint2("frame  = ",frame);		   /*			     */
#ifdef DEBUG
  DebugPrintF1("+++ BibTool: flags   = ");	   /*			     */
  if (flags & RULE_NOT) DebugPrintF1(" NOT"); 	   /*                        */
  if (flags & RULE_ADD) DebugPrintF1(" ADD"); 	   /*                        */
  if (flags & RULE_REGEXP) DebugPrintF1(" REGEXP"); /*                       */
  DebugPrintF1("\n");		   		   /*			     */
#endif
						   /*			     */
  if ( stackp == 0 )				   /* No field specified.    */
  { rule = new_rule((Uchar*)0,pattern,frame,flags,casep); /*		     */
    if ( *rp == RuleNULL )			   /*                        */
    { *rp = *rp_end = rule; }			   /*			     */
    else					   /*                        */
    { NextRule(*rp_end) = rule; *rp_end = rule;}   /*			     */
    return;					   /*                        */
  }						   /*                        */
 						   /*                        */
  for ( sp=0; sp<stackp; sp++ )			   /*                        */
  { rule = new_rule(stack[sp],pattern,frame,flags,casep);/*		     */
    if ( *rp == RuleNULL )			   /*                        */
    { *rp = *rp_end = rule; }			   /*			     */
    else					   /*                        */
    { NextRule(*rp_end) = rule; *rp_end = rule;}   /*			     */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rewrite_1()
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
  Uchar		*frame;			   	   /*			     */
  StringBuffer	*sb;			   	   /*			     */
  Uchar		*match;			   	   /*			     */
  DB		db;			   	   /*                        */
  Record	rec;			   	   /*			     */
{						   /*			     */
  for ( ; *frame; frame++ )			   /*			     */
  { if ( *frame == '%' )			   /*	                     */
    { frame = fmt_expand(sb,frame,db,rec);	   /*                        */
    }		   				   /*	                     */
    else if ( *frame != '\\' )			   /* Transfer normal	     */
    { (void)sbputchar(*frame,sb); }		   /*	characters.	     */
    else					   /*			     */
    {						   /*			     */
      switch ( *++frame )			   /*			     */
      { case '1': case '2': case '3':		   /*			     */
	case '4': case '5': case '6':		   /*			     */
	case '7': case '8': case '9':		   /*			     */
#ifdef REGEX
	  { int i = *frame - '0';		   /* Look for register no   */
	    int e = reg.end[i];			   /* get end of match	     */
						   /*			     */
	    for ( i=reg.start[i]; i<e; ++i )	   /* transfer from start    */
	    { (void)sbputchar(match[i],sb); }	   /*	to end of match.     */
	  }					   /*			     */
#endif
	  break;				   /*			     */
	case '$':				   /*			     */
	  (void)sbputs(*RecordHeap(rec),sb);	   /*			     */
	  break;				   /*			     */
	case '@':				   /*			     */
	  (void)sbputs(EntryName(RecordType(rec)),sb);/*		     */
	  break;				   /*			     */
	case 'n': (void)sbputchar('\n',sb); break; /*			     */
	case 't': (void)sbputchar('\t',sb); break; /*			     */
	default:				   /*			     */
	  if ( *frame ) (void)sbputchar(*frame,sb);/* Use '\\' as quote	     */
	  else --frame;				   /* or ignore at end of str*/
      }						   /*			     */
    }						   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	repl_regex()
** Purpose:	
**		
**
** Arguments:
**	field
**	value
**	rule
**	rec
** Returns:	
**___________________________________________________			     */
static Uchar * repl_regex(field,value,rule,db,rec)  /*			     */
  Uchar	 *field;				   /*			     */
  Uchar	 *value;				   /*			     */
  Rule	 rule;			   	   	   /*			     */
  DB	 db;				   	   /*                        */
  Record rec;			   	   	   /*			     */
{						   /*			     */
#ifdef REGEX
  char			c;			   /*			     */
  int			len;			   /*			     */
  StringBuffer		*sp;			   /* intermediate pointer   */
  int			once_more;		   /*                        */
  int			limit;			   /* depth counter to break */
 						   /*  out of infinite loops */
  static StringBuffer	*s1 = 0L;		   /*			     */
  static StringBuffer	*s2 = 0L;		   /*			     */
						   /*			     */
  if ( rule == RuleNULL ) return value;		   /*			     */
						   /*			     */
  if ( s1 == NULL ) { s1 = sbopen(); s2 = sbopen(); }/*			     */
  else		    { sbrewind(s1);  sbrewind(s2);  }/*			     */
						   /*			     */
  (void)sbputs(value,s1);			   /*			     */
  value     = (Uchar*)sbflush(s1);		   /*			     */
  len	    = strlen((char*)value);		   /*			     */
  limit     = rsc_rewrite_limit;		   /*			     */
  once_more = TRUE;				   /*                        */
    					   	   /*			     */
  while ( once_more ) 				   /*			     */
  {						   /*			     */
    once_more = FALSE;				   /*                        */
    while ( rule != RuleNULL )			   /*                        */
    {						   /*                        */
      if ( (   RuleField(rule) == NULL		   /*			     */
	    || RuleField(rule) == field ) &&	   /*			     */
	   (RuleFlag(rule) & RULE_ADD) == 0 &&	   /*                        */
	   re_search(&RulePattern(rule),	   /*			     */
		     value,			   /*                        */
		     len,			   /*                        */
		     0,				   /*                        */
		     len-1,			   /*                        */
		     &reg) >=0 )		   /*			     */
      {					   	   /*			     */
	if ( 0 > --limit )			   /*                        */
	{ ErrPrint("\n*** BibTool WARNING: Rewrite limit exceeded for field ");
	  ErrPrint((char*)field);		   /*                        */
	  ErrPrint("\n\t\t     in record ");	   /*                        */
	  ErrPrint((*RecordHeap(rec)?(char*)*RecordHeap(rec):""));/*         */
	  ErrPrint("\n");			   /*                        */
	  once_more = FALSE;			   /*                        */
	  break;				   /*                        */
	}					   /*                        */
	if ( RuleFrame(rule) == (Uchar*)NULL )	   /*			     */
	{ return (Uchar*)NULL; }		   /*			     */
						   /*			     */
	if ( reg.start[0] > 0 )		   	   /*			     */
	{ c = value[reg.start[0]];		   /* Push initial segment   */
	value[reg.start[0]] = '\0';		   /*			     */
	(void)sbputs(value,s2);		   	   /*			     */
	value[reg.start[0]] = c;		   /*			     */
	}					   /*			     */
						   /*			     */
	rewrite_1(RuleFrame(rule),s2,value,db,rec);/*		             */
						   /*			     */
	(void)sbputs(value+reg.end[0],s2);	   /* Transfer the end.	     */
						   /*			     */
	value = (Uchar*)sbflush(s2);		   /* update the value	     */
	len   = strlen((char*)value);		   /*  and its length	     */
	sp = s1; s1 = s2; s2 = sp;		   /* rotate the two string  */
	sbrewind(s2);				   /*  buffers and reset     */
						   /*  the destination.      */
	once_more = TRUE;			   /*                        */
      }						   /*                        */
      else					   /*                        */
      { rule = NextRule(rule);			   /*                        */
	limit = rsc_rewrite_limit;		   /*			     */
      }						   /*                        */
    }						   /*                        */
  }						   /*			     */
#endif
  return value;					   /* return the result.     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	check_regex()
** Purpose:	
**		
**
** Arguments:
**	field
**	value
**	rule
**	rec
** Returns:	
**___________________________________________________			     */
static Uchar * check_regex(field,value,rule,db,rec) /*			     */
  Uchar		*field;			   	   /*			     */
  Uchar		*value;			   	   /*			     */
  Rule		rule;			   	   /*			     */
  DB			db;			   /*                        */
  Record		rec;			   /*			     */
{						   /*			     */
#ifdef REGEX
  int			len;			   /*			     */
  static StringBuffer	*s2 = 0L;		   /*			     */
						   /*			     */
  if ( rule == RuleNULL ) return value;		   /*			     */
						   /*			     */
  if ( s2 == NULL ) { s2 = sbopen(); }		   /*			     */
  else		    { sbrewind(s2);  }		   /*			     */
						   /*			     */
  for ( len  =	strlen((char*)value);		   /* Loop through all rules */
	rule != RuleNULL;			   /*			     */
	rule =	NextRule(rule) )		   /*			     */
  {						   /*			     */
    if ( (   RuleField(rule) == NULL		   /*			     */
	  || RuleField(rule) == field )		   /*			     */
	&&
	 (   (RuleFlag(rule)&RULE_REGEXP) == 0
	  || re_search(&RulePattern(rule),	   /*			     */
		       value,len,0,len-1,&reg) >=0 /*			     */
	 )
       )					   /*			     */
    { if ( RuleFrame(rule) == (Uchar*)NULL )	   /*			     */
      { return (Uchar*)NULL; }			   /*			     */
      rewrite_1(RuleFrame(rule),s2,value,db,rec);  /*		             */
      value = (Uchar*)sbflush(s2);		   /* update the value	     */
      return value;				   /*			     */
    }						   /*                        */
  }						   /*			     */
#endif
  return (Uchar*)NULL;				   /* return the result.     */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/

 static Rule r_rule = RuleNULL;
 static Rule r_rule_end	= RuleNULL;

/*-----------------------------------------------------------------------------
** Function:	add_rewrite_rule()
** Purpose:	Save a rewrite rule for later use.
**		The main task is performed by |add_rule()|.
** Arguments:
**	s	Rule to save.
** Returns:	nothing
**___________________________________________________			     */
void add_rewrite_rule(s)			   /*			     */
  Uchar *s;				   	   /*			     */
{						   /*			     */
  add_rule(s,					   /*                        */
	   &r_rule,				   /*                        */
	   &r_rule_end,				   /*                        */
	   RULE_REGEXP,				   /*                        */
	   rsc_case_rewrite);			   /*			     */
}						   /*------------------------*/

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
  Uchar *s;				   	   /*			     */
{						   /*			     */
  add_rule(s,					   /*                        */
	   &c_rule,				   /*                        */
	   &c_rule_end,				   /*                        */
	   RULE_REGEXP,				   /*                        */
	   rsc_case_check);  			   /*			     */
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
void rewrite_record(db,rec)			   /*			     */
  DB		  db;				   /*                        */
  register Record rec;				   /*			     */
{ register int	  i;				   /*			     */
  register Uchar  **hp;				   /* heap pointer	     */
  register Macro  mac;				   /*			     */
  Uchar           *cp;				   /*			     */
  static StringBuffer *sb = NULL;		   /*                        */
 						   /*                        */
  if ( sb == NULL ) sb = sbopen();		   /*                        */
						   /*			     */
  if ( c_rule != RuleNULL )			   /*			     */
  {						   /*                        */
    for ( i=RecordFree(rec), hp=RecordHeap(rec);   /*			     */
	  i > 0;				   /*			     */
	  i-=2, hp +=2	)			   /*			     */
    {						   /*			     */
      if (   *hp				   /*			     */
	  && *(hp+1)				   /*			     */
	  && (Uchar*)NULL !=			   /*			     */
	     (cp=check_regex(*hp,*(hp+1),c_rule,db,rec))/*		     */
	  )					   /*			     */
      { Err(cp); }				   /*			     */
    }						   /*			     */
  }						   /*			     */
						   /*			     */
  if ( r_rule != RuleNULL )			   /*			     */
  {   						   /*			     */
    for ( i=RecordFree(rec), hp=RecordHeap(rec);   /*			     */
	 i>0;					   /*			     */
	 i-=2, hp+=2  )				   /*			     */
    {						   /*			     */
      if ( *hp && *(hp+1) )			   /*			     */
      {						   /*			     */
	cp = repl_regex(*hp,*(hp+1),r_rule,db,rec);/*			     */
	if ( cp == (Uchar*)NULL )		   /*			     */
	{ *hp = *(hp+1) = (Uchar*)NULL; }	   /*			     */
	else if ( cp != *(hp+1) )		   /*			     */
	{ *(hp+1) = symbol(cp); }		   /*			     */
      }						   /*			     */
    }						   /*			     */
  }						   /*			     */
 						   /*                        */
  for ( mac=addlist;				   /* Add all items in the   */
	mac;					   /*  add list		     */
	mac=NextMacro(mac) )			   /*			     */
  { cp = MacroValue(mac);			   /*                        */
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
    sbputc('}',sb);				   /*                        */
    push_to_record(rec,			   	   /*                        */
		   MacroName(mac),		   /*                        */
		   sym_add((Uchar*)sbflush(sb),1));/*                        */
  }						   /*			     */
}						   /*------------------------*/

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
  Uchar *s;				   	   /*			     */
  int regexp;					   /*                        */
  int notp;					   /*                        */
{						   /*                        */
  add_rule(s,					   /* The main task is       */
	   &x_rule,				   /*  performed by          */
	   &x_rule_end,				   /*  |add_rule()|.         */
	   (regexp?RULE_REGEXP:RULE_NONE) |	   /*                        */
	   (notp  ?RULE_NOT   :RULE_NONE) ,	   /*                        */
	   !rsc_case_select);			   /*			     */
  rsc_select = TRUE;				   /*                        */
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
  Uchar *s;				   	   /*                        */
{ char *t;				   	   /*			     */
 						   /*			     */
  if ( (t=malloc( (size_t)strlen((char*)s)	   /*                        */
		 +(size_t)strlen(rsc_sel_fields)   /*                        */
		 +4 )) == NULL )   		   /*			     */
  { OUT_OF_MEMORY("string"); }	   		   /*			     */
 						   /*                        */
  (void)strcpy(t,rsc_sel_fields);	   	   /*			     */
  (void)strcat(t," \"");			   /*			     */
  (void)strcat(t,(char*)s);		   	   /*			     */
  (void)strcat(t,"\"");			   	   /*			     */
 						   /*                        */
  add_rule((Uchar*)t,				   /*                        */
	   &x_rule,				   /*                        */
	   &x_rule_end,				   /*                        */
	   RULE_REGEXP,				   /*                        */
	   !rsc_case_select);			   /*			     */
 						   /*                        */
  free(t);					   /*                        */
  rsc_select = TRUE;				   /*                        */
}						   /*------------------------*/


 static char s_class[256];
 static Uchar *s_ignored = (Uchar*)NULL;
 static int  s_cased    = -33;

/*-----------------------------------------------------------------------------
** Function:	init_s_search()
** Purpose:	
**		
**		
** Arguments:
**	ignored	
** Returns:	Nothing
**___________________________________________________			     */
static void init_s_search(ignored)		   /*                        */
  char * ignored;				   /*                        */
{ int i;					   /*                        */
  for (i=0;i<256;i++) s_class[i] = i;		   /*                        */
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
  s_ignored = symbol((Uchar*)rsc_sel_ignored);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	s_match()
** Purpose:	
**		
**		
** Arguments:
**	p	
**	s	
** Returns:	
**___________________________________________________			     */
static int s_match(p,s)				   /*                        */
  Uchar * p;					   /*                        */
  Uchar * s;					   /*                        */
{						   /*                        */
  while ( *p && s_class[(unsigned int)*p] == '\0' ) p++;/*                   */
 						   /*                        */
  while ( *p )					   /*                        */
  {						   /*                        */
    while ( *s && s_class[(unsigned int)*s] == '\0' ) s++;
    /*printf(" '%c' [%c] =?= '%c' [%c]\n",*s,s_class[*s],*p,s_class[*p] );*/
    if ( s_class[(unsigned int)*s] != s_class[(unsigned int)*p] ) return FALSE;
    while ( *p && s_class[(unsigned int)*p] == '\0' ) p++;/*                 */
    if (*s) s++;				   /*                        */
    if (*p) p++;				   /*                        */
  }						   /*                        */
  return TRUE;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	s_search()
** Purpose:	Match a pattern against all positions in a string. If
**		a match is found then |TRUE| is returned. Otherwise
**		|FALSE|.
** Arguments:
**	pattern	
**	s	
** Returns:	
**___________________________________________________			     */
static int s_search(pattern,s)			   /*                        */
  Uchar * pattern;				   /*                        */
  Uchar * s;					   /*                        */
{						   /*                        */
  if ( s_cased != rsc_case_select ||		   /*                        */
       strcmp((char*)s_ignored,rsc_sel_ignored) != 0 )/*                     */
  { init_s_search(rsc_sel_ignored); }		   /*                        */
 						   /*                        */
  for ( ; *s; s++ )				   /*                        */
  { if ( s_match(pattern,s) ) return TRUE;	   /*                        */
  }						   /*                        */
  return FALSE;					   /*                        */
}						   /*------------------------*/


#define ReturnIf(COND)					\
  if ( COND )						\
  { if ( !(RuleFlag(rule) & RULE_NOT) ) return TRUE; }	\
  else							\
  { if (  (RuleFlag(rule) & RULE_NOT) ) return TRUE; }

/*-----------------------------------------------------------------------------
** Function:	is_selected()
** Purpose:	Boolean function to decide whether a record should be
**		considered. These selections are described by a set of
**		regular expressions which are applied. If none are
**		given then the match simply succeeds.
** Arguments:
**	db	Database containing the record.
**	rec	Record to look at.
** Returns:	|TRUE| iff the record is seleced by a regexp or none is
**		given.
**___________________________________________________			     */
int is_selected(db,rec)	   		   	   /*			     */
  DB     db;					   /*                        */
  Record rec;			   		   /*			     */
{						   /*			     */
  int	 len, i;				   /*			     */
  Uchar  *value;				   /*                        */
  Rule   rule;					   /*                        */
 						   /*                        */
  if ( (rule=x_rule) == RuleNULL ||		   /* If no rule is given or */
       !rsc_select	   			   /*  no selection is       */
     )				   		   /*  requested then        */
    return TRUE;				   /*  select all records.   */
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
	{ len = strlen((char*)(RecordHeap(rec)[0]));/*                       */
	  ReturnIf(re_search(&RulePattern(rule),   /*			     */
			     RecordHeap(rec)[0],   /*                        */
			     len,		   /*                        */
			     0,		   	   /*                        */
			     len-1,		   /*                        */
			     &reg) >=0 );	   /*		             */
	}					   /*                        */
	for ( i=2; i < RecordFree(rec); i+=2 )	   /*                        */
	{ if ( RecordHeap(rec)[i] )		   /*                        */
	  { len = strlen((char*)(RecordHeap(rec)[i+1]));/*                   */
	    ReturnIf(re_search(&RulePattern(rule), /*			     */
			       RecordHeap(rec)[i+1],/*                       */
			       len,		   /*                        */
			       0,		   /*                        */
			       len-1,		   /*                        */
			       &reg) >=0 );	   /*		             */
	  }					   /*                        */
	}					   /*                        */
#endif
      }						   /*                        */
      else					   /*                        */
      {						   /*                        */
	if ( RecordHeap(rec)[0] )		   /*                        */
	{ ReturnIf(s_search(RuleGoal(rule),	   /*			     */
			    RecordHeap(rec)[0]) ); /*		             */
	}					   /*                        */
	for ( i=2; i < RecordFree(rec); i+=2 )	   /*                        */
	{ if ( RecordHeap(rec)[i] )		   /*                        */
	  { ReturnIf(s_search(RuleGoal(rule),	   /*			     */
			      RecordHeap(rec)[i+1]) );/*		     */
	  }					   /*                        */
	}					   /*                        */
      }						   /*                        */
    }						   /*                        */
    else if ( (value=get_field(db,		   /*                        */
			       rec,		   /*                        */
			       RuleField(rule)))   /*                        */
	     != NULL )				   /*                        */
    {						   /*                        */
      if ( RuleFlag(rule) & RULE_REGEXP )	   /*                        */
      {						   /*                        */
#ifdef REGEX
	len = strlen((char*)value);		   /*                        */
        ReturnIf(re_search(&RulePattern(rule),	   /*			     */
			   value,		   /*                        */
			   len,			   /*                        */
			   0,			   /*                        */
			   len-1,		   /*                        */
			   &reg) >=0 ) 		   /*			     */
#endif
      }						   /*                        */
      else ReturnIf(s_search(RuleGoal(rule),value))/*                        */
    }						   /*			     */
    else if ( RuleFlag(rule) & RULE_NOT )	   /*                        */
    { return TRUE;				   /*                        */
    }						   /*                        */
  }						   /*                        */
  return FALSE;				   	   /* return the result.     */
}						   /*------------------------*/

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
