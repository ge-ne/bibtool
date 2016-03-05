#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2016 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

list.t - Test suite for BibTool 3 list features.

=head1 SYNOPSIS

list.t

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
BUnit::run(name         => 'list-1',
	   args	        => '--eval',
	   resource     => "[]",
	   expected_err => '',
	   expected_out => "[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-2',
	   args	        => '--eval',
	   resource     => "[123]",
	   expected_err => '',
	   expected_out => "[123]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-3',
	   args	        => '--eval',
	   resource     => "[true]",
	   expected_err => '',
	   expected_out => "[true]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-4',
	   args	        => '--eval',
	   resource     => "[false]",
	   expected_err => '',
	   expected_out => "[false]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-5',
	   args	        => '--eval',
	   resource     => "[\"123\"]",
	   expected_err => '',
	   expected_out => "[\"123\"]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-6',
	   args	        => '--eval',
	   resource     => "x=123;[x]",
	   expected_err => '',
	   expected_out => "[123]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-7',
	   args	        => '--eval',
	   resource     => "x=123;[[x]]",
	   expected_err => '',
	   expected_out => "[[123]]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-length-1',
	   args	        => '--eval',
	   resource     => "[]:length()",
	   expected_err => '',
	   expected_out => "0\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-length-2',
	   args	        => '--eval',
	   resource     => "[111]:length()",
	   expected_err => '',
	   expected_out => "1\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-length-3',
	   args	        => '--eval',
	   resource     => "[3,4]:length()",
	   expected_err => '',
	   expected_out => "2\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-as-string-1',
	   args	        => '--eval',
	   resource     => "[]:as.string()",
	   expected_err => '',
	   expected_out => "\"[]\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-as-string-2',
	   args	        => '--eval',
	   resource     => "[111]:as.string()",
	   expected_err => '',
	   expected_out => "\"[111]\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-as-string-3',
	   args	        => '--eval',
	   resource     => "[3,4]:as.string()",
	   expected_err => '',
	   expected_out => "\"[3, 4]\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-as-string-10',
	   args	        => '--eval',
	   resource     => "x=3;[x,4]:as.string()",
	   expected_err => '',
	   expected_out => "\"[3, 4]\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-join-1',
	   args	        => '--eval',
	   resource     => "[]:join()",
	   expected_err => '',
	   expected_out => "\"\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-join-2',
	   args	        => '--eval',
	   resource     => "[111]:join()",
	   expected_err => '',
	   expected_out => "\"111\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-join-3',
	   args	        => '--eval',
	   resource     => "[11,22]:join()",
	   expected_err => '',
	   expected_out => "\"1122\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-join-4',
	   args	        => '--eval',
	   resource     => "[11,22]:join(\"\")",
	   expected_err => '',
	   expected_out => "\"1122\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-join-10',
	   args	        => '--eval',
	   resource     => "[11,22]:join(\" \")",
	   expected_err => '',
	   expected_out => "\"11 22\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-as-boolean-1',
	   args	        => '--eval',
	   resource     => '[121]:as.boolean()',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-as-boolean-2',
	   args	        => '--eval',
	   resource     => '[]:as.boolean()',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-car-1',
	   args	        => '--eval',
	   resource     => '[]:car()',
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-car-2',
	   args	        => '--eval',
	   resource     => 'x=[]; x:car()',
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-car-3',
	   args	        => '--eval',
	   resource     => '[111]:car()',
	   expected_err => '',
	   expected_out => "111\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-car-4',
	   args	        => '--eval',
	   resource     => '[111, 222]:car()',
	   expected_err => '',
	   expected_out => "111\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-cdr-1',
	   args	        => '--eval',
	   resource     => '[]:cdr()',
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-cdr-2',
	   args	        => '--eval',
	   resource     => 'x=[]; x:cdr()',
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-cdr-3',
	   args	        => '--eval',
	   resource     => '[111]:cdr()',
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-cdr-4',
	   args	        => '--eval',
	   resource     => '[111, 222]:cdr()',
	   expected_err => '',
	   expected_out => "[222]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-empty-1',
	   args	        => '--eval',
	   resource     => '[]:empty()',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-empty-2',
	   args	        => '--eval',
	   resource     => '[111]:empty()',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-empty-3',
	   args	        => '--eval',
	   resource     => '[111, 222]:empty()',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-equals-1',
	   args	        => '--eval',
	   resource     => '[]:equals([])',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-equals-2',
	   args	        => '--eval',
	   resource     => '[1]:equals([1])',
	   expected_err => '',
	   expected_out => "true\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-equals-3',
	   args	        => '--eval',
	   resource     => '[]:equals([1])',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-equals-10',
	   args	        => '--eval',
	   resource     => '[]:equals(1)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-equals-11',
	   args	        => '--eval',
	   resource     => '[]:equals("1")',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-equals-20',
	   args	        => '--eval',
	   resource     => '[1]:equals(1)',
	   expected_err => '',
	   expected_out => "false\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-equals-21',
	   args	        => '--eval',
	   resource     => '[1]:equals("1")',
	   expected_err => '',
	   expected_out => "false\n" );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
