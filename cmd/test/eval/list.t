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

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
