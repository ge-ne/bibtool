#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2016 Gerd Neugebauer
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

parse.exit.on.error.t - Test suite for BibTool pass.comments.

=head1 SYNOPSIS

parse.exit.on.error.t

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally files
*.out and *.err are left if the expected result does not match the
actual result.

=head1 OPTIONS

none

=head1 AUTHOR

Gerd Neugebauer

=head1 BUGS

=over 4

=item *

...

=back

=cut

use strict;
use BUnit;

use constant BIBTEX => <<__EOF__;
\@Misc{		  xxx
  author	= "A. U. Thor"
}
This is a comment.
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'parse_exit_on_error_1',
	   resource	=> <<__EOF__ ,
parse.exit.on.error = off
__EOF__
	   bib 	        => BIBTEX,
	   expected_err => <<__EOF__ ,

  author	= "A. U. Thor"
___^
*** BibTool ERROR:  (line 2 in ./_test.bib): Unexpected character encountered

*** BibTool WARNING: Skipping to next '\@'
__EOF__
	   expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name         => 'parse_exit_on_error_2',
	   resource	=> <<__EOF__ ,
parse.exit.on.error = on
__EOF__
	   bib 	        => BIBTEX,
	   expected_err => <<__EOF__ ,

  author	= "A. U. Thor"
___^
*** BibTool ERROR:  (line 2 in ./_test.bib): Unexpected character encountered
__EOF__
	   expected_out => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
