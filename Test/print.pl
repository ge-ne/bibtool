#!/bin/perl -W
#******************************************************************************
# $Id: print.pl,v 1.3 2011-11-13 08:26:55 gene Exp $
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

print.pl - Test suite for BibTool print.

=head1 SYNOPSIS

print.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name  => 'print_0',
    args	 => '',
    resource 	 => 'print',
    expected_out => '',
    expected_err => <<__EOF__,

*** BibTool ERROR:  (line 2 in ./_test.rsc): Unterminated value
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_1',
    args	 => '',
    resource 	 => 'print{Hello World!}',
    expected_out => '',
    expected_err => <<__EOF__,
Hello World!
__EOF__
    );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
