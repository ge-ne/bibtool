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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-0',
	   args	        => '--eval',
	   resource     => 'false;',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-1',
	   args	        => '--eval',
	   resource     => 'true;',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-0',
	   args	        => '--eval',
	   resource     => 'not false;',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-1',
	   args	        => '--eval',
	   resource     => 'not true;',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-10',
	   args	        => '--eval',
	   resource     => 'not(true);',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-err-1',
	   args	        => '--eval',
	   resource     => 'not 1;',
	   expected_err => "\n*** BibTool ERROR: Type error: boolean expected\n",
	   expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-err-2',
	   args		=> '--eval',
	   ignore	=> 1,
	   resource	=> 'not(true, true);',
	   expected_err	=> "\n*** BibTool ERROR: Type error: boolean expected\n",
	   expected_out	=> '' );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-err-3',
	   args	        => '--eval',
	   resource     => 'not "1";',
	   expected_err => "\n*** BibTool ERROR: Type error: boolean expected\n",
	   expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-1',
	   args	        => '--eval',
	   resource     => 'true and true;',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-2',
	   args	        => '--eval',
	   resource     => 'true and false;',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-3',
	   args	        => '--eval',
	   resource     => 'false and true;',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-4',
	   args	        => '--eval',
	   resource     => 'false and false;',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-1',
	   args	        => '--eval',
	   resource     => 'true or true;',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-2',
	   args	        => '--eval',
	   resource     => 'true or false;',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-3',
	   args	        => '--eval',
	   resource     => 'false or true;',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-4',
	   args	        => '--eval',
	   resource     => 'false or false;',
	   expected_err => '',
	   expected_out => "false\n" );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
