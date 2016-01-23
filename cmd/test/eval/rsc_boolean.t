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
	   args		=> '--eval',
	   resource	=> "$cmd;\n",
	   expected_err	=> '',
	   expected_out	=> "$value\n" );
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
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-10",
	   args	        => '--eval',
	   resource     => "$cmd 0;\n" ,
	   expected_err	=> '',
	   expected_out	=> "false\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-11",
	   args	        => '--eval',
	   resource     => "$cmd 42;\n" ,
	   expected_err	=> '',
	   expected_out	=> "true\n" );
}

  boolean_tests( "apply.alias"			, "false"   );
  boolean_tests( "apply.modify"			, "false"   );
  boolean_tests( "apply.include"		, "false"   );
  boolean_tests( "check.double"			, "false"   );
  boolean_tests( "check.double.delete"		, "false"   );
  boolean_tests( "check.case.sensitive" 	, "true"    );
  boolean_tests( "count.all"			, "false"   );
  boolean_tests( "count.used"			, "false"   );
  boolean_tests( "dump.symbols"			, "false"   );
  boolean_tests( "expand.macros"		, "false"   );
  boolean_tests( "expand.crossref"		, "false"   );
  boolean_tests( "key.generation"		, "false"   );
  boolean_tests( "key.make.alias"		, "false"   );
  boolean_tests( "key.expand.macros"		, "true"    );
  boolean_tests( "pass.comments"		, "false"   );
  boolean_tests( "preserve.key.case"		, "false"   );
  boolean_tests( "preserve.keys"		, "false"   );
  boolean_tests( "print.all.strings"		, "true"    );
  boolean_tests( "print.equal.right"		, "true"    );
  boolean_tests( "print.braces"			, "true"    );
  boolean_tests( "print.comma.at.end"		, "true"    );
  boolean_tests( "print.deleted.entries"	, "true"    );
  boolean_tests( "print.parentheses"		, "false"   );
  boolean_tests( "print.terminal.comma" 	, "false"   );
  boolean_tests( "print.use.tab"		, "true"    );
  boolean_tests( "print.wide.equal"		, "false"   );
  boolean_tests( "quiet"			, "false"   );
  boolean_tests( "rewrite.case.sensitive"	, "true"    );
  boolean_tests( "select.case.sensitive"	, "false"   );
  boolean_tests( "select.crossrefs"		, "false"   );
  boolean_tests( "sort"				, "false"   );
  boolean_tests( "sort.cased"			, "false"   );
  boolean_tests( "sort.macros"			, "true"    );
  boolean_tests( "sort.reverse"			, "false"   );
  boolean_tests( "suppress.initial.newline"	, "false"   );
  boolean_tests( "verbose"			, "false"   );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
