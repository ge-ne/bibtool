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

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-equals-1',
	   args	        => '--eval',
	   resource     => 'false:equals(false)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-equals-2',
	   args	        => '--eval',
	   resource     => 'false:equals(true)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-equals-3',
	   args	        => '--eval',
	   resource     => 'true:equals(false)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-equals-4',
	   args	        => '--eval',
	   resource     => 'true:equals(true)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-equals-10',
	   args	        => '--eval',
	   resource     => 'true:equals(1)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-equals-11',
	   args	        => '--eval',
	   resource     => 'true:equals("1")',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-equals-12',
	   args	        => '--eval',
	   resource     => 'true:equals(nil)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-negate-1',
	   args	        => '--eval',
	   resource     => 'true:negate()',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-negate-2',
	   args	        => '--eval',
	   resource     => 'false:negate()',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-1',
	   args	        => '--eval',
	   resource     => 'true:and()',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-2',
	   args	        => '--eval',
	   resource     => 'false:and()',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-10',
	   args	        => '--eval',
	   resource     => 'true:and(true)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-11',
	   args	        => '--eval',
	   resource     => 'true:and(false)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-12',
	   args	        => '--eval',
	   resource     => 'true:and(true, false)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-13',
	   args	        => '--eval',
	   resource     => 'true:and(true, true)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-20',
	   args	        => '--eval',
	   resource     => 'false:and(true)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-21',
	   args	        => '--eval',
	   resource     => 'false:and(false)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-22',
	   args	        => '--eval',
	   resource     => 'false:and(true, false)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-and-23',
	   args	        => '--eval',
	   resource     => 'false:and(true, true)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-1',
	   args	        => '--eval',
	   resource     => 'true:or()',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-2',
	   args	        => '--eval',
	   resource     => 'false:or()',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-10',
	   args	        => '--eval',
	   resource     => 'true:or(true)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-11',
	   args	        => '--eval',
	   resource     => 'true:or(false)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-12',
	   args	        => '--eval',
	   resource     => 'true:or(true, false)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-13',
	   args	        => '--eval',
	   resource     => 'true:or(false, true)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-20',
	   args	        => '--eval',
	   resource     => 'false:or(true)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-21',
	   args	        => '--eval',
	   resource     => 'false:or(false)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-22',
	   args	        => '--eval',
	   resource     => 'false:or(true, false)',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-or-23',
	   args	        => '--eval',
	   resource     => 'false:or(false, true)',
	   expected_err => '',
	   expected_out => "true\n" );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
