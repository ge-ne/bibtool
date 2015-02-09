# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2015 Gerd Neugebauer
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

default all: $(BIBTOOL) $(SUITES)
	@${PERL} -MBUnit -e "exit all()"

$(BIBTOOL): ../*.c ../*.h ../include/bibtool/*.h ../regex-0.12/*.[ch]
	(cd ..; make)

clean:
	${RM} *.log *.err *.???-expected *.out *~ *.bak

distclean: clean

# -----------------------------------------------------------------------------

.SUFFIXES: .t .test $(SUFFIXES)

.t.test: $(BIBTOOL)
	@${PERL} -I. $<

#
