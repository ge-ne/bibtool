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

rsc_string.t - Test suite for the BibTool built-in string parameters.

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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
# Function:	string_tests
# Arguments:	
# Description:	
#
sub string_tests
{ my $cmd    = shift;
  my $value  = shift;
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-1",
	   args		=> '--eval',
	   resource	=> "$cmd;\n",
	   expected_err	=> '',
	   expected_out	=> "\"$value\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-2",
	   args	        => '--eval',
	   resource     => "$cmd \"\"; $cmd;\n" ,
	   expected_err => '',
	   expected_out => "\"\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-3",
	   args	        => '--eval',
	   resource     => "$cmd \"1\"; $cmd;\n" ,
	   expected_err	=> '',
	   expected_out	=> "\"1\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-10",
	   args	        => '--eval',
	   resource     => "$cmd true;\n" ,
	   expected_err	=> '',
	   expected_out	=> "\"true\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-11",
	   args	        => '--eval',
	   resource     => "$cmd false;\n" ,
	   expected_err	=> '',
	   expected_out	=> "\"false\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-20",
	   args	        => '--eval',
	   resource     => "$cmd 0;\n" ,
	   expected_err	=> '',
	   expected_out	=> "\"0\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-21",
	   args	        => '--eval',
	   resource     => "$cmd 123;\n" ,
	   expected_err	=> '',
	   expected_out	=> "\"123\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$cmd-30",
	   args	        => '--eval',
	   resource     => "$cmd nil;\n" ,
	   expected_err	=> '',
	   expected_out	=> "\"\"\n" );
}

string_tests( "bibtex.env.name"	         , "BIBINPUTS" ); 
string_tests( "bibtex.search.path"       , "");
string_tests( "dir.file.separator"       , "/" );
string_tests( "env.separator"	         , ":" ); 
string_tests( "print.entry.types"        , "pisnmac");
string_tests( "print.deleted.prefix"     , "###"   );
string_tests( "select.by.string.ignored" , "{}\\\\[] "); 
string_tests( "select.fields"	         , "\$key"  ); 

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
