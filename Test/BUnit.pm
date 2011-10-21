#!/bin/perl -W
#******************************************************************************
# $Id: BUnit.pm,v 1.4 2011-10-21 19:10:42 gene Exp $
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
BUnit.pm - Driver for BibTool test cases

=head1 SYNOPSIS

perl -MBUnit -e "exit summary(qw(a b c))"

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
package BUnit;

use strict;
use Exporter;
our @ISA       = qw(Exporter);
our @EXPORT    = qw(run_test summary);
our @EXPORT_OK = qw();

use FileHandle;

use constant TEST_RSC =>'_test.rsc';
use constant TEST_BIB =>'_test.bib';

#------------------------------------------------------------------------------
# Variable:	$verbose
# Description:	
#
our $verbose = undef;

#------------------------------------------------------------------------------
# Variable:	$VERSION
# Description:	
#
our $VERSION = ('$Revision: 1.4 $ ' =~ m/[0-9.]+/ ? $& : '0.0' );

#------------------------------------------------------------------------------
# Variable:	$BIBTOOL
# Description:	
#
our $BIBTOOL = '../bibtool';

#------------------------------------------------------------------------------
# Function:	out
#
sub out (@) {
  print STDOUT @_;
  print STDERR @_;
}

#------------------------------------------------------------------------------
# Function:	run
#
sub run {
  my %a		   = @_;
  my $name	   = $a{name};
  my $prepare      = $a{prepare};

  &{$prepare}($name) if defined $prepare;

  out sprintf("%-23s","$name");

  if ($a{ignore}) {
    out "\tignored\n";
    return;
  }

  my $out  = "$name.out";
  my $err  = "$name.err";
  my $null = "/dev/null";

  my $rsc = store_file(TEST_RSC, $a{resource}, "-r ".TEST_RSC);
  my $bib = store_file(TEST_BIB, $a{bib}, TEST_BIB);
  local $_ = `$BIBTOOL $rsc $a{args} $bib <$null 1>$out 2>$err`;

  if ( run_check($name, $a{check}) +
       check($a{expected_out}, $out, 'out', $a{fct_out}) +
       check($a{expected_err}, $err, 'err', $a{fct_err}) ) {
    out "\tfail\n"
  } else {
    out "\tok\n"
  }
  unlink(TEST_RSC) if -e TEST_RSC;
  unlink(TEST_BIB) if -e TEST_BIB;
}

#------------------------------------------------------------------------------
# Function:	store_file
#
sub store_file  {
  my ($file,$content, $ret) = @_;
  return '' if not defined $content;

  local $_ = new FileHandle($file,'w') || die "$file: $!\n";
  print $_ $content;
  $_->close();
  return $ret;
}

#------------------------------------------------------------------------------
# Function:	run_check
#
sub run_check {
  my ($name, $check) = @_;
  return 0 if not defined $check;
  return &{$check}($name);
}

#------------------------------------------------------------------------------
# Function:	check
#
sub check {
  my ($expected, $file, $type, $fct) = @_;

  if (not defined $expected) {
    unlink $file;
    return 0
  }

  my $fd       = new FileHandle($file,'r') || die("$file: $!\n");
  local $/     = undef;
  local $_     = <$fd>;
  $fd->close();

  $_ = &$fct($_) if defined $fct;

  if ($_ ne $expected) {
    out "\n\tdifference in $type;";
    return 1;
  }
  unlink $file;
  return 0;
}

#------------------------------------------------------------------------------
# Function:	summary
#
sub summary {
  my $quiet    = 0;
  my $g_ok     = 0;
  my $g_ignore = 0;
  my $g_fail   = 0;

  print "\n";

  foreach my $f (@_) {
    my $file = $f;
    $file      =~ s/\.[a-z]*$//;
    $file     .= '.log';
    my $ok     = 0;
    my $fail   = 0;
    my $ignore = 0;
    my $fd     = new FileHandle($file) || die "$file: $!\n";
    while(<$fd>) {
      if (m/\tok/) { $ok++; }
      elsif (m/\tfail/) { $fail++; }
      elsif (m/\tignore/) { $ignore++; }
    }
    $fd->close();
    if (not $quiet) {
      local $_ = $file;
      s/\.[a-z]*$//g;
      printf("%-14ssuccess: %3d\tignored: %3d\tfailure: %3d\n", $_,
	     $ok, $ignore, $fail);
    }
    $g_ok     += $ok;
    $g_fail   += $fail;
    $g_ignore += $ignore;
  }
  printf("\nTOTAL         success: %3d\tignored: %3d\tfailure: %3d\t sucess rate: %3.1f%%\n",
	 $g_ok,
	 $g_ignore,
	 $g_fail,
	 100.*$g_ok/($g_ok+$g_ignore+$g_fail)) if not $quiet;
  return $g_fail;
}

#------------------------------------------------------------------------------
# Function:	suites
#
sub suites {
  local $_;

  foreach $_ (@_) {
    eval $_;
  }
  return summary(@_);
}

1;
#
