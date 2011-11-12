#!/bin/perl -W
#******************************************************************************
# $Id: extract_file.pl,v 1.1 2011-11-12 14:06:15 gene Exp $
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

tex_aux.pl - Test suite for BibTool tex_aux.

=head1 SYNOPSIS

tex_aux.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name => '_x_1',
    args => '-x xyzzy',
    expected_out => '',
    expected_err => <<EOF,

*** BibTool ERROR: aux file xyzzy not found.
EOF
    );

#------------------------------------------------------------------------------
BUnit::run(name => 'extract_file_1',
    args => '-- \'extract.file={xyzzy}\'',
    expected_out => '',
    expected_err => <<EOF,

*** BibTool ERROR: aux file xyzzy not found.
EOF
    );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
