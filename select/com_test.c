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

  int verbose = FALSE;			   	   /*                        */

/*-----------------------------------------------------------------------------
** Function:	usage()
** Type:	static void
** Purpose:	
**		
** Arguments:
**		
** Returns:	nothing
**___________________________________________________			     */
static void usage(char * prog) {		   /*                        */
  fprintf(stderr,				   /*                        */
	  "%s [-h|--help] [-t|--test] [-v|--verbose] [<test> ...]\n",/*      */
	  prog);				   /*                        */
}						   /*------------------------*/

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
  int in	  = 1;				   /*                        */
 						   /*                        */
  for (i = 1; i < argc; i++)			   /*                        */
  {						   /*                        */
    if (strcmp("--test", argv[i]) == 0		   /*                        */
	|| strcmp("-t", argv[i]) == 0)	   	   /*                        */
    { in = run_tests(i < argc-1 ? argv[++i] : NULL);/*                       */
    } else if (strcmp("--help", argv[i]) == 0 	   /*                        */
	      || strcmp("-h", argv[i]) == 0)	   /*                        */
    { usage(argv[0]);				   /*                        */
    } else if (strcmp("--verbose", argv[i]) == 0   /*                        */
	      || strcmp("-v", argv[i]) == 0)	   /*                        */
    { verbose = TRUE;				   /*                        */
    } else					   /*                        */
    { dump_term(stdout, eval_command(argv[i]));	   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	save_input_file()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	
** Returns:	nothing
**___________________________________________________			     */
void save_input_file(file)			   /*                        */
  char *file;					   /*                        */
{}						   /*                        */

/*-----------------------------------------------------------------------------
** Function:	save_macro_file()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	
** Returns:	nothing
**___________________________________________________			     */
void save_macro_file(file)			   /*                        */
  char *file;					   /*                        */
{}						   /*                        */

/*-----------------------------------------------------------------------------
** Function:	save_output_file()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	
** Returns:	nothing
**___________________________________________________			     */
void save_output_file(file)			   /*                        */
  char * file;					   /*                        */
{}						   /*                        */

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

#define TEST_FILE ".test"
#define TEST_OUT ".test-out"

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
{ int size;					   /*                        */
  char * s;					   /*                        */
  FILE * is = fopen(TEST_FILE, "w");		   /*                        */
  if (is == NULL) return fail(id, "Opening .test failed");/*                 */
  fputs(in, is);				   /*                        */
  fclose(is);					   /*                        */
 						   /*                        */
  Term t = eval_command(TEST_FILE);		   /*                        */
  if (t == NIL) return fail(id, "Parsing failed"); /*                        */
  FILE *os = fopen(TEST_OUT, "w");		   /*                        */
  if (os == NULL) return fail(id, "Opening .test-out failed");/*             */
  fclose(os);					   /*                        */
 						   /*                        */
  FILE * fp = fopen(TEST_OUT, "r");		   /*                        */
  if (fp == NULL) return fail(id, "Opening .test-out for reading failed");/* */
  fseek(fp, 0L, SEEK_END);			   /*                        */
  size = ftell(fp);				   /*                        */
  fseek(fp, 0L, SEEK_SET);			   /*                        */
  s = malloc(size);				   /*                        */
  read(fp, s, size);
  fclose(fp);					   /*                        */

  if (strcmp(out,s) != 0)
  { fprintf(stderr, "*** %s\n>%s\n<%s\n", id, s, out);
    return 1;
  }
  if ( verbose)
  { fprintf(stderr, "*** %s\n>%s\n<%s\n", id, s, out);
  }
  return 0;
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
void verbose_1()				   /*                        */
{ expect("verbose_1", "verbose = on\n", "");	   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
void select_num_1()				   /*                        */
{ expect("select_num_1", "crossref.limit = 123\n", "");/*                    */
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
int run_tests(s)				   /*                        */
  char * s;
{						   /*                        */
#define TEST(CASE, FCT)  if (s == NULL || strcmp(s, CASE) == 0) FCT

  TEST("select_num_1", select_num_1());
  TEST("verbose_1", verbose_1());

  return 0;
}						   /*------------------------*/
