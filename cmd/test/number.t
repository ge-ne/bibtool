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

number.t - Test suite for BibTool numbers.

=head1 SYNOPSIS

number.t

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
BUnit::run(name         => 'number-0',
	   resource	=> <<__EOF__ ,
0;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
0
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'number-o0',
	   resource	=> <<__EOF__ ,
00;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
0
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'number-x0',
	   resource	=> <<__EOF__ ,
0x0;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
0
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'number-1',
	   resource	=> <<__EOF__ ,
123;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
123
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'number-2',
	   resource	=> <<__EOF__ ,
-123;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
-123
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'number-3',
	   resource	=> <<__EOF__ ,
0xff;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
255
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'number-4',
	   resource	=> <<__EOF__ ,
077;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
63
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
