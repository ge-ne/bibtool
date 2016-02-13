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

set.t - Test suite for BibTool assignments.

=head1 SYNOPSIS

set.t

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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
sub set_test {
  my ($key,$value) = @_;
  BUnit::run(name         => "$key-0",
	     args	  => '--eval',
	     resource     => "abc=$value;",
	     expected_err => '',
	     expected_out => "$value\n" );
  BUnit::run(name         => $key,
	     args	  => '--eval',
	     resource     => "abc=$value;abc;",
	     expected_err => '',
	     expected_out => "$value\n" );
}

set_test('set-0', 0);
set_test('set-1', 1);
set_test('set-2', 42);
set_test('set-3', -42);
set_test('set-10', 'false');
set_test('set-11', 'true');
set_test('set-20', '[]');
set_test('set-21', '[12]');
set_test('set-30', '""');
set_test('set-31', '"12"');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
