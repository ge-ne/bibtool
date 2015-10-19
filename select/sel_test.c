/******************************************************************************
** $Id: sel_test.c,v 0.00 2015/10/17 20:57:50 gene Exp $
*******************************************************************************
** Author: Gerd Neugebauer
**===========================================================================*/

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
    { in = run_file(argv[i]);
    }
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

int run_file(fname)
  char * fname;
{ int c;					   /*                        */
  StringBuffer *sb = sbopen();		   	   /*                        */
  FILE * fd = fopen(fname, "r");		   /*                        */
  while ((c=fgetc(fd)) != EOF) {		   /*                        */
    sbputc(c, sb);				   /*                        */
  }						   /*                        */
  fclose(fd);					   /*                        */
  Term t = selection(sbflush(sb));		   /*                        */
  
  if (t) dump_term(t);  			   /*                        */
  return 0;
}						   /*------------------------*/

int run_tests()
{
  return 0;
}						   /*------------------------*/
