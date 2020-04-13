/*** record.h *****************************************************************
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
**	This module contains functions which deal with records in databases. 
**
**
******************************************************************************/

#ifndef RecordNULL

#include <bibtool/type.h>
#include <bibtool/symbols.h>
#include <bibtool/wordlist.h>

typedef int rec_type;

/*-----------------------------------------------------------------------------
** Typedef:	Record
** Purpose:	This data type represents a record in a \BibTeX{}
**		database.  Since the record can contain an arbitrary
**		number of fields the central r\^ole is taken by the
**		dynamic array |rc_heap|. This array contains at even
**		positions the name of the field and the following odd
**		position the associated value. In normal records the
**		position 0 contains the reference key of the record.
**		
**		If a field is deleted then the name is replaced by a
**		|NULL|. The structure member |rc_free| contains the
**		size of the heap.
**
**		The type of the record is determined by the integer
**		|rc_type|. 
**
**________________________________________________   			     */
typedef struct rECORD				/*                           */
{ Symbol	rc_key;				/* The sort key.             */
  Symbol	rc_old_key;			/* The old sort key.         */
  rec_type	rc_type;			/* The type of the record.   */
  int		rc_flags;			/* Some bits; e.g. used      */
 						/*  during selecting aux     */
 						/*  records.                 */
  int		rc_free;			/* The size of the heap. This*/
 						/*  is purely internal and   */
 						/*  must not be modified.    */
  Symbol	*rc_heap;			/* The heap.                 */
  Symbol	rc_comment;			/* The comment following     */
 						/*  the given record.        */
  Symbol	rc_source;			/* The source of the record. */
 						/*  I.e. the file name it    */
 						/*  has been read from.      */
  int           rc_lineno;			/* Line number or -1.        */
  struct rECORD *rc_next;			/* Pointer to the next       */
 						/*  record.                  */
  struct rECORD *rc_prev;			/* Pointer to the previous   */
 						/*  record.                  */
} SRecord, *Record;				/*                           */

/*-----------------------------------------------------------------------------
** Constant:	RecordNULL
** Type:	Record
** Purpose:	Symbolic constant for the NULL pointer of type
**		|Record|. This is used as special (invalid) record.
**___________________________________________________			     */
#define RecordNULL		(Record)0

/*-----------------------------------------------------------------------------
** Macro:	RecordType()
** Type:	rec_type
** Purpose:	Functional representation of the record
**		token. This can be used to access the token component
**		of a record. It can also be used as lvalue.
**		
** Arguments:
**	R	Record to consider.
** Returns:	The pure token.
**___________________________________________________			     */
#define RecordType(R)		((R)->rc_type)

/*-----------------------------------------------------------------------------
** Macro:	RecordFlags()
** Type:	int
** Purpose:	Functional representation of the record type.  This
**		can be used to access the token component of a
**		record. It can also be used as lvalue. 
** Arguments:
**	R	Record to consider.
** Returns:	The flags as integer.
**___________________________________________________			     */
#define RecordFlags(R)		((R)->rc_flags)

#define RecordIs(R,F)		(RecordFlags(R)&(F))
#define RecordHas(R,F)		(RecordFlags(R)&(F))
#define RecordSet(R,F)		(RecordFlags(R) |= (F))
#define RecordClear(R,F)	(RecordFlags(R) &= ~(F))

/*-----------------------------------------------------------------------------
** Constant:	RecordFlagMARKED
** Type:	int
** Purpose:	Bit mask for the |MARKED| flag of a record.  The mark
**		is used temporarily to determine certain records;
**		e.g. during gc.
**
**		This macro is usually not used directly but implicitly
**		with other macros from this header file. 
**___________________________________________________			     */
#define RecordFlagMARKED	0x01

/*-----------------------------------------------------------------------------
** Constant:	RecordFlagXREF
** Type:	int
** Purpose:	Bit mask for the |XREF| flag of a record. This flag is
**		maintained to indicate that the record contains an
**		|crossref| field. This is done for efficiency reasons
**		only. 
**
**		This macro is usually not used directly but implicitly
**		with other macros from this header file. 
**___________________________________________________			     */
#define RecordFlagXREF		0x02

/*-----------------------------------------------------------------------------
** Constant:	RecordFlagDELETED
** Type:	int
** Purpose:	Bit mask for the |DELETED| flag of a record.  This
**		flag indicates that the record has been deleted.  To
**		avoid dangling pointers the deleted records are not
**		removed from the database immediately but a call to
**		|record_gc()| performs this cleanup. In the meantime
**		the deleted records are just left in the chain. Many
**		operations automatically ignore deleted records.
**
**		This macro is usually not used directly but implicitly
**		with other macros from this header file. 
**___________________________________________________			     */
#define RecordFlagDELETED	0x04

