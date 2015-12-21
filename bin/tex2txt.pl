#!/usr/bin/perl -w
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

=head1 NAME

tex2txt.pl - ...

=head1 SYNOPSIS

tex2txt.pl [-v|--verbose] 

tex2txt.pl [-h|-help]

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

my %macros = (
  'begin'  => sub { return shift; },
  'end'  => sub { return shift; },
  'section'  => sub { return shift; },
  'newpage'  => sub { return shift; },
  'file'  => sub { return shift; },
  'texttt'  => sub { return shift; },
  'emph'  => sub { return shift; },
  'item'  => sub { return shift; },
  '_'  => sub { return shift; },
  '#'  => sub { return shift; },
  '\\'  => sub { return shift; },
  'label'  => sub { return shift; },
  'ref'  => sub { return shift; },
  'tableofcontents'  => sub { return shift; },
  'TeX' => sub { out('TeX'), return shift; },
  'LaTeX' => sub { out('LaTeX'), return shift; },
  'LaTeXe' => sub { out('LaTeX2e'), return shift; },
  'BibTeX' => sub { out('BibTeX'), return shift; },
  'BibTool' => sub { out('BibTool'), return shift; }
    );

use Getopt::Long;
GetOptions("h|help"	=> \&usage,
	   "v|verbose"	=> \$verbose,
	  );
my @contents = ();
while (<>) {
  push @contents,$_;
}

while ($_ = shift @contents) {
  last if m/\\begin{document}/;
}

while ($_ = shift @contents) {
  last if m/\\end{document}/;
  while (m/\\([a-zA-Z]+\s*|.)/) {
    $_	   = $';
    my $cs = $1;
    my $macro = $macros{$cs};
    out($');
    if (defined $macro) {
      $_ = &$macro($_);
    } else {
      print STDERR "*** \\$cs is undefined\n";
    }
  }
  out($_);
}

sub out {
  local $_ = shift;
  s/\s+/ /;
  s/[{}]//;
  print $_;
}

sub scan_arg {
}

package InStream;

sub new {
  bless {}
}

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
