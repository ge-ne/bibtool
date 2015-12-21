#!/usr/bin/perl -w
##*****************************************************************************
## make_version.pl
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

=head1 NAME

make_version.pl - Create the content for config.tex

=head1 SYNOPSIS

make_version.pl [-v|--verbose] 

make_version.pl [-h|-help]

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=back

=cut

use strict;

#------------------------------------------------------------------------------
# Function:	usage
# Arguments:	none
# Returns:	    nothing
# Description:	Print the POD of this file to stderr.
#
sub usage
{ use Pod::Text;
  Pod::Text->new()->parse_from_filehandle(new FileHandle($0,'r'),\*STDERR);
}

#------------------------------------------------------------------------------
# Variable:	$verbose
# Description:	Indicator for verbosity
#
my $verbose = 0;

my $LIBDIR = '/usr/local/lib/BibTool'

use Getopt::Long;
GetOptions("h|help"	=> \&usage,
	   "v|verbose"	=> \$verbose,
	  );

my $version = undef;
@_ 	     = localtime;
my $year = 1900 + $_[5];

while(<>) {
  $version = $1 if m/bibtool_version *= *"([0-9.]*)/;
  $year    = $1 if m/bibtool_year *= *"([0-9]*)/;
}

die "*** Missing version\n" if not defined $version;

print <<__EOF__;
%%********************************************************
%%
%% This file is part of BibTool.
%% It is distributed under the GNU General Public License.
%% See the file COPYING for details.
%%
%% (c) 1995-$year Gerd Neugebauer
%%
%% Net: gene\@gerd-neugebauer.de
%%
%%********************************************************
\\newcommand\\LIBDIR{$LIBDIR}
\\newcommand\\Year{$year}
\\newcommand\\Version{$version}
__EOF__

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
