#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

list.t - Test suite for BibTool list expressions.

=head1 SYNOPSIS

list.t

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
BUnit::run(name         => 'list-1',
	   resource	=> <<__EOF__ ,
[];
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
 nil 
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-2',
	   resource	=> <<__EOF__ ,
[ ];
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
 nil 
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-3',
	   resource	=> <<__EOF__ ,
nil;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
 nil 
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-10',
	   resource	=> <<__EOF__ ,
[123];
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(123) 
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-20',
	   resource	=> <<__EOF__ ,
[123, "abc"];
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(123 "abc")
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
