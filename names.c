/******************************************************************************
** $Id: names.c,v 1.17 2013-11-24 22:07:52 gene Exp $
*******************************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2013 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/names.h>
#include <bibtool/error.h>
#include <bibtool/symbols.h>
#include <bibtool/stack.h>
#include <bibtool/sbuffer.h>
#include <bibtool/s_parse.h>

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 NameNode name_format _ARG((Uchar *s));		   /* names.c                */
 Uchar * pp_list_of_names _ARG((Uchar **wa,NameNode format,char *trans,int max,Uchar *comma,Uchar *and,char *namesep,char *etal));/* names.c*/
 char * pp_names _ARG((char *s,NameNode format,char *trans,int max,char *namesep,char *etal));/* names.c*/
 static NameNode new_name_node _ARG((int type,int strip,int trim,Uchar *pre,Uchar *mid,Uchar *post));/* names.c*/
 static int is_jr _ARG((Uchar * s, int eager));	   /* names.c                */
 static int is_lower_word _ARG((Uchar *s));	   /* names.c                */
 static void initial _ARG((Uchar *s,char *trans,int len,StringBuffer *sb));/* names.c*/
 static void pp_one_name _ARG((StringBuffer *sb,Uchar **w,NameNode format,char *trans,int len,Uchar *comma,int commas));/* names.c*/

#ifdef BIBTEX_SYNTAX
 static void set_type _ARG((char **sp,char **midp));/* names.c               */
 void set_name_format _ARG((NameNode *nodep,char *s));/* names.c             */
#endif

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	new_name_node()
** Purpose:	Allocate a name node structure and fill it with the values 
**		given as arguments.
**		If no more memory is available then en error is raised and
**		the program is terminated.
** Arguments:
**	type	
**	strip	
**	trim	
**	pre	
**	mid	
**	post	
** Returns:	The new instance of a node.
**___________________________________________________			     */
static NameNode new_name_node(type,strip,trim,pre,mid,post)/*                */
  int      type;				   /*                        */
  int      strip;				   /*                        */
  int      trim;				   /*                        */
  Uchar    *pre;				   /*                        */
  Uchar    *mid;				   /*                        */
  Uchar    *post;				   /*                        */
{ NameNode node;				   /*                        */
 						   /*                        */
  if ( (node = (NameNode)malloc(sizeof(SNameNode))) == NameNULL )/*          */
  { OUT_OF_MEMORY("NameNode"); }	   	   /*                        */
  NameType(node)  = type;			   /*                        */
  NameStrip(node) = strip;			   /*                        */
  NameTrim(node) = trim;			   /*                        */
  NamePre(node)   = pre;			   /*                        */
  NameMid(node)   = mid;			   /*                        */
  NamePost(node)  = post;			   /*                        */
  NextName(node)  = NameNULL;			   /*                        */
  return node;					   /*                        */
}						   /*------------------------*/

#ifdef UNUSED

/*-----------------------------------------------------------------------------
** Function:	free_name_node()
** Purpose:	Release the memory allocated for a node together with all
**		nodes reachable via a |NextName| chain.
**		It is not save to access a freed node.
** Arguments:
**	node	Node to free.
** Returns:	nothing
**___________________________________________________			     */
static void free_name_node(node)		   /*                        */
  NameNode node;				   /*                        */
{ NameNode next;				   /*                        */
 						   /*                        */
  while ( node )				   /*                        */
  { next = NextName(node);			   /*                        */
    free(node);					   /*                        */
    node = next;				   /*                        */
  }						   /*                        */
}						   /*------------------------*/
#endif

