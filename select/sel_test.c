/*** sel_test.c ***************************************************************
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
#include <bibtool/sbuffer.h>
#include "term.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

 extern Term selection();

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Function:    main()
** Purpose:     Main rountine
** Arguments:
**	argc	Number of arguments (+1)
**	argv	Array of command line arguments (and program name)
** Returns:     
**___________________________________________________                        */
int main(argc, argv)				   /*                        */
  int  argc;					   /*                        */
  char *argv[];					   /*                        */
{ int i;					   /*                        */
  int in = 1;					   /*                        */
 						   /*                        */
  for (i = 1; i < argc; i++)			   /*                        */
  {						   /*                        */
    if (strcmp("-t", argv[i]) == 0)		   /*                        */
    { in = run_tests();				   /*                        */
    } else					   /*                        */
    { in = run_file(argv[i]);			   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  if (in)					   /*                        */
  { int c;					   /*                        */
    StringBuffer *sb = sbopen();		   /*                        */
    while ((c=getchar()) != EOF) {		   /*                        */
      sbputc(c, sb);				   /*                        */
    }						   /*                        */
    Term t = selection(sbflush(sb));		   /*                        */
    if (t) dump_term(t);  			   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	run_file()
** Type:	int
** Purpose:	
**		
** Arguments:
**	fname	
** Returns:	
**___________________________________________________			     */
int run_file(fname)				   /*                        */
  char * fname;					   /*                        */
{ int c;					   /*                        */
  StringBuffer *sb = sbopen();		   	   /*                        */
  FILE * fd = fopen(fname, "r");		   /*                        */
  while ((c=fgetc(fd)) != EOF) {		   /*                        */
    sbputc(c, sb);				   /*                        */
  }						   /*                        */
  fclose(fd);					   /*                        */
  Term t = selection(sbflush(sb));		   /*                        */
  						   /*                        */
  if (t) dump_term(t);  			   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	run_tests()
** Type:	int
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
int run_tests()					   /*                        */
{						   /*                        */
  return 0;
}						   /*------------------------*/
