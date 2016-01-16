/*** record.c *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/error.h>
#include <bibtool/record.h>
#include <bibtool/symbols.h>

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Record copy_record _ARG((Record rec));
 Record new_record _ARG((int token,int size));
 Record record_gc _ARG((Record rec));
 Record unlink_record _ARG((Record rec));
 WordList new_wordlist _ARG((String  s));
 void add_sort_order _ARG((String val));
 void free_1_record _ARG((Record rec));
 void free_record _ARG((Record rec));
 void provide_to_record _ARG((Record rec,String s,String t));
 void push_to_record _ARG((Record rec,String s,String t));
 void sort_record _ARG((Record rec));

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Function:	copy_record()
** Purpose:	Copy a record and return a new instance.
**		If no memory is left then an error is raised and the
**		program is terminated. 
** Arguments:
**	rec	The record to copy.
** Returns:	The new copy of |rec|.
**___________________________________________________			     */
Record copy_record(rec)				   /*			     */
  register Record rec;				   /*			     */
{ register Record new;				   /*			     */
  register String *new_heap,			   /*			     */
		  *old_heap;			   /*			     */
  register int	  i;				   /*			     */
						   /*			     */
  if (	(new=(Record)malloc(sizeof(SRecord))) == 0L/*			     */
     || (new_heap=(String*)malloc(sizeof(String)*(size_t)RecordFree(rec)))/* */
	== 0L )					   /*			     */
  { OUT_OF_MEMORY("Record"); }      		   /*                        */
  RecordSortkey(new)	  = sym_empty;		   /*			     */
  RecordOldKey(new)	  = RecordOldKey(rec);	   /*			     */
  NextRecord(new)	  = RecordNULL;		   /*			     */
  PrevRecord(new)	  = RecordNULL;		   /*			     */
  RecordType(new)	  = RecordType(rec);	   /*			     */
  RecordFree(new)	  = RecordFree(rec);	   /*			     */
  RecordComment(new)	  = RecordComment(rec);	   /*			     */
  RecordSource(new)	  = RecordSource(rec);	   /*			     */
  RecordHeap(new)	  = new_heap;		   /*			     */
  RecordFlags(new)	  = RecordFlags(rec);	   /*			     */
  for (i = 0, old_heap = RecordHeap(rec);	   /*			     */
	i < RecordFree(new);			   /*			     */
	++i)					   /*			     */
  { *(new_heap++) = *(old_heap++); }		   /*			     */
  return (new);					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_record()
** Purpose:	Create a new record and return it.
**		If no memory is left then an error is raised and the
**		program is terminated. 
** Arguments:
**	token	The token type of the record.
**	size	The initial heap size.
** Returns:	The new record.
**___________________________________________________			     */
Record new_record(token,size)			   /*			     */
  int		  token;			   /*			     */
  int		  size;				   /*                        */
{ register Record new;				   /*			     */
  register String *new_heap;			   /*			     */
  register int	  i;				   /*			     */
						   /*			     */
  if ( size < 1 ) size = 1;			   /*                        */
  if (	(new=(Record)malloc(sizeof(SRecord))) == 0L/*			     */
     || (new_heap=(String*)malloc(sizeof(String)*(size_t)(size)))/*          */
	== 0L )					   /*			     */
  { OUT_OF_MEMORY("Record"); }      		   /*                        */
  RecordSortkey(new)	= sym_empty;		   /*			     */
  RecordOldKey(new)	= RecordSortkey(new);	   /*			     */
  NextRecord(new)	= RecordNULL;		   /*			     */
  PrevRecord(new)	= RecordNULL;		   /*			     */
  RecordType(new)	= token;		   /*			     */
  RecordFree(new)	= size;			   /*			     */
  RecordComment(new)	= sym_empty;		   /*			     */
  RecordSource(new)	= sym_empty;		   /*			     */
  RecordFlags(new)	= 0;	   		   /*			     */
  RecordHeap(new)	= new_heap;		   /*			     */
  for (i = 0; i < RecordFree(new); ++i)		   /*			     */
  { *(new_heap++) = StringNULL; }	   	   /*			     */
  return (new);					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_record()
** Purpose:	Release a list of records. All records reachable through a
**		previous/next chain are deallocated.
** Arguments:
**	rec	Arbitrary Record in the chain.
** Returns:	nothing
**___________________________________________________			     */
void free_record(rec)				   /*                        */
  Record rec;					   /*                        */
{ Record r;					   /*                        */
 						   /*                        */
  if ( rec == RecordNULL ) return;		   /*                        */
 						   /*                        */
  while ( PrevRecord(rec) != RecordNULL )	   /* rewind                 */
  { rec = PrevRecord(rec); }			   /*                        */
 						   /*                        */
  while ( rec != RecordNULL )			   /*                        */
  { r = rec;					   /*                        */
    rec = NextRecord(rec);			   /*                        */
    free_1_record(r);				   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_1_record()
** Purpose:	Free the memory occupied by a single record.
**		This does not ensure that there is no dangling pointer to
**		the record. Thus beware!
** Arguments:
**	rec	record to free
** Returns:	nothing
**___________________________________________________			     */
void free_1_record(rec)				   /*                        */
  Record rec;					   /*                        */
{ int i;					   /*                        */
 						   /*                        */
  if ( rec != RecordNULL )			   /*                        */
  {						   /*                        */
    ReleaseSymbol(RecordSortkey(rec));		   /*                        */
    ReleaseSymbol(RecordOldKey(rec));		   /*                        */
    ReleaseSymbol(RecordComment(rec));		   /*                        */
    ReleaseSymbol(RecordSource(rec));		   /*                        */
    if ( RecordHeap(rec) != NULL )		   /*                        */
    {						   /*                        */
      for (i = 0; i < RecordFree(rec); i++ )	   /*                        */
      { ReleaseSymbol(RecordHeap(rec)[i]); }	   /*                        */
      free(RecordHeap(rec));			   /*                        */
    }						   /*                        */
    free(rec);					   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	unlink_record()
** Purpose:	Remove a record from a chain and free its memory. The
**		chain is modified such that the freed Record is not
**		referenced any more. A neighbor in the chain of the
**		given record is returned or |NULL| if there is none.
** Arguments:
**	rec	Record to free.
** Returns:	nothing
**___________________________________________________			     */
Record unlink_record(rec)			   /*                        */
  Record rec;					   /*                        */
{ Record r;					   /*                        */
 						   /*                        */
  if ( NextRecord(rec) )			   /*                        */
  { PrevRecord(NextRecord(rec)) = PrevRecord(rec); /*                        */
    if (PrevRecord(rec))			   /*                        */
    { NextRecord(PrevRecord(rec)) = NextRecord(rec);/*                       */
    }						   /*                        */
    r = NextRecord(rec);			   /*                        */
  }						   /*                        */
  else if (PrevRecord(rec))			   /*                        */
  { NextRecord(PrevRecord(rec)) = NextRecord(rec); /*                        */
    r = PrevRecord(rec);			   /*                        */
  }						   /*                        */
  else						   /*                        */
  { r = RecordNULL;				   /*                        */
  }						   /*                        */
  free_1_record(rec);				   /*                        */
  return r;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	record_gc()
** Purpose:	Garbage collecting a record list. The entries marked
**		as deleted are unlinked and the memory is freed. Any
**		pointer to such a deleted entry becomes invalid.
**		
**		Be careful when using this function!
** Arguments:
**	rec	Pointer to any entry in the chain.
** Returns:	Pointer to some entry in the cleared chain or
**		|RecordNULL| if none is left.
**___________________________________________________			     */
Record record_gc(rec)				   /*                        */
  Record rec;					   /*                        */
{ Record ret = RecordNULL;			   /*                        */
 						   /*                        */
  if ( rec == RecordNULL ) return rec;		   /*                        */
 						   /*                        */
  while ( PrevRecord(rec) != RecordNULL )	   /* Rewind                 */
  { rec = PrevRecord(rec); }			   /*                        */
  						   /*                        */
  while ( rec != RecordNULL )			   /*                        */
  {						   /*                        */
    if ( RecordIsDELETED(rec) )			   /*                        */
    { rec = unlink_record(rec);			   /*                        */
    }						   /*                        */
    else					   /*                        */
    { ret = rec;				   /*                        */
      rec = NextRecord(rec);			   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  return ret;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	push_to_record()
** Purpose:	Put an equation s=t onto the heap of a record.
**		If a field s is already there then the value is
**		overwritten.  The arguments are expected to be
**		symbols. Thus it is not necessary to make private
**		copies and it is possible to avoid expensive string
**		comparisons. 
** Arguments:
**	s	Left hand side of the equation.
**	t	Right hand side of the equation.
** Returns:	nothing
**___________________________________________________			     */
void push_to_record(rec,s,t)			   /*			     */
  register Record rec;				   /*                        */
  register String s;				   /*			     */
  register String t;				   /*			     */
{ register int i;		   		   /*			     */
   						   /*                        */
  if ( s == sym_crossref ) { SetRecordXREF(rec); } /*			     */
 						   /*                        */
  for (i = 2; i < RecordFree(rec); i += 2 )	   /* search the field       */
  { if ( RecordHeap(rec)[i] == s )		   /* if found then          */
    { RecordHeap(rec)[i+1] = t;			   /* overwrite the value    */
      return;					   /*                        */
    }   					   /*                        */
  }						   /*                        */
  for (i = 2; i < RecordFree(rec); i += 2 )	   /* search empty field     */
  { if ( RecordHeap(rec)[i] == StringNULL )	   /* if found then          */
    { RecordHeap(rec)[i++] = s;			   /* add the new item       */
      RecordHeap(rec)[i]   = t;			   /*                        */
      return;					   /*                        */
    }   					   /*                        */
  }						   /*                        */
  i = RecordFree(rec);				   /*                        */
  RecordFree(rec) += 2;				   /*                        */
  if ( (RecordHeap(rec)   			   /* enlarge the heap	     */
	=(String*)realloc(RecordHeap(rec),	   /*	                     */
			 RecordFree(rec)*sizeof(String)))/*                  */
     == (String*)NULL )			   	   /*	                     */
  { OUT_OF_MEMORY("heap"); }      		   /*                        */
						   /*			     */
  RecordHeap(rec)[i++] = s;		   	   /*			     */
  RecordHeap(rec)[i]   = t;		   	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	provide_to_record()
** Purpose:	Put an equation s=t onto the heap of a record if the key s
**              is not defined already.
**		If a field s is already there then the value is
**		ignored.  The arguments are expected to be
**		symbols. Thus it is not necessary to make private
**		copies and it is possible to avoid expensive string
**		comparisons. 
** Arguments:
**	s	Left hand side of the equation.
**	t	Right hand side of the equation.
** Returns:	nothing
**___________________________________________________			     */
void provide_to_record(rec,s,t)			   /*			     */
  register Record rec;				   /*                        */
  register String s;				   /*			     */
  register String t;				   /*			     */
{ register int i;		   		   /*			     */
   						   /*                        */
  if ( s == sym_crossref ) { SetRecordXREF(rec); } /*			     */
 						   /*                        */
  for (i = 2; i < RecordFree(rec); i += 2 )	   /* search the field       */
  { if ( RecordHeap(rec)[i] == s )		   /* if found then          */
    { return;					   /*  done                  */
    }   					   /*                        */
  }						   /*                        */
  for (i = 2; i < RecordFree(rec); i += 2 )	   /* search empty field     */
  { if ( RecordHeap(rec)[i] == StringNULL )	   /* if found then          */
    { RecordHeap(rec)[i++] = s;			   /* add the new item       */
      RecordHeap(rec)[i]   = t;			   /*                        */
      return;					   /*                        */
    }   					   /*                        */
  }						   /*                        */
  i = RecordFree(rec);				   /*                        */
  RecordFree(rec) += 2;				   /*                        */
  if ( (RecordHeap(rec)   			   /* enlarge the heap	     */
	=(String*)realloc(RecordHeap(rec),	   /*	                     */
			 RecordFree(rec)*sizeof(String)))/*                  */
     == (String*)NULL )			   	   /*	                     */
  { OUT_OF_MEMORY("heap"); }      		   /*                        */
						   /*			     */
  RecordHeap(rec)[i++] = s;		   	   /*			     */
  RecordHeap(rec)[i]   = t;		   	   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***			                         			   ***/
/*****************************************************************************/

#include <bibtool/wordlist.h>
#include <bibtool/s_parse.h>
#include <bibtool/entry.h>
 

/*-----------------------------------------------------------------------------
** Function:	new_wordlist()
** Purpose:	Allocate a WordList and fill its slots.
** Arguments:
**	s	Initial string to fill in the WordList structure
** Returns:	
**___________________________________________________			     */
WordList new_wordlist(s)			   /*                        */
  String  s;				   	   /*                        */
{ register WordList wl;				   /*                        */
  if ( (wl=(WordList)malloc(sizeof(SWordList))) == WordNULL )/*              */
  { OUT_OF_MEMORY("WordList"); }		   /*                        */
  ThisWord(wl) = s;				   /*                        */
  NextWord(wl) = WordNULL;			   /*                        */
  return wl;					   /*                        */
}						   /*------------------------*/

 typedef struct oRDERLIST			   /*                        */
 { int		    ol_type;			   /*                        */
   WordList	    ol_val;			   /*                        */
   struct oRDERLIST *ol_next;			   /*                        */
 } SOrderList, *OrderList;			   /*                        */

#define OrderType(OL) ((OL)->ol_type)
#define OrderVal(OL)  ((OL)->ol_val)
#define NextOrder(OL) ((OL)->ol_next)
#define OrderNULL     ((OrderList)0)

 static OrderList order = OrderNULL;		   /*                        */

/*-----------------------------------------------------------------------------
** Function:	add_sort_order()
** Purpose:	Insert the sort order into the order list.
**		
**
** Arguments:
**	val	string resource of the order.
** Returns:	nothing
**___________________________________________________			     */
void add_sort_order(val)			   /*                        */
  String    val;				   /*                        */
{ String    s;					   /*                        */
  int       type;				   /*                        */
  OrderList ol;					   /*                        */
  WordList  *wlp = NULL;			   /*                        */
  WordList  wl, wl_next;			   /*                        */
 						   /*                        */
  (void)SParseSkip(&val);			   /*                        */
  if ( *val == '*' )				   /*                        */
  { s    = StringNULL;			   	   /*                        */
    type = BIB_NOOP;				   /*                        */
    val++;					   /*                        */
  }						   /*                        */
  else if ( (s=SParseSymbol(&val)) == StringNULL ) /*                        */
  { return; }					   /*                        */
  else if ( (type=find_entry_type(s)) == BIB_NOOP )/*                        */
  { Err("Undefined entry type for sort order");	   /*                        */
    return;					   /*                        */
  }						   /*                        */
 						   /*                        */
  for (ol = order;				   /*                        */
       ol != OrderNULL && OrderType(ol) != type;   /*                        */
       ol = NextOrder(ol)) {}			   /*                        */
 						   /*                        */
  if ( ol )					   /*                        */
  { wlp = &OrderVal(ol);			   /*                        */
  } 						   /*                        */
  else if ( (ol=(OrderList)malloc(sizeof(SOrderList))) == OrderNULL )/*      */
  { OUT_OF_MEMORY("OrderList"); }		   /*                        */
  else						   /*                        */
  { OrderType(ol) = type;			   /*                        */
    OrderVal(ol)  = WordNULL;			   /*                        */
    NextOrder(ol) = order;			   /*                        */
    order         = ol;				   /*                        */
    wlp           = &OrderVal(ol);		   /*                        */
  }						   /*                        */
   						   /*                        */
  (void)SParseSkip(&val);			   /*                        */
  						   /*                        */
  while ( *val )				   /*                        */
  { if ( (s=SParseSymbol(&val)) != NULL )	   /*                        */
    { if ( *wlp ) { ThisWord(*wlp) = s;     }	   /*                        */
      else        { *wlp = new_wordlist(s); }	   /*                        */
      wlp = &NextWord(*wlp);			   /*                        */
    }						   /*                        */
    else break;					   /*                        */
    SParseSkip(&val);				   /*                        */
  }						   /*                        */
  						   /*                        */
  wl   = *wlp;					   /*                        */
  *wlp = WordNULL;				   /*                        */
  while ( wl )					   /* Free remaining word    */
  { wl_next = NextWord(wl);			   /*  nodes at the end.     */
    free((char*)wl);				   /*                        */
    wl = wl_next;				   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	sort_record()
** Purpose:	The heap is reordered according to the sorting order
**		determined by the record type.
**		For this purpose a copy of the original record is made and the
**		original record is overwritten. The copy is released at the
**		end.
**		Memory management is easy since all strings are in fact
**		symbols, i.e. they must not be freed and comparison is done
**		by pointer comparison.
** Arguments:
**	rec     Record to sort
** Returns:	nothing
**___________________________________________________			     */
void sort_record(rec)				   /*			     */
  register Record rec;				   /*			     */
{ Record          r;				   /* Temp. record           */
  OrderList       ol;				   /*                        */
  int             i, ptr;			   /*                        */
  int             type = RecordType(rec);	   /*                        */
  WordList        wl;				   /*                        */
 						   /*                        */
  for (ol = order;				   /* Search for an order    */
       ol && OrderType(ol) != type;		   /*  for this type of      */
       ol = NextOrder(ol) ) {}			   /*  record first.         */
  if ( ol == OrderNULL )			   /* If none was found then */
  { for (ol = order;				   /* Search for an order    */
	 ol && OrderType(ol) != BIB_NOOP;	   /*  applicable for all    */
	 ol = NextOrder(ol) ) {}		   /*  record types.         */
    if ( ol == OrderNULL ) return;		   /* No order then return.  */
  }						   /*                        */
  						   /*                        */
  if ( (wl=OrderVal(ol)) == WordNULL ) return;	   /* Empty order found. Done*/
 						   /*                        */
  r   = copy_record(rec);			   /*                        */
  ptr = 2;					   /* Heap pointer for rec   */
 						   /*                        */
  while ( wl )					   /* For all words          */
  { for ( i = 2; i < RecordFree(r); i += 2 )	   /* Find the word on the   */
    { if ( RecordHeap(r)[i] == ThisWord(wl) )	   /*  heap and              */
      { RecordHeap(rec)[ptr++] = RecordHeap(r)[i]; /*  transfer it into the  */
	RecordHeap(rec)[ptr++] = RecordHeap(r)[i+1];/* original record.      */
	RecordHeap(r)[i]       = NULL;		   /* Delete the copy.       */
	i = RecordFree(r);			   /*                        */
      }						   /*                        */
    }   					   /*                        */
    wl = NextWord(wl);				   /* Look at next word.     */
  }						   /*                        */
  for ( i = 2; i < RecordFree(r); i += 2 )	   /* Transfer all remaining */
  { if ( RecordHeap(r)[i] )			   /*  elements of the heap  */
    { RecordHeap(rec)[ptr++] = RecordHeap(r)[i];   /*  which are not         */
      RecordHeap(rec)[ptr++] = RecordHeap(r)[i+1]; /*  deleted.              */
    }						   /*                        */
  }   						   /*                        */
  while ( ptr < RecordFree(r) )			   /* Clear the remaining    */
  { RecordHeap(rec)[ptr++] = NULL;		   /*  elements of the heap. */
  }						   /*                        */
 						   /*                        */
  free((char*)RecordHeap(r));			   /* Free the temp. record. */
  free((char*)r);				   /*                        */
}						   /*------------------------*/

