#!/usr/local/bin/perl
##*****************************************************************************
## $Id: hyph_de.pm,v 1.1 2010-07-24 05:21:10 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

=head1 NAME

hyph_de.pm - ...

=head1 SYNOPSIS

hyph_de.pm

=head1 DESCRIPTION

=head1 Attributes

=head1 Methods

=head1 AUTHOR

Gerd Neugebauer

=head1 BUGS

=over 4

=item *

...

=back

=cut

#------------------------------------------------------------------------------
package hyph_de;

use strict;
use Exporter;
our @ISA       = qw(Exporter);
our @EXPORT    = qw(hyph);
our @EXPORT_OK = qw(hyph);

use FileHandle;

#------------------------------------------------------------------------------
# Variable:	$VERSION
# Description:	
#
our $VERSION = ('$Revision: 1.1 $ ' =~ m/[0-9.]+/ ? $& : '0.0' );

my %hyph;
my @learned;
my $verbose = 0;

#------------------------------------------------------------------------------
# Function:	hyph
# Arguments:	
# Returns:	
# Description:	
#
sub hyph
{ local $_ = shift;

  if ( not m/^[A-ZÄÖÜ]*$/ and  m/^[A-ZÄÖÜ]/ ) {
    return hyphenateWord(lcfirst($_), 1);
  }
  return hyphenateWord($_);
}

#------------------------------------------------------------------------------
# Function:	hyphenateWord
# Arguments:	
# Returns:	
# Description:	
#
sub hyphenateWord {
  my $word = shift;
  local $_ = $hyph{$word};
  if (defined $_) {
    return ucfirst($_) if $_[0];
    return $_;
  }
  $hyph{$word} = $word;
  push @learned,$word;
  print STDERR "$word\n" if $verbose;
  return ucfirst($word) if $_[0];
  return $word;
}

#------------------------------------------------------------------------------
# Function:	locate
# Arguments:	
# Returns:	
# Description:	
#
sub locate {
  my $file = shift;
  local $_;
  foreach $_ (@INC) {
    return "$_/$file" if -e "$_/$file";
  }
  return undef;
}

#------------------------------------------------------------------------------
# Function:	load
# Arguments:	
# Returns:	
# Description:	
#
sub load {
  my $file = shift;
  local $_;
  if (not defined $file or not -e $file) {
    die ": $file\n" if $_[0]; 
    return;
  }
  my $fd = new FileHandle($file,'r') || die "$file: $!\n";
  while(<$fd>) {
    chomp;
    my $w = lcfirst($_);
    $w 	  =~ s/-//g;
    s/-/&shy;/g;
    $hyph{$w} = $_;
  }
  $fd->close();
}

#------------------------------------------------------------------------------
# Function:	unloadNew
# Arguments:	
# Returns:	
# Description:	
#
sub unloadNew {
  my $file = shift;
  local $_;

  my $fd = new FileHandle($file, 'w') || die "$file: $!\n";
  print $fd <<__EOF__;
#
# WARNING: This file has been generated automatically.
#          It might be overwritten without notification.
#
__EOF__
  foreach $_ (@learned) {
    print $fd $_,"\n" if length($_)>2;
  }
  $fd->close();
}

load(locate('lang.de'),1);
load('langUser.de');
load('lang.de');

1;
##-----------------------------------------------------------------------------
## Local Variables: 
## mode: perl
## End: 
