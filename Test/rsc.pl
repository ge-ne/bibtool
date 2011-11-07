#!/bin/perl -W
#******************************************************************************
# $Id: rsc.pl,v 1.2 2011-11-07 18:26:30 gene Exp $
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

rsc.pl - Test suite for BibTool rsc.

=head1 SYNOPSIS

rsc.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name  => 'print_1',
    args	 => '',
    resource 	 => 'print{Hello World!}',
    expected_out => '',
    expected_err => <<EOF,
Hello World!
EOF
    );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
