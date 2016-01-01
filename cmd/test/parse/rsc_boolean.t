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

rsc_boolean.t - Test suite for the BibTool built-in boolean parameters.

=head1 SYNOPSIS

rsc_boolean.t

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
# Function:	boolean_tests
# Arguments:	
# Description:	
#
sub boolean_tests
{ my $cmd = shift;
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-0",
	   resource     => "-$cmd;\n",
	   expected_err => '',
	   expected_out => "(- $cmd)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-1",
	   resource     => "$cmd = true;\n" ,
	   expected_err => '',
	   expected_out => "($cmd true)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-2",
	   resource     => "$cmd true;\n" ,
	   expected_err => '',
	   expected_out => "($cmd true)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-3",
	   resource     => "$cmd = \"true\";\n" ,
	   expected_err	=> '',
	   expected_out	=> "($cmd \"true\")\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-4",
	   resource     => "$cmd = {true};\n" ,
	   expected_err	=> '',
	   expected_out	=> "($cmd \{true\})\n" );
}

  boolean_tests('apply.alias');
  boolean_tests('apply.modify');
  boolean_tests('apply.include');
  boolean_tests('check.double');
  boolean_tests('check.double.delete');
  boolean_tests('check.case.sensitive');
  boolean_tests('count.all');
  boolean_tests('count.used');
  boolean_tests('dump.symbols');
  boolean_tests('expand.macros');
  boolean_tests('expand.crossref');
  boolean_tests('key.generation');
  boolean_tests('key.make.alias');
  boolean_tests('key.expand.macros');
  boolean_tests('pass.comments');
  boolean_tests('preserve.key.case');
  boolean_tests('preserve.keys');
  boolean_tests('print.all.strings');
  boolean_tests('print.equal.right');
  boolean_tests('print.braces');
  boolean_tests('print.comma.at.end');
  boolean_tests('print.deleted.entries');
  boolean_tests('print.parentheses');
  boolean_tests('print.terminal.comma');
  boolean_tests('print.use.tab');
  boolean_tests('print.wide.equal');
  boolean_tests('quiet');
  boolean_tests('rewrite.case.sensitive');
  boolean_tests('select.case.sensitive');
  boolean_tests('select.crossrefs');
  boolean_tests('sort');
  boolean_tests('sort.cased');
  boolean_tests('sort.macros');
  boolean_tests('sort.reverse');
  boolean_tests('suppress.initial.newline');
  boolean_tests('verbose');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
