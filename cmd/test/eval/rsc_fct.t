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

rsc_fct.t - Test suite for the BibTool built-in function-backed parameters.

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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
BUnit::run(name       => "input-1",
	   args		=> '--eval',
	   resource	=> "input \"a.bib\";input;\n",
	   expected_err	=> '',
	   expected_out	=> "[\"a.bib\"]\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "input-2",
	   args		=> '--eval',
	   resource	=> "input {a.bib};input;\n",
	   expected_err	=> '',
	   expected_out	=> "[\"a.bib\"]\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "macro.file-1",
	   args		=> '--eval',
	   resource	=> "macro.file \"a.bib\";\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "macro.file-2",
	   args		=> '--eval',
	   resource	=> "macro.file \"a.bib\";macro.file;\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "macro.file-3",
	   args		=> '--eval',
	   resource	=> "macro.file {a.bib};macro.file;\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
