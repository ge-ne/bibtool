#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

verbose.t - Test suite for BibTool verbose.

=head1 SYNOPSIS

verbose.t 

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

my @library_path;
my $fs;

{ local $_ = BUnit::get_library_path();
  $_ 	   = '.' if $_ eq 'none';
  if (m/;/) { @library_path = split /;/;
  } else {    @library_path = split /:/;
  }
  if (m/\\/) { $fs = '\\';
  } else {     $fs = '/';
  }
}
my $options = BUnit::get_configuration_options();
my $xampl   = "--- BibTool: Trying .${fs}bib/xampl.bib\n";
$xampl 	    = '' if $options =~ m/kpathsea/;

#------------------------------------------------------------------------------
BUnit::run(name => 'verbose_1',
    resource    => <<__EOF__,
verbose	     =on
__EOF__
	   args	=> 'bib/xampl.bib',
    expected_err => <<__EOF__);
$xampl--- BibTool: Reading bib/xampl.bib
++
*** BibTool WARNING:  (line 29 in .${fs}bib/xampl.bib): 125 non-space characters ignored.
++++++++++++++++++++++++++++++++++--- BibTool: Done with bib/xampl.bib
__EOF__

my $t = '';
foreach $_ (@library_path) {
  $t .= "--- BibTool: Trying $_$fs.bibtoolrsc\n--- BibTool: Trying $_$fs.bibtoolrsc.rsc\n";
}

#------------------------------------------------------------------------------
BUnit::run(name => '_v_1',
    args	=> '-v bib/xampl.bib',
    expected_err => <<__EOF__);
--- BibTool: Trying $ENV{HOME}$fs.bibtoolrsc
--- BibTool: Trying $ENV{HOME}$fs.bibtoolrsc.rsc
$t$xampl--- BibTool: Reading bib/xampl.bib
++
*** BibTool WARNING:  (line 29 in .${fs}bib/xampl.bib): 125 non-space characters ignored.
++++++++++++++++++++++++++++++++++--- BibTool: Done with bib/xampl.bib
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
