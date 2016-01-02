# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015-2016 Gerd Neugebauer
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
# -----------------------------------------------------------------------------
PERL = perl
TEST_PRG=../tester

all: clean test

test tests: $(TEST_PRG)
	@BIBTOOL_PRG=$(TEST_PRG) ${PERL} -I../../test/lib -MBUnit -e "exit all()"

clean:
	@$(RM) */*.out */*.err */*.err-expected */*.out-expected */*~ *~

# -----------------------------------------------------------------------------

.SUFFIXES: .t .test $(SUFFIXES)

.t.test: $(TEST_PRG)
	@BIBTOOL_PRG=$(TEST_PRG) $(PERL) -I../../test/lib -I. $<

#
