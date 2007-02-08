/******************************************************************************
** $Id: bibtool.c,v 1.2 2007-02-08 05:27:32 gene Exp $
*******************************************************************************
** Author: Gerd Neugebauer
**===========================================================================*/

#include <ctype.h>
#include <tcl.h>
#include <bibtool/bibtool.h>

#define OBJECT_PROC

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

int BibtoolObjectCmd(ClientData c, Tcl_Interp *i,int argc, char *argv[]);
int BibtoolCmd(ClientData c, Tcl_Interp *i,int argc, char *argv[]);

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


 void save_input_file (char *file){}	   	   /* main.c                 */
 void save_macro_file (char * file){}	   	   /* main.c                 */
 void save_output_file (char * file){}	   	   /* main.c                 */

 extern char * bibtool_version;

/*---------------------------------------------------------------------------*/


#define MAX_HANDLE_LENGTH 256
 static Tcl_HashTable bibtool_table;		   /*                        */
 static Tcl_HashEntry *ep;			   /*                        */
 static DB the_db;
 static char buffer[MAX_HANDLE_LENGTH];

 static char * empty   = "";
 static char * zero    = "0";
 static char * one     = "1";
 static char * err_0   = "*** bibtool error '";
 static char * err_1   = "': bibtool ";
 static char * err_2   = "too few arguments";
 static char * err_rec = "invalid record";
 static char * err_db  = "invalid database";

 static Tcl_DString ds;



#define ErrorExit(FCT)		\
  Tcl_AppendResult(interp,err_0,FCT,err_1,argv[1],NULL); return TCL_ERROR

#define NeedArgs(N)	if (argc<=N) { ErrorExit(err_2); }

#define CheckArg(N,V)	argc>N && strcmp(argv[N],V)==0

#define GetRecord(R,N)		\
  if ( (R=get__record(N)) == RecordNULL ) { ErrorExit(err_rec); }

#define GetDB(D,N)		\
  if ( (D=get__db(N)) == (DB)NULL ) { ErrorExit(err_db); }

#define IsNoRec(S) strchr(S,'/') == NULL

#ifdef OBJECT_PROC
#define MakeObject(S)		\
  Tcl_CreateCommand(interp,S,BibtoolObjectCmd,(ClientData)NULL, \
		    (Tcl_CmdDeleteProc *)NULL)
#else
#define MakeObject(S)	
#endif

