#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2019 Gerd Neugebauer
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

lib__check_y.t - Test suite for BibTool library check_y.

=head1 SYNOPSIS

lib__check_y.t 

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
use warnings;
use BUnit;

#------------------------------------------------------------------------------
BUnit::run(name     => 'lib__check_y_1',
	   args     => '-r check_y',
	   BIBTOOL  => '.:../lib',
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'lib__check_y_2',
	   args     => '-r check_y',
	   BIBTOOL  => '.:../lib',
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "99"
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'lib__check_y_10',
	   args     => '-r check_y',
	   BIBTOOL  => '.:../lib',
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "219"
}
__EOF__
    expected_err => "*** BibTool (line 1 in _test.bib): Manual bibtool: Semantic error. Year has to be a suitable number\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'lib__check_y_11',
	   args     => '-r check_y',
	   BIBTOOL  => '.:../lib',
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "1799"
}
__EOF__
    expected_err => "*** BibTool (line 1 in _test.bib): Manual bibtool: Semantic error. Year has to be a suitable number\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'lib__check_y_12',
	   args     => '-r check_y',
	   BIBTOOL  => '.:../lib',
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2100"
}
__EOF__
    expected_err => "*** BibTool (line 1 in _test.bib): Manual bibtool: Semantic error. Year has to be a suitable number\n"
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
