#!/bin/perl -W
#******************************************************************************
# $Id: macros.pl,v 1.1 2011-09-25 13:41:53 gene Exp $
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

macros.pl - Test suite for BibTool macros.

=head1 SYNOPSIS

macros.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name         => 'macros_1',
	   args         => '-m - -o null.out xampl.bib',
	   expected_out => <<EOF,
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }
EOF
    expected_err => <<EOF,

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.
EOF
   check => sub {unlink('null.out'); return 0;}
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