#define THE_MARK 0x100

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	rec_gt()
** Purpose:	
**		
**
** Arguments:
**	r1
**	r2
** Returns:	
**___________________________________________________			     */
static int rec_gt(r1,r2)			   /*                        */
  Record r1;					   /*                        */
  Record r2;					   /*                        */
{ char * s1 = RecordSortkey(r1);		   /*                        */
  char * s2 = RecordSortkey(r2);		   /*                        */
  if ( s1 == NULL || *s1 == '\0' ) s1 = *RecordHeap(r1);/*                   */
  if ( s2 == NULL || *s2 == '\0' ) s2 = *RecordHeap(r2);/*                   */
  return (strcmp(s1,s2) < 0);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_lt()
** Purpose:	
**		
**
** Arguments:
**	r1
**	r2
** Returns:	
**___________________________________________________			     */
static int rec_lt(r1,r2)			   /*                        */
  Record r1;					   /*                        */
  Record r2;					   /*                        */
{ char * s1 = RecordSortkey(r1);		   /*                        */
  char * s2 = RecordSortkey(r2);		   /*                        */
  if ( s1 == NULL || *s1 == '\0' ) s1 = *RecordHeap(r1);/*                   */
  if ( s2 == NULL || *s2 == '\0' ) s2 = *RecordHeap(r2);/*                   */
  return (strcmp(s1,s2) > 0);			   /*                        */
}						   /*------------------------*/

#define REC_BEGINNING	1
#define REC_END		2
#define REC_HERE	0

/*-----------------------------------------------------------------------------
** Function:	new__record()
** Purpose:	Create a new handle for a record.
** Arguments:
**	rec	
**	pos	
** Returns:	
**___________________________________________________			     */
static char * new__record(interp,rec,s_db,pos)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  Record     rec;				   /*                        */
  char       *s_db;				   /*                        */
  int	     pos;				   /*                        */
{ int	     i;				   	   /*                        */
  char	     *name;				   /*                        */
 						   /*                        */
  if ( rec == NULL ) return empty;		   /*                        */
						   /*                        */
  switch (pos)					   /*                        */
  {						   /*                        */
    case REC_BEGINNING:				   /*                        */
      while (PrevRecord(rec)!=RecordNULL)	   /*                        */
	rec = PrevRecord(rec);			   /*                        */
      while ( rec && RecordIsDELETED(rec) )	   /*                        */
	rec = NextRecord(rec);			   /*                        */
      break;					   /*                        */
    case REC_END:				   /*                        */
      while (NextRecord(rec)!=RecordNULL)	   /*                        */
	rec = NextRecord(rec);			   /*                        */
      while ( rec && RecordIsDELETED(rec) )	   /*                        */
	rec = PrevRecord(rec);			   /*                        */
      break;					   /*                        */
  }						   /*                        */
 						   /*                        */
  if ( rec == NULL ) return empty;		   /*                        */
						   /*                        */
  i = 1;					   /*                        */
  do						   /*                        */
  { sprintf(buffer,"%s/=%d=",s_db,i++);		   /*                        */
  } while (Tcl_FindHashEntry(&bibtool_table,buffer) != NULL);/*              */
 						   /*                        */
  if ( (name = malloc(strlen(buffer)+1)) == NULL ) return empty;/*           */
  strcpy(name,buffer);				   /*                        */
 						   /*                        */
  MakeObject(name);				   /*                        */
  Tcl_SetHashValue(Tcl_CreateHashEntry(&bibtool_table,name,&i),/*            */
		   (ClientData)rec);		   /*                        */
  return name;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get__record()
** Purpose:	
**		
**		
** Arguments:
**	name	
** Returns:	
**___________________________________________________			     */
static Record get__record(name)	   		   /*                        */
  char	 *name;				   	   /*                        */
{ char	 *cp;				   	   /*                        */
  Record rec;				   	   /*                        */
  Tcl_HashEntry *ep2;				   /*                        */
 						   /*                        */
  if ( strlen(name) >= MAX_HANDLE_LENGTH )	   /*                        */
  { return RecordNULL; }			   /*                        */
  strcpy(buffer,name);				   /*                        */
  if ( (cp = strchr(buffer,'/')) == NULL )	   /*                        */
  { return RecordNULL; }			   /*                        */
  *cp = '\0';					   /*                        */
 						   /*                        */
  if ( NULL == (ep2=Tcl_FindHashEntry(&bibtool_table,buffer)) )/*            */
  { return RecordNULL; }			   /*                        */
  the_db = (DB) Tcl_GetHashValue(ep2);		   /*                        */
						   /*                        */
  if (NULL == (ep=Tcl_FindHashEntry(&bibtool_table,name)) )/*                */
  { Tcl_DeleteHashEntry(ep2);			   /*                        */
    return RecordNULL;			   	   /*                        */
  }						   /*                        */
						   /*                        */
  rec = (Record)Tcl_GetHashValue(ep);		   /*                        */
  if ( RecordIsDELETED(rec) )			   /*                        */
  { Tcl_DeleteHashEntry(ep);			   /*                        */
    return RecordNULL;				   /*                        */
  }						   /*                        */
  return rec;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new__db()
** Purpose:	
**		
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
static char * new__db()			   	   /*                        */
{ int	      i;				   /*                        */
  char	      *name;				   /*                        */
 						   /*                        */
  i = 1;					   /*                        */
  do						   /*                        */
  { sprintf(buffer,"=BibTcl=%d=",i++);		   /*                        */
  } while (Tcl_FindHashEntry(&bibtool_table,buffer) != NULL);/*              */
   						   /*                        */
  if ( (name = malloc(strlen(buffer)+1)) == NULL ) return empty;/*           */
  strcpy(name,buffer);				   /*                        */
  the_db = new_db();				   /*                        */
  Tcl_SetHashValue(Tcl_CreateHashEntry(&bibtool_table,name,&i),/*            */
		   (ClientData)the_db);		   /*                        */
  return name;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get__db()
** Purpose:	
**		
**		
** Arguments:
**	name	
** Returns:	
**___________________________________________________			     */
static DB get__db(name)			   	   /*                        */
  char *name;					   /*                        */
{						   /*                        */
  ep = Tcl_FindHashEntry(&bibtool_table,name);	   /*                        */
  return (ep==NULL?(DB)NULL:(DB)Tcl_GetHashValue(ep));/*                     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	yes()
** Purpose:	
**		
**		
** Arguments:
**	db	
**	rec	
** Returns:	
**___________________________________________________			     */
static int yes(db,rec)				   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
{ return 1;					   /*                        */
}						   /*------------------------*/

 static Tcl_Interp *ip;

/*-----------------------------------------------------------------------------
** Function:	aux__1i()
** Purpose:	
**		
**		
** Arguments:
**	s	
** Returns:	
**___________________________________________________			     */
static int aux__1i(s)				   /*                        */
  char * s;					   /*                        */
{						   /*                        */
  Tcl_AppendElement(ip,s);			   /*                        */
  return 1;
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	aux__0()
** Purpose:	
**		
**		
** Arguments:
**	s	
** Returns:	nothing
**___________________________________________________			     */
static void aux__0(s)
  char *s;
{
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	aux__1()
** Purpose:	
**		
**		
** Arguments:
**	s	
** Returns:	
**___________________________________________________			     */
static void aux__1(s)				   /*                        */
  char * s;					   /*                        */
{						   /*                        */
  Tcl_AppendElement(ip,s);			   /*                        */

}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_aux()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_aux(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ void	     (*fct)_ARG((char*));		   /*                        */
 						   /*                        */
  ip = interp;					   /*                        */
  NeedArgs(2);					   /*                        */
  if ( CheckArg(3,"-db") ) fct = aux__1;	   /*                        */
  else fct = aux__0;				   /*                        */
  clear_aux();					   /*                        */
  if ( read_aux(argv[2],fct,0) )		   /*                        */
  { ErrorExit("aux file not readable"); }	   /*                        */
 						   /*                        */
  if ( CheckArg(3,"-db") )
  {}			   			   /*                        */
  else						   /*                        */
  { if ( foreach_aux(aux__1i) )			   /*                        */
    { Tcl_SetResult(interp,"*",TCL_STATIC); }	   /*                        */
  }						   /*                        */
  return TCL_OK;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_count()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_count(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB         db;				   /*                        */
  int        *cnt,i;				   /*                        */
  NeedArgs(3);					   /*                        */
  GetDB(db,argv[2]);				   /*                        */
  Tcl_UnsetVar(interp,argv[3],0);		   /*                        */
  cnt = db_count(db,&i);			   /*                        */
  while ( 0 <= --i )				   /*                        */
  { sprintf(buffer,				   /*                        */
	    "set %s(%s) %d",			   /*                        */
	    argv[3],EntryName(i),cnt[i]);	   /*                        */
    Tcl_Eval(interp,buffer);			   /*                        */
  }						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_delete()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_delete(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
  DB	     db;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
					       	   /*                        */
  if ( IsNoRec(argv[2]) )
  { GetDB(db,argv[2]);
    free_db(db);
    Tcl_DeleteHashEntry(ep);
  }						   /*                        */
  else						   /*                        */
  { GetRecord(rec,argv[2]);
    Tcl_DeleteHashEntry(ep);
  }						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_equal()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_equal(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec1, rec2;			   /*                        */
						   /*                        */
  NeedArgs(3);					   /*                        */
  GetRecord(rec1,argv[2]);			   /*                        */
  GetRecord(rec2,argv[3]);			   /*                        */
  Tcl_SetResult(interp,(rec1==rec2?one:zero),TCL_STATIC);/*                  */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_dup()
** Purpose:	Duplicate a record handle.
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_dup(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
  Tcl_SetResult(interp,				   /*                        */
		new__record(interp,		   /*                        */
			    rec,		   /*                        */
			    argv[2],		   /*                        */
			    REC_HERE),		   /*                        */
		TCL_VOLATILE);	   		   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_fields()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_fields(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
  int n;					   /*                        */
  Uchar **cpp;					   /*                        */
 						   /*                        */
  NeedArgs(1);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
  cpp = RecordHeap(rec);		   	   /*                        */
  n   = RecordFree(rec);			   /*                        */
  for ( n -= 2, cpp += 2;			   /*			     */
	n > 0;				   	   /*			     */
	n -= 2 )				   /*			     */
  {						   /*                        */
    if (*cpp) { Tcl_AppendElement(interp,	   /*                        */
				  (char*)(*cpp)); }/*                        */
    cpp++; cpp++;				   /*                        */
  }						   /*                        */
 						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_find()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_find(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB	     db;				   /*                        */
 						   /*                        */
  NeedArgs(3);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */
  Tcl_SetResult(interp,				   /*                        */
		new__record(interp,		   /*                        */
			    db_find(db,sym_add(argv[3],0)),/*                */
			    argv[2],		   /*                        */
			    REC_HERE),	   	   /*                        */
		TCL_VOLATILE);	   		   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_format()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_format(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
  StringBuffer *sb;				   /*                        */
  int ret;
 						   /*                        */
  NeedArgs(3);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
  if ( (sb=sbopen()) == NULL )			   /*                        */
  {
    return TCL_ERROR;				   /*                        */
  }
  ret = apply_fmt(sb,argv[3],rec,the_db);
  Tcl_AppendResult(interp,sbflush(sb),NULL);
  sbclose(sb);
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_get()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_get(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
  int	     n;					   /*                        */
  char	     *s;				   /*                        */
  int	     all    = 0;			   /*                        */
  int        xref_limit = rsc_xref_limit;	   /*                        */
  int        key_expand = rsc_key_expand_macros;   /*                        */
 						   /*                        */
  NeedArgs(3);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
 						   /*                        */
  rsc_key_expand_macros = 1;			   /*                        */
  for ( n=4; argc>n; n++ )			   /*                        */
  { if ( strcmp(argv[n],"-noexpand") == 0 )	   /*                        */
    { rsc_key_expand_macros = 0; }		   /*                        */
    else if ( strcmp(argv[n],"-all") == 0 )	   /*                        */
    { all = 1; }				   /*                        */
  }

  if ( !all ) rsc_xref_limit = 1;

  if ( (s=get_field(the_db,rec,symbol(argv[3]))) == NULL )/*                 */
  { Tcl_SetResult(interp,empty,TCL_STATIC); }
  else if ( rsc_key_expand_macros )
  { Tcl_SetResult(interp,s,TCL_VOLATILE); }    /*                        */
  else 
  {
    int    level;
    char   c, *cp, *t, ec;
    Tcl_DStringInit(&ds);
   
    t = s;
    for ( cp=s; *cp; cp++ )
    {
      if ( *cp == '"' || *cp == '{' )
      { if ( *cp == '"' )
        { ec    = '"';
	  level = 0;
	}
        else 
	{ ec    = '}';
	  level = -1;
	}
        for ( t = cp++;
	      *cp && (level>0 || *cp != ec);
	      cp ++ )
	{ switch ( *cp )
	  { case '{': level++; break;
	    case '}': level--; break;
	  }
	}
	if ( *cp )
	{ c = *++cp;
	  *cp = '\0';
	  Tcl_DStringAppendElement(&ds,t);
	  *cp = c;
	  t = cp;
	}
      }
      else if ( isdigit(*cp) )
      { do { ++cp; } while (isdigit(*cp));
        c = *cp;
	*cp = '\0';
	Tcl_DStringAppendElement(&ds,t);
	*cp = c;
	t = cp--;
      }
      else if ( strchr("#%'(){}\",=",*cp) == NULL
		&& !isspace(*cp) )
      { do { ++cp; }
	while ( *cp
		&& !isdigit(*cp)
		&& !isspace(*cp)
		&& strchr("#%'(){}\",=",*cp) == NULL
	      );
        c = *cp;
	*cp = '\0';
	Tcl_DStringAppendElement(&ds,t);
	*cp = c;
	t = cp--;
      }
    }						   /*                        */
    Tcl_DStringResult(interp,&ds);		   /*                        */
  }						   /*                        */
 						   /*                        */
  rsc_xref_limit        = xref_limit;		   /*                        */
  rsc_key_expand_macros = key_expand;		   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_ig_clear()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_ig_clear(interp,argc,argv)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{						   /*                        */
  clear_ignored_words();			   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_ig_add()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_ig_add(interp,argc,argv)	   	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ int i;					   /*                        */
  for (i=2;i<argc;i++)
  { add_ignored_word(symbol(argv[i])); }
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	ig_get()
** Purpose:	
**		
**		
** Arguments:
**	s	
** Returns:	
**___________________________________________________			     */
int ig_get(s)					   /*                        */
  char * s;					   /*                        */
{ Tcl_DStringAppendElement(&ds,s);		   /*                        */
  return 1;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_ig_get()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_ig_get(interp,argc,argv)	   	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{
  Tcl_DStringInit(&ds);
  foreach_ignored_word(ig_get);
  Tcl_DStringResult(interp,&ds);		   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_ismarked()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_ismarked(interp,argc,argv)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
  Tcl_SetResult(interp,
		(RecordIs(rec,THE_MARK)?one:zero),
		TCL_STATIC);	   		   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_key()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_key(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record rec;
  DB db;

  NeedArgs(2);					   /*                        */
  if ( IsNoRec(argv[2]) )			   /*                        */
  { GetDB(db,argv[2]);				   /*                        */
    if ( (rec = DBnormal(db)) != RecordNULL )
    { while ( PrevRecord(rec) != RecordNULL )
      { rec = PrevRecord(rec); }
      while ( rec != RecordNULL )
      { make_key(db,rec);
	rec = NextRecord(rec);
      }
    }
    Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  }
  else
  {
    GetRecord(rec,argv[2]);			   /*                        */
    make_key(the_db,rec);
    Tcl_SetResult(interp,*RecordHeap(rec),TCL_VOLATILE);/*                   */
  }						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}

static int do_mark(db,rec)
  DB db;
  Record rec;
{ RecordSet(rec,THE_MARK);
  return 0;
}

static int do_unmark(db,rec)
  DB db;
  Record rec;
{ RecordClear(rec,THE_MARK);
  return 0;
}

/*-----------------------------------------------------------------------------
** Function:	bt_mark()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
**	addp	
** Returns:	
**___________________________________________________			     */
static int bt_mark(interp,argc,argv,addp)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
  int	     addp;				   /*                        */
{
 						   /*                        */
  NeedArgs(2);					   /*                        */
  if ( IsNoRec(argv[2]) )			   /*                        */
  { DB db;
    GetDB(db,argv[2]);				   /*                        */
    if ( addp ) db_forall(db,do_mark);
    else        db_forall(db,do_unmark);
  }
  else
  { Record rec;
    GetRecord(rec,argv[2]);			   /*                        */
    if ( addp ) RecordSet(rec,THE_MARK);
    else        RecordClear(rec,THE_MARK);
  }
 						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_missing()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_missing(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
  int n;					   /*                        */
  Uchar **cpp;					   /*                        */
 						   /*                        */
  NeedArgs(3);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
 						   /*                        */
  cpp = RecordHeap(rec);			   /*                        */
  n   = RecordFree(rec);			   /*                        */
  for ( n -= 2, cpp += 2;			   /*			     */
	n > 0;				   	   /*			     */
	n -= 2 )				   /*			     */
  { if (*cpp && case_cmp((char*)(*cpp),argv[3])==0 )/*                       */
    { Tcl_SetResult(interp,zero,TCL_STATIC);	   /*                        */
      return TCL_OK;	   	   		   /*                        */
    }						   /*                        */
    cpp++; cpp++;				   /*                        */
  }						   /*                        */
 						   /*                        */
  Tcl_SetResult(interp,one,TCL_STATIC);	   	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_move()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
**	dir	
** Returns:	
**___________________________________________________			     */
static int bt_move(interp,argc,argv,dir)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
  int	     dir;				   /*                        */
{ Record     rec;				   /*                        */
						   /*                        */
  NeedArgs(1);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
						   /*                        */
  if ( dir > 0 )				   /*                        */
  { do						   /*                        */
    { rec = NextRecord(rec);			   /*                        */
    } while ( rec != RecordNULL && RecordIsDELETED(rec) );/*                 */
  }						   /*                        */
  else						   /*                        */
  { do						   /*                        */
    { rec = PrevRecord(rec);			   /*                        */
    } while ( rec != RecordNULL && RecordIsDELETED(rec) );/*                 */
  }						   /*                        */
						   /*                        */
  if ( rec==RecordNULL ) 			   /*                        */
  { Tcl_DeleteHashEntry(ep);			   /*                        */
    Tcl_SetResult(interp,empty,TCL_VOLATILE);	   /*                        */
    return TCL_OK;	   	   		   /*                        */
  }						   /*                        */
 						   /*                        */
  Tcl_SetHashValue(ep,(ClientData)rec);		   /*                        */
  Tcl_SetResult(interp,argv[2],TCL_VOLATILE);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_name()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_name(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ char	     *s, *t, *tmp;			   /*                        */
  int	     i;					   /*                        */
 						   /*                        */
  NeedArgs(3);					   /*                        */
 						   /*                        */
  if ( strcmp(argv[2],"list")==0 )		   /*                        */
  {						   /*                        */
    s = argv[3];				   /*                        */
    while (is_space(*s)) s++;			   /*                        */
    if ( *s == '\0' ) return TCL_OK;		   /*                        */
    s = t = tmp = new_string(s);		   /*                        */
    while ( *s )				   /*                        */
    { 						   /*                        */
      if ( (*s == ' ' || *s == '\t' ) &&	   /*                        */
	   strncmp(s+1,"and",3) == 0  &&	   /*                        */
	   (s[4] == ' ' || s[4] == '\t' )	   /*                        */
	 )					   /*                        */
      { *s = '\0';				   /*                        */
        Tcl_AppendElement(interp,t);		   /*                        */
	s += 5;					   /*                        */
	while (is_space(*s)) s++;		   /*                        */
	t = s;					   /*                        */
      }						   /*                        */
      else					   /*                        */
      { s++;					   /*                        */
      }						   /*                        */
    }						   /*                        */
    if (*t) Tcl_AppendElement(interp,t);	   /*                        */
 						   /*                        */
    free(tmp);					   /*                        */
  }						   /*                        */
  else if ( strcmp(argv[2],"count")==0 )	   /*                        */
  { char buffer[32];				   /*                        */
 						   /*                        */
    s = argv[3];				   /*                        */
    i = 0;					   /*                        */
    while (is_space(*s)) s++;			   /*                        */
    if ( *s )					   /*                        */
    { i++;					   /*                        */
      while ( *s )				   /*                        */
      { 					   /*                        */
	if ( (*s == ' ' || *s == '\t' ) &&	   /*                        */
	     strncmp(s+1,"and",3) == 0  &&	   /*                        */
	     (s[4] == ' ' || s[4] == '\t' )	   /*                        */
	   )					   /*                        */
	{					   /*                        */
	  i++;					   /*                        */
	  s += 5;				   /*                        */
	}					   /*                        */
	else					   /*                        */
	{ s++;					   /*                        */
	}					   /*                        */
      }						   /*                        */
    }						   /*                        */
    sprintf(buffer,"%d",i);			   /*                        */
    Tcl_SetResult(interp,buffer,TCL_VOLATILE);	   /*                        */
  }
  else if ( strcmp(argv[2],"format")==0 )
  {
    NeedArgs(4);				   /*                        */



  }
  else
  {
    Tcl_SetResult(interp,"unknown subcommand",TCL_STATIC);/*                 */
    return TCL_ERROR;				   /*                        */
  }						   /*                        */
 						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_new()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_new(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ char	     *sdb;				   /*                        */
  int	     i;					   /*                        */
 						   /*                        */
  if ( (sdb=new__db()) == NULL )		   /*                        */
  { ErrorExit("db creation failed"); }		   /*                        */
 						   /*                        */
  for ( i=2; i<argc; i++ )			   /*                        */
  { read_db(the_db,argv[i],yes,0); }		   /*                        */
 						   /*                        */
  MakeObject(sdb);				   /*                        */
  Tcl_SetResult(interp,sdb,TCL_VOLATILE);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_preamble()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_preamble(interp,argc,argv)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB db;					   /*                        */
  Record rec;					   /*                        */
 						   /*                        */
  NeedArgs(1);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */
  rec = DBpreamble(db);				   /*                        */
  if ( rec == RecordNULL )			   /*                        */
  { Tcl_SetResult(interp,empty,TCL_STATIC); }	   /*                        */
  else						   /*                        */
  { Tcl_SetResult(interp,*RecordHeap(rec),TCL_VOLATILE);/*                   */
  }						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_read()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_read(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB	     db;				   /*                        */
  int	     i;					   /*                        */
 						   /*                        */
  NeedArgs(1);					   /*                        */
  GetDB(db,argv[2]);		   		   /*                        */
  for ( i=3; i<argc; i++ )			   /*                        */
  { if ( read_db(db,argv[i],yes,0) )		   /*                        */
    { ErrorExit("db reading failed."); }	   /*                        */
  }						   /*                        */
 						   /*                        */
  Tcl_SetResult(interp,argv[2],TCL_VOLATILE);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_rec()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
**	pos	
** Returns:	
**___________________________________________________			     */
static int bt_rec(interp,argc,argv,pos)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
  int	     pos;				   /*                        */
{ DB	     db;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */
 						   /*                        */
  Tcl_SetResult(interp,				   /*                        */
		new__record(interp,		   /*                        */
			    DBnormal(db),	   /*                        */
			    argv[2],		   /*                        */
			    pos),		   /*                        */
		TCL_VOLATILE);	   	   	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_record()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_record(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB         db;				   /*                        */
  Record     rec;				   /*                        */
  int	     type;				   /*                        */
 						   /*                        */
  NeedArgs(3);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */
  						   /*                        */
  { if ( (type = find_entry_type(argv[3])) < 0 )   /*                        */
    { ErrorExit("undefined entry type"); }	   /*                        */
  }						   /*                        */
 						   /*                        */
  rec = new_record(type,4);	   		   /*                        */
  push_to_record(rec,empty,NULL);		   /*                        */
  db_add_record(db,rec);			   /*                        */
  Tcl_SetResult(interp,				   /*                        */
		new__record(interp,		   /*                        */
			    rec,		   /*                        */
			    argv[2],		   /*                        */
			    REC_HERE), 		   /*                        */
		TCL_VOLATILE);	   		   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_rsc()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
**	i	
** Returns:	
**___________________________________________________			     */
static int bt_rsc(interp,argc,argv,i)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
  int	     i;					   /*                        */
{						   /*                        */
  for ( ; i<argc; i++ )				   /*                        */
  { if ( use_rsc(argv[i]) )			   /*                        */
    { ErrorExit("resource failure"); }		   /*                        */
  }						   /*                        */
 						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_resource()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
**	i	
** Returns:	
**___________________________________________________			     */
static int bt_resource(interp,argc,argv)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ char *s;
  int ret;

  NeedArgs(2);					   /*                        */

  s = malloc(strlen(argv[1])+strlen(argv[2])+4);
  strcpy(s,argv[1]);
  strcat(s,"={");
  strcat(s,argv[2]);
  strcat(s,"}");
  ret = use_rsc(s);
  free(s);
 						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return ret?TCL_ERROR:TCL_OK;			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_remove()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
**	i	
** Returns:	
**___________________________________________________			     */
static int bt_remove(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */

  if ( argc > 3 )				   /*                        */
  { remove_field(sym_add(argv[3],0),rec); }	   /*                        */
  else						   /*                        */
  { SetRecordDELETED(rec); }			   /*                        */
 						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	search__()
** Purpose:	
**		
**		
** Arguments:
**	rec	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int search__(rec,argc,argv)
  Record rec;
  int    argc;
  char   *argv[];
{ char   *s = argv[3];

  if ( RecordIsDELETED(rec) ) return 0;


  return 1;
}

/*-----------------------------------------------------------------------------
** Function:	bt_search()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_search(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
  DB	     db;				   /*                        */
 						   /*                        */
  NeedArgs(3);					   /*                        */
 						   /*                        */
  if ( IsNoRec(argv[2]) )
  { GetDB(db,argv[2]);
    rec = DBnormal(db);
    if ( rec != RecordNULL )
    { while ( PrevRecord(rec) != RecordNULL )
      { rec = PrevRecord(rec); }
      while ( rec )
      { if ( search__(rec,argc,argv) )
        { Tcl_SetResult(interp,			   /*                        */
			new__record(interp,	   /*                        */
				    rec,	   /*                        */
				    argv[2],	   /*                        */
				    REC_HERE),	   /*                        */
			TCL_VOLATILE);		   /*                        */
	  return TCL_OK;			   /*                        */
	}
	rec = NextRecord(rec);
      }
    }
  }						   /*                        */
  else						   /*                        */
  { GetRecord(rec,argv[2]);
    rec = NextRecord(rec);
    while ( rec )
    { if ( search__(rec,argc,argv) )
      {
	Tcl_SetHashValue(ep,(ClientData)rec);	   /*                        */
	Tcl_SetResult(interp,argv[2],TCL_VOLATILE);/*                        */
      }
      rec = NextRecord(rec);
    }

    Tcl_DeleteHashEntry(ep);			   /*                        */
    Tcl_SetResult(interp,empty,TCL_VOLATILE);	   /*                        */
    return TCL_OK;	   	   		   /*                        */
  }						   /*                        */
 						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_set()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_set(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
  int	     n;					   /*                        */
 						   /*                        */
  NeedArgs(4);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
 						   /*                        */
#define If_Separator_(S,N) if (strcmp(argv[3],S)==0) set_separator(N,argv[4])
 						   /*                        */
  if ( *argv[3] == '$' )			   /*                        */
  {						   /*                        */
    if ( strcmp(argv[3],"$key") == 0 )		   /*                        */
    { RecordOldKey(rec)				   /*                        */
	= *RecordHeap(rec) = symbol(argv[4]);	   /*                        */
    }	   					   /*                        */
    else if ( strcmp(argv[3],"$source") == 0 )	   /*                        */
    { RecordSource(rec) = symbol(argv[4]); }	   /*                        */
    else if ( strcmp(argv[3],"$type") == 0 )	   /*                        */
    { if ( (n = find_entry_type(argv[4])) < 0 )	   /*                        */
      { ErrorExit("undefined entry type"); }	   /*                        */
      RecordType(rec) = n;			   /*                        */
    }						   /*                        */
    else if ( strcmp(argv[3],"$sortkey") == 0 )	   /*                        */
    { RecordSortkey(rec) = symbol(argv[4]); }	   /*                        */
    else If_Separator_("$default.key"    ,0);	   /*                        */
    else If_Separator_("$fmt.inter.name" ,1);	   /*                        */
    else If_Separator_("$fmt.name.pre"   ,2);	   /*                        */
    else If_Separator_("$fmt.name.name"  ,3);	   /*                        */
    else If_Separator_("$fmt.name.title" ,4);	   /*                        */
    else If_Separator_("$fmt.title.title",5);	   /*                        */
    else If_Separator_("$fmt.key.number" ,6);	   /*                        */
    else If_Separator_("$fmt.et.al"      ,7);	   /*                        */
    else					   /*                        */
    {						   /*                        */
      Tcl_SetResult(interp,"illegal key",TCL_STATIC);/*                      */
      return TCL_ERROR;	   	   		   /*                        */
    }						   /*                        */
  }						   /*                        */
  else if ( *argv[3] == '@' )	   		   /*                        */
  {
  }
  else						   /*                        */
  { push_to_record(rec,				   /*                        */
		   symbol(argv[3]),		   /*                        */
		   symbol(argv[4]));		   /*                        */
  }						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_sort()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_sort(interp,argc,argv)	   	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB	     db;				   /*                        */
  Record     rec;				   /*                        */
  int        i;				   	   /*                        */
  int	     (*fct)();			   	   /* Function pointer	     */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  if ( IsNoRec(argv[2]) )			   /*                        */
  {						   /*                        */
    GetDB(db,argv[2]);			   	   /*                        */
    if ( (rec=DBnormal(db)) != RecordNULL )	   /*                        */
    {						   /*                        */
      while ( PrevRecord(rec) != RecordNULL )      /*                        */
      { rec = PrevRecord(rec); }                   /*                        */
      if ( CheckArg(3,"-generate") ||		   /*                        */
	   CheckArg(4,"-generate") )		   /*                        */
      {						   /*                        */
	for ( ; rec!=RecordNULL; rec=NextRecord(rec) )/*                     */
	{ make_sort_key(db,rec); }		   /*                        */
      }						   /*                        */
      else					   /*                        */
      {						   /*                        */
	for ( ; rec!=RecordNULL; rec=NextRecord(rec) )/*                     */
	{ if ( RecordSortkey(rec) == NULL	   /*                        */
	       || *RecordSortkey(rec) == '\0' )	   /*                        */
          { RecordSortkey(rec) = *RecordHeap(rec); }/*                       */
	}					   /*                        */
      }						   /*                        */
 						   /*                        */
      i = rsc_sort_reverse;			   /*                        */
      if ( CheckArg(3,"-reverse") ||		   /*                        */
	   CheckArg(4,"-reverse") ) { i = !i; }	   /*                        */
      if ( i ) fct = rec_lt;	   		   /*                        */
      else     fct = rec_gt;	   		   /*                        */
      db_sort(db,fct);			   	   /*                        */
    }						   /*                        */
  }						   /*                        */
  else						   /*                        */
  {						   /*                        */
    GetRecord(rec,argv[2]);			   /*                        */
    sort_record(rec);				   /*                        */
  }						   /*                        */
						   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_sput()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_sput(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetRecord(rec,argv[2]);			   /*                        */
						   /*                        */
  Tcl_SetResult(interp,				   /*                        */
		sput_record(rec,the_db,"@"),	   /*                        */
		TCL_VOLATILE);	   		   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_str_get()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_str_get(interp,argc,argv)	   	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB db;					   /*                        */
  char * s;					   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */
						   /*                        */
  for (s=argv[3];*s;s++) { *s = ToLower(*s); }
  s = db_string(db,symbol(argv[3]),-1);	   	   /*                        */
  if ( s == NULL )				   /*                        */
  { Tcl_SetResult(interp,empty,TCL_STATIC); }	   /*                        */
  else						   /*                        */
  { Tcl_SetResult(interp,s,TCL_VOLATILE); }	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_str_missing()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_str_missing(interp,argc,argv)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB db;					   /*                        */
  char * s;					   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */
						   /*                        */
  for (s=argv[3];*s;s++) { *s = ToLower(*s); }

  if ( CheckArg(4,"-global") )
  { s = (look_macro(argv[3],-1)==NULL?"1":"0");
  }
  else
  { s = ( db_string(db,symbol(argv[3]),-1) == NULL /*                        */
	  ?"1":"0");	   			   /*                        */
  }						   /*                        */
  Tcl_SetResult(interp,s,TCL_STATIC);		   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_str_remove()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_str_remove(interp,argc,argv)	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB	     db;				   /*                        */
  Record     rec;				   /*                        */
  Uchar      *s;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */
						   /*                        */
  for (s=argv[3];*s;s++) { *s = ToLower(*s); }	   /*                        */
  s = symbol(argv[3]);	   	   		   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
 						   /*                        */
  if ( CheckArg(4,"-global") )
  { def_macro(s,NULL,0);
  }
  else
  { 
    for ( rec=DBstring(db); rec ; rec=NextRecord(rec) )
    { if ( RecordHeap(rec)[0] == s )
      { DBstring(db) = unlink_record(rec);
        return TCL_OK;
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_str_set()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_str_set(interp,argc,argv)	   	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB	     db;				   /*                        */
  Record     rec;				   /*                        */
  Uchar      *s, *t;				   /*                        */
 						   /*                        */
  NeedArgs(4);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */
						   /*                        */
  for (s=argv[3];*s;s++) { *s = ToLower(*s); }	   /*                        */
  s = symbol(argv[3]);	   	   		   /*                        */
  t = symbol(argv[4]);	   	   		   /*                        */
  Tcl_SetResult(interp,empty,TCL_STATIC);	   /*                        */
 						   /*                        */
  if ( CheckArg(5,"-global") )			   /*                        */
  { def_macro(s,t,0);
  }
  else
  { 
    for ( rec=DBstring(db); rec ; rec=NextRecord(rec) )
    { if ( RecordHeap(rec)[0] == s )
      { RecordHeap(rec)[1] = t;
        return TCL_OK;
      }
    }
    rec = new_record(BIB_STRING,2);
    RecordHeap(rec)[0] = s;
    RecordHeap(rec)[1] = t;
    if ( DBstring(db) )
    { Record r;
      PrevRecord(rec) = DBstring(db);
      if ( (r=NextRecord(DBstring(db))) )
      { NextRecord(rec) = r;
        PrevRecord(NextRecord(r)) = rec;
      }
      NextRecord(DBstring(db)) = rec;
    }
    DBstring(db) = rec;
  }						   /*                        */
 						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	str__1()
** Purpose:	
**		
**		
** Arguments:
**	s	
**	t	
** Returns:	
**___________________________________________________			     */
static int str__1(s,t)				   /*                        */
  char *s;					   /*                        */
  char *t;					   /*                        */
{ Tcl_AppendElement(ip,s);			   /*                        */
  return 1;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_strings()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_strings(interp,argc,argv)	   	   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB	     db;				   /*                        */
  Record     rec;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  GetDB(db,argv[2]);			   	   /*                        */

  if ( CheckArg(3,"-global") )
  { ip = interp;
    foreach_macro(str__1);
  }
  else
  {
    if ( (rec=DBstring(db)) )			   /*                        */
    {						   /*                        */
      while ( PrevRecord(rec) )			   /*                        */
      { rec = PrevRecord(rec); }		   /*                        */
 						   /*                        */
      while ( rec )				   /*                        */
      { Tcl_AppendElement(interp,RecordHeap(rec)[0]);/*                      */
        rec = NextRecord(rec);			   /*                        */
      }						   /*                        */
    }						   /*                        */
  }						   /*                        */
						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_tex()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_tex(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Uchar	     *s;				   /*                        */
  int	     kept = 0;				   /*                        */
  char       q[2];				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  switch ( *argv[2] )				   /*                        */
  {						   /*                        */
    case 'd':					   /*                        */
      if (strcmp(argv[2],"define") == 0)	   /*                        */
      {						   /*                        */
	NeedArgs(3);				   /*                        */
	TeX_def(argv[3]);
	return TCL_OK;
      }
      break;
    case 'e':
      if (strcmp(argv[2],"expand") == 0)
      {
	NeedArgs(3);				   /*                        */
	q[1] = '\0';
	TeX_open_string(argv[3]);

	while ( TeX_read(q,&s) )		   /*			     */
	{ if ( kept )				   /*			     */
	  { if ( isalpha(*q) ) Tcl_AppendResult(interp," ",NULL);/*	     */
	    kept = 0;				   /*			     */
	  }					   /*			     */
	  Tcl_AppendResult(interp,q,NULL);
	  if ( s )				   /*			     */
	  { Tcl_AppendResult(interp,s,NULL);
	    kept = isalpha(*s);			   /*			     */
	  }					   /*			     */
	}					   /*			     */

	TeX_close();
	return TCL_OK;
      }
      break;
    case 'r':
      if (strcmp(argv[2],"reset") == 0)
      {
	TeX_reset();
	return TCL_OK;
      }
      break;
  }
  ErrorExit(argv[2]);	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_types()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_types(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ char	     *s;				   /*                        */
  int	     i;					   /*                        */
						   /*                        */
  i = ( CheckArg(2,"-all") ? 0 : 6);		   /*                        */
						   /*                        */
  for ( s=get_entry_type(i);			   /*			     */
	s != NULL;				   /*			     */
	s=get_entry_type(++i) )			   /*			     */
  { Tcl_AppendElement(interp,s); }  		   /*                        */
 						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_valid()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_valid(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ Record     rec;				   /*                        */
 						   /*                        */
  NeedArgs(2);					   /*                        */
  if ( IsNoRec(argv[2]) )			   /*                        */
  { Tcl_SetResult(interp,(get__db(argv[2])?one:zero),TCL_STATIC);/*          */
  }						   /*                        */
  else if ( (rec=get__record(argv[2])) == RecordNULL )/*                     */
  { Tcl_SetResult(interp,zero,TCL_STATIC);	   /*                        */
  }						   /*                        */
  else if ( argc == 3 ) 			   /*                        */
  { Tcl_SetResult(interp,one,TCL_STATIC);	   /*                        */
  }						   /*                        */
  else if ( CheckArg(3,"-next") ) 		   /*                        */
  { Tcl_SetResult(interp,(NextRecord(rec)?one:zero),TCL_STATIC);/*           */
  }						   /*                        */
  else if ( CheckArg(3,"-previous") ) 		   /*                        */
  { Tcl_SetResult(interp,(PrevRecord(rec)?one:zero),TCL_STATIC);/*           */
  }						   /*                        */
  else						   /*                        */
  { ErrorExit("unknown option");		   /*                        */
  }						   /*                        */
 						   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bt_write()
** Purpose:	
**		
**		
** Arguments:
**	interp	
**	argc	
**	argv	
** Returns:	
**___________________________________________________			     */
static int bt_write(interp,argc,argv)		   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	     argc;				   /*                        */
  char	     *argv[];				   /*                        */
{ DB	     db;				   /*                        */
  FILE *file;					   /*                        */
  char * mode = "w";				   /*                        */
 						   /*                        */
  NeedArgs(3);					   /*                        */
  GetDB(db,argv[2]);		   		   /*                        */
  if ( CheckArg(4,"-append") ) { mode = "a"; }	   /*                        */
						   /*                        */
  if ( *argv[3] == '\0' )			   /*                        */
  { file = stdout; }				   /*                        */
  else if ( (file=fopen(argv[3],mode))==NULL )	   /*                        */
  { ErrorExit("file open error"); }		   /*                        */
						   /*                        */
  print_db(file,db,"pisnmac");		   	   /*                        */
						   /*                        */
  if ( file != stdout ) fclose(file);		   /*                        */
 						   /*                        */
  Tcl_SetResult(interp,argv[2],TCL_VOLATILE);	   /*                        */
  return TCL_OK;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	BibtoolCmd()
** Purpose:	
**		
** Arguments:
**	ClientData clientData
**	 Tcl_Interp *interp
**	 int argc
**	 char* argv[]
** Returns:	
**___________________________________________________			     */
int BibtoolCmd(clientData, interp, argc, argv)	   /*                        */
  ClientData clientData;			   /*                        */
  Tcl_Interp *interp;				   /*                        */
  int	 argc;					   /*                        */
  char	 *argv[];				   /*                        */
{ char   *s;					   /*                        */
 						   /*                        */
  if ( argc < 2 )				   /*                        */
  { Tcl_SetResult(interp,bibtool_version,TCL_STATIC);/*                      */
    return TCL_OK;				   /*                        */
  }						   /*                        */
						   /*                        */
#ifdef DEBUG
  { int i;					   /*                        */
    for ( i=0; i<argc; i++ ) puts(argv[i]);	   /*                        */
    puts("");					   /*                        */
  }						   /*                        */
#endif
#define OnCommand(X)	if (strcmp(argv[1],X) == 0) return 
#ifdef SHORTCUT
#define ResourceCommand(X) OnCommand(X) bt_resource(interp,argc,argv)
#else
#define ResourceCommand(X)
#endif
						   /*			     */
  switch ( *argv[1] )				   /*			     */
  {						   /*			     */
    case 'a':					   /*			     */
      OnCommand("aux")		bt_aux(interp,argc,argv);/*		     */
      OnCommand("add_ignored")	bt_ig_add(interp,argc,argv);/*		     */
      break;					   /*			     */
    case 'b':					   /*			     */
      OnCommand("backward")	bt_move(interp,argc,argv,-1);/*		     */
      break;					   /*			     */
    case 'c':					   /*			     */
      OnCommand("clear_ignored" )bt_ig_clear(interp,argc,argv);/*	     */
      OnCommand("count" )	bt_count(interp,argc,argv);/*	             */
      break;					   /*			     */
    case 'd':					   /*			     */
      OnCommand("delete")	bt_delete(interp,argc,argv);/*		     */
      OnCommand("dup")		bt_dup(interp,argc,argv);/*		     */
      break;					   /*			     */
    case 'e':					   /*			     */
      OnCommand("entry")	bt_record(interp,argc,argv);/*		     */
      OnCommand("equal")	bt_equal(interp,argc,argv);/*		     */
      break;					   /*			     */
    case 'f':					   /*			     */
      OnCommand("first")	bt_rec(interp,argc,argv,REC_BEGINNING);/*    */
      OnCommand("forward")	bt_move(interp,argc,argv,1);/*		     */
      OnCommand("fields")	bt_fields(interp,argc,argv);/*		     */
      OnCommand("find")		bt_find(interp,argc,argv);/*		     */
      OnCommand("format")	bt_format(interp,argc,argv);/*		     */
      ResourceCommand("fmt.name.title");	   /*			     */
      ResourceCommand("fmt.title.title");	   /*			     */
      ResourceCommand("fmt.name.name");		   /*			     */
      ResourceCommand("fmt.inter.name");	   /*			     */
      ResourceCommand("fmt.name.pre");		   /*			     */
      ResourceCommand("fmt.et.al");		   /*			     */
      break;					   /*			     */
    case 'g':					   /*			     */
      OnCommand("get")		bt_get(interp,argc,argv,-1);/*		     */
      OnCommand("get_string")	bt_str_get(interp,argc,argv);/*		     */
      OnCommand("get_ignored")	bt_ig_get(interp,argc,argv);/*		     */
      break;					   /*			     */
    case 'i':					   /*			     */
      OnCommand("is_marked")	bt_ismarked(interp,argc,argv);/*	     */
      ResourceCommand("ignored.word");		   /*			     */
      break;					   /*			     */
    case 'k':					   /*			     */
      OnCommand("key")		bt_key(interp,argc,argv);/*		     */
      OnCommand("keys")		bt_key(interp,argc,argv);/*		     */
      ResourceCommand("key.format");		   /*			     */
      ResourceCommand("key.generation");	   /*			     */
      break;					   /*			     */
    case 'l':					   /*			     */
      OnCommand("last")		bt_rec(interp,argc,argv,REC_END);/*	     */
      break;					   /*			     */
    case 'm':					   /*			     */
      OnCommand("mark")		bt_mark(interp,argc,argv,TRUE);/*	     */
      OnCommand("missing")	bt_missing(interp,argc,argv);/*		     */
      OnCommand("missing_string") bt_str_missing(interp,argc,argv);/*	     */
      break;					   /*			     */
    case 'n':					   /*			     */
      OnCommand("new")		bt_new(interp,argc,argv);/*		     */
      OnCommand("name")		bt_name(interp,argc,argv);/*		     */
      break;					   /*			     */
    case 'p':					   /*			     */
      OnCommand("preamble")	bt_preamble(interp,argc,argv);/*	     */
      ResourceCommand("pass.comments");		   /*			     */
      ResourceCommand("print.line.length");	   /*			     */
      ResourceCommand("print.indent");		   /*			     */
      ResourceCommand("print.align");		   /*			     */
      ResourceCommand("print.align.key");	   /*			     */
      ResourceCommand("print.align.preamble");	   /*			     */
      ResourceCommand("print.align.comment");	   /*			     */
      ResourceCommand("print.newline");		   /*			     */
      ResourceCommand("print.use.tab");		   /*			     */
      ResourceCommand("print.braces");		   /*			     */
      ResourceCommand("print.parentheses");	   /*			     */
      break;					   /*			     */
    case 'q':					   /*			     */
      ResourceCommand("quiet");			   /*			     */
      break;					   /*			     */
    case 'r':					   /*			     */
      OnCommand("read")		bt_read(interp,argc,argv);/*		     */
      OnCommand("record")	bt_record(interp,argc,argv);/*		     */
      OnCommand("remove")	bt_remove(interp,argc,argv);/*		     */
      OnCommand("remove_string") bt_str_remove(interp,argc,argv);/*	     */
      OnCommand("rsc")		bt_rsc(interp,argc,argv,2);/*		     */
      OnCommand("resource")	bt_rsc(interp,argc,argv,2);/*		     */
      break;					   /*			     */
    case 's':					   /*			     */
      OnCommand("set")		bt_set(interp,argc,argv,-1);/*		     */
      OnCommand("sort")		bt_sort(interp,argc,argv);/*		     */
      ResourceCommand("sort.format");		   /*			     */
      OnCommand("sprint")	bt_sput(interp,argc,argv);/*		     */
      OnCommand("strings")	bt_strings(interp,argc,argv);/*		     */
      OnCommand("set_string")	bt_str_set(interp,argc,argv);/*		     */
      OnCommand("string_get")	bt_str_get(interp,argc,argv);/*		     */
      OnCommand("string_missing") bt_str_missing(interp,argc,argv);/*	     */
      OnCommand("string_set")	bt_str_set(interp,argc,argv);/*		     */
      OnCommand("string_remove") bt_str_remove(interp,argc,argv);/*	     */
      break;					   /*			     */
    case 't':					   /*			     */
      OnCommand("tex")		bt_tex(interp,argc,argv);/*		     */
      OnCommand("types")	bt_types(interp,argc,argv);/*		     */
      break;					   /*			     */
    case 'u':					   /*			     */
      OnCommand("unmark")	bt_mark(interp,argc,argv,FALSE);/*	     */
      break;					   /*			     */
    case 'v':					   /*			     */
      OnCommand("valid")	bt_valid(interp,argc,argv);/*		     */
      if ( strcmp(argv[1],"version") == 0 )	   /*			     */
      { Tcl_SetResult(interp,bibtool_version,TCL_STATIC);/*		     */
	return TCL_OK;				   /*			     */
      }						   /*			     */
      ResourceCommand("verbose");		   /*			     */
      break;					   /*			     */
    case 'w':					   /*			     */
      OnCommand("write")	bt_write(interp,argc,argv);/*		     */
      break;					   /*			     */
    case '=':					   /*			     */
      OnCommand("==")		bt_equal(interp,argc,argv);/*		     */
      break;					   /*			     */
  }						   /*			     */
						   /*			     */
  s = argv[1];					   /*			     */
  switch(*s) {					   /*			     */
#define RSC_FIRST(C) case C:
#define RSC_NEXT(C)  break; case C:
#define RscByFct(NAME,A,B)
#define RscNumeric(NAME,A,Var,B)					\
  if (strcmp(s,NAME)==0)						\
  { sprintf(buffer,"%d",Var); Tcl_SetResult(interp,buffer,TCL_VOLATILE);\
    return TCL_OK; }
#define RscBoolean(NAME,A,Var,B)					\
  if (strcmp(s,NAME)==0)						\
  { Tcl_SetResult(interp,(Var?one:zero),TCL_STATIC); return TCL_OK; }
#define RscString(NAME,A,Var,B)						\
  if (strcmp(s,NAME)==0)						\
  { Tcl_SetResult(interp,Var,TCL_VOLATILE); return TCL_OK; }
#include <bibtool/resource.h>
  }						   /*			     */
						   /*			     */
  return bt_rsc(interp,argc,argv,1);		   /*			     */
}						   /*------------------------*/

#define MAXARGS 64

/*-----------------------------------------------------------------------------
** Function:	BibToolObjectCmd()
** Purpose:	
**		
**		
** Arguments:
**	clientData	
**	 interp	
**	 argc	
**	 argv	
** Returns:	
**___________________________________________________			     */
int BibtoolObjectCmd(clientData, interp, argc, argv)/*                       */
  ClientData clientData;			   /*                        */
  Tcl_Interp  *interp;				   /*                        */
  int	      argc;				   /*                        */
  char	      *argv[];				   /*                        */
{ static char *av[MAXARGS];			   /*                        */
  int	      i;				   /*                        */
 						   /*                        */
  if ( argc >= MAXARGS-2 ) argc = MAXARGS-2;	   /* too many args ignored  */
  av[0] = "bibtool";				   /*                        */
  av[1] = argv[1];				   /*                        */
  av[2] = argv[0];				   /*                        */
  for ( i=2; i<=argc; i++ )			   /*                        */
  { av[i+1] = argv[i]; }			   /*                        */
  av[i] = NULL;					   /*                        */
  return BibtoolCmd(clientData,interp,argc+1,av);  /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	Bibtool_Init()
** Purpose:	**		
**
** Arguments:
**	interp
** Returns:	
**___________________________________________________			     */
int Bibtool_Init (interp)			   /*                        */
  Tcl_Interp *interp;				   /*                        */
{						   /*                        */
  init_bibtool("bibtool");			   /*                        */
 						   /*                        */
  Tcl_InitHashTable(&bibtool_table,TCL_STRING_KEYS);/*                       */
  Tcl_CreateCommand(interp,			   /*                        */
		    "bibtool",			   /*                        */
		    BibtoolCmd,			   /*                        */
		    (ClientData)NULL,		   /*                        */
		    (Tcl_CmdDeleteProc *)NULL);	   /*                        */
  return TCL_OK;				   /*                        */
}						   /*------------------------*/
