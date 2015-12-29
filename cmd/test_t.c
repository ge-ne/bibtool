/*** xxx.c *****************************************************************
** 
** This file is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <bibtool/error.h>
#include "term.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

int verbose = 0;

/*-----------------------------------------------------------------------------
** Function:	action()
** Type:	int
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	
**___________________________________________________			     */
int action(t)					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  print_term(stdout, t);			   /*                        */
  putchar('\n');				   /*                        */

  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	run_test()
** Type:	void
** Purpose:	
**		
** Arguments:
**	file	
** Returns:	nothing
**___________________________________________________			     */
void run_test(file)				   /*                        */
  char * file;					   /*                        */
{						   /*                        */
  if (verbose)					   /*                        */
    fprintf(stderr, "--- reading %s\n", file);	   /*                        */
 						   /*                        */
  parse_term(file, action);			   /*                        */
}						   /*------------------------*/

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
  int ok = 0;					   /*                        */
  char *arg;					   /*                        */
#define ArgIs(A,B) strcmp(A, arg) == 0 || strcmp(B, arg) == 0
 						   /*                        */
  init_error(stderr);				   /*                        */
  init_symdef();				   /*                        */
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
		"Usage: %s [-i] [infile]\n",	   /*                        */
		argv[0]);			   /*                        */
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
  return 0;					   /*                        */
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