#ifdef DEBUG
/*-----------------------------------------------------------------------------
** Function:	dump_name_node()
** Purpose:	
**		
**		
** Arguments:
**	n	
** Returns:	nothing
**___________________________________________________			     */
static void dump_name_node(n)			   /*                        */
  NameNode n;					   /*                        */
{						   /*                        */
  fputc('%',err_file);				   /*                        */
  switch ( NameType(n) & NameTranslationMask )	   /*                        */
  { case NameLower:    fputc('-',err_file); break; /*                        */
    case NameUpper:    fputc('+',err_file); break; /*                        */
    case NameExternal: fputc('*',err_file); break; /*                        */
  }						   /*                        */
  if ( NameStrip(n) >= 0 )			   /*                        */
  { fprintf(err_file,"%d",NameStrip(n)); }	   /*                        */
  if ( NameTrim(n) >= 0 )			   /*                        */
  { fprintf(err_file,".%d",NameTrim(n)); }	   /*                        */
  switch ( NameType(n) & NameTypeMask)		   /*                        */
  { case NameFirst:  fputc('f',err_file); break;   /*                        */
    case NameLast:   fputc('l',err_file); break;   /*                        */
    case NameVon:    fputc('v',err_file); break;   /*                        */
    case NameJr:     fputc('j',err_file); break;   /*                        */
    case NameString: fputc('s',err_file); break;   /*                        */
    default:	     fputc('?',err_file); break;   /*                        */
  }						   /*                        */
  fprintf(err_file,				   /*                        */
	  "[%s][%s][%s]\n",			   /*                        */
	  (NamePre(n)?(char*)NamePre(n):""),	   /*                        */
	  (NameMid(n)?(char*)NameMid(n):""),	   /*                        */
	  (NamePost(n)?(char*)NamePost(n):""));	   /*                        */
}						   /*------------------------*/
#else
#define dump_name_node(N)
#endif


#ifdef BIBTEX_SYNTAX
/*-----------------------------------------------------------------------------
** Function:	set_type()
** Purpose:	
**		
**
** Arguments:
**	sp
**	midp
** Returns:	
**___________________________________________________			     */
static void set_type(sp,midp)			   /*                        */
  char **sp;					   /*                        */
  char **midp;					   /*                        */
{ char c, *s, *mid;				   /*                        */
  int type = 0;					   /*                        */
   						   /*                        */
  s = *sp;					   /*                        */
  if ( *(s+1) == '{' )				   /*                        */
  { mid = ++s;					   /*                        */
    while ( *s && *s != '}' ) s++;		   /*                        */
    c = *s; *s = '\0';				   /*                        */
    *midp = symbol(++mid);			   /*                        */
    *s = c;					   /*                        */
  }						   /*                        */
  *sp = s;					   /*                        */
}						   /*------------------------*/

#define SetType(T,C) type = T;				\
	c = *s; *s = '\0'; pre = symbol(pre); *s = c;	\
	if ( *(s+1) == C ) { strip = -1; s++; }		\
	set_type(&s,&mid);				\
	post = s+1

