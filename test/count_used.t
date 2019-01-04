#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2019 Gerd Neugebauer
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

count_used.t - Test suite for BibTool count.used.

=head1 SYNOPSIS

count_used.t 

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
use BUnit;use warnings;



#------------------------------------------------------------------------------
BUnit::run(name => 'count_used_1',
	 args	      => '-- count.used=on bib/x1',
	 expected_err		  => "\n---  Manual              1 read      1 written\n");

#------------------------------------------------------------------------------
BUnit::run(name => 'count_used_2',
	 args	      => '-- count.used=off bib/x1',
	 expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => '_at_1',
	 args	      => '-@ bib/x1',
	 expected_err => "\n---  Manual              1 read      1 written\n");

#------------------------------------------------------------------------------
BUnit::run(name => '_at_2',
	 args	      => '-@ bib/xampl',
	 expected_err => <<__EOF__);

*** BibTool WARNING (line 29 in ./bib/xampl.bib): 125 non-space characters ignored.

---  STRING              3 read      3 written
---  PREAMBLE            1 read      1 written
---  Article             4 read      4 written
---  Book                5 read      5 written
---  Booklet             2 read      2 written
---  InBook              3 read      3 written
---  InCollection        3 read      3 written
---  InProceedings       3 read      3 written
---  Manual              2 read      2 written
---  MastersThesis       2 read      2 written
---  Misc                3 read      3 written
---  PhDThesis           2 read      2 written
---  Proceedings         3 read      3 written
---  TechReport          2 read      2 written
---  Unpublished         2 read      2 written
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
