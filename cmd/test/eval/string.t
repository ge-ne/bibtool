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

string.t - Test suite for BibTool string values.

=head1 SYNOPSIS

string.t

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
BUnit::run(name         => 'string-0',
	   args	        => '--eval',
	   resource     => '""',
	   expected_err => '',
	   expected_out => "\"\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-1',
	   args	        => '--eval',
	   resource     => '"123"',
	   expected_err => '',
	   expected_out => "\"123\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-length-0',
	   args	        => '--eval',
	   resource     => '"":length()',
	   expected_err => '',
	   expected_out => "0\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-length-1',
	   args	        => '--eval',
	   resource     => '"123":length()',
	   expected_err => '',
	   expected_out => "3\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-length-2',
	   args	        => '--eval',
	   resource     => 'x="123"; x:length()',
	   expected_err => '',
	   expected_out => "3\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-toString-1',
	   args	        => '--eval',
	   resource     => '"123":toString()',
	   expected_err => '',
	   expected_out => "\"123\"\n" );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
