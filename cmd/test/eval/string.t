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
BUnit::run(name         => 'string-substring-1',
	   args	        => '--eval',
	   resource     => '"123":substring(-1)',
	   expected_err => '',
	   expected_out => "\"123\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-substring-2',
	   args	        => '--eval',
	   resource     => '"123":substring(0)',
	   expected_err => '',
	   expected_out => "\"123\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-substring-3',
	   args	        => '--eval',
	   resource     => '"123":substring(1)',
	   expected_err => '',
	   expected_out => "\"23\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-substring-4',
	   args	        => '--eval',
	   resource     => '"123":substring(4)',
	   expected_err => '',
	   expected_out => "\"\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-substring-10',
	   args	        => '--eval',
	   resource     => '"123":substring(1,0)',
	   expected_err => '',
	   expected_out => "\"\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-substring-11',
	   args	        => '--eval',
	   resource     => '"123":substring(1,2)',
	   expected_err => '',
	   expected_out => "\"23\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-substring-12',
	   args	        => '--eval',
	   resource     => '"123":substring(1,22)',
	   expected_err => '',
	   expected_out => "\"23\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-trim-1',
	   args	        => '--eval',
	   resource     => '"123":trim()',
	   expected_err => '',
	   expected_out => "\"123\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-trim-2',
	   args	        => '--eval',
	   resource     => '" 123 ":trim()',
	   expected_err => '',
	   expected_out => "\"123\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-trim-3',
	   args	        => '--eval',
	   resource     => '"1 2 3":trim()',
	   expected_err => '',
	   expected_out => "\"1 2 3\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-trim-4',
	   args	        => '--eval',
	   resource     => '" 1 2 3 ":trim()',
	   expected_err => '',
	   expected_out => "\"1 2 3\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-as-1',
	   args	        => '--eval',
	   resource     => '"123":as.string()',
	   expected_err => '',
	   expected_out => "\"123\"\n" );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
