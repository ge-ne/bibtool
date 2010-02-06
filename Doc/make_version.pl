#!/usr/bin/perl -w
##*****************************************************************************
## $Id: make_version.pl,v 1.2 2010-02-06 10:50:25 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

=head1 NAME

make_version.pl - ...

=head1 SYNOPSIS

make_version.pl [-v|--verbose] 

make_version.pl [-h|-help]

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=head1 BUGS

=over 4

=item *

...

=back

=cut

use strict;

#------------------------------------------------------------------------------
# Function:	usage
# Arguments:	
# Returns:	
# Description:	
#
sub usage
{ use Pod::Text;
  Pod::Text->new()->parse_from_filehandle(new FileHandle($0,'r'),\*STDERR);
}

#------------------------------------------------------------------------------
# Variable:	$verbose
# Description:	
#
my $verbose = 0;

use Getopt::Long;
GetOptions("h|help"	=> \&usage,
	   "v|verbose"	=> \$verbose,
	  );

my $version = undef;
@_ 	    = localtime;
my $year    = 1900 + $_[5];

while(<>) {
  $version = $1 if m/bibtool_version *= *"([0-9.]*)";/;
  $year = $1 if m/\$Id: make_version.pl,v 1.2 2010-02-06 10:50:25 gene Exp $/;
}

die "Missing version" if not defined $version;

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
\\newcommand\\Year{$year}
\\newcommand\\Version{$version}
__EOF__

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
