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

or.t - Test suite for BibTool && operator.

=head1 SYNOPSIS

or.t

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
BUnit::run(name         => 'or-err-1',
	   resource	=> <<__EOF__ ,
123 ||
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for or
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-err-2',
	   resource	=> <<__EOF__ ,
123 or
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for or
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-1',
	   resource	=> <<__EOF__ ,
123||456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-2',
	   resource	=> <<__EOF__ ,
123 || -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-3',
	   resource	=> <<__EOF__ ,
-123 || -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or -123 -456)
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'or-11',
	   resource	=> <<__EOF__ ,
123or 456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-12',
	   resource	=> <<__EOF__ ,
123 or -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-13',
	   resource	=> <<__EOF__ ,
-123 or -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or -123 -456)
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
