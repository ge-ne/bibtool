/*** pxfile.c *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2018 Gerd Neugebauer
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
**	This file provides routines for extended file opening. Files
**	are sought in a list of directories and optionally with a set
**	of extensions appended to them.
**
**	Patterns may be given which are used to determine the full file 
**	name.
**	The patterns are stored in a special data structure.  A
**	function is provided to allocate a pattern structure and fill
**	it from a string specification.
**	    
******************************************************************************/

#include "config.h"
#include <bibtool/general.h>
#include <bibtool/pxfile.h>
#include <bibtool/sbuffer.h>

#include <ctype.h>

#ifndef __STDC__
#ifndef HAVE_GETENV
 extern char * getenv _ARG((char* name));	   /*			     */
#endif
#endif

#ifndef DEFAULT_PATTERN
#ifdef MSDOS
#define DEFAULT_PATTERN "%s\\%s"
#else
#define DEFAULT_PATTERN "%s/%s"
#endif
#endif

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 FILE * px_fopen _ARG((char * name,char * mode,char **pattern,char **path,int (*show)_ARG((char*))));
 char ** px_s2p _ARG((char * s,int sep));
 static bool absolute_file _ARG((char *name,char **basename,char ***path));
 static void expand_env _ARG((char * s,char * se,StringBuffer * res));

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/


/*****************************************************************************/

/*-----------------------------------------------------------------------------
** Variable:	px_filename
** Purpose:	This variable contains the file name actually used by
**		the last |px_fopen()| call. The memory is automatically
**		managed and will be reused by the next call to
**		|px_fopen()|.  Thus if you need to use it make a
**		private copy immediately after the call to the
**		function |px_fopen()|.
**___________________________________________________			     */
 char	       *px_filename   = "" ;
 static size_t px_len	      = 0  ;

 static char   * no_path[]    = { "."		 , NULL };
 static char   * no_pattern[] = { DEFAULT_PATTERN, NULL };

