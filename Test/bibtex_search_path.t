#!/bin/perl -W
#******************************************************************************
# $Id: bibtex_search_path.t,v 1.1 2011-11-20 15:22:45 gene Exp $
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

bibtex_search_path.t - Test suite for BibTool bibtex.search.path.

=head1 SYNOPSIS

bibtex_search_path.t 

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
BUnit::run(name         => 'bibtex_search_path_1',
	   resource	=> "bibtex.search.path={.:bib}",
	   args		=> 'x1.bib',
	   expected_err	=> ""
    );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
