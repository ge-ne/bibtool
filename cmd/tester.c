/*** tester.c *****************************************************************
** 
** This file is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <bibtool/error.h>
#include <bibtool/io.h>
#include <bibtool/bibtool.h>
#include "binding.h"
#include "lcore.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

 extern int read_loop();

/*---------------------------------------------------------------------------*/

 int verbose  = 0;
 int evaluate = 0;

 Term result = NIL;

/*-----------------------------------------------------------------------------
** Function:	action()
** Type:	int
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	
**___________________________________________________			     */
int action(b, t)				   /*                        */
  Binding b;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (evaluate)					   /*                        */
  { if (result) free_term(result);		   /*                        */
    result = eval_term(b, t); }	   		   /*                        */
  else						   /*                        */
  { print_term(stdout, t);			   /*                        */
    putchar('\n');				   /*                        */
    free_term(t);				   /*                        */
  }						   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	run_test()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	the name of the file to read from
** Returns:	nothing
**___________________________________________________			     */
void run_test(file)				   /*                        */
  char * file;					   /*                        */
{ Binding b = root_binding();	   		   /*                        */
					       	   /*                        */
  if (verbose)					   /*                        */
    fprintf(stderr, "--- reading %s\n", file);	   /*                        */
   						   /*                        */
  read_loop(b, file, action);			   /*                        */
  if (evaluate)					   /*                        */
  { print_term(stdout, result);			   /*                        */
    putchar('\n');				   /*                        */
  }						   /*                        */
  free_term(result);				   /*                        */
}						   /*------------------------*/

#define ArgIs(A,B) strcmp(A, arg) == 0 || strcmp(B, arg) == 0

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
{ int  ok = 0;					   /*                        */
  int  i;					   /*                        */
  char *arg;					   /*                        */
 						   /*                        */
  init_bibtool(argv[0]);			   /*                        */
  init_error(stderr);				   /*                        */
  init_lreader();				   /*                        */
 						   /*                        */
  for (i = 1; i < argc; i++)			   /*                        */
  { arg = argv[i];				   /*                        */
    if (*arg == '-')			   	   /*                        */
    {						   /*                        */
      if (ArgIs("-i", "--input") ||		   /*                        */
	  ArgIs("-r", "--resource"))   	   	   /* for comparibility      */
      {						   /*  to BibTool            */
        if (++i >= argc)			   /*                        */
	{ fprintf(stderr,			   /*                        */
		  "Missing input file name\n");	   /*                        */
	  return -1;				   /*                        */
	}					   /*                        */
	run_test(argv[i]);			   /*                        */
	ok = 1;					   /*                        */
      } else if (ArgIs("-h", "--help"))   	   /*                        */
      { fprintf(stderr,			   	   /*                        */
		"Usage: %s [-v] [-e||--eval] [-i|-r|--infile|--resource] <file>\n",/*     */
		argv[0]);			   /*                        */
      } else if (ArgIs("-e", "--eval"))	   	   /*                        */
      { evaluate = 1;	   			   /*                        */
      } else if (ArgIs("-v", "--verbose"))	   /*                        */
      { verbose = 1;	   			   /*                        */
      } else {					   /*                        */
	fprintf(stderr,				   /*                        */
		"Unknown option: %s\n",arg);   	   /*                        */
      }						   /*                        */
    } else {					   /*                        */
      run_test(arg);			   	   /*                        */
      ok = 1;					   /*                        */
    }						   /*                        */
  }						   /*                        */
  if (ok == 0)					   /*                        */
  { fprintf(stderr, "Missing input file name\n");  /*                        */
    return -1;					   /*                        */
  }						   /*                        */
 						   /*                        */
  dump_terms(stderr);				   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/
