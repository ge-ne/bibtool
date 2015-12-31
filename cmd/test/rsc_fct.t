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

rsc_fct.t - Test suite for BibTool built-in functions.

=head1 SYNOPSIS

rsc_fct.t

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


sub fct_tests
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
	     ignore	=> 1,
	   resource	=> "$cmd = \{123\};\n" ,
	   expected_err	=> '',
	   expected_out	=> "($cmd \{123\})\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-4",
	     ignore	=> 1,
	   resource	=> "$cmd \{123\};\n" ,
	   expected_err	=> '',
	   expected_out	=> "($cmd \{123\})\n" );
}

fct_tests('add.field');
fct_tests('check.rule');
fct_tests('clear.ignored.words');
fct_tests('default.key');
fct_tests('delete.field');
fct_tests('extract.file');
fct_tests('extract.regex');
fct_tests('fmt.inter.name');
fct_tests('fmt.name.pre');
fct_tests('fmt.name.name');
fct_tests('fmt.name.title');
fct_tests('fmt.title.title');
fct_tests('fmt.et.al');
fct_tests('fmt.word.separator');
fct_tests('field.type');
fct_tests('input');
fct_tests('ignored.word');
fct_tests('key.base');
fct_tests('key.format');
fct_tests('key.number.separator');
fct_tests('macro.file');
fct_tests('new.entry.type');
fct_tests('new.field.type');
fct_tests('new.format.type');
fct_tests('output.file');
fct_tests('print');
fct_tests('regexp.syntax');
fct_tests('rename.field');
fct_tests('resource');
fct_tests('resource.search.path');
fct_tests('rewrite.rule');
fct_tests('select');
fct_tests('select.by.string');
fct_tests('select.by.non.string');
fct_tests('select.non');
fct_tests('sort.order');
fct_tests('sort.format');
fct_tests('symbol.type');
fct_tests('tex.define');
fct_tests('version');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