/*-----------------------------------------------------------------------------
** Macro:	SetRecordXREF()
** Type:	int
** Purpose:	Mark the record with the |XREF| flag. If it is marked
**		already nothing is done.
**
**		The |XREF| flag is used to mark those records which
**		contain a |crossref| field. This is done for
**		efficiency only.
** Arguments:
**	R	The record to consider.
** Returns:	The new value of the record flags.
**___________________________________________________			     */
#define SetRecordXREF(R)	(RecordFlags(R) |= RecordFlagXREF)

/*-----------------------------------------------------------------------------
** Macro:	ClearRecordXREF()
** Type:	int
** Purpose:	Remove the XREF mark.
** Arguments:
**	R	The record to consider.
** Returns:	The new value of the record flags.
**___________________________________________________			     */
#define ClearRecordXREF(R)	(RecordFlags(R) &= ~RecordFlagXREF)

/*-----------------------------------------------------------------------------
** Macro:	RecordIsXREF()
** Type:	int
** Purpose:	Check whether the |XREF| flag of a record is set.
** Arguments:
**	R	Record to consider.
** Returns:	|FALSE| iff the |XREF| flag is not set.
**___________________________________________________			     */
#define RecordIsXREF(R)		(RecordFlags(R) & RecordFlagXREF)

/*-----------------------------------------------------------------------------
** Macro:	SetRecordDELETED()
** Type:	int
** Purpose:	Mark the record with the |DELETED| flag. If it is marked
**		already nothing is done.
**
**		The |DELETED| flag is used to mark those records which
**		should be treated as non existent. Deleted records are
**		ignored for most operations.
** Arguments:
**	R	Record to consider.
** Returns:	The new value of the record flags.
**___________________________________________________			     */
#define SetRecordDELETED(R)	(RecordFlags(R) |= RecordFlagDELETED)

/*-----------------------------------------------------------------------------
** Macro:	ClearRecordDELETED()
** Type:	int
** Purpose:	Remove the deleted flag. Thus you can effictively
**		undelete a record as long as its memory has not been
**		released. 
** Arguments:
**	R	Record to consider.
** Returns:	The new value of the record flags.
**___________________________________________________			     */
#define ClearRecordDELETED(R)	(RecordFlags(R) &= ~RecordFlagDELETED)

/*-----------------------------------------------------------------------------
** Macro:	RecordIsDELETED()
** Type:	int
** Purpose:	Check whether the record is marked as deleted.
** Arguments:
**	R	Record to consider.
** Returns:	|FALSE| iff the |DELETED| flag is not set.
**___________________________________________________			     */
#define RecordIsDELETED(R)	(RecordFlags(R) & RecordFlagDELETED)

/*-----------------------------------------------------------------------------
** Macro:	SetRecordMARK()
** Type:	int
** Purpose:	Mark the record. The mark is used temporarily. Do not
**		assume that the mark is preserved in each function.
** Arguments:
**	R	Record to consider.
** Returns:	The new value of the record flags.
**___________________________________________________			     */
#define SetRecordMARK(R)	(RecordFlags(R) |= RecordFlagMARKED)

/*-----------------------------------------------------------------------------
** Macro:	ClearRecordMARK()
** Type:	int
** Purpose:	Remove the deleted flag. Thus you can effictively
**		undelete a record as long as its memory has not been
**		released. 
** Arguments:
**	R	Record to consider.
** Returns:	The new value of the record flags.
**___________________________________________________			     */
#define ClearRecordMARK(R)	(RecordFlags(R) &= ~RecordFlagMARKED)

/*-----------------------------------------------------------------------------
** Macro:	RecordIsMARKED()
** Type:	int
** Purpose:	Check whether the record is marked as deleted.
** Arguments:
**	R	Record to consider.
** Returns:	|FALSE| iff the |DELETED| flag is not set.
**___________________________________________________			     */
#define RecordIsMARKED(R)	(RecordFlags(R) & RecordFlagMARKED)

/*-----------------------------------------------------------------------------
** Macro:	RecordKey()
** Type:	String 
** Purpose:	
**		
**		
** Arguments:
**	R	Record to consider
**___________________________________________________			     */
#define RecordKey(R)		(*((R)->rc_heap))

/*-----------------------------------------------------------------------------
** Macro:	RecordOldKey()
** Type:	String 
** Purpose:	
**		
**		
** Arguments:
**	R	Record to consider
**___________________________________________________			     */
#define RecordOldKey(R)		((R)->rc_old_key)

