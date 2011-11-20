#!/bin/perl -W
#******************************************************************************
# $Id: quiet.t,v 1.1 2011-11-20 15:22:45 gene Exp $
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

quiet.t - Test suite for BibTool quiet.

=head1 SYNOPSIS

quiet.t 

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
BUnit::run(name         => 'quiet_1',
	   resource    	=> 'quiet=on',
	   args		=> 'bib/xampl.bib',
	   expected_err	=> '');

#------------------------------------------------------------------------------
BUnit::run(name 	=> '_q_1',
	   args		=> '-q bib/xampl.bib',
	   expected_err	=> '');

#------------------------------------------------------------------------------
BUnit::run(name 	=> '_q_2',
	   args		=> '-q xyzzy',
	   expected_out	=> '',
	   expected_err	=> '');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
