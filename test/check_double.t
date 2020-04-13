#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2018-2020 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#*=============================================================================

=head1 NAME

check_double.t - Test suite for BibTool check.double.

=head1 SYNOPSIS

check_double.t 

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally files
*.out and *.err are left if the expected result does not match the
actual result.

=head1 OPTIONS

none

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;
use warnings;

#------------------------------------------------------------------------------
BUnit::run(name     => 'check_double_1',
	   resource => <<__EOF__,
check.double = true
__EOF__
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
__EOF__
    expected_err => "*** BibTool WARNING (line 6 in _test.bib): Possible double entry discovered to (line 1 in _test.bib) `bibtool'\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'check_double_2',
	   resource => <<__EOF__,
check.double = true
__EOF__
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}

\@BOOK{book-minimal,
   author = "Donald E. Knuth",
   title = "Seminumerical Algorithms",
   publisher = "Addison-Wesley",
   year = "{\noopsort{1973c}}1981",
}

\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
__EOF__
    expected_err => "*** BibTool WARNING (line 15 in _test.bib): Possible double entry discovered to (line 1 in _test.bib) `bibtool'\n"
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
