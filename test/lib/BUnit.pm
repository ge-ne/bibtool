#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2016 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME
BUnit.pm - Driver for BibTool test cases

=head1 SYNOPSIS

perl -MBUnit -e "exit all()"

=head1 DESCRIPTION

This is the test driver for unit tests of BibTool.

=head1 Attributes

=head1 Methods

=head1 AUTHOR

Gerd Neugebauer

=head1 BUGS

none

=cut

#------------------------------------------------------------------------------
package BUnit;

use strict;
use Exporter;
use base qw(Exporter);
our @EXPORT    = qw(all summary run);
our @EXPORT_OK = qw();

use Cwd;
use FileHandle;

use Time::HiRes qw/gettimeofday/;

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
our $VERSION = '1.17';

#------------------------------------------------------------------------------
# Variable:	$BIBTOOL
# Description:	
#
our $BIBTOOL = $ENV{'BIBTOOL_PRG'} || '../bibtool';

#------------------------------------------------------------------------------
# Variable:	$name_prefix
# Description:	
#
our $name_prefix = '';

#------------------------------------------------------------------------------
# Variable:	%summary
# Description:	
#
our %summary = ();

#------------------------------------------------------------------------------
# Variable:	%id
# Description:	
#
our %names = ();

our ($success, $ignored, $failure);

#------------------------------------------------------------------------------
# Function:	out
#
sub out (@) {
  print @_ if $verbose;
}

#------------------------------------------------------------------------------
# Function:	run
#
sub run {
  my %a	      = @_;
  my $name    = $name_prefix . $a{name};
  my $prepare = $a{prepare};

  if (defined $names{$name}) {
    print STDERR "*** Warning: Multiple test cases named $name\n";
  } else {
    $names{$name} = 1;
  }

  &{$prepare}($name) if defined $prepare;

  local $_ = '';
  $_ 	   = '.' x (40-length($name)) if length($name) < 40;
  out "  ",$name,$_;

  if ($a{ignore}) {
    $ignored++;
    out "ignored $a{ignore}\n";
    return 1;
  }

  my $out  = "$name.out";
  my $err  = "$name.err";
  my $null = "/dev/null";

  my $args = $a{args} || '';
  my $rsc  = store_file(TEST_RSC, $a{resource}, "-r ".TEST_RSC);
  my $bib  = store_file(TEST_BIB, $a{bib}, TEST_BIB) if $a{bib};
  $bib 	   = '' if not $bib;

  `$BIBTOOL $rsc $args $bib <$null 1>$out 2>$err`;

  if ( run_check($name, $a{check}) +
       check($a{expected_out}, $out, 'out', $a{fct_out}) +
       check($a{expected_err}, $err, 'err', $a{fct_err}) ) {
    $failure++;
    out "\n\t\t\t\t  fail\n"
  } else {
    $success++;
    out "ok\n"
  }
  unlink(TEST_RSC) if -e TEST_RSC;
  unlink(TEST_BIB) if -e TEST_BIB;
  my $post = $a{post};
  &{$post}($name) if defined $post;

  return 1;
}

#------------------------------------------------------------------------------
# Function:	store_file
#
sub store_file  {
  my ($file, $content, $ret) = @_;
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

  if (defined $expected) {
    my $fd   = new FileHandle($file,'r') || die("$file: $!\n");
    local $/ = undef;
    local $_ = <$fd>;
    $fd->close();
    
    $_ = &$fct($_) if defined $fct;
    
    if ($_ ne $expected) {
      my $fd = new FileHandle("$file-expected",'w') || die("$file-expected: $!\n");
      print $fd $expected;
      $fd->close();
      print STDERR "\n***\tSee actual $type in $file; " if $verbose;
      return 1;
    }
  }
  unlink $file;
  return 0;
}

#------------------------------------------------------------------------------
# Function:	all
#
sub all {
  suites (glob '*.t */*.t')
}

#------------------------------------------------------------------------------
# Function:	suites
#
sub suites {
  local $_;
  my @a	  = sort(@_);
  my $len = 6;
  my $suite;

  $ENV{HOME} = getcwd;

  die "*** '$BIBTOOL' executable not found\n" if not -x $BIBTOOL;
  die "*** Current dircetory is not writable\n" if not -w '.';
  die "*** .bibtoolrsc exists in current directory. Aborted\n"
      if -e ".bibtoolrsc";
  die "*** .bibtoolrsc exists in this directory. Aborted \n"
      if -e "$ENV{HOME}/.bibtoolrsc";

  foreach $_ (@a) {
    my $l = length($_);
    $len  = $l if $l > $len;
  }

  my $time = gettimeofday; 

  foreach $_ (@a) {
    $success = 0;
    $ignored = 0;
    $failure = 0;
    $suite   = $_;
    $suite   =~ s/\.t$//;

    my $ret = do "$_";
    unless($ret) {
      if ($@) {                   warn "couldn't parse $_: $@\n"
      } elsif(not defined $ret) { warn "couldn't do $_: $!\n"
      } else {                    warn "couldn't run $_\n"
      }
      $failure++;
    }
    $summary{$_} = [$success, $ignored, $failure];
  }

  $success = 0;
  $ignored = 0;
  $failure = 0;
  printf("\n%-${len}s  success ignored failure\n", '') if $verbose;

  foreach $suite (@a) {
    $_ = $suite;
    s/\.t$//;
    printf("%-${len}s%7d %7d %7d\n", $_,
	     $summary{$suite}[0], $summary{$suite}[1], $summary{$suite}[2])
	if $verbose;
    $success += $summary{$suite}[0];
    $ignored += $summary{$suite}[1];
    $failure += $summary{$suite}[2];;
  }

  $time = gettimeofday - $time;

  my $no = $success + $failure;
  if ($no == 0) { $_ = 100 }
  else { $_ = 100. * $success/$no; }

  printf("%s\n%-${len}s%7d %7d %7d\nSuccess rate: %3.2f%%\n",
	 ('_' x ($len+40)),
	 'TOTAL',
	 $success,
	 $ignored,
	 $failure,
	 $_) if $verbose;
  printf("Run time:     %1.2fs\tAverage: %1.0fms\n\n",
	 $time, $time*1000/$no) if $verbose;

  return $failure;
}

#------------------------------------------------------------------------------
# Function:	get_library_path
#
sub get_library_path {
  my $err  = '_lib.err';
  `$BIBTOOL -h 2>$err`;

  my $library_path;
  local $_;
  my $fd = new FileHandle($err) || die "$err: $!\n";
  while(<$fd>) {
    $library_path = $1 if m/^Library path: (.*)/;
  }
  $fd->close();
  unlink($err);
  return $library_path;
}

#------------------------------------------------------------------------------
# Function:	get_configuration_options
#
sub get_configuration_options {
  my $err  = '_lib.err';
  `$BIBTOOL -h 2>$err`;

  my $options;
  local $_;
  my $fd = new FileHandle($err) || die "$err: $!\n";
  while(<$fd>) {
    $options = $1 if m/^Special configuration options: (.*)/;
  }
  $fd->close();
  unlink($err);
  return $options;
}

#------------------------------------------------------------------------------
1;
#