/*-----------------------------------------------------------------------------
** Function*:	absolute_file()
** Purpose:	Check is the file is an absolute file name.
**		In this case make a new path array which contains the absolute
**		path only and its location in path. basename is the modified
**		file name.
**
**		Currently UN*X and MSDOS like file names are supported.
** Arguments:
**	name	the name of the file
**	basename
**	path
** Returns:	The return value is |true|
**		Otherwise |false| is returned and nothing changed.
**___________________________________________________			     */
static bool absolute_file(name,basename,path)	   /*                        */
  char        *name;				   /*                        */
  char        **basename;			   /*                        */
  char        ***path;				   /*                        */
{ static char *absolut_path[2];			   /*                        */
  static int  first = (-1);			   /*                        */
  size_t         l;				   /*                        */
  char        *sp;				   /*                        */
#undef SEPARATOR
  						   /*                        */
#ifdef MSDOS
#define SEPARATOR '\\'
  if ( *name != SEPARATOR			   /* starting with root or  */
      && ( *name == '\0'			   /*                        */
	  || *(name+1) != ':'		   	   /*                        */
	  || *(name+2) != SEPARATOR ) )	   	   /*	with drive 	     */
#endif
#ifdef AMIGA
#define SEPARATOR '/'
  if ( strchr(name,':') == NULL )		   /* starting with root     */
#endif
#ifndef SEPARATOR
#define SEPARATOR '/'
  if ( *name != SEPARATOR )			   /* starting with root     */
#endif
  { return false; }				   /*                        */
 						   /*                        */
  sp = strrchr(name,SEPARATOR);			   /* find last separator    */
  						   /* existence guarenteed!  */
#ifdef AMIGA
  if ( sp == NULL ) sp = strchr(name,':');	   /*                        */
#endif
  l = (size_t)(sp-name);			   /* length of directory.   */
  if (first)				   	   /*                        */
  { first = 0;					   /*                        */
    absolut_path[1] = NULL;			   /* mark end of array.     */
    absolut_path[0] = malloc(l+1);		   /* allocate               */
  }						   /*  or                    */
  else						   /*  reallocate            */
  { absolut_path[0] = realloc(*absolut_path,l+1);  /*  space for the         */
  }						   /*  directory name        */
 						   /*                        */
  (void)strncpy(absolut_path[0],name,l);	   /* save directory name    */
  *(absolut_path[0]+l) = '\0';			   /* and mark the end.      */
 						   /*                        */
  *basename = name+l+1;				   /* return the base name   */
  *path = absolut_path;				   /* return the path array  */
  						   /*                        */
  return true;					   /* finished.              */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	px_fopen()
** Purpose:	Open a file using path and pattern.
**
**
** Arguments:
**	name	(base) name of the file to open.
**	mode	Mode for opening the file like used with |fopen()|.
**	pattern	A |NULL| terminated array of patterns.
**	path	The |NULL| terminated array of directories.
**	show	A function pointer or |NULL|.
** Returns:	A file pointer refering to the file or |NULL|.
**___________________________________________________			     */
FILE * px_fopen(name,mode,pattern,path,show)	   /*			     */
  char	* name;					   /*			     */
  char	* mode;					   /*			     */
  char	**pattern;				   /*			     */
  char	**path;					   /*			     */
  int	(*show)_ARG((char*));			   /*			     */
{ char	**fmt;					   /*			     */
  char	**pp;					   /*			     */
  FILE	* file;					   /*			     */
  size_t len,plen;				   /*			     */
  char  **new_path;				   /*                        */
  char  *new_name;				   /*                        */
						   /*			     */
  if (	 path  == NULL )    path = no_path;	   /* use default path	     */
  if ( pattern == NULL ) pattern = no_pattern;	   /* use default pattern    */
						   /*			     */
  if ( absolute_file(name,&new_name,&new_path) )   /*			     */
  { name = new_name;				   /*                        */
    path = new_path;				   /*                        */
  }						   /*			     */
						   /*			     */
  for ( plen=0,fmt=pattern;*fmt;++fmt )		   /* compute longest	     */
  { len = strlen(*fmt);				   /*	pattern		     */
    if ( len > plen ) plen = len;		   /*			     */
  }						   /*			     */
  plen += 1+strlen(name);			   /* add length of name     */
						   /*	and 1 for '\0'	     */
  if ( px_len == 0 &&				   /* initial filename	     */
       (px_filename = malloc(plen))==NULL )	   /*	then allocate or     */
    return(NULL);				   /*	terminate	     */
  px_len = plen-1;				   /* usable is 1 less	     */
						   /*			     */
  for ( pp=path;*pp;++pp )			   /* use all paths	     */
  { len = strlen(*pp) + plen;			   /* required space	     */
    if ( px_len < len )				   /* if less present get it */
    { char * old = px_filename;			   /*                        */
      if ( (px_filename = realloc(px_filename,len))==NULL ) {/*		     */
	free(old);				   /*                        */
	return(NULL);				   /*                        */
      }						   /*                        */
      px_len = len-1;				   /* usable is 1 less	     */
    }						   /*			     */
						   /*			     */
    for ( fmt=pattern;*fmt;++fmt )		   /* use all patterns	     */
    { (void)sprintf(px_filename,*fmt,*pp,name);	   /* construct new filename */
      if ( ( show == NULL ||			   /* if function present    */
	     (*show)(px_filename) ) &&		   /*	and it says yes	     */
	   (file=fopen(px_filename,mode)) != NULL )/*  and open succeeds     */
	return(file);				   /* then return file ptr   */
    }						   /*			     */
  }						   /*			     */
  *px_filename = '\0';				   /* clear filename	     */
  return(NULL);					   /* failure		     */
}						   /*------------------------*/

#define INIT_SIZE 32
#define INC_SIZE 16
	
/*-----------------------------------------------------------------------------
** Function:	px_s2p()
** Purpose:	Translate a path string specification into an array of the 
**		components.
**		The memory of the array is malloced and should be freed when
**		not used any longer.
** Arguments:
**	s	String to analyze
**	sep	Separator
** Returns:	The array of the components
**___________________________________________________			     */
char ** px_s2p(s,sep)				   /*			     */
  char		  * s;				   /*			     */
  int		  sep;				   /*			     */
{ register char	  *cp;				   /*			     */
  register size_t l = 1;			   /*			     */
  char		  **pattern;			   /*			     */
  int		  *array;			   /*                        */
  size_t	  array_size = INIT_SIZE;	   /*                        */
  size_t	  array_ptr  = 0;		   /*                        */
  char 		  *t;				   /*                        */
  StringBuffer    *sb;				   /*                        */
					       	   /*			     */
  if (s == NULL) return NULL;		   	   /* No string to analyze   */
						   /*			     */
  if ( (array=(int*)malloc(array_size*sizeof(int)))/*                        */
       == NULL )				   /*                        */
  { return NULL; }				   /*                        */
 						   /*                        */
  t  = cp = s;					   /*                        */
  sb = sbopen();				   /*                        */
  for(;;)	   	   			   /* Count the number of    */
  {			   			   /*  fields and expand     */
    if ( *cp == sep || *cp == '\0' )		   /*                        */
    { if ( array_ptr >= array_size )		   /*                        */
      { array_size += INC_SIZE;			   /*                        */
	int* old    = array;			   /*                        */
        array	    = (int*)realloc(array,	   /*                        */
				    array_size*sizeof(int));/*               */
	if ( array == NULL ) {			   /*                        */
	  free(old);				   /*                        */
	  return NULL;	   			   /*                        */
	}					   /*                        */
      }						   /*                        */
      array[array_ptr++] = sbtell(sb);		   /*                        */
      expand_env(t,cp,sb);			   /*                        */
      sbputchar('\0',sb);			   /*                        */
      t = cp+1;					   /*                        */
      if ( *cp ) cp++;				   /*                        */
      else break;				   /*                        */
    }						   /*                        */
    else					   /*                        */
    { cp++;					   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  l = sbtell(sb);				   /*                        */
  s = sbflush(sb);				   /*                        */
 						   /*                        */
  if ( (pattern=(char**)malloc( (array_ptr+1)*sizeof(char*)/*		     */
			       +l*sizeof(char)))   /*			     */
      == (char**)NULL )				   /* Try to allocate space  */
  { return NULL; }				   /*			     */
						   /*			     */
  cp = (char*)&pattern[array_ptr+1];		   /*                        */
  (void)memcpy(cp,s,l);		   		   /* save the string spec   */
 						   /*                        */
  for ( l = 0; l < array_ptr; l++ )		   /*                        */
  { pattern[l] = cp + array[l]; }		   /*                        */
  pattern[array_ptr] = 0L;			   /* Mark end		     */
						   /*			     */
  (void)free(array);				   /*                        */
  (void)sbclose(sb);				   /*                        */
  return pattern;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function*:	expand_env()
** Type:	static char *
** Purpose:	
**		
** Arguments:
**	s	
**	se	
** Returns:	
**___________________________________________________			     */
static void expand_env(s,se,res)		   /*                        */
  char * s;					   /*                        */
  char * se;					   /*                        */
  StringBuffer * res;				   /*                        */
{						   /*                        */
  StringBuffer * val = sbopen();		   /*                        */
 						   /*                        */
  for (; s < se; s++)				   /*                        */
  {						   /*                        */
    if (*s == '$')				   /*                        */
    { char beg = '\0';				   /*                        */
      char * env;				   /*                        */
      sbrewind(val);				   /*                        */
      s++;					   /*                        */
      if ( *s == '{' || *s == '(' )		   /*                        */
      { beg = *(s++); }				   /*                        */
      while ( isalpha(*s) || isdigit(*s) || *s == '_' )/*                    */
      { sbputchar(*s,val);			   /*                        */
        s++;					   /*                        */
      }						   /*                        */
      if ( ( beg == '{' && *s == '}' ) ||	   /*                        */
	   ( beg == '(' && *s == ')' )		   /*                        */
	 )					   /*                        */
      { s++; }					   /*                        */
      env = sbflush(val);			   /*                        */
      if (*env)				   	   /*                        */
      { env = getenv(env);			   /*                        */
        if ( env != NULL )			   /*                        */
	{ sbputs(env,res); }			   /*                        */
      }						   /*                        */
    }						   /*                        */
#ifdef HOME_ENV_VAR 
    else if (*s == '~')			   	   /*                        */
    {						   /*                        */
      char * env = getenv(HOME_ENV_VAR);	   /*                        */
      if (env != NULL)			   	   /*                        */
      { sbputs(env,res); }			   /*                        */
    }						   /*                        */
#endif
    else					   /*                        */
    { sbputchar(*s,res);			   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

