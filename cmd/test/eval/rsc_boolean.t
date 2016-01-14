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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
# Function:	boolean_tests
# Arguments:	
# Description:	
#
sub boolean_tests
{ my $cmd   = shift;
  my $value = shift;
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-1",
	   args	        => '--eval',
	   resource     => "$cmd;\n",
	   expected_err => '',
	   expected_out => "$value\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-2",
	   args	        => '--eval',
	   resource     => "$cmd true; $cmd;\n" ,
	   expected_err => '',
	   expected_out => "true\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-3",
	   args	        => '--eval',
	   resource     => "$cmd false; $cmd;\n" ,
	   expected_err	=> '',
	   expected_out	=> "false\n" );
}

  boolean_tests('apply.alias', "true");
  boolean_tests('apply.modify', "true");
  boolean_tests('apply.include', "true");
  boolean_tests('check.double', "true");
  boolean_tests('check.double.delete', "true");
  boolean_tests('check.case.sensitive', "true");
  boolean_tests('count.all', "true");
  boolean_tests('count.used', "true");
  boolean_tests('dump.symbols', "true");
  boolean_tests('expand.macros', "true");
  boolean_tests('expand.crossref', "true");
  boolean_tests('key.generation', "true");
  boolean_tests('key.make.alias', "true");
  boolean_tests('key.expand.macros', "true");
  boolean_tests('pass.comments', "true");
  boolean_tests('preserve.key.case', "true");
  boolean_tests('preserve.keys', "true");
  boolean_tests('print.all.strings', "true");
  boolean_tests('print.equal.right', "true");
  boolean_tests('print.braces', "true");
  boolean_tests('print.comma.at.end', "true");
  boolean_tests('print.deleted.entries', "true");
  boolean_tests('print.parentheses', "true");
  boolean_tests('print.terminal.comma', "true");
  boolean_tests('print.use.tab', "true");
  boolean_tests('print.wide.equal', "true");
  boolean_tests('quiet', "false");
  boolean_tests('rewrite.case.sensitive', "true");
  boolean_tests('select.case.sensitive', "true");
  boolean_tests('select.crossrefs', "true");
  boolean_tests('sort', "true");
  boolean_tests('sort.cased', "true");
  boolean_tests('sort.macros', "true");
  boolean_tests('sort.reverse', "true");
  boolean_tests('suppress.initial.newline', "true");
  boolean_tests('verbose', "false");

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