/*-----------------------------------------------------------------------------
** Macro:	RecordSortkey()
** Type:	String 
** Purpose:	This is the functional representation of the sort key
**		of a record. This can be used to access the key component
**		of a record. It can also be used as lvalue.
**		
**		Note that the reference key of a normal record is
**		stored in the heap at position 0.
** Arguments:
**	R	Record to consider.
**___________________________________________________			     */
#define RecordSortkey(R)	((R)->rc_key)

/*-----------------------------------------------------------------------------
** Macro*:	RecordFree()
** Type:	int
** Purpose:	This is the functional representation of the first
**		free position on the heap.
** Arguments:
**	R	Record to consider
**___________________________________________________			     */
#define RecordFree(R)		((R)->rc_free)

/*-----------------------------------------------------------------------------
** Macro:	RecordHeap()
** Type:	String *
** Purpose:	The heap of a record is a array of strings. The even
**		positions contain the names of fields and the
**		following array cell contains its value. If the name
**		or value is |NULL| then this slot is not used. Thus it
**		is easy to delete a field. Simply write a |NULL| into
**		the appropriate place.
** Arguments:
**	R	Record to consider.
**___________________________________________________			     */
#define RecordHeap(R)		((R)->rc_heap)

/*-----------------------------------------------------------------------------
** Macro:	NextRecord()
** Type:	Record
** Purpose:	This is the functional representation of the next
**		record of a record. It can be used to get this value
**		as well as an lvalue to set it.
** Arguments:
**	R	Record to consider
**___________________________________________________			     */
#define NextRecord(R)		((R)->rc_next)

/*-----------------------------------------------------------------------------
** Macro:	PrevRecord()
** Type:	Record
** Purpose:	This is the functional representation of the previous
**		record of a record. It can be used to get this value
**		as well as an lvalue to set it.
** Arguments:
**	R	Record to consider
**___________________________________________________			     */
#define PrevRecord(R)		((R)->rc_prev)

/*-----------------------------------------------------------------------------
** Macro:	RecordComment()
** Type:	String 
** Purpose:	This is the functional representation of the comment
**		component of a record. It can be used to get this value
**		as well as an lvalue to set it.
** Arguments:
**	R	Record to consider
**___________________________________________________			     */
#define RecordComment(R)	((R)->rc_comment)

/*-----------------------------------------------------------------------------
** Macro:	RecordSource()
** Type:	String 
** Purpose:	This is the functional representation of the source
**		indicator of a record. It is a string containing the
**		file name from which this record has been read. The
**		empty string is used to denote unknown sources.
** Arguments:
**	R	Record to consider
** Returns:	
**___________________________________________________			     */
#define RecordSource(R)	((R)->rc_source)

/*-----------------------------------------------------------------------------
** Macro:	RecordLineno()
** Type:	int
** Purpose:	This is the line number where the record has been read from.
**              The value -1 is used for an unknown line number.
** Arguments:
**	R	Record to consider
** Returns:	
**___________________________________________________			     */
#define RecordLineno(R)	((R)->rc_lineno)

/*-----------------------------------------------------------------------------
** Macro:	RecordFlags()
** Type:	int
** Purpose:	This is the functional representation of the record
**		flags. They are extra bits used for arbitrary
**		purposes. Right now only the bit with the mask 1  is
**		used for selecting the records found in an aux file.
** Arguments:
**	R	Record to consider
** Returns:	
**___________________________________________________			     */
#define RecordFlags(R)	((R)->rc_flags)


#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Record copy_record _ARG((Record rec));		   /* record.c               */
 Record new_record _ARG((int token,int size));	   /* record.c               */
 Record record_gc _ARG((Record rec));		   /* record.c               */
 Record unlink_record _ARG((Record rec));	   /* record.c               */
 Symbol record_get _ARG((Record rec, Symbol key)); /* record.c               */
 WordList new_wordlist _ARG((Symbol s));	   /* record.c               */
 int count_record _ARG((Record rec));		   /* record.c               */
 void add_sort_order _ARG((Symbol val));	   /* record.c               */
 void free_1_record _ARG((Record rec));		   /* record.c               */
 void free_record _ARG((Record rec));		   /* record.c               */
 void provide_to_record _ARG((Record rec,Symbol s, Symbol t));/*             */
 void push_to_record _ARG((Record rec,Symbol s, Symbol t, bool err));/* record.c*/
 void sort_record _ARG((Record rec));		   /* record.c               */

#endif
