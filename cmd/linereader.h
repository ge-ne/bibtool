/*** linereader.h **************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2017-2018 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------
** Typedef:	*LineReader
** Purpose:	
**		
**		
**___________________________________________________			     */
 typedef struct S_LINEREADER			   /*                        */
 { FILE * file;					   /*                        */
   char * filename;				   /*                        */
   int lineno;					   /*                        */
   size_t bend;					   /*                        */
   char* buffer;				   /*                        */
   size_t ptr;					   /*                        */
 } *LineReader;					   /*                        */

#define LineReaderFile(LR)	((LR)->file)
#define LineReaderFilename(LR)	((LR)->filename)
#define LineReaderLineno(LR)	((LR)->lineno)
#define LineReaderBEnd(LR)	((LR)->bend)
#define LineReaderLine(LR)	((LR)->buffer)
#define LineReaderPtr(LR)	((LR)->ptr)

#define LineReaderAtEOF(LR)	(LineReaderFile(LR) == NULL)
#define LineReaderGetC(LR)	(LineReaderLine(LR)[LineReaderPtr(LR)]	\
				 ? LineReaderLine(LR)[LineReaderPtr(LR)++]	\
				 : lr_getc(LR))
#define LineReaderUnGetC(C,LR)	LineReaderLine(LR)[--LineReaderPtr(LR)] = (C)

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

extern LineReader lr_open _ARG((FILE* file, char* fname));/*                 */
extern int lr_getc _ARG((LineReader lr));	   /*                        */
extern void lr_close _ARG((LineReader lr));	   /*                        */
