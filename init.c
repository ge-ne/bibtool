/******************************************************************************
** $Id: init.c,v 1.2 2007-02-08 05:27:32 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2001 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This module contains the global initialization function which
**	has to be called before any modules in \BibTool{} are
**	activated.  This is for convenience, thus nobody has to call
**	the various initialization functions for the different modules
**	by hand.
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/rsc.h>
#include <bibtool/key.h>
#include <bibtool/entry.h>
#include <bibtool/symbols.h>
#include <bibtool/macros.h>
#include <bibtool/parse.h>
#include <bibtool/type.h>
#include <bibtool/sbuffer.h>
#include "config.h"
#ifdef HAVE_LIBKPATHSEA
#include <kpathsea/proginit.h>
#endif

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	init_bibtool()
** Purpose:	Perform any initializations necessary for \BibTool.
**		
**		
** Arguments:
**	progname Name of the program for |KPATHSEA|.
** Returns:	nothing
**___________________________________________________			     */
void init_bibtool(progname)			   /*                        */
  char * progname;				   /*                        */
{						   /*                        */
#ifdef EMTEX_LIKE_PATH
  static StringBuffer *sb_rsc;			   /*                        */
  static StringBuffer *sb_bibtex;		   /*                        */
 						   /*                        */
  { char *emtexdir = getenv(EMTEXDIR);		   /*                        */
    if ( emtexdir == NULL ) emtexdir = EMTEXTDIR_DEFAULT;/*                  */
    sb_rsc = sbopen();				   /*                        */
    sbputs(".;",sb_rsc);			   /*                        */
    sbputs(emtexdir,sb_rsc);			   /*                        */
    sbputs(EMTEXT_RESOURCE,sb_rsc);		   /*                        */
    rsc_v_rsc = sbflush(sb_rsc);		   /*                        */
    sb_bibtex = sbopen();			   /*                        */
    sbputs(".;",sb_bibtex);			   /*                        */
    sbputs(emtexdir,sb_bibtex);			   /*                        */
    sbputs(EMTEXT_BIBTEX,sb_bibtex);		   /*                        */
    rsc_v_bibtex = sbflush(sb_bibtex);		   /*                        */
  }						   /*                        */
#endif
#ifdef HAVE_LIBKPATHSEA
#ifdef HAVE_LIBKPATHSEA2
  kpse_set_progname(progname);			   /*                        */
#else
  kpse_set_program_name(progname,"bibtool");	   /*                        */
#endif
#endif
						   /*			     */
  init_type();					   /*			     */
  init_symbols();				   /*			     */
  init_entries();				   /*			     */
  init_read();					   /*			     */
 						   /*                        */
  set_rsc_path(rsc_v_rsc);			   /*                        */
 						   /*                        */
  init_macros();				   /*			     */
  init_read();					   /*			     */
}						   /*------------------------*/
