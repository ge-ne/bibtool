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

rsc_string.t - Test suite for BibTool built-in string parameters.

=head1 SYNOPSIS

rsc_string.t

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


sub string_tests
{ my $cmd = shift;
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-1",
	   resource     => "$cmd = \"123\";\n" ,
	   expected_err => '',
	   expected_out => "($cmd \"123\")\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-2",
	   resource     => "$cmd \"123\";\n" ,
	   expected_err => '',
	   expected_out => "($cmd \"123\")\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-3",
	   resource	=> "$cmd = \{123\};\n" ,
	   expected_err	=> '',
	   expected_out	=> "($cmd \{123\})\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-4",
	   resource	=> "$cmd \{123\};\n" ,
	   expected_err	=> '',
	   expected_out	=> "($cmd \{123\})\n" );
}

string_tests('bibtex.env.name');
string_tests('bibtex.search.path');
string_tests('dir.file.separator');
string_tests('env.separator');
string_tests('print.entry.types');
string_tests('print.deleted.prefix');
string_tests('select.by.string.ignored');
string_tests('select.fields');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
