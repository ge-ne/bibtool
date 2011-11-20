#!/bin/perl -W
#******************************************************************************
# $Id: bibtex_env_name.t,v 1.1 2011-11-20 15:22:45 gene Exp $
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

bibtex_env_name.t - Test suite for BibTool bibtex.env.name.

=head1 SYNOPSIS

bibtex_env_name.t 

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


#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtex_env_name_0',
	   args         => 'x1',
	   expected_err => "\n*** BibTool WARNING: File x1 not found.\n"
    );

$ENV{BIBINPUTS} = "bib";
#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtex_env_name_1',
	   args         => 'x1',
	   expected_err => ""
    );
delete $ENV{BIBINPUTS};

$ENV{BIBTOOLINPUTS} = "bib";
#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtex_env_name_2',
	   resource	=> "bibtex.env.name={BIBTOOLINPUTS}",
	   args		=> 'x1',
	   expected_err	=> ""
    );
delete $ENV{BIBTOOLINPUTS};

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
