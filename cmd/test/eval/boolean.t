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
BUnit::run(name         => 'not-20',
	   args	        => '--eval',
	   resource     => 'not 0;',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-21',
	   args	        => '--eval',
	   resource     => 'not 1;',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-30',
	   args	        => '--eval',
	   resource     => 'not "";',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-31',
	   args	        => '--eval',
	   resource     => 'not "1";',
	   expected_err => '',
	   expected_out => "false\n" );

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


#------------------------------------------------------------------------------
BUnit::run(name         => 'if-1',
	   args	        => '--eval',
	   resource     => 'if(true){111}',
	   expected_err => '',
	   expected_out => "111\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-2',
	   args	        => '--eval',
	   resource     => 'if(false){111}',
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-3',
	   args	        => '--eval',
	   resource     => 'if(true){111}else{222}',
	   expected_err => '',
	   expected_out => "111\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-4',
	   args	        => '--eval',
	   resource     => 'if(false){111}else{222}',
	   expected_err => '',
	   expected_out => "222\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-5',
	   args	        => '--eval',
	   resource     => 'if(){111}else{222}',
	   expected_err => '',
	   expected_out => "222\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-string-1',
	   args	        => '--eval',
	   resource     => 'true:as.string()',
	   expected_err => '',
	   expected_out => "\"true\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-string-2',
	   args	        => '--eval',
	   resource     => 'x=true; x:as.string()',
	   expected_err => '',
	   expected_out => "\"true\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-string-3',
	   args	        => '--eval',
	   resource     => 'false:as.string()',
	   expected_err => '',
	   expected_out => "\"false\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-string-4',
	   args	        => '--eval',
	   resource     => 'x=false; x:as.string()',
	   expected_err => '',
	   expected_out => "\"false\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-number-1',
	   args	        => '--eval',
	   resource     => 'true:as.number()',
	   expected_err => '',
	   expected_out => "1\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-number-2',
	   args	        => '--eval',
	   resource     => 'x=true; x:as.number()',
	   expected_err => '',
	   expected_out => "1\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-number-3',
	   args	        => '--eval',
	   resource     => 'false:as.number()',
	   expected_err => '',
	   expected_out => "0\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-number-4',
	   args	        => '--eval',
	   resource     => 'x=false; x:as.number()',
	   expected_err => '',
	   expected_out => "0\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-boolean-1',
	   args	        => '--eval',
	   resource     => 'true:as.boolean()',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-as-boolean-2',
	   args	        => '--eval',
	   resource     => 'false:as.boolean()',
	   expected_err => '',
	   expected_out => "false\n" );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
