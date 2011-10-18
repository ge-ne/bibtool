#******************************************************************************
#* $Id: makefile,v 1.2 2011-10-18 16:57:15 gene Exp $
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================
# 
# This is the makefile to run the test suite for BibTool. It should
# work at least for Unix-like systems with GNUmake and bash.
# For instance Linux and Windows with cygwin fulfill this pre-condition.
#
# Note that portability hasn't been an issue for this makefile yet.
#

# -------------------------------------------------------
#  EXT is the optional extension of the final executable.
#  Various Operating Systems have their own ideas about
#  that.
# 

EXT =

# -----------------------------------------------------------------------------
BIBTOOL  = ../bibtool$(EXT)
PERL     = perl
SUITES   = database.test	 \
	   key.test 		 \
	   macros.test 		 \
	   main.test 		 \
	   print.test 		 \
	   rewrite.test 	 \
	   rsc.test 		 \
	   tex_aux.test

default all: $(BIBTOOL) $(SUITES)
	@${PERL} -MBUnit -e "exit summary(qw($(SUITES)))"

$(BIBTOOL): ../*.c
	(cd ..; make)

clean:
	${RM} *.log *.err *.out *~ *.bak

distclean: clean

# -----------------------------------------------------------------------------

.SUFFIXES: .pl .test $(SUFFIXES)

.pl.test:
	@${PERL} -I. $< >$*.log

#
