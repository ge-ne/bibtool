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

numeric.t - Test suite for BibTool numerics.

=head1 SYNOPSIS

numeric.t

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

#------------------------------------------------------------------------------
BUnit::run(name         => 'plus-err-0',
	   resource	=> <<__EOF__ ,
+
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Unexpected operator +
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'plus-err-1',
	   resource	=> <<__EOF__ ,
123 +
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for +
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'plus-1',
	   resource	=> <<__EOF__ ,
123+456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(+ 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'plus-2',
	   resource	=> <<__EOF__ ,
123 + -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(+ 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'plus-3',
	   resource	=> <<__EOF__ ,
-123 + -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(+ -123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'minus-err-0',
	   resource	=> <<__EOF__ ,
-
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for -
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'minus-err-1',
	   resource	=> <<__EOF__ ,
123 -
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for -
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'minus-1',
	   resource	=> <<__EOF__ ,
123-456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(- 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'minus-2',
	   resource	=> <<__EOF__ ,
123 - -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(- 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'minus-3',
	   resource	=> <<__EOF__ ,
-123 - -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(- -123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'times-err-1',
	   resource	=> <<__EOF__ ,
123 *
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for *
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'times-1',
	   resource	=> <<__EOF__ ,
123*456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(* 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'times-2',
	   resource	=> <<__EOF__ ,
123 * -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(* 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'times-3',
	   resource	=> <<__EOF__ ,
-123 * -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(* -123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'divide-err-1',
	   resource	=> <<__EOF__ ,
123 /
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for /
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'divide-0',
	   resource	=> <<__EOF__ ,
123/0;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(/ 123 0)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'divide-1',
	   resource	=> <<__EOF__ ,
123/456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(/ 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'divide-2',
	   resource	=> <<__EOF__ ,
123 / -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(/ 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'divide-3',
	   resource	=> <<__EOF__ ,
-123 / -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(/ -123 -456)
__EOF__

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
