/*** parse.c ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/entry.h>
#include <bibtool/error.h>
#include <bibtool/pxfile.h>
#include <bibtool/rsc.h>
#include <bibtool/stack.h>
#include <bibtool/sbuffer.h>
#include <bibtool/macros.h>
#include <bibtool/print.h>
#ifdef HAVE_LIBKPATHSEA
#ifdef __STDC__
#define HAVE_PROTOTYPES
#endif
#include <kpathsea/tex-file.h>
#endif

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int parse_bib _ARG((Record rec));		   /* parse.c                */
 int read_rsc _ARG((String name));		   /* parse.c                */
 int see_bib _ARG((String fname));		   /* parse.c                */
 static int see_rsc _ARG((String fname));	   /* parse.c                */
 int seen _ARG((void));				   /* parse.c                */
 static int fill_line _ARG((void));		   /* parse.c                */
 static int parse_block _ARG((int quotep));	   /* parse.c                */
 static int parse_equation _ARG((Record rec));	   /* parse.c                */
 static int parse_key _ARG((int alpha));	   /* parse.c                */
 static int parse_rhs _ARG((void));		   /* parse.c                */
 static int parse_string _ARG((int quotep));	   /* parse.c                */
 static int parse_symbol _ARG((int alpha));	   /* parse.c                */
 static int parse_value _ARG((void));		   /* parse.c                */
 static int see_bib_msg _ARG((char *s));	   /* parse.c                */
 static int skip _ARG((int inc));		   /* parse.c                */
 static int skip_c _ARG((void));		   /* parse.c                */
 static int skip_nl _ARG((void));		   /* parse.c                */
 static void init___ _ARG((char ***pathp,char **pattern,char **envvp,char *env));/* parse.c*/
 static void init_parse _ARG((void));		   /* parse.c                */
 static void parse_number _ARG((void));		   /* parse.c                */
 void init_read _ARG((void));			   /* parse.c                */
 void set_rsc_path _ARG((String  val));		   /* parse.c                */

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Variable*:	parse_sb
** Purpose:	
**		
**		
**___________________________________________________			     */
 static StringBuffer * parse_sb = (StringBuffer*)NULL;

#define FLBLEN	80		/* initial size and increment of line buffer */

 static char	*filename;
 static FILE	*file;
 static String	file_line_buffer;
 static String	flp;
 static size_t	fl_size	 = 0;
 static int	flno	 = 0;

/*---------------------------------------------------------------------------*/

#define EmptyC		(*flp=='\0')
#define CurrentC	*flp
#define FutureC		*(flp+1)
#define ClearLine	(*flp='\0')
#define GetC		skip(TRUE)
#define NextC		*(flp++)
#define SkipC		++flp
#define TestC		skip(FALSE)
#define UnGetC		flp--

#define InitLine	*file_line_buffer = '\0';	\
			flp  = file_line_buffer;	\
			flno = 0;

/*---------------------------------------------------------------------------*/

 static String str_unexpected	= (String)"Unexpected character encountered";
 static char *str_stdin		= "<stdin>";

#define Error3(X,Y,Z)	error(ERR_ERROR|ERR_POINT|ERR_FILE,(String)X,	\
			      (String)Y,(String)Z,			\
			      file_line_buffer,flp,flno,filename)
#define Error(X)	error(ERR_ERROR|ERR_POINT|ERR_FILE,(String)X,	\
			      sym_empty,sym_empty,			\
			      file_line_buffer,flp,flno,filename)
#define Warning(X)	error(ERR_WARN|ERR_POINT|ERR_FILE,(String)X,	\
			      sym_empty,sym_empty,			\
			      file_line_buffer,flp,flno,filename)
#define UnterminatedError(X,LINE)					\
			error(ERR_ERROR|ERR_FILE,(String)X,		\
			      sym_empty,sym_empty,			\
			      NULL,NULL,LINE,filename)
#define UnexpectedError Error(str_unexpected)

/*-----------------------------------------------------------------------------
** Function:	init___()
** Purpose:	Initialize the reading apparatus.
** Arguments:
**	pathp
**	pattern
**	envvp
**	env
** Returns:	nothing
**___________________________________________________			     */
static void init___(pathp,pattern,envvp,env)	   /*			     */
  char		***pathp;			   /*			     */
  char		**pattern;			   /*			     */
  char		**envvp;			   /*			     */
  char		*env;				   /*			     */
{ register char **cpp,				   /*			     */
		*cp;				   /*			     */
						   /*			     */
  if ( *pathp != (char**)0 )			   /*			     */
  { free((char*)*pathp);			   /*                        */
    *pathp = (char**)0;				   /*                        */
  }	   					   /*			     */
						   /*			     */
  if ( (cp = getenv(env)) != NULL )		   /*			     */
  { *envvp = cp; }				   /*			     */
						   /*			     */
  if ( *envvp )					   /*			     */
  { *pathp = px_s2p(*envvp,*rsc_env_sep);	   /*			     */
    if ( *pathp == (char**)0 )			   /*			     */
    { WARNING2(env,"search path extension failed.");/*			     */
    }						   /*			     */
    DebugPrint2("Path extension ",env);		   /*                        */
  }						   /*			     */
						   /*			     */
  if ( *rsc_dir_file_sep != '/' )		   /*			     */
  { for ( cpp = pattern; *cpp; ++cpp )		   /*			     */
    { *cpp = new_string(*cpp);			   /*                        */
      for (cp = *cpp; *cp; ++cp )		   /*			     */
      { if ( *cp == '/' ) *cp = *rsc_dir_file_sep; /*			     */
      }						   /*			     */
    }						   /*			     */
  }						   /*			     */
}						   /*------------------------*/

