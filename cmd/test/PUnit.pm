#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME
PUnit.pm - Driver for BibTool parser test cases

=head1 SYNOPSIS

perl -MPUnit -e "exit all()"

=head1 DESCRIPTION

This is the test driver for unit tests of BibTool 3 parser.

=head1 Attributes

=head1 Methods

=head1 AUTHOR

Gerd Neugebauer

=head1 BUGS

none

=cut

#------------------------------------------------------------------------------
package PUnit;

use strict;
use Exporter;
use base qw(Exporter);
our @EXPORT    = qw(all summary);
our @EXPORT_OK = qw();

use Cwd;
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
our $VERSION = '1.0';

#------------------------------------------------------------------------------
# Variable:	$TEST_PRG
# Description:	
#
our $TEST_PRG = $ENV{'TEST_PRG'} || '../test_t';

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
  my $name    = $a{name};
  my $prepare = $a{prepare};

  if (defined $names{$name}) {
    print STDERR "*** Warning: Multiple test cases named $name\n";
  } else {
    $names{$name} = 1;
  }

  &{$prepare}($name) if defined $prepare;

  local $_ = '';
  $_ 	   = '.' x (32-length($name)) if length($name) < 32;
  out "  ",$name,$_;

  if ($a{ignore}) {
    $ignored++;
    out "ignored $a{ignore}\n";
    return 1;
  }

  my $out  = "$name.out";
  my $err  = "$name.err";
  my $null = "/dev/null";

  my $rsc  = store_file(TEST_RSC, $a{resource}, TEST_RSC);
  my $args = $a{args} || '';

  `$TEST_PRG $rsc $args <$null 1>$out 2>$err`;

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
  my $post      = $a{post};
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
  suites (glob '*.t')
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


  die "*** '$TEST_PRG' executable not found\n" if not -x $TEST_PRG;
  die "*** Current dircetory is not writable\n" if not -w '.';
  die "*** .bibtoolrsc exists in current directory. Aborted\n"
      if -e ".bibtoolrsc";
  die "*** .bibtoolrsc exists in this directory. Aborted \n"
      if -e "$ENV{HOME}/.bibtoolrsc";

  foreach $_ (@a) {
    my $l = length($_);
    $len  = $l if $l> $len;
  }

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
  print "\n";

  foreach $suite (@a) {
    $_ = $suite;
    s/\.t$//;
    printf("%-${len}ssuccess: %3d  ignored: %3d  failure: %3d\n", $_,
	     $summary{$suite}[0], $summary{$suite}[1], $summary{$suite}[2])
	if $verbose;
    $success += $summary{$suite}[0];
    $ignored += $summary{$suite}[1];
    $failure += $summary{$suite}[2];;
  }

  $_ = $success + $failure;
  if ($_ == 0) { $_ = 100 } else { $_ = 100. * $success/$_; }
  printf("%s\n%-${len}ssuccess: %3d  ignored: %3d  failure: %3d\n%${len}ssucess rate: %3.2f%%\n",
	 ('_' x ($len+40)),
	 'TOTAL',
	 $success,
	 $ignored,
	 $failure,
	 '',
	 $_) if $verbose;

  return $failure;
}

#------------------------------------------------------------------------------
# Function:	get_library_path
#
sub get_library_path {
  my $err  = '_lib.err';
  `$TEST_PRG -h 2>$err`;

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
  `$TEST_PRG -h 2>$err`;

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
