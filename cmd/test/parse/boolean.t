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

boolean.t - Test suite for BibTool boolean values.

=head1 SYNOPSIS

boolean.t

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
BUnit::run(name         => 'boolean-0',
	   resource	=> <<__EOF__ ,
false;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
false
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-1',
	   resource	=> <<__EOF__ ,
true;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
true
__EOF__


sub boolean_tests
{ my ($key, $op) = @_;

  #----------------------------------------------------------------------------
  BUnit::run(name         => "$key-err-1",
	     resource	  => "123 $op\n",
	     expected_err => "\n\n^\n*** BibTool ERROR:  (line 1 in _test.rsc): Missing operator for $op\n");
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-1",
	     resource	  => "123${op}456",
	     expected_err => '',
	     expected_out => "(123 $op 456)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-2",
	     resource	  => "123 $op -456",
	     expected_err => '',
	     expected_out => "(123 $op -456)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-3",
	     resource	  => "-123 $op -456",
	     expected_err => '',
	     expected_out => "(-123 $op -456)\n" );
}

boolean_tests('eq','==');
boolean_tests('ge','>=');
boolean_tests('gt','>');
boolean_tests('le','<=');
boolean_tests('lt','<');
boolean_tests('ne','!=');


sub and_or_tests
{ my ($key, $op) = @_;

  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-err-1",
	     resource	  => "123 $op\n",
	     expected_err => "\n\n^\n*** BibTool ERROR:  (line 1 in _test.rsc): Missing operator for $key\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-err-2",
	     resource	  => "123 $op;\n",
	     expected_err => "\n123 $op;\n^\n*** BibTool ERROR:  (line 1 in _test.rsc): Missing operator after $key\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-1",
	     resource	  => "123${op}456",
	     expected_err => '',
	     expected_out => "(123 $key 456)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-2",
	     resource	  => "123 $op -456",
	     expected_err => '',
	     expected_out => "(123 $key -456)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-3",
	     resource	  => "-123 $op -456",
	     expected_err => '',
	     expected_out => "(-123 $key -456)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-11",
	     resource	  => "-123 $key 456",
	     expected_err => '',
	     expected_out => "(-123 $key 456)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-12",
	     resource	  => "123 $key -456",
	     expected_err => '',
	     expected_out => "(123 $key -456)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name         => "$key-13",
	     resource	  => "-123 $key -456",
	     expected_err => '',
	     expected_out => "(-123 $key -456)\n" );
}

and_or_tests('and','&&');
and_or_tests('or','||');


#------------------------------------------------------------------------------
BUnit::run(name         => 'not-2',
	   resource	=> <<__EOF__ ,
not true;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
not(true)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-3',
	   resource	=> <<__EOF__ ,
not not a;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
not(not(a))
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-10',
	   resource	=> <<__EOF__ ,
not a and b;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(not(a) and b)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-11',
	   resource	=> <<__EOF__ ,
not a or b;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(not(a) or b)
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
