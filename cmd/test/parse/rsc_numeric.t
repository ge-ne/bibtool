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

rsc_numeric.t - Test suite for BibTool built-in numeric parameters.

=head1 SYNOPSIS

rsc_numeric.t

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
# Function:	numeric_tests
# Arguments:	
# Description:	
#
sub numeric_tests
{ my $cmd = shift;
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-1",
	   resource     => "$cmd = 123;\n" ,
	   expected_err => '',
	   expected_out => "($cmd 123)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-2",
	   resource     => "$cmd 123;\n" ,
	   expected_err => '',
	   expected_out => "($cmd 123)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-3",
	     ignore	=> 'TODO',
	   resource	=> "$cmd = -123;\n" ,
	   expected_err	=> '',
	   expected_out	=> "($cmd -123)\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-4",
	   resource     => "$cmd = 0;\n" ,
	   expected_err	=> '',
	   expected_out	=> "($cmd 0)\n" );
}

numeric_tests('crossref.limit');
numeric_tests('print.align.string');
numeric_tests('print.align.comment');
numeric_tests('print.align.preamble');
numeric_tests('print.align.key');
numeric_tests('print.align');
numeric_tests('print.indent');
numeric_tests('print.line.length');
numeric_tests('print.newline');
numeric_tests('rewrite.limit');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
