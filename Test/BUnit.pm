#!/bin/perl -W
#******************************************************************************
# $Id: BUnit.pm,v 1.11 2011-11-16 18:26:13 gene Exp $
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

perl -MBUnit -e "exit all()"

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
our @EXPORT    = qw(all summary);
our @EXPORT_OK = qw();

use FileHandle;

use constant TEST_RSC =>'_test.rsc';
use constant TEST_BIB =>'_test.bib';

#------------------------------------------------------------------------------
# Variable:	$verbose
# Description:	
#
our $verbose = 1;

#------------------------------------------------------------------------------
# Variable:	$VERSION
# Description:	
#
our $VERSION = ('$Revision: 1.11 $ ' =~ m/[0-9.]+/ ? $& : '0.0' );

#------------------------------------------------------------------------------
# Variable:	$BIBTOOL
# Description:	
#
our $BIBTOOL = '../bibtool';

#------------------------------------------------------------------------------
# Variable:	%summary
# Description:	
#
our %summary = ();

our ($success,$ignored,$failure);

#------------------------------------------------------------------------------
# Variable:	$suite
# Description:	
#
our $suite = '';

#------------------------------------------------------------------------------
# Function:	out
#
sub out (@) {
  print STDERR @_ if $verbose;
}

#------------------------------------------------------------------------------
# Function:	run
#
sub run {
  my %a		   = @_;
  my $name	   = $a{name};
  my $prepare      = $a{prepare};

  &{$prepare}($name) if defined $prepare;

  local $_ = '';
  $_ 	   = '.' x (32-length($name)) if length($name) < 32;
  out "  ",$name,$_;

  if ($a{ignore}) {
    $ignored++;
    out "ignored\n";
    return;
  }

  my $out  = "$name.out";
  my $err  = "$name.err";
  my $null = "/dev/null";

  my $rsc  = store_file(TEST_RSC, $a{resource}, "-r ".TEST_RSC);
  my $bib  = store_file(TEST_BIB, $a{bib}, TEST_BIB);
  my $args = $a{args} || '';
  local $_ = `$BIBTOOL $rsc $args $bib <$null 1>$out 2>$err`;

  if ( run_check($name, $a{check}) +
       check($a{expected_out}, $out, 'out', $a{fct_out}) +
       check($a{expected_err}, $err, 'err', $a{fct_err}) ) {
    $failure++;
    out "fail\n"
  } else {
    $success++;
    out "ok\n"
  }
  unlink(TEST_RSC) if -e TEST_RSC;
  unlink(TEST_BIB) if -e TEST_BIB;
  my $post      = $a{post};
  &{$post}($name) if defined $post;

  return 1;
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

  my $fd   = new FileHandle($file,'r') || die("$file: $!\n");
  local $/ = undef;
  local $_ = <$fd>;
  $fd->close();

  $_ = &$fct($_) if defined $fct;

  if ($_ ne $expected) {
    out "\n***\tdifference in $type; ";
    return 1;
  }
  unlink $file;
  return 0;
}

#------------------------------------------------------------------------------
# Function:	all
#
sub all {
  suites (glob '*.pl')
}

#------------------------------------------------------------------------------
# Function:	suites
#
sub suites {
  local $_;
  my @a	  = sort(@_);
  my $len = 6;

  foreach $_ (@a) {
    my $l = length($_);
    $len  = $l if $l> $len;
  }

  foreach $_ (@a) {
    $success = 0;
    $ignored = 0;
    $failure = 0;
    $suite   = $_;
    $suite   =~ s/.pl$//;
#    out "$suite:\n";
    my $ret = do "$_";
    unless($ret) {
      if ($@) {                   warn "couldn't parse $_: $@\n"
      } elsif(not defined $ret) { warn "couldn't do $_: $!\n"
      } else {                    warn "couldn't run $_\n"
      }
    }
    $summary{$_} = [$success, $ignored, $failure];
  }

  $success = 0;
  $ignored = 0;
  $failure = 0;
  print "\n";

  foreach $suite (@a) {
    $_ = $suite;
    s/\.pl$//;
    printf("%-${len}ssuccess: %3d  ignored: %3d  failure: %3d\n", $_,
	     $summary{$suite}[0], $summary{$suite}[1], $summary{$suite}[2])
	if $verbose;
    $success += $summary{$suite}[0];
    $ignored += $summary{$suite}[1];
    $failure += $summary{$suite}[2];;
  }

  $_ = $success + $ignored + $failure;
  if ($_ == 0) { $_ = 100 } else { $_ = 100. * $success/$_; }
  printf("\n%-${len}ssuccess: %3d  ignored: %3d  failure: %3d  sucess rate: %3.1f%%\n",
	 'TOTAL:',
	 $success,
	 $ignored,
	 $failure,
	 $_) if $verbose;

  return $failure;
}

1;
#
