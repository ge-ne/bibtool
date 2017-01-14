#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2017 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

rsc_numeric.t - Test suite for the BibTool built-in numeric parameters.

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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
# Function:	numeric_tests
# Arguments:	
# Description:	
#
sub numeric_tests
{ my $cmd    = shift;
  my $value  = shift;
  my $value1 = $value + 1;
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-1",
	   args		=> '--eval',
	   resource	=> "$cmd;\n",
	   expected_err	=> '',
	   expected_out	=> "$value\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-2",
	   args	        => '--eval',
	   resource     => "$cmd 0; $cmd;\n" ,
	   expected_err => '',
	   expected_out => "0\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-3",
	   args	        => '--eval',
	   resource     => "$cmd 1; $cmd;\n" ,
	   expected_err	=> '',
	   expected_out	=> "1\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-4",
	   args	        => '--eval',
	   resource     => "$cmd 3+4;\n" ,
	   expected_err	=> '',
	   expected_out	=> "7\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-10",
	   args	        => '--eval',
	   resource     => "$cmd \"\";\n" ,
	   expected_err	=> '',
	   expected_out	=> "0\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-11",
	   args	        => '--eval',
	   resource     => "$cmd \"xx\";\n" ,
	   expected_err	=> '',
	   expected_out	=> "0\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-12",
	   args	        => '--eval',
	   resource     => "$cmd \"23\";\n" ,
	   expected_err	=> '',
	   expected_out	=> "23\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-13",
	   args	        => '--eval',
	   resource     => "$cmd \"aa 23 xx\";\n" ,
	   expected_err	=> '',
	   expected_out	=> "23\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-20",
	   args	        => '--eval',
	   resource     => "$cmd true;\n" ,
	   expected_err	=> '',
	   expected_out	=> "1\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-21",
	   args	        => '--eval',
	   resource     => "$cmd false;\n" ,
	   expected_err	=> '',
	   expected_out	=> "0\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-30",
	   args	        => '--eval',
	   resource     => "$cmd nil;\n" ,
	   expected_err	=> '',
	   expected_out	=> "0\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-31",
	   args	        => '--eval',
	   resource     => "$cmd [22];\n" ,
	   expected_err	=> '',
	   expected_out	=> "1\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-32",
	   args	        => '--eval',
	   resource     => "$cmd [3,3];\n" ,
	   expected_err	=> '',
	   expected_out	=> "2\n" );
}

numeric_tests( "crossref.limit"	        ,  32 );
numeric_tests( "print.align.string"     ,  18 );
numeric_tests( "print.align.comment"    ,  10 );
numeric_tests( "print.align.preamble"   ,  11 );
numeric_tests( "print.align.key"	,  18 );
numeric_tests( "print.align"	        ,  18 );
numeric_tests( "print.indent"	        ,   2 );
numeric_tests( "print.line.length"      ,  77 );
numeric_tests( "print.newline"          ,   1 );
numeric_tests( "rewrite.limit"	        , 512 );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