#ifndef HAVE_LIBKPATHSEA
 static char **f_path = (char**)0;		   /*                        */
 static char *f_pattern[] =			   /*                        */
 { "%s/%s", "%s/%s.bib", NULL };		   /*                        */
#endif

/*-----------------------------------------------------------------------------
** Function:	init_read()
** Purpose:	Initialize the reading apparatus.
**		Primarily try to figure out the file search path.
**
**		Note that this function is for internal purposes
**		mainly. The normal user should call |init_bibtool()|
**		instead. Just in case the search paths are changed
**		afterwards this function has to be called again to
**		propagate the information.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void init_read()				   /*			     */
{						   /*			     */
#ifndef HAVE_LIBKPATHSEA
  init___(&f_path,				   /*			     */
	  f_pattern,				   /*			     */
	  (char**)&rsc_v_bibtex,		   /*			     */
	  (char*)rsc_e_bibtex	);		   /*			     */
#endif
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	see_bib_msg()
** Purpose:	Message function for use with  |px_fopen()|.
** Arguments:
**	s	String to print
** Returns:	|TRUE| to indicate that continuation is desired.
**___________________________________________________			     */
static int see_bib_msg(s)			   /*			     */
  register char *s;				   /*			     */
{						   /*			     */
  if ( rsc_verbose ) VerbosePrint2("Trying ",s);   /*			     */
  return TRUE;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	see_bib()
** Purpose:	Open a \BibTeX{} file to read from. 
**		If the argument is |NULL| then |stdin| is used as
**		input stream.
**
**		This function has to be called before |parse()| can be
**		called. It initializes the parser routine and takes
**		care that the next reading is done from the given
**		file.
**
**		The file opened with this function has to be closed
**		with |seen()|.
**
**		This function is for internal purposes mainly. See
**		|read_db()| for a higher level function to read a
**		database. 
** Arguments:
**	fname	Name of the file or |NULL|.
** Returns:	|TRUE| iff the file could be opened for reading.
**___________________________________________________			     */
int see_bib(fname)				   /*			     */
  register String  fname;			   /*			     */
{						   /*			     */
  init_parse();					   /*			     */
  InitLine;					   /*			     */
  if ( fname == NULL )				   /*			     */
  {						   /*                        */
    filename = str_stdin;		   	   /*			     */
    file     = stdin;			   	   /*			     */
    return TRUE;				   /*			     */
  }						   /*                        */
#ifdef HAVE_LIBKPATHSEA
  filename = kpse_find_file((char*)fname,	   /*                        */
			    kpse_bib_format,	   /*                        */
			    TRUE);		   /*                        */
  if ( filename == NULL ) return FALSE;	   	   /*                        */
  file = fopen(filename,"r");			   /*                        */
#else
  file = px_fopen((char*)fname,			   /*			     */
		  "r",			   	   /*			     */
		  f_pattern,			   /*			     */
		  f_path,			   /*			     */
		  see_bib_msg);		   	   /*			     */
  filename = px_filename;			   /*			     */
#endif
  return ( file != NULL );			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	seen()
** Purpose:	Close input file for the \BibTeX{} reading apparatus.
**		After this function has been called |parse()| might
**		not return sensible results.
**
**		This function is for internal purposes mainly. See
**		|read_db()| for a higher level function to read a
**		database. 
** Arguments:	none
** Returns:	|FALSE| if an attempt was made to close an already
**		closed file.
**___________________________________________________			     */
int seen()					   /*			     */
{ 						   /*                        */
  if ( file == stdin )			   	   /*			     */
  { file = NULL;				   /*                        */
    return TRUE;				   /*                        */
  }    						   /*                        */
  else if ( file )			   	   /*			     */
  { (void)fclose(file);				   /*			     */
    file = NULL;				   /*			     */
    return TRUE;				   /*			     */
  }						   /*			     */
  return FALSE;					   /*			     */
}						   /*------------------------*/


#define Expect(C,N)	  if ( GetC != C ) { UnexpectedError; return(N); }
#define ExpectSymbol(C,N) if (!parse_symbol(C))		return(N)
#define ExpectKey(C,N)    if (!parse_key(C))		return(N)
#define ExpectRhs(N)	  if (!parse_rhs())		return(N)
#define ExpectEq(R,N)	  if (!parse_equation(R))	return(N)
#define ExpectEqMac(R,N)  if (!parse_equation(R))	return(N)

/*-----------------------------------------------------------------------------
** Function:	init_parse()
** Purpose:	Initialize the parser.
**
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
static void init_parse()			   /*			     */
{						   /*			     */
  if ( fl_size != 0 ) return;			   /* Already initialzed?    */
						   /*			     */
  fl_size = FLBLEN;				   /*			     */
  if ( (file_line_buffer=(String)malloc(fl_size*sizeof(Uchar))) == NULL )/*  */
  { OUT_OF_MEMORY("line buffer"); }		   /* Allocate line buffer   */
				   		   /*  or message and exit.  */
  if ( parse_sb		   == (StringBuffer*)0 &&  /* Try to initialize the  */
       (parse_sb=sbopen()) == (StringBuffer*)0 )   /*  string buffer for the */
  { OUT_OF_MEMORY("parser");	   		   /*  parser or exit	     */
  }			   			   /*  with error message.   */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	fill_line()
** Purpose:	Filling the line buffer until end-of-line or end-of-file
**		encountered.
**		
**		Since I don't want to use a fixed line length the algorithm
**		is a little bit more complicated.
**		First I try to read into the file_line_buffer as it is.
**		If this succeeds I check to see what caused |fgets| to
**		terminate. Either a end-of-line is in the buffer or
**		the buffer is not filled, i.e. end-of-file has been
**		encountered, then |0| is returned.
**		Otherwise the buffer has been filled and I try to enlarge the
**		buffer and read another chunk of bytes.
** Arguments:	none
** Returns:	Returns 0 iff a character has been read.
**___________________________________________________'			     */
static int fill_line()				   /*			     */
{ register size_t	len;			   /*			     */
						   /*			     */
  flp = file_line_buffer;			   /* Reset line pointer     */
  ++flno;					   /* Increase line number   */
						   /*			     */
  if ( fgets((char*)file_line_buffer,fl_size,file) == NULL )/*Get first chunk*/
  { ClearLine; 		   			   /*	or report EOF	     */
    DebugPrint1("Reading failed for first line."); /*                        */
    return 1;					   /*                        */
  }						   /*                        */
						   /*			     */
  FOREVER					   /*			     */
  { for (len = 0;				   /* Find the end	     */
	 file_line_buffer[len] != '\0';		   /*  of the buffer and     */
	 ++len ) ;				   /*  count the length.     */
						   /*			     */
#ifdef DEBUG
    ErrPrintF2("+++ BibTool: line buffer: used %d of %d\n",len+1,fl_size);/* */
#endif
						   /*			     */
    if ( file_line_buffer[len-1] == '\n'	   /*			     */
	|| len < fl_size - 1)			   /*			     */
    { return 0; }				   /*			     */
						   /*			     */
    if ( (file_line_buffer = (String)		   /* Try to enlarge	     */
	  realloc((char*)file_line_buffer,	   /*  the line buffer	     */
		  fl_size+=FLBLEN)) == NULL )	   /*			     */
    { OUT_OF_MEMORY("line buffer"); }		   /*			     */
    flp = file_line_buffer;			   /* Reset line pointer     */
						   /*			     */
    if ( fgets((char*)file_line_buffer+len,FLBLEN+1,file)/*		     */
	== NULL )				   /*			     */
    { return 0; }				   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	skip()
** Purpose:	Skip over spaces. Return the next non-space character or |EOF|.
**		If inc is TRUE point to the first character after the one
**		returned.
** Arguments:
**	inc
** Returns:	The next character
**___________________________________________________			     */
static int skip(inc)				   /*			     */
  register int inc;				   /*			     */
{						   /*			     */
  FOREVER					   /*			     */
  { if ( EmptyC && fill_line() )   return EOF;	   /*			     */
    else if ( is_space(CurrentC) ) SkipC;	   /*			     */
    else return ( inc ? NextC : CurrentC );	   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	skip_c()
** Purpose:	Return the next character or EOF.
** Arguments:	none
** Returns:	
**___________________________________________________			     */
static int skip_c()				   /*			     */
{						   /*			     */
  FOREVER					   /*			     */
  { if ( EmptyC && fill_line() )   return EOF;	   /*			     */
    else { return ( NextC ); }			   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	skip_nl()
** Purpose:	Return the next character or EOF.
**		Any number of spaces is returned as a single space.
**		Doubled newlines are preserved.
** Arguments:	none
** Returns:	
**___________________________________________________			     */
static int skip_nl()				   /*			     */
{ static int state = FALSE;			   /*			     */
  int c;					   /*                        */
 						   /*                        */
  if ( state ) { state = FALSE; return '\n'; }	   /*                        */
 						   /*                        */
  FOREVER					   /*			     */
  { if ( EmptyC && fill_line() )   return EOF;	   /*			     */
    else if ( is_space(CurrentC) )		   /*			     */
    {						   /*                        */
      for ( c = skip_c();			   /*                        */
	    c != EOF && is_space(c) && c != '\n';  /*                        */
	    c = skip_c() ) {}			   /*                        */
      if ( c == EOF  ) return EOF;		   /*                        */
      if ( c != '\n' ) { UnGetC; return ' '; }	   /*                        */
 						   /*                        */
      for ( c = skip_c();			   /*                        */
	    c != EOF && is_space(c) && c != '\n';  /*                        */
	    c = skip_c() ) {}			   /*                        */
      if ( c == EOF  ) return EOF;		   /*                        */
      if ( c != '\n' ) { UnGetC; return ' '; }	   /*                        */
 						   /*                        */
      for ( c = skip_c();			   /*                        */
	    c != EOF && is_space(c);		   /*                        */
	    c = skip_c() ) {}			   /*                        */
      if ( c == EOF  ) return EOF;		   /*                        */
      UnGetC;					   /*                        */
      state = TRUE;				   /*                        */
      return '\n';				   /*                        */
    }						   /*			     */
    else { return ( NextC ); }		   	   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_symbol()
** Purpose:	Parse a symbol and push it to the stack.
**		Upon failure issue an appropriate message.
** Arguments:
**	alpha	indicator that the symbol has to start with an alpha character
** Returns:	Success status
**___________________________________________________			     */
static int parse_symbol(alpha)			   /*			     */
  register int   alpha;				   /*			     */
{ register Uchar c;				   /*			     */
  register String cp;				   /*			     */
						   /*			     */
  c = GetC;					   /*                        */
  cp = flp-1;			   	   	   /*			     */
  if ( alpha && (! is_alpha(c)) )		   /*			     */
  { Warning("Symbol does not start with a letter");/*                        */
  }		   				   /*			     */
  while ( is_allowed(CurrentC) ) { SkipC; }	   /*			     */
  c = CurrentC;					   /*                        */
  CurrentC = '\0';		   		   /*			     */
  push_string(symbol(lower(cp)));		   /*			     */
  CurrentC = c;					   /*			     */
  return TRUE;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_key()
** Purpose:	Parse a symbol and push it to the stack.
**		Upon failure issue an appropriate message.
** Arguments:
**	alpha	indicator that the symbol has to start with an alpha character
** Returns:	Success status
**___________________________________________________			     */
static int parse_key(alpha)			   /*			     */
  register int   alpha;				   /*			     */
{ register Uchar c;				   /*			     */
  register String cp;			   	   /*			     */
						   /*			     */
  c  = GetC;					   /*                        */
  cp = flp - 1;			   		   /*			     */
  if ( alpha && (! is_alpha(c)) )		   /*			     */
  { Error("Key does not start with a letter");	   /*                        */
    return(FALSE);				   /*                        */
  }		   				   /*			     */
  while ( is_allowed(CurrentC) || CurrentC == '\'')/*                        */
  { SkipC; }	   				   /*			     */
  c = CurrentC;					   /*                        */
  CurrentC = '\0';		   		   /*			     */
  if ( rsc_key_case )				   /*                        */
  { String s;					   /*                        */
    s  = symbol(cp);				   /*                        */
    cp = symbol(lower(cp));			   /*                        */
    save_key(cp,s);				   /*                        */
  }						   /*                        */
  else						   /*                        */
  { cp = symbol(lower(cp));			   /*                        */
  }						   /*                        */
  push_string(cp);			   	   /*			     */
  CurrentC = c;					   /*			     */
  return TRUE;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_number()
** Purpose:	Parse a number and push it to the stack.
**		This function is called when at least one digit has been seen.
**		Thus no error can occur in this function.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
static void parse_number()			   /*			     */
{ register Uchar c;				   /*			     */
  register String cp;				   /*			     */
						   /*			     */
  cp = flp;				   	   /*                        */
  while ( is_digit(CurrentC) ) { SkipC; }	   /*			     */
  c = CurrentC;					   /*                        */
  CurrentC = '\0';			   	   /*			     */
  push_string(symbol(cp));			   /*                        */
  CurrentC = c;		   			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_string()
** Purpose:	Parse a string and push it to the stack.
**		A string is something enclosed in ""
**		Consider the brace level to determine the end of the string.
** Arguments:
**	quotep	Boolean. TRUE iff the leading " has already been stripped off
**		the input stream.
** Returns:	Success status
**___________________________________________________"			     */
static int parse_string(quotep)			   /*			     */
  int quotep;				   	   /*			     */
{ int c;					   /*                        */
  int left;				   	   /*			     */
  int start_flno = flno;			   /*                        */
						   /*			     */
  left = 0;					   /*			     */
  if ( quotep ) (void)sbputchar('"',parse_sb);	   /*"			     */
  do						   /*			     */
  { switch ( c=skip_nl() )			   /*			     */
    { case EOF:					   /*                        */
	UnterminatedError("Unterminated double quote",/*                     */
			  start_flno);		   /*                        */
	return(FALSE);	   			   /*			     */
      case '{':	 left++; (void)sbputchar((char)c,parse_sb); break;/*	     */
      case '}':	 if ( left--<0 )		   /*			     */
		 { Warning("Expecting \" here"); } /*			     */
		 (void)sbputchar((char)c,parse_sb);/*                        */
		 break;                            /*                        */
      case '\\': (void)sbputchar((char)c,parse_sb); c = NextC;/*	     */
		 (void)sbputchar((char)c,parse_sb); c = ' ';/*		     */
		 break;				   /*			     */
      case '"':	 if ( !quotep ) break;		   /*			     */
      default:	 (void)sbputchar((char)c,parse_sb);/*			     */
    }						   /*			     */
  } while ( c != '"' );				   /*			     */
						   /*			     */
  if ( left ) Warning("Unbalanced parenthesis");   /*			     */
  return(TRUE);					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_block()
** Purpose:	Parse a block and push it to the stack.
**		A block is something enclosed in {}
**		Consider the brace level to determine the end of the string.
** Arguments:
**	quotep	Boolean. TRUE iff the leading { has already been stripped off
**		the input stream.
** Returns:	Success status
**___________________________________________________			     */
static int parse_block(quotep)			   /*			     */
  int quotep;					   /*			     */
{ int c;					   /*                        */
  int left;				   	   /*			     */
  int start_flno = flno;			   /*                        */
						   /*			     */
  left = 1;					   /*			     */
  if ( quotep ) (void)sbputchar('{',parse_sb);	   /*			     */
 						   /*                        */
  FOREVER					   /*			     */
  { switch ( c=skip_nl() )			   /*			     */
    { case EOF:					   /*                        */
	UnterminatedError("Unterminated open brace",/*                       */
			  start_flno);		   /*                        */
	return FALSE;		   		   /*			     */
      case '{': left++; break;			   /*			     */
      case '}':					   /*			     */
	if ( --left < 1 )			   /*			     */
	{ if ( quotep ) (void)sbputchar('}',parse_sb);/*		     */
	  return TRUE;				   /*			     */
	}					   /*			     */
    }						   /*			     */
    (void)sbputchar(c,parse_sb);		   /*			     */
  }						   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_rhs()
** Purpose:	Parse the right hand side of an item.
**		This can be composed of strings, blocks, numbers, and symbols
**		separated by #
** Arguments:	none
** Returns:	Success status
**___________________________________________________			     */
static int parse_rhs()				   /*			     */
{						   /*			     */
  int start_flno = flno;			   /*                        */
 						   /*                        */
  sbrewind(parse_sb);				   /*			     */
  do						   /*			     */
  { if ( sbtell(parse_sb) != 0 )		   /*			     */
    { (void)sbputs(" # ",parse_sb); }		   /*			     */
						   /*			     */
    switch ( GetC )				   /*			     */
    { case EOF:					   /*                        */
	UnterminatedError("Unterminated value",	   /*                        */
			  start_flno);		   /*                        */
	return(FALSE);  			   /*			     */
						   /*			     */
      case '"':					   /*                        */
	if ( !parse_string(TRUE) ) return(FALSE);  /*		             */
	break;					   /*			     */
						   /*			     */
      case '{':					   /*                        */
	if ( !parse_block(TRUE) ) return(FALSE);   /*		             */
	break;					   /*			     */
						   /*			     */
      case '0': case '1': case '2': case '3': case '4':/*		     */
      case '5': case '6': case '7': case '8': case '9':/*		     */
	UnGetC;					   /*                        */
	parse_number();			   	   /*			     */
	(void)sbputs((char*)pop_string(),parse_sb);/*			     */
	break;					   /*			     */
						   /*			     */
      default:					   /*			     */
	UnGetC;					   /*                        */
	ExpectSymbol(TRUE,FALSE);	   	   /*			     */
	{ register String  mac;			   /*			     */
	  mac = pop_string();			   /*			     */
#ifdef OLD
	  (void)look_macro(mac,1);		   /*			     */
#endif
	  (void)sbputs((char*)mac,parse_sb);	   /*			     */
	}					   /*			     */
    }						   /*			     */
  } while ( GetC == '#' );			   /*			     */
						   /*			     */
  push_string(symbol((String)sbflush(parse_sb)));  /*			     */
  sbrewind(parse_sb);				   /*			     */
  UnGetC; return(TRUE);				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_equation()
** Purpose:	Parse a pair separated by an equals sign.
**
** Arguments:
**	rec	The record to store the result in
** Returns:	Success status
**___________________________________________________			     */
static int parse_equation(rec)		   	   /*			     */
  Record rec;					   /*                        */
{ String s, t;				   	   /*			     */
						   /*			     */
  ExpectSymbol(TRUE,FALSE);			   /*			     */
  Expect('=',FALSE);				   /*			     */
  ExpectRhs(FALSE);				   /*			     */
						   /*			     */
  t = pop_string();				   /*			     */
  s = pop_string();				   /*			     */
  push_to_record(rec,s,t);			   /*			     */
  return(TRUE);					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_bib()
** Purpose:	Read one entry and fill the internal record structure.
**		Return the type of the entry read.
**
**		|BIB_EOF| is returned if nothing could be read and
**		the end of the file has been encountered.
**
**		|BIB_NOOP| is returned when an error has occurred. This is
**		an indicator that no record has been read but the
**		error recovery is ready to try it again.
**
**		This function is for internal purposes mainly. See
**		|read_db()| for a higher level function to read a
**		database. 
** Arguments:
**	rec	Record to store the result in.
** Returns:	The type of the entry read, |BIB_EOF|, or |BIB_NOOP|.
**___________________________________________________			     */
int parse_bib(rec)				   /*			     */
  Record rec;					   /*                        */
{ register int type,				   /*			     */
	       n,				   /*			     */
	       c,				   /*			     */
	       om;				   /*			     */
  long	       ignored = 0L;			   /*			     */
  char         *name;				   /*                        */
  int          line;				   /*                        */
  char	       buffer[32];			   /*                        */
  static StringBuffer * comment_sb = (StringBuffer*)NULL;/*                  */
 						   /*                        */
  if ( file == NULL ) return BIB_EOF;	   	   /*                        */
  if ( comment_sb == (StringBuffer*)NULL )	   /*                        */
  { comment_sb = sbopen(); } 			   /*                        */
 						   /*                        */
  RecordOldKey(rec)  = NULL;	   	   	   /*			     */
  RecordFree(rec)    = 0;		   	   /*			     */
  RecordComment(rec) = sym_empty;	   	   /*                        */
 						   /*                        */
  do						   /*                        */
  { init_parse();				   /*			     */
						   /*			     */
    while ( (c=skip_c()) != '@' )		   /* Skip to next @	     */
    { if ( c == EOF )				   /*                        */
      { char *s, *t;				   /*                        */
	if ( ignored == 0 ) return(BIB_EOF); 	   /*			     */
	RecordType(rec) = BIB_COMMENT;		   /*                        */
 						   /*                        */
	s = t = sbflush(comment_sb);		   /*                        */
	while ( *s ) s++;			   /*                        */
	while ( t <= --s  && is_space(*s) ) *s = '\0';/*                     */
	if ( *t ) RecordComment(rec) = symbol((String)t);/*                  */
	sbrewind(comment_sb);			   /*                        */
	return(BIB_COMMENT);		   	   /*			     */
      }						   /*                        */
      if ( !is_space(c) ) ++ignored;		   /*			     */
      if ( ignored > 0 && rsc_pass_comment )	   /*			     */
      { sbputchar(c,comment_sb); }		   /*			     */
    }						   /*			     */
    						   /*			     */
    if ( ignored != 0L )			   /*			     */
    { if ( rsc_pass_comment )			   /*                        */
      { sbputchar('\n',comment_sb); }	   	   /*			     */
      else					   /*			     */
      { (void)sprintf(buffer,"%ld",ignored);	   /*			     */
	error(ERR_WARN|ERR_FILE,(String)buffer,	   /*			     */
	      (String)" non-space characters ignored.",/*		     */
	      StringNULL,StringNULL,StringNULL,	   /*			     */
	      flno,filename);			   /*			     */
      }						   /*			     */
    }						   /*			     */
						   /*			     */
    if ( (type=find_entry_type(flp)) == BIB_NOOP ) /*		             */
    { Error("Unknown entry type");		   /*                        */
      return(BIB_NOOP);				   /*                        */
    }						   /*		             */
    flp += strlen((char*)EntryName(type));	   /*			     */
 						   /*                        */
    if ( type == BIB_COMMENT && rsc_pass_comment ) /*                        */
    { sbputchar('@', comment_sb);		   /*                        */
      sbputs((char*)EntryName(type), comment_sb);  /*                        */
    }						   /*                        */
  } while (type == BIB_COMMENT);		   /*                        */
					   	   /*			     */
  c = GetC;					   /*			     */
  if ( c != '{' && c != '(' )			   /*			     */
  { Error("Expected '{' or '(' missing");	   /*			     */
    return(BIB_NOOP);				   /*			     */
  }						   /*			     */
  line = flno;					   /*                        */
  name = filename;				   /*                        */
						   /*			     */
  RecordType(rec) = type;			   /*                        */
						   /*			     */
  switch ( type )				   /*			     */
  { case BIB_COMMENT:				   /* This code is not used  */
      UnGetC; 					   /*  any more.             */
      (void)parse_rhs();			   /*                        */
      push_to_record(rec,pop_string(),StringNULL);  /*			     */
      return type;				   /*                        */
 						   /*                        */
    case BIB_PREAMBLE:				   /*			     */
      ExpectRhs(BIB_NOOP);			   /*			     */
      push_to_record(rec,pop_string(),StringNULL);  /*			     */
      break;					   /*			     */
						   /*			     */
    case BIB_STRING:				   /*			     */
      ExpectEqMac(rec,BIB_NOOP);		   /*			     */
      break;					   /*			     */
						   /*			     */
    case BIB_ALIAS:				   /*			     */
      ExpectEq(rec,BIB_NOOP);			   /*			     */
      break;					   /*			     */
						   /*			     */
    case BIB_INCLUDE:				   /*			     */
      ExpectRhs(BIB_NOOP);			   /*			     */
      push_to_record(rec,pop_string(),StringNULL);  /*			     */
      break;					   /*			     */
						   /*			     */
    case BIB_MODIFY:				   /*			     */
    default:					   /*			     */
      if ( TestC == ',' )			   /*			     */
      { Warning("Missing reference key");	   /*			     */
	push_to_record(rec,sym_empty,StringNULL);   /*			     */
	(void)GetC;				   /*			     */
      }						   /*			     */
      else					   /*			     */
      { ExpectKey(FALSE,BIB_NOOP);		   /*			     */
	Expect(',',BIB_NOOP);			   /*			     */
	push_to_record(rec,pop_string(),StringNULL); /*			     */
      }						   /*			     */
						   /*			     */
      do					   /*			     */
      { ExpectEq(rec,BIB_NOOP);			   /*			     */
	for( n=0; GetC==','; n++)		   /*			     */
	{ if ( n == 1 )				   /*			     */
	  { Warning("Multiple ',' ignored."); }	   /*			     */
	}					   /*			     */
	UnGetC;					   /*			     */
	switch (TestC)				   /*                        */
	{ case EOF:				   /*                        */
	  case '}':				   /*                        */
	  case ')': om = FALSE; break;		   /*                        */
	  default:  om = TRUE;			   /*                        */
	    if ( n == 0 )			   /*			     */
	    { Warning("Missing ',' assumed."); }   /*			     */
	}					   /*                        */
      } while ( om );				   /*			     */
  }						   /*			     */
						   /*			     */
  switch ( GetC )				   /*			     */
  { case '}':					   /*			     */
      if( c != '{' )				   /*			     */
      { Warning("Parenthesis '(' closed by '}'"); }/*			     */
      break;					   /*			     */
    case ')':					   /*			     */
      if( c != '(' )				   /*			     */
      { Warning("Parenthesis '{' closed by ')'"); }/*			     */
      break;					   /*			     */
    case EOF:					   /*                        */
      { char *s;				   /*                        */
        if (c == '{') { s = "'{'"; }		   /*                        */
	else          { s = "'('"; } 		   /*                        */
	error(ERR_ERROR|ERR_FILE,(String)s,	   /*                        */
	      (String)" not closed at end of file.",/*                       */
	      StringNULL,StringNULL,StringNULL,	   /*			     */
	      line,name);			   /*			     */
      }						   /*                        */
      break;					   /*                        */
    default:					   /*			     */
      { String s;				   /*                        */
        if (c == '{') { s = (String)"'{'"; }	   /*                        */
	else	      { s = (String)"'('"; }	   /*                        */
	error(ERR_ERROR|ERR_FILE,		   /*                        */
	      s,				   /*                        */
	      (String)" not properly terminated.", /*                        */
	      StringNULL,StringNULL,StringNULL,	   /*			     */
	      line,name);			   /*			     */
      }						   /*                        */
      return(BIB_NOOP);				   /*			     */
  }						   /*			     */
 						   /*                        */
  { char *s, *t;				   /*                        */
    s = t = sbflush(comment_sb);		   /*                        */
    while ( *s ) s++;				   /*                        */
    while ( t <= --s  && is_space(*s) ) *s = '\0'; /*                        */
    if ( *t ) RecordComment(rec) = (String)symbol((String)t);/*              */
  }						   /*                        */
  sbrewind(comment_sb);				   /*                        */
  return(type);					   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/*									     */
/*****************************************************************************/

 static char **r_path	  = (char**)0;
 static char *r_pattern[] =
 { "%s/%s", "%s/%s.rsc", NULL };

/*-----------------------------------------------------------------------------
** Function:	set_rsc_path()
** Purpose:	Initialize the resource file reading apparatus.
**		Primarily try to figure out the file search path.
** Arguments:
**	val	The string representation of the file search path.
** Returns:	nothing
**___________________________________________________			     */
void set_rsc_path(val)				   /*			     */
  String  val;				   	   /*			     */
{						   /*			     */
  rsc_v_rsc = val;			   	   /*			     */
  init___(&r_path,				   /*			     */
	  r_pattern,				   /*			     */
	  (char**)&rsc_v_rsc,			   /*			     */
	  (char*)rsc_e_rsc  );			   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	see_rsc()
** Purpose:	Open a rsc file to read from. The resource file path
**		and the optional extensions are used to construct the
**		full file name.
** Arguments:
**	fname	The file name to take into account.
** Returns:	|TRUE| iff the operation succeeds.
**___________________________________________________			     */
static int see_rsc(fname)			   /*			     */
  String fname;				   	   /*			     */
{						   /*			     */
  if ( fname )					   /*			     */
  { init_parse();				   /*			     */
    InitLine;					   /*			     */
    file = px_fopen((char*)fname,		   /*			     */
		    "r",			   /*			     */
		    r_pattern,			   /*			     */
		    r_path,			   /*			     */
		    see_bib_msg);		   /*			     */
    filename = px_filename;			   /*			     */
    return( file != NULL );			   /*			     */
  }						   /*			     */
  return FALSE;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	parse_value()
** Purpose:	
**		
**
** Arguments:
**	
** Returns:	
**___________________________________________________			     */
static int parse_value()			   /*			     */
{						   /*			     */
  int   start_flno = flno;			   /*                        */
 						   /*                        */
  sbrewind(parse_sb);				   /*			     */
  switch ( GetC )				   /*			     */
  { case EOF:					   /*                        */
      UnterminatedError("Unterminated value",	   /*                        */
			start_flno);		   /*                        */
      return FALSE;	   			   /*			     */
						   /*			     */
    case '"':					   /*			     */
      if ( !parse_string(FALSE) ) return(FALSE);   /*			     */
      push_string(symbol((String)sbflush(parse_sb)));/*			     */
      sbrewind(parse_sb);			   /*			     */
      break;					   /*			     */
						   /*			     */
    case '0': case '1': case '2': case '3': case '4':/*			     */
    case '5': case '6': case '7': case '8': case '9':/*			     */
      UnGetC; parse_number();			   /*			     */
      break;					   /*			     */
						   /*			     */
    case '{':					   /*			     */
      if ( !parse_block(FALSE) ) return FALSE;	   /*			     */
      push_string(symbol((String)sbflush(parse_sb)));/*			     */
      sbrewind(parse_sb);			   /*			     */
      break;					   /*			     */
						   /*			     */
    default:					   /*			     */
      UnGetC; ExpectSymbol(TRUE,FALSE);		   /*			     */
  }						   /*			     */
						   /*			     */
  return TRUE;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_rsc()
** Purpose:	Read a resource file and evaluate all instructions
**		contained.
**
**		The characters |#|, |%|, and |;| start an endline
**		comment but only between resource instructions. They
**		are not recognized between a resource instruction
**		and its value or inside the value braces.
**
**		This function is contained in this module because it
**		shares several functions with the \BibTeX{} parsing
**		routines. 
** Arguments:
**	name	Name of the file to read from.
** Returns:	
**___________________________________________________			     */
int read_rsc(name)				   /*			     */
  String	name;				   /*			     */
{ int	        c;				   /*			     */
  String	token;				   /*			     */
  char		*s_filename;			   /*			     */
  FILE		*s_file;			   /*                        */
  String	s_file_line_buffer;		   /*                        */
  size_t	s_fl_size;			   /*                        */
  int		s_flno;				   /*                        */
  String	s_flp;				   /*                        */
 						   /* Save the old state in  */
 						   /*  local variables to    */
 						   /*  restore it later.     */
  s_filename	     = filename;		   /*			     */
  s_file	     = file;			   /*                        */
  s_file_line_buffer = file_line_buffer;	   /*                        */
  s_fl_size	     = fl_size;			   /*                        */
  s_flno	     = flno;			   /*                        */
  s_flp		     = flp;			   /*                        */
 						   /*                        */
  fl_size	     = 0;			   /*                        */
						   /*			     */
  init_parse();					   /*			     */
						   /*			     */
  if ( see_rsc(name) )				   /*                        */
  {						   /*                        */
    while ( (c=TestC) != EOF )			   /*			     */
    { switch (c)				   /*			     */
      { case '#': case '%': case ';':		   /*			     */
	  ClearLine; break;			   /*			     */
	default:				   /*			     */
	  if ( !parse_symbol(c) )		   /*			     */
	  { (void)seen(); return(1); }		   /*			     */
	  token = pop_string();			   /*			     */
	  if ( TestC == '=' ) (void)GetC;	   /* = is optional	     */
	  if ( !parse_value() )			   /*			     */
	  { (void)seen();			   /*                        */
	    return(-1);				   /*                        */
	  }					   /*			     */
	  (void)set_rsc(token,pop_string());	   /*			     */
	}					   /*			     */
    }						   /*			     */
    (void)seen();				   /*			     */
    c = TRUE;					   /*			     */
  }						   /*                        */
  else						   /*                        */
  { c = FALSE;		   			   /*			     */
  }						   /*                        */
  if ( fl_size > 0 ) 				   /*                        */
  { free((char*)file_line_buffer);		   /*                        */
  }						   /*                        */
  filename	   = s_filename;		   /*			     */
  file	     	   = s_file;			   /*                        */
  file_line_buffer = s_file_line_buffer;	   /*                        */
  fl_size	   = s_fl_size;			   /*                        */
  flno		   = s_flno;			   /*                        */
  flp		   = s_flp;			   /*                        */
 						   /*                        */
  return c;					   /*                        */
}						   /*------------------------*/
