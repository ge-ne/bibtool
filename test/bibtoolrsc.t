#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2017 Gerd Neugebauer
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

bibtoolrsc.t - Test suite for BibTool .bibtoolrsc.

=head1 SYNOPSIS

bibtoolrsc.t 

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


#------------------------------------------------------------------------------
BUnit::run(name         => '_bibtoolrsc_1',
	   ignore 	=> (-e ".bibtoolrsc"),
	   prepare 	=> sub {
	     BUnit::store_file('.bibtoolrsc','print{Done that}');
	   },
	   check 	=> sub {
	     unlink('.bibtoolrsc');
	     return 0;
	   },
	   expected_err	=> "Done that\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name         => '_bibtoolrsc_2',
	   ignore 	=> (-e "$ENV{HOME}/.bibtoolrsc"),
	   prepare 	=> sub {
	     BUnit::store_file("$ENV{HOME}/.bibtoolrsc",'print{Done that too}');
	   },
	   check 	=> sub {
	     unlink("$ENV{HOME}/.bibtoolrsc");
	     return 0;
	   },
	   expected_err	=> "Done that too\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name         => '_bibtoolrsc_3',
	   ignore 	=> (-e ".bibtoolrsc" or -e "$ENV{HOME}/.bibtoolrsc"),
	   prepare 	=> sub {
	     BUnit::store_file(".bibtoolrsc",'print{Been there}');
	     BUnit::store_file("$ENV{HOME}/.bibtoolrsc",'print{Done that}');
	   },
	   check 	=> sub {
	     unlink("$ENV{HOME}/.bibtoolrsc");
	     unlink('.bibtoolrsc');
	     return 0;
	   },
	   expected_err	=> "Done that\n"
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
