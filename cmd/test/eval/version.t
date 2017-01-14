#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2017 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

version.t - Test suite for BibTool version builtin.

=head1 SYNOPSIS

version.t

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
use FileHandle;

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
# Function:	retrieveVersion
# Arguments:	
# Description:	
#
sub retrieveVersion
{ local $_;
  my $fd = new FileHandle('../../version.c' ,'r') || die " File not found\n";
  while (<$fd>)
  { if (m/char \* bibtool_version = "([^\"]*)";/)
    { $fd->close();
      return $1;
    }
  }
  die "*** Version not found.\n";
}

my $vers = retrieveVersion();


#------------------------------------------------------------------------------
BUnit::run(name         => 'version-1',
	   args	        => '--eval',
	   resource     => "version;" ,
	   expected_err => '',
	   expected_out => "\"$vers\"\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'version-err-1',
	   args	        => '--eval',
	   resource     => "version = \"x\";" ,
	   expected_err => "\n*** BibTool ERROR: Parameter version is immutable\n",
	   expected_out => '');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
