#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2020 Gerd Neugebauer
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

parse.t - Test suite for the BibTool parser and its messages.

=head1 SYNOPSIS

parse.t 

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
BUnit::run(name     => 'parse_1',
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {A.U. Thor},
  author =	 {Gerd Neugebauer},
  year =	 2019
}
__EOF__
	   expected_err => "\n*** BibTool WARNING (line 1 in _test.bib): Duplicate field `author' overwritten\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'parse_10',
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {A.U. Thor}
  year =	 2019
}
__EOF__
	   expected_err => <<__EOF__

  year =	 2019
__^
*** BibTool WARNING (line 4 in ./_test.bib): Missing ',' assumed.
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'parse_11',
	   args	    => '-s',
	   bib      => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {A.U. Thor}
  year =	 2019
}
__EOF__
	   expected_err => <<__EOF__

  year =	 2019
__^
*** BibTool WARNING (line 4 in ./_test.bib): Missing ',' assumed.
__EOF__
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
