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

mod.t - Test suite for BibTool mod operator.

=head1 SYNOPSIS

mod.t

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
BUnit::run(name         => 'mod-err-1',
	   resource	=> <<__EOF__ ,
123 mod
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for mod
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'mod-1',
	   resource	=> <<__EOF__ ,
123 mod 456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(mod 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'mod-2',
	   resource	=> <<__EOF__ ,
123 mod -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(mod 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'mod-3',
	   resource	=> <<__EOF__ ,
-123 mod -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(mod -123 -456)
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
