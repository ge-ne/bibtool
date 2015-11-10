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
#include "eval_term.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

 extern Term eval_command();

/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
** Function:    main()
** Purpose:     Main routine
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
    { in = run_tests(i < argc-1 ? argv[++i] : NULL);/*                       */
    } else					   /*                        */
    { Term t = eval_command(argv[i]);		   /*                        */
      dump_term(t);				   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	fail()
** Type:	int
** Purpose:	
**		
** Arguments:
**	id	
**	 msg	
** Returns:	
**___________________________________________________			     */
int fail(id, msg)				   /*                        */
  char * id;					   /*                        */
  char * msg;					   /*                        */
{						   /*                        */
  fprintf(stderr,"--- %s: %s\n", id, msg);	   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	expect()
** Type:	int
** Purpose:	
**		
** Arguments:
**	id	
**	 in	
**	 out	
** Returns:	
**___________________________________________________			     */
int expect(id, in, out)				   /*                        */
  char *id;					   /*                        */
  char *in;					   /*                        */
  char *out;					   /*                        */
{						   /*                        */
#define TEST_FILE ".test"
  int size;
  char * s;
  FILE * is = fopen(TEST_FILE, "w");
  if (is == NULL) return fail(id, "Opening .test failed");
  fputs(in, is);
  fclose(is);

  Term t = eval_command(TEST_FILE);
  if (t == TermNULL) return fail(id, "Parsing failed");
  FILE * os = fopen(".test-out", "w");
  if (os == NULL) return fail(id, "Opening .test-out failed");
  dump_term(os, t);
  fclose(os);

  FILE * fp = fopen(".test-out","r");
  if (fp == NULL) return fail(id, "Opening .test-out for reading failed");
  fseek(fp, 0L, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  s = malloc(size);
  fclose(fp);

}

void select_1()
{ expect("select_1", "verbose = on\n", "");
}

/*-----------------------------------------------------------------------------
** Function:	run_tests()
** Type:	int
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
int run_tests(s)				   /*                        */
  char * s;
{						   /*                        */
#define TEST(CASE, FCT)  if (s == NULL || strcmp(s, CASE) == 0) FCT

  TEST("select_1", select_1());
  return 0;
}						   /*------------------------*/

void save_input_file(file)
  char *file;
{}
void save_macro_file(file)
  char *file;
{}
void save_output_file(file)
  char * file;
{}


