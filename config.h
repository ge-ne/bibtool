/******************************************************************************
** $Id: config.h,v 1.5 2012-01-30 05:08:02 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2012 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

/******************************************************************************
**			    Configuration Section
******************************************************************************/

/*-----------------------------------------------------------------------------
**  Define the default value of the resource search path.
**  This is a string containing a colon/semicolon/comma separated list of
**  directories.
**  DON'T FORGET THE CURRENT DIRECTORY.
**  To clear it set it to NULL.
**  This can also be specified in the Makefile. This value is used if no
**  Makefile is used or the macro is not set in the makefile.
*/
#ifndef RSC_BIBTOOL_DEFAULT
#define RSC_BIBTOOL_DEFAULT NULL
#endif

/*-----------------------------------------------------------------------------
**  If the following macro is defined then the standard @types are provided
**  automatically.
**  The value is a comma separated list of strings.
**  Note that COMMENT, PREAMBLE, STRING, ALIAS, MODIFY, and INCLUDE
**  are hard wired and need not to be in this list!
*/
#define INITIALIZE_BIBTEX_ENTRIES					 \
	"Article"	,"Book"		,"Booklet"	,"Conference"	,\
	"InBook"	,"InCollection"	,"InProceedings","Manual"	,\
	"MastersThesis"	,"Misc"		,"PhDThesis"	,"Proceedings"	,\
	"TechReport"	,"Unpublished"	

/*-----------------------------------------------------------------------------
**  If the following macro is defined then the listed macros are predefined.
**  The value is a comma separated list of strings.
*/
#define INITIALIZE_MACROS						 \
	"jan", "feb", "mar", "apr", "may", "jun",			 \
	"jul", "aug", "sep", "oct", "nov", "dec"

/*-----------------------------------------------------------------------------
**  If the following macro is defined then ignored words are initialized.
**  Those words anre not taken into account when sorting or key generation
**  for titles is performed.
**  The value is a comma separated list of strings.
*/
#define INITIALIZE_IGNORED_WORDS 		\
	"a", "an", "the",			\
	"der", "die", "das", "ein", "eine",	\
	"einen", "eines", "einer", "einem",	\
    	"le", "les", "la", "un", "une",		\
	"el", "il"

/*-----------------------------------------------------------------------------
**  Define the default value of the BibTeX search path.
**  This is a string containing a colon separated list of directories.
**  DON'T FORGET THE CURRENT DIRECTORY.
**  To clear it set it to NULL.
**  This can also be specified in the Makefile. This value is used if no
**  Makefile is used or the macro is not set in the makefile.
*/
#ifndef RSC_BIBINPUTS_DEFAULT
#define RSC_BIBINPUTS_DEFAULT NULL
#endif

/*-----------------------------------------------------------------------------
**  Define the name of an environment variable of the BibTeX search path.
**  Consult your local guide on the environment variable used.
**  Be careful and strip the ninth character if only eight are allowed.
*/
#define RSC_BIBINPUTS       "BIBINPUTS"

/*-----------------------------------------------------------------------------
**  Define the name of the default resource file name.
**  On MSDOS-like maschines I recommend "bibtool.rsc"
*/
#ifdef MSDOS
#define DefaultResourceFile "bibtool.rsc"
#else
#define DefaultResourceFile ".bibtoolrsc"
#endif

/*-----------------------------------------------------------------------------
**  Define the name of an environment variable containing a resource file name.
**  Undefine this macro if no such feature is present in your system.
*/
#define RSC_ENV_VAR         "BIBTOOLRSC"

/*-----------------------------------------------------------------------------
**  Define the name of an environment variable of the resource search path.
**  Undefine this macro if no such feature is present in your system.
*/
#define RSC_BIBTOOL         "BIBTOOL"

/*-----------------------------------------------------------------------------
**  This character separates the directories in environment search paths.
**  This is also done in the makefile. Do not define it here if you use the
**  makefile.
**  On UN*X systems it should be ":".
**  On MSDOS and Atari I recommend ";".
**  On Amiga I recommend ",".
*/
#ifndef ENV_SEP
#ifdef MSDOS
#define ENV_SEP		    ";"
#else
#ifdef AMIGA
#define ENV_SEP		    ","
#else
#define ENV_SEP		    ":"
#endif
#endif
#endif

/*-----------------------------------------------------------------------------
**  Define the name of an environment variable containing the home directory.
**  This implies a UN*X-like file system.
**  Undefine this macro if no such feature is present in your system.
*/
#define HOME_ENV_VAR        "HOME"

/*-----------------------------------------------------------------------------
**  This character separates directory and file components of a complete file
**  name.
**  This is also defined in the makefile. Do not define it here if you use the
**  makefile.
**  On UN*X systems it should be "/".
**  On M$DOS-like systems it should be "\\".
*/
#ifndef DIR_SEP
#ifdef MSDOS
#define DIR_SEP "\\"
#else
#define DIR_SEP "/"
#endif
#endif

/*-----------------------------------------------------------------------------
**  This character starts options on the command line.
**  On UN*X systems it should be '-'
*/
#define OptionLeadingCharacter '-'

/*-----------------------------------------------------------------------------
**  Maximal number of user defined formats.
**  At least 2 are required by BibTool!
*/
#define NUMBER_OF_FORMATS 128

/*-----------------------------------------------------------------------------
**  Size of the hash table.
**  This should be a prime number. Don't use a value which is too small.
**  307 is just ok if you consider databases with up to 100 entries.
**  1021 is for larger databases.
*/
#define HASH_TABLE_SIZE 1021

/*-----------------------------------------------------------------------------
**  Define the next macro to enable output of the symbol table.
**  Mainly interesting for debugging (i.e. not for you:-).
*/
/* #define SYMBOL_DUMP */


#ifdef MSDOS
/*-----------------------------------------------------------------------------
**  The following section contains (some) support for M*DOS like computers.
**  They only are in effect when the macro MSDOS is defined.
**  Don't blame me, I do not use such such a kind of "OS"
**-----------------------------------------------------------------------------
*/
/*-----------------------------------------------------------------------------
**  Define the following macro to enable emtex like search path initalization.
*/
#define EMTEX_LIKE_PATH

/*-----------------------------------------------------------------------------
**  The following macro holds the environment variable containing the path.
*/
#define EMTEXDIR		"EMTEXDIR"
/*-----------------------------------------------------------------------------
**  The following macro holds the default if no environment variable is found.
*/
#define EMTEXTDIR_DEFAULT	"\\emtex"
/*-----------------------------------------------------------------------------
**  The following macro holds the subdir of EMTEXDIR for bibtex.
*/
#define EMTEXT_BIBTEX		"\\bibtex\\bib"
/*-----------------------------------------------------------------------------
**  The following macro holds the subdir of EMTEXDIR for bibtool.
*/
#define EMTEXT_RESOURCE		"\\bibtool"

#endif
