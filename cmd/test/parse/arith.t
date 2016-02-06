#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015-2016 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

arith.t - Test suite for BibTool arithmetic expressions.

=head1 SYNOPSIS

arith.t

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

$BUnit::name_prefix = 'parse/';

#------------------------------------------------------------------------------
BUnit::run(name         => 'arith-err-1',
	   resource	=> <<__EOF__ ,
(


__EOF__
	   expected_err => <<__EOF__ );


^
*** BibTool ERROR:  (line 1 in _test.rsc): Missing ) before end of file
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'arith-1',
	   resource	=> "123;\n" ,
	   expected_err => '',
	   expected_out => <<__EOF__ );
123
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'arith-2',
	   resource	=> <<__EOF__ ,
-123;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
-123
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'arith-3',
	   resource	=> <<__EOF__ ,
-   123;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
-123
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'arith-10',
	   resource	=> <<__EOF__ ,
2 * 3 + 4;
__EOF__
	   expected_out => <<__EOF__ );
((2 * 3) + 4)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'arith-11',
	   resource	=> <<__EOF__ ,
2 + 3 * 4;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(2 + (3 * 4))
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'arith-12',
	   resource	=> <<__EOF__ ,
1 * (3 + 4);
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(1 * (3 + 4))
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'arith-21',
	   resource	=> <<__EOF__ ,
1 + 2 + 3;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(1 + (2 + 3))
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