/*-----------------------------------------------------------------------------
** Function:	set_name_format()
** Purpose:	
**		
**
** Arguments:
**	nodep	
**	s	
** Returns:	nothing
**___________________________________________________			     */
void set_name_format(nodep,s)			   /*                        */
  NameNode *nodep;				   /*                        */
  char     *s;					   /*                        */
{ int      n,					   /*                        */
	   type,				   /*                        */
    	   strip,				   /*                        */
    	   trim;				   /*                        */
  Uchar    *mid,				   /*                        */
	   *pre,				   /*                        */
	   *post,				   /*                        */
	   c;					   /*                        */
  Uchar    *space;				   /*                        */
  char     buffer[256];				   /*                        */
#define UseBuffer(S) strcpy(buffer,S); s = buffer
 						   /*                        */
  space = symbol(" ");				   /*                        */
  free_name_node(*nodep);			   /*                        */
  *nodep = NameNULL;				   /*                        */
 						   /*                        */
  if      (strcmp(s,"short")==0) { UseBuffer("{ll{-}}"); }/*                 */
  else if (strcmp(s,"med")  ==0) { UseBuffer("{f{}}{ll{-}}"); }/*            */
 						   /*                        */
  while ( *s  )					   /*                        */
  {						   /*                        */
    if (*s && *s != '{') 			   /*                        */
    { mid = s;					   /*                        */
      while ( *s && *s != '{' ) s++;		   /*                        */
      c = *s;					   /*                        */
      *s = '\0';				   /*                        */
      mid = symbol(mid);			   /*                        */
      *s = c;					   /*                        */
      *nodep = new_name_node(NameString,	   /*                        */
			     -1,		   /*                        */
			     -1,		   /*                        */
			     (Uchar*)NULL,	   /*                        */
			     mid,		   /*                        */
			     (Uchar*)NULL));	   /*                        */
      nodep  = &NextName(*nodep);		   /*                        */
 						   /*                        */
      if ( c == '\0' ) return;			   /*                        */
    }						   /*                        */
 						   /*                        */
    pre   = ++s;				   /*                        */
    type  = NoName;				   /*                        */
    mid   = space;				   /*                        */
    strip = 1;					   /*                        */
    for ( n = 1 ; n > 0; ++s )			   /*                        */
    { switch (*s)				   /*                        */
      { case '{': n++; break;			   /*                        */
	case '}': n--; break;			   /*                        */
        case 'f': SetType(NameFirst,'f'); break;   /*                        */
	case 'l': SetType(NameLast,'l');  break;   /*                        */
        case 'v': SetType(NameVon,'v');   break;   /*                        */
        case 'j': SetType(NameJr,'j');    break;   /*                        */
        case '\0': return;			   /*                        */
      }						   /*                        */
    }						   /*                        */
 						   /*                        */
    if ( type != NoName ) 			   /*                        */
    { c = *(s-1);				   /*                        */
      *(s-1) = '\0';				   /*                        */
      post = symbol(post);			   /*                        */
      *(s-1) = c;				   /*                        */
      *nodep = new_name_node(type, strip, trim, pre, mid, post);/*           */
      dump_name_node(*nodep);			   /*                        */
      nodep  = &NextName(*nodep);		   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

#endif

/*-----------------------------------------------------------------------------
** Function:	name_format()
** Purpose:	
**		
**
** Arguments:
**	s
** Returns:	
**___________________________________________________			     */
NameNode name_format(s)				   /*                        */
  Uchar	   *s;					   /*                        */
{ int	   type,				   /*                        */
	   strip,				   /*                        */
	   trim;				   /*                        */
  Uchar	   *pre,				   /*                        */
     	   *mid,				   /*                        */
     	   *post;				   /*                        */
  Uchar	   c;					   /*                        */
  Uchar    *cp;					   /*                        */
  NameNode node = NameNULL;			   /*                        */
  NameNode *nnp;				   /*                        */
  static char *msg = "Missing ']' in format string.";
#define OptionalArg(S)						\
  if ( *cp == '[' )						\
  { for ( S=++cp; *cp && *cp != ']'; cp++) ;			\
    if ( *cp )							\
    { c = *cp; *cp = '\0'; S = symbol(S); *(cp++) = c; }	\
    else { S = sym_empty; WARNING(msg); }			\
  } else { S = sym_empty; }
 						   /*                        */
  nnp = &node;					   /*                        */
  cp  = s;					   /*                        */
  while (*cp)					   /*                        */
  {						   /*                        */
    if ( *cp == '%' )				   /*                        */
    {						   /*                        */
      switch ( *++cp )				   /*                        */
      { case '+': type = NameUpper;    cp++; break;/*                        */
        case '-': type = NameLower;    cp++; break;/*                        */
        case '*': type = NameExternal; cp++; break;/*                        */
	default:  type = NameNone;		   /*                        */
      }						   /*                        */
      if ( is_digit(*cp) )			   /*                        */
      { strip = 0;				   /*                        */
        while(is_digit(*cp))			   /*                        */
        { strip = strip*10 + (*cp++) - '0';}	   /*                        */
      } else { strip = -1; }			   /*                        */
 						   /*                        */
      if ( *cp == '.' )			   	   /*                        */
      { trim = 0;				   /*                        */
        cp++;					   /*                        */
        while(is_digit(*cp))			   /*                        */
        { trim = trim*10 + (*cp++) - '0';}	   /*                        */
      } else { trim = -1; }			   /*                        */
 						   /*                        */
      switch ( *cp )				   /*                        */
      { case 'f': type |= NameFirst; break;	   /*                        */
        case 'l': type |= NameLast;  break;	   /*                        */
        case 'v': type |= NameVon;   break;	   /*                        */
        case 'j': type |= NameJr;    break;	   /*                        */
        default:  type |= NoName;		   /*                        */
	  error(ERR_ERROR|ERR_POINT,		   /*                        */
		(Uchar*)"Wrong type of format.",   /*                        */
		(Uchar*)0,			   /*                        */
		(Uchar*)0,			   /*                        */
		s,				   /*                        */
		cp,0,(char*)0);			   /*                        */
      }						   /*                        */
      cp++;					   /*                        */
      OptionalArg(pre);				   /*                        */
      OptionalArg(mid);				   /*                        */
      OptionalArg(post);			   /*                        */
    }						   /*                        */
    else 					   /*                        */
    { mid = cp;					   /*                        */
      while ( *cp && *cp != '%' ) { cp++; }	   /*                        */
      c     = *cp;				   /*                        */
      *cp   = '\0';				   /*                        */
      mid   = symbol(mid);			   /*                        */
      *cp   = c;				   /*                        */
      type  = NameString;			   /*                        */
      pre   = NULL;				   /*                        */
      post  = NULL;				   /*                        */
      strip = -1;				   /*                        */
      trim  = -1;				   /*                        */
    }						   /*                        */
    if ( type != NoName )			   /*                        */
    { *nnp = new_name_node(type,		   /*                        */
                           strip,		   /*                        */
                           trim,		   /*                        */
                           pre,			   /*                        */
                           mid,			   /*                        */
                           post);		   /*                        */
      nnp = &NextName(*nnp);			   /*                        */
    }						   /*                        */
  }						   /*                        */
  return node;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	pp_list_of_names()
** Purpose:	
**		
**
** Arguments:
**	wa	Word array of name constituents
**	format
**	comma	","
**	and	name separator
**	namesep
**	etal
** Returns:	Pointer to static string which is reused upon the next
**		invocation of this function.
**___________________________________________________			     */
Uchar * pp_list_of_names(wa,format,trans,max,comma,and,namesep,etal)/*       */
  Uchar    **wa;				   /*                        */
  NameNode format;				   /*                        */
  char     *trans;				   /*                        */
  int      max;					   /*                        */
  Uchar     *comma;				   /*                        */
  Uchar    *and;				   /*                        */
  char     *namesep;				   /*                        */
  char     *etal;				   /*                        */
{ Uchar    **w;					   /*                        */
  Uchar    *word;				   /*                        */
  int      commas;				   /*                        */
  int      first = TRUE;			   /*                        */
  static StringBuffer*sb = (StringBuffer*)0;	   /*                        */
 						   /*                        */
  if ( sb == (StringBuffer*)0 			   /*                        */
      && (sb=sbopen()) == (StringBuffer*)0 )	   /*                        */
  { OUT_OF_MEMORY("name list"); }		   /*                        */
  else						   /*                        */
  { sbrewind(sb); }				   /*                        */
 						   /*                        */
  while ( *wa )					   /*                        */
  {						   /*                        */
    if ( *(wa+1) == NULL			   /* Look at the end        */
	 && strcmp((char*)(*wa),"others")==0 )	   /*  for `and others'      */
    { sbputs(etal,sb);			   	   /*                        */
      break;					   /*                        */
    }						   /*                        */
    if ( max >= 0 && --max < 0 )		   /*                        */
    { sbputs(etal,sb);			   	   /*                        */
      break;					   /*                        */
    }						   /*                        */
 						   /*                        */
    commas = 0;					   /*                        */
    for( w = wa; *w && *w != and; w++ )		   /*                        */
    { if ( *w == comma ) commas++;		   /*                        */
      DebugPrint1(*w);				   /*                        */
    }						   /*                        */
    word = *w;					   /*                        */
    *w = NULL;					   /*                        */
    if ( first ) { first = FALSE; }		   /*                        */
    else { sbputs(namesep,sb); }		   /*                        */
    pp_one_name(sb,wa,format,trans,(int)(w-wa),comma,commas);/*              */
    *w = word;					   /*                        */
    wa = ( word != NULL? ++w : w ) ;		   /*                        */
  }						   /*                        */
 						   /*                        */
  return (Uchar*)sbflush(sb);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	pp_one_name()
** Purpose:	
**		
**
** Arguments:
**	sb
**	w
**	len
**	comma
**	commas
** Returns:	nothing
**___________________________________________________			     */
static void pp_one_name(sb, w, format, trans, len, comma, commas)/*          */
  StringBuffer *sb;				   /*                        */
  Uchar        **w;				   /*                        */
  NameNode     format;				   /*                        */
  char	       *trans;				   /*                        */
  int	       len;				   /*                        */
  Uchar         *comma;				   /*                        */
  int          commas;				   /*                        */
{ NameNode     nn;				   /*                        */
  char         t;				   /*                        */
  char         *type;				   /*                        */
  char         *tr;				   /*                        */
  int          i, j, again;			   /*                        */
  int	       first, last, von, jr;		   /*                        */
 						   /*                        */
  first = last = von = jr = 0;			   /*                        */
  if ( len < 1 ) return;			   /*                        */
 						   /*                        */
  if ( (type=(char*)malloc(len)) == NULL )	   /*                        */
  { OUT_OF_MEMORY("name type"); }   		   /*                        */
 						   /*                        */
#ifdef DEBUG
  ErrPrint("+++ BibTool: Name parts: ");	   /*                        */
  for (i = 0; i < len; i++)			   /*                        */
  { ErrPrintF("\n\t/%s/ ",w[i]); }		   /*                        */
  ErrC('\n');				   	   /*                        */
#endif
 						   /*                        */
  if ( commas == 0 )				   /*------------------------*/
  {						   /* ff vv ll               */
    j = len - 1;				   /* ff vv ll jr            */
    if ( is_jr((Uchar*)w[j], TRUE) )		   /*                        */
    { type[j--] = 'j'; jr++; }			   /*                        */
    if ( j >= 0 )				   /*                        */
    { type[j] = 'l'; last++; }  		   /*                        */
    i = 0;					   /*                        */
    while ( i < j && !is_lower_word((Uchar*)w[i]) )/*                        */
    { type[i++] = 'f'; first++; }		   /*                        */
    while ( i < j && is_lower_word((Uchar*)w[i]) ) /*                        */
    { type[i++] = 'v'; von++; }			   /*                        */
    while ( i < j )				   /*                        */
    { type[i++] = 'l'; last++; }		   /*                        */
  }						   /*                        */
  else if (   commas == 1			   /*------------------------*/
	   && len > 2				   /* ff vv ll, jj           */
	   && w[len-2] == comma			   /*                        */
	   && is_jr(w[len-1], FALSE) )	   	   /*                        */
  { j = len - 1;				   /*                        */
    type[j--] = 'j'; jr++;			   /*                        */
    type[j--] = ',';				   /*                        */
    if ( j >= 0 ) { type[j--] = 'l'; last++; }	   /*                        */
    i = 0;					   /*                        */
    while ( i < j && !is_lower_word((Uchar*)w[i]) )/*                        */
    { type[i++] = 'f'; first++; }		   /*                        */
    while ( i < j && is_lower_word((Uchar*)w[i]) ) /*                        */
    { type[i++] = 'v'; von++; }			   /*                        */
    while ( i < j )				   /*                        */
    { type[i++] = 'l'; last++; }		   /*                        */
  }						   /*                        */
  else						   /*                        */
  { i = 0;			   		   /*------------------------*/
    if ( is_lower_word((Uchar*)w[i]) )		   /* vv ll, ff              */
    { while ( i < len &&			   /*                        */
	      w[i] != comma &&	   		   /*                        */
	      is_lower_word((Uchar*)w[i]) )	   /*                        */
      { type[i++] = 'v'; von++; }		   /*                        */
    }						   /*                        */
			   			   /*------------------------*/
    while ( i < len && w[i] != comma )		   /* ll, ff vv              */
    { type[i++] = 'l'; last++; }		   /*                        */
    if (i < len) { type[i++] = ','; }		   /*                        */
			   			   /*------------------------*/
    if ( commas == 2 )				   /* ll, jj, ff vv          */
    { while ( i < len && w[i] != comma )	   /*                        */
      { type[i++] = 'j'; jr++; }		   /*                        */
      if (i < len) { type[i++] = ','; }		   /*                        */
    }						   /*                        */
    while ( i < len && !is_lower_word((Uchar*)w[i]) )/*                      */
    { if (w[i] == comma) {	   		   /*                        */
        type[i++] = ',';			   /*                        */
      } else {					   /*                        */
        type[i++] = 'f'; first++;		   /*                        */
      }						   /*                        */
    }		   				   /*                        */
    while ( i < len && is_lower_word((Uchar*)w[i]) )/*                       */
    { type[i++] = 'v'; von++; }			   /*                        */
  }						   /*                        */
 						   /*                        */
#ifdef DEBUG
  ErrPrint("+++ BibTool: Classified name parts: ");/*                        */
  for ( i = 0; i < len; i++)			   /*                        */
  { ErrPrintF2("\n\t%c/%s/ ",type[i], w[i]); }	   /*                        */
  ErrC('\n');				   	   /*                        */
#endif
 						   /*                        */
  for ( nn = format;				   /*                        */
        nn != NameNULL;				   /*                        */
        nn = NextName(nn) )			   /*                        */
  { int strip = NameStrip(nn);			   /*                        */
    int trim  = NameTrim(nn);			   /*                        */
    dump_name_node(nn);				   /* only in debug mode     */
    switch( NameType(nn) & NameTypeMask )	   /*                        */
    { case NameFirst:	t = 'f'; j = first; break; /*                        */
      case NameLast:	t = 'l'; j = last;  break; /*                        */
      case NameVon:	t = 'v'; j = von;   break; /*                        */
      case NameJr:	t = 'j'; j = jr;    break; /*                        */
      case NameString:	sbputs((char*)NameMid(nn),sb);/*                     */
      default:		t = ' '; j = 0; 	   /*                        */
    }						   /*                        */
    switch( NameType(nn) & NameTranslationMask )   /*                        */
    { case NameLower:   tr = trans_lower;   break; /*                        */
      case NameUpper:   tr = trans_upper;   break; /*                        */
      case NameNone:    tr = trans_id;      break; /*                        */
      default:	        tr = trans; 	   	   /*                        */
    }						   /*                        */
 						   /*                        */
    if ( j > 0 )				   /*                        */
    { sbputs((char*)NamePre(nn), sb);		   /*                        */
      again = FALSE;				   /*                        */
      for ( i = 0; i < len; i++ )		   /*                        */
      { if ( type[i] == t )			   /*                        */
	{					   /*                        */
  	  if ( trim-- == 0 ) break;		   /*                        */
	  if ( again ) sbputs((char*)NameMid(nn), sb);/*                     */
	  else again = TRUE;			   /*                        */
 						   /*                        */
	  initial(w[i], tr, strip, sb);	   	   /*                        */
	}					   /*                        */
      }						   /*                        */
      sbputs((char*)NamePost(nn), sb);		   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  free(type);					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	initial()
** Purpose:	
**		
**
** Arguments:
**	s
**	sb
** Returns:	nothing
**___________________________________________________			     */
static void initial(s,trans,len,sb)		   /*                        */
  Uchar        *s;				   /*                        */
  char         *trans;				   /*                        */
  int          len;				   /*                        */
  StringBuffer *sb;				   /*                        */
{ 						   /*                        */
  if ( len < 0 ) { sbputs((char*)s,sb); return; }  /*                        */
 						   /*                        */
  while ( len > 0 )				   /*                        */
  { if (*s=='\0') { return; }			   /*                        */
    if ( is_alpha(*s) )				   /*                        */
    { sbputc(trans[*((unsigned char *)s)],sb);	   /*                        */
      len--;					   /*                        */
    }						   /*                        */
    s++;					   /*                        */
  }					   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	is_jr()
** Purpose:	
**		
**
** Arguments:
**	s	string to consider
**      eager   indicator whether single letters should be classified as
**		Roman numbers
** Returns:	
**___________________________________________________			     */
static int is_jr(s, eager)			   /*                        */
  Uchar * s;					   /*                        */
  int  eager;					   /*                        */
{						   /*                        */
  switch ( ToLower(*s) )			   /*                        */
  { case 'j':					   /*                        */
      s++;					   /*                        */
      return ( case_cmp(s,(Uchar*)"r")    ||	   /*                        */
	       case_cmp(s,(Uchar*)"r.")   ||	   /*                        */
	       case_cmp(s,(Uchar*)"unior") );	   /*                        */
    case 's':					   /*                        */
      s++;					   /*                        */
      return ( case_cmp(s,(Uchar*)"en")   ||	   /*                        */
	       case_cmp(s,(Uchar*)"en.")  ||	   /*                        */
	       case_cmp(s,(Uchar*)"enior") );	   /*                        */
    case 'm':					   /*                        */
      s++;					   /*                        */
      return ( case_cmp(s,(Uchar*)"d") );	   /*                        */
    case 'p':					   /*                        */
      s++;					   /*                        */
      return ( case_cmp(s,(Uchar*)"hD")   ||	   /*                        */
	       case_cmp(s,(Uchar*)"hD.")  );	   /*                        */
    case 'i':					   /*                        */
      s++;					   /*                        */
      return ( (*s == '\0' && eager)      ||	   /*                        */
	       strcmp((char*)s,"I")  == 0 ||	   /*                        */
	       strcmp((char*)s,"II") == 0 ||	   /*                        */
	       strcmp((char*)s,"V")  == 0 ||	   /*                        */
	       strcmp((char*)s,"X")  == 0 );	   /*                        */
    case 'v':					   /*                        */
      s++;					   /*                        */
      return ( (*s == '\0' && eager) ||		   /*                        */
	       strcmp((char*)s,"I")    == 0 ||	   /*                        */
	       strcmp((char*)s,"II")   == 0 ||	   /*                        */
	       strcmp((char*)s,"III")  == 0 );	   /*                        */
    case 'x':					   /*                        */
      s++;					   /*                        */
      return ( (*s == '\0' && eager) ||		   /*                        */
	       strcmp((char*)s,"I")     == 0 ||	   /*                        */
	       strcmp((char*)s,"II")    == 0 ||	   /*                        */
	       strcmp((char*)s,"III")   == 0 ||	   /*                        */
	       strcmp((char*)s,"IV")    == 0 ||	   /*                        */
	       strcmp((char*)s,"V")     == 0 ||	   /*                        */
	       strcmp((char*)s,"VI")    == 0 ||	   /*                        */
	       strcmp((char*)s,"VII")   == 0 ||	   /*                        */
	       strcmp((char*)s,"VIII")  == 0 ||	   /*                        */
	       strcmp((char*)s,"IX")    == 0 ||	   /*                        */
	       strcmp((char*)s,"X")     == 0 ||	   /*                        */
	       strcmp((char*)s,"XI")    == 0 ||	   /*                        */
	       strcmp((char*)s,"XII")   == 0 ||	   /*                        */
	       strcmp((char*)s,"XIII")  == 0 ||	   /*                        */
	       strcmp((char*)s,"XIV")   == 0 ||	   /*                        */
	       strcmp((char*)s,"XV")    == 0 ||	   /*                        */
	       strcmp((char*)s,"XVI")   == 0 ||	   /*                        */
	       strcmp((char*)s,"XVII")  == 0 ||	   /*                        */
	       strcmp((char*)s,"XVIII") == 0 ||	   /*                        */
	       strcmp((char*)s,"XIX")   == 0 ||	   /*                        */
	       strcmp((char*)s,"XX")    == 0 );	   /*                        */
    case 'e':					   /*                        */
      return ( case_cmp(++s,(Uchar*)"sc") ||	   /*                        */
	       case_cmp(s,(Uchar*)"sc.")  );	   /*                        */
  }						   /*                        */
  return FALSE;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	is_lower_word()
** Purpose:	Test if the word given as argument starts with a lower case
**		letter. Non letter characters are ignored.
**		TeX control sequences are partially ignored: 
**
** Arguments:
**	s	Word to test
** Returns:	TRUE or FALSE
**___________________________________________________			     */
static int is_lower_word(s)			   /*                        */
  register Uchar *s;				   /*                        */
{ 						   /*                        */
  while(*s)					   /*                        */
  { if ( is_lower(*s) ) return TRUE;		   /*                        */
    if ( is_upper(*s) ) return FALSE;		   /*                        */
    if ( *s == '\\' ) { s++; if (*s) s++; }	   /*                        */
    else s++;					   /*                        */
  }						   /*                        */
  return FALSE;					   /*                        */
}						   /*------------------------*/


/*---------------------------------------------------------------------------*/

#ifdef STANDALONE

/*-----------------------------------------------------------------------------
** Function*:	pp_names()
** Purpose:	Take a string consisting of a list of names, parse it and
**		reformat it according to a format specification.
**		This function is modelled according to the specification
**		for |format.name$| in \BibTeX.
** Arguments:
**	s	string to be parsed and reformatted.
**	format	
**	trans	translation table
**	max	
**	namesep	string to be inserted between names.
**	etal	string to be added instead of `and others'
** Returns:	a new symbol with the reformatted names.
**___________________________________________________			     */
char * pp_names(s,format,trans,max,namesep,etal)   /*                        */
  char     *s;					   /*                        */
  NameNode format;				   /*                        */
  char	   *trans;				   /*                        */
  int	   max;					   /*                        */
  char     *namesep;				   /*                        */
  char     *etal;				   /*                        */
{ char     *wp,					   /*                        */
           *comma,				   /*                        */
           *and;				   /*                        */
  int      brace,				   /*                        */
           n,					   /*                        */
           cc;					   /*                        */
  char     **words;				   /*                        */
 						   /*                        */
  if ( format == NameNULL ) return s;	   	   /*                        */
 						   /*                        */
  s = new_string(s);				   /*                        */
  wp    = s;					   /*                        */
  brace = 0;					   /*                        */
  n     = 0;					   /*                        */
  comma = ",";					   /*                        */
  and   = "&";					   /*                        */
 						   /*                        */
  for ( ; *s; s++ )				   /*                        */
  { switch(*s)					   /*                        */
    { case '{': brace++; break;			   /*                        */
      case '}': brace--; break;			   /*                        */
      case ',':					   /*                        */
        if ( brace < 1 )			   /*                        */
	{ *s = '\0';				   /*                        */
	  if (*wp) { push_string(wp); n++; }	   /*                        */
	  push_string(comma); n++;		   /*                        */
	  wp = s+1;				   /*                        */
	}					   /*                        */
        break;					   /*                        */
      case ' ': case '~': case '\t': case '\n':	   /*                        */
      case '\r':   				   /*                        */
        if ( brace < 1 )			   /*                        */
	{ *s = '\0';				   /*                        */
	  if (*wp)				   /*                        */
	  { push_string(strcmp(wp,"and")==0?and:wp);/*                       */
	    n++;				   /*                        */
	  }					   /*                        */
	  wp = s+1;				   /*                        */
	}					   /*                        */
        break;					   /*                        */
    }						   /*                        */
  }						   /*                        */
  if (*wp) { push_string(wp); n++; }		   /*                        */
  push_string(NULL);				   /*                        */
  n++;						   /*                        */
 						   /*                        */
  if ( (words=(char**)malloc(n*sizeof(char*))) == (char**)0 )/* Allocate     */
  { OUT_OF_MEMORY("Names"); }	   		   /* temp. array of words.  */
 						   /*                        */
  while( --n >= 0 )				   /* Transfer the stack into*/
  { words[n] = pop_string();			   /*  the word array.       */
  }						   /*                        */
  						   /*                        */
  wp = symbol(pp_list_of_names(words,		   /*                        */
			       format,		   /*                        */
			       trans,		   /*                        */
			       max,		   /*                        */
			       comma,		   /*                        */
			       and,		   /*                        */
			       namesep,etal));	   /*                        */
 						   /*                        */
  free(words);					   /*                        */
  free(s);					   /*                        */
  return wp;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:   main()
** Purpose:     Main rountine
** Arguments:
**	argc	Number of arguments (+1)
**	argv	Array of command line arguments (and program name)
** Returns:     
**___________________________________________________                        */
int main(argc,argv)				   /*                        */
  int  argc;					   /*                        */
  char *argv[];					   /*                        */
{ Uchar s[1024];				   /*                        */
  NameNode format = NameNULL;			   /*                        */
 						   /*                        */
  init_type();					   /*                        */
 						   /*                        */
  fputs("Format: ",stdout);			   /*                        */
  gets(s);					   /*                        */
 						   /*                        */
  format = name_format(s);		   	   /*                        */
 						   /*                        */
  while ( gets(s) ) 				   /*                        */
  { puts (pp_names(s,format,trans_lower,-1," and "," and others"));/*        */
  }						   /*                        */
}						   /*------------------------*/

 int rsc_quiet = 1;
/*

   gcc -g -DDEBUG -DSTANDALONE names.c stack.o symbols.o sbuffer.o type.o error.o -o names
   ./names
*/

#endif
