/*** linereader.c *****************************************************************
** 
** This file is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2017-2018 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/error.h>
#include <bibtool/sbuffer.h>
#include "linereader.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	lr_open()
** Type:	LineReader
** Purpose:	Create a new line reader and initialize it.
** Arguments:
**	file	the file to read from
**	fname	the name of the file
** Returns:	the new LineReader or NULL on failure
**___________________________________________________			     */
LineReader lr_open (file, fname)		   /*                        */
  FILE* file;					   /*                        */
  char* fname;					   /*                        */
{ LineReader lr = (LineReader)malloc(sizeof(struct S_LINEREADER));/*         */
  if (lr == NULL)				   /*                        */
  { return NULL; }				   /*                        */
 						   /*                        */
  LineReaderFile(lr)	 = file;		   /*                        */
  LineReaderFilename(lr) = fname;		   /*                        */
  LineReaderLineno(lr)	 = 0;			   /*                        */
  LineReaderBEnd(lr)	 = 1023;		   /*                        */
  LineReaderPtr(lr)	 = 0;			   /*                        */
  LineReaderLine(lr)	 = (char*)malloc(LineReaderBEnd(lr)+1);/*            */
  if (LineReaderLine(lr) == NULL)		   /*                        */
  { return NULL; }				   /*                        */
 						   /*                        */
  return lr;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	lr_getc()
** Type:	int
** Purpose:	
**		
** Arguments:
**	lr	the line reader
** Returns:	the next character
**___________________________________________________			     */
int lr_getc(lr)					   /*                        */
  LineReader lr;				   /*                        */
{ int c;					   /*                        */
  FILE * file = LineReaderFile(lr);		   /*                        */
  if (file == NULL) return EOF;	   		   /*                        */
 						   /*                        */
  LineReaderPtr(lr) = 0;			   /*                        */
  for (c = fgetc(file); c >= 0; c = fgetc(file))   /*                        */
  { if (LineReaderPtr(lr) >= LineReaderBEnd(lr))   /*                        */
    { LineReaderBEnd(lr)  += 1024;		   /*                        */
      LineReaderLine(lr) = (char*)realloc(LineReaderLine(lr),/*              */
					  LineReaderBEnd(lr)+1);/*           */
    }						   /*                        */
    LineReaderLine(lr)[LineReaderPtr(lr)++] = c;   /*                        */
    if (c == '\n') break;			   /*                        */
  }						   /*                        */
  if (LineReaderPtr(lr) == 0 && c == EOF)	   /*                        */
  { LineReaderFile(lr) = NULL;			   /*                        */
    LineReaderLine(lr)[0] = '\0';		   /*                        */
    return EOF;					   /*                        */
  }						   /*                        */
  LineReaderLine(lr)[LineReaderPtr(lr)] = '\0';	   /*                        */
  LineReaderPtr(lr) = 1;			   /*                        */
  LineReaderLineno(lr)++;			   /*                        */
  return LineReaderLine(lr)[0];		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	lr_close()
** Type:	void
** Purpose:	Release the memory occupied by the line reader.
** Arguments:
**	lr	the line reader
** Returns:	nothing
**___________________________________________________			     */
void lr_close(lr)				   /*                        */
  LineReader lr;				   /*                        */
{						   /*                        */
  free(LineReaderLine(lr));			   /*                        */
  free(lr);					   /*                        */
}						   /*------------------------*/

#ifdef LINE_READER_TEST

int main(argc, argv)
  int argc;
  char *argv;
{ int i;
  FILE * file 	= fopen("linereader.h", "r");
  LineReader lr	= lr_open(file, "linereader.h");

  for (i = 0; i < 555; i++)
  { if (lr_getc(lr) == EOF) break;
    printf("%d: %s",
	   LineReaderLineno(lr),
	   LineReaderLine(lr));
  }
  return 0;
}
#endif
