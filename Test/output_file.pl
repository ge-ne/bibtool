#!/bin/perl -W
#******************************************************************************
# $Id: output_file.pl,v 1.1 2011-11-16 18:51:06 gene Exp $
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

main.pl - Test suite for BibTool main.

=head1 SYNOPSIS

main.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;

use constant OUT_FILE => '_output.bib';


#------------------------------------------------------------------------------
BUnit::run(name => 'output_file_0',
    args         => "--output.file",
    expected_err => <<__EOF__);

output.file
___________^
*** BibTool ERROR: Symbol expected.
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name => 'output_file_1',
    args         => "-q --output.file=".OUT_FILE." x1",
    expected_out => '',
    expected_err => '',
    prepare      => sub { unlink(OUT_FILE) if -e OUT_FILE; },
    check        => sub { if (-e OUT_FILE)  {
                            unlink(OUT_FILE);
			    return 0;
			  }
			  print STDERR "missing ".OUT_FILE."\t";
			  return 1});


#------------------------------------------------------------------------------
BUnit::run(name => '_o_0',
    args         => "-o",
    expected_err => <<__EOF__);

*** BibTool WARNING: Missing output file name
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name => '_o_1',
    args         => "-q -o ".OUT_FILE." x1",
    expected_out => '',
    expected_err => '',
    prepare      => sub { unlink(OUT_FILE) if -e OUT_FILE; },
    check        => sub { if (-e OUT_FILE)  {
                            unlink(OUT_FILE);
			    return 0;
			  }
			  print STDERR "missing ".OUT_FILE."\t";
			  return 1});

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
