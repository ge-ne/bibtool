#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2020 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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
use BUnit;use warnings;



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


my $use_kpathsea = undef;
$use_kpathsea 	 = "since only applicable without kpathsea"
    if BUnit::get_configuration_options() =~ m/kpathsea/;

$ENV{BIBTOOLINPUTS} = "bib";
#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtex_env_name_2',
	   ignore 	=> $use_kpathsea,
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
