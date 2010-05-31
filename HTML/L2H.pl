#!d:/Programme/Perl/bin/perl -w
##*****************************************************************************
## $Id: L2H.pl,v 1.8 2010-05-31 04:02:43 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

use File::Basename;
use File::Copy;
use lib dirname($0);
use lib dirname($0).'/lib';

use strict;
use L2H;
use L2H_file;

sub usage
{ print STDERR <<__EOF__;
$0 [options] [files]
	Translate (La)TeX to HTML.
	The following options are supported:
	-author=<s>	Set the author information.
	-debug <s>	Set the debug flags.
	-dir=<s>	Set the base dir for HTML files.
	-email=<s>	Set the email address for the HTML pages.
	-ext=<s>	Set the extension for the HTML pages.
			The default is '.html'.
	-h
	-help		Show this information.
	-load <s>	Load the given file with macro definitions.
	-main=<s>	Set the name for the topmost HTML file.
	-prefix=<s>	Set the prefix for the generated HTML files.
	-title=<s>	Set the title information for the HTML pages.
	-v	
	-verbose	Turn on verbose output about file operations.
	-year=<s>	Set the copyright year.
__EOF__
    exit(0);
}

my $trans = new L2H_file;

$trans->load('LaTeX.lh');
$trans->load('BibTool.lh');
$trans->load('Changes.lh');

my $verbose = 0;
my $debug   = 0;
my @debug   = ();
my %debug_map = ( all     => 255,
		  verbose => 1,
		  files   => 2,
		  passes  => 128,
		);
my $profile = 'profile';
my $dirname = $trans->opt('dirname');
my $author  = $trans->opt('author');
my $title   = $trans->opt('title');
my $prefix  = $trans->opt('prefix');
my $email   = $trans->opt('email');
my $main    = $trans->opt('main');
my $year    = $trans->opt('year');
my $ext	    = $trans->opt('ext');
my $nocopy  = 0;

use Getopt::Long;
GetOptions ('author=s'	=> \$author,
	    'd=s'	=> \@debug,
	    'debug=s'	=> \@debug,
	    'dir=s'	=> \$dirname,
	    'email=s'	=> \$email,
	    'ext=s'	=> \$ext,
	    'h|help'	=> \&usage,
	    'load=s'	=> \&load,
	    'main=s'	=> \$main,
	    'nocopy'	=> \$nocopy,
	    'prefix=s'	=> \$prefix,
	    'profile=s'	=> \$profile,
	    'title=s'	=> \$title,
	    'v|verbose'	=> \$verbose,
	    'year'	=> \$year,
	   );

$trans->set_opt('dirname', $dirname);
$trans->set_opt('author', $author);
$trans->set_opt('prefix', $prefix);
$trans->set_opt('title', $title);
$trans->set_opt('email', $email);
$trans->set_opt('main', $main);
$trans->set_opt('year', $year);
$trans->set_opt('ext', $ext);

foreach $_ (@debug)
{ my $k;
  foreach $k (split(/,/,$_)) { $debug |= $debug_map{$k}; }
}
$debug |= 1 if $verbose;

$trans->{'debug'} = $debug;

{ local $/ = undef;
  my $contents;
  while (<>) { $contents .= $_; }
  $_ = $contents;
}

print STDERR "--- Pass 1\n" if $debug > 1;

$trans->restart();
$trans->LaTeX2HTML($_);
$trans->redirect(undef, 1);

print STDERR "--- Pass 2\n" if $debug >  1;
print STDERR "\n"           if $debug == 1;

$trans->{'debug'} &= 1 if ($debug & 128) == 0;
$trans->restart('message:p' => 1);
$trans->LaTeX2HTML($_);
$trans->redirect(undef, 1);
$trans->make_nav();

print STDERR "\n" if $debug & 1;

if (not $nocopy)
{
  foreach $_ (glob("$profile/*.*"))
  { my $f = $_;
    s|.*/||;
    copy($f, $dirname.'/'.$_);
    print STDERR "+" if $verbose;
  }
  
  print STDERR "\n" if $verbose;
}

exit(0);

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
