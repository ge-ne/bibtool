/*** database.h ***************************************************************
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
**	This header file contains functions which deal with databases. 
**
**	This header file provides also access to the functions and
**	variables defined in |database.c|. Consult the documentation
**	of this file for details.
**
**	This header file automatically includes |<stdio.h>| and
**	|record.h| aswell.
**
******************************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <bibtool/record.h>

/*-----------------------------------------------------------------------------
** Typedef:	DB
** Purpose:	This is a pointer type referencing a \BibTeX{}
**		database.  It contains all information which
**		characterizes a database.
**		
**		The members of this record should not be used
**		explicitly.  Instead the macros should be used which
**		are provided to accss this data type.
**
**___________________________________________________			     */
 typedef struct					   /*                        */
 { Record db_normal;				   /* List of normal records.*/
   Record db_string;				   /* List of local macros.  */
   Record db_preamble;				   /* List of additional     */
 						   /*  \TeX{} code.          */
   Record db_comment;				   /* List of trailing       */
   						   /*  comments which are    */
 						   /*  not attached to	     */
 						   /*  records.              */
   Record db_modify;				   /* List of modification   */
						   /*  rules.                */
   Record db_include;				   /* List of included files.*/
   Record db_alias;				   /* List of aliases.       */
 } sDB, *DB;					   /*                        */

/*-----------------------------------------------------------------------------
** Constant:	NoDB()
** Type:	DB
** Purpose:	This is an invalid database. In fact it is |NULL| of
**		the type |DB|.
**___________________________________________________			     */
#define NoDB	      ((DB)0)

/*-----------------------------------------------------------------------------
** Macro:	DBnormal()
** Type:	Record
** Purpose:	This is the functional representation of the normal
**		component of a database. It can be used to extract
**		this information. It can also be used as a lvalue.
** Arguments:
**	DB	The database to consider.
**___________________________________________________			     */
#define DBnormal(DB)   ((DB)->db_normal)

/*-----------------------------------------------------------------------------
** Macro:	DBstring()
** Type:	Record
** Purpose:	This is the functional representation of the string
**		component of a database. It can be used to extract
**		this information. It can also be used as a lvalue.
** Arguments:
**	DB	The database to consider.
**___________________________________________________			     */
#define DBstring(DB)   ((DB)->db_string)

/*-----------------------------------------------------------------------------
** Macro:	DBpreamble()
** Type:	Record
** Purpose:	This is the functional representation of the preamble
**		component of a database. It can be used to extract
**		this information. It can also be used as a lvalue.
** Arguments:
**	DB	The database to consider.
**___________________________________________________			     */
#define DBpreamble(DB) ((DB)->db_preamble)

/*-----------------------------------------------------------------------------
** Macro:	DBcomment()
** Type:	Record
** Purpose:	This is the functional representation of the comment
**		component of a database. It can be used to extract
**		this information. It can also be used as a lvalue.
** Arguments:
**	DB	The database to consider.
**___________________________________________________			     */
#define DBcomment(DB)  ((DB)->db_comment)

/*-----------------------------------------------------------------------------
** Macro:	DBalias()
** Type:	Record
** Purpose:	This is the functional representation of the alias
**		component of a database. It can be used to extract
**		this information. It can also be used as a lvalue.
** Arguments:
**	DB	The database to consider.
**___________________________________________________			     */
#define DBalias(DB)    ((DB)->db_alias)

/*-----------------------------------------------------------------------------
** Macro:	DBmodify()
** Type:	Record
** Purpose:	This is the functional representation of the modify
**		component of a database. It can be used to extract
**		this information. It can also be used as a lvalue.
** Arguments:
**	DB	The database to consider.
**___________________________________________________			     */
#define DBmodify(DB)   ((DB)->db_modify)

/*-----------------------------------------------------------------------------
** Macro:	DBinclude()
** Type:	Record
** Purpose:	This is the functional representation of the include
**		component of a database. It can be used to extract
**		this information. It can also be used as a lvalue.
** Arguments:
**	DB	The database to consider.
**___________________________________________________			     */
#define DBinclude(DB)  ((DB)->db_include)

/*---------------------------------------------------------------------------*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 DB new_db _ARG((void));			   /*                        */
 Record db_find _ARG((DB db, Symbol key));	   /*                        */
 Record db_search _ARG((DB db, Symbol key));	   /*                        */
 Symbol db_new_key _ARG((DB db, Symbol key));	   /*                        */
 Symbol db_string _ARG((DB db, Symbol sym, bool localp));/*                  */
 bool read_db _ARG((DB db,String file, bool verbose));/*                     */
 int *db_count _ARG((DB db, int *lp));		   /*                        */
 void db_insert _ARG((DB db,Record rec, bool verbose));/*                    */
 void db_forall _ARG((DB db,bool (*fct)_ARG((DB, Record))));/*               */
 void db_mac_sort _ARG((DB db));		   /*                        */
 void db_rewind _ARG((DB db));			   /*                        */
 void db_sort _ARG((DB db,int (*less)_ARG((Record, Record))));/*             */
 void db_xref_undelete _ARG((DB db));		   /*                        */
 void delete_record _ARG((DB db, Record rec));	   /*                        */
 void free_db _ARG((DB db));			   /*                        */
 void print_db _ARG((FILE *file, DB db, char *spec));/*                      */

/*---------------------------------------------------------------------------*/

#endif
