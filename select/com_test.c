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

 extern Term eval_command();

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
    { Term t = eval_command(argv[i]);		   /*                        */
      dump_term(t);
    }						   /*                        */
  }						   /*                        */
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

void save_input_file(file)
  char *file;
{}
void save_macro_file(file)
  char *file;
{}
void save_output_file(file)
  char * file;
{}

