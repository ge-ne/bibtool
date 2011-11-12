#!/bin/perl -W
#******************************************************************************
# $Id: extract_file.pl,v 1.2 2011-11-12 14:45:01 gene Exp $
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

extract_file.pl - Test suite for BibTool extract.file.

=head1 SYNOPSIS

extract_file.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name => '_x_1',
    args => '-x xyzzy',
    expected_out => '',
    expected_err => <<__EOF__,

*** BibTool ERROR: aux file xyzzy not found.
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name => '_x_2',
    args     => '-x _xyzzy.aux',
    prepare  => sub {
      my $fd = new FileHandle("_xyzzy.aux",'w') || die "_xyzzy.aux: $!\n";
      print $fd <<__EOF__;
\\citation{whole-collection}
\\bibstyle{alpha}
\\bibdata{xampl_s.bib}
__EOF__
      $fd->close();
	   },
    post         => sub {
      unlink('_xyzzy.aux');
	   },
    expected_err => '',
    expected_out => <<__EOF__,

\@Book{		  whole-collection,
  title		= ""
}
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name => 'extract_file_1',
    args => '-- \'extract.file={xyzzy}\'',
    expected_out => '',
    expected_err => <<__EOF__,

*** BibTool ERROR: aux file xyzzy not found.
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name => 'extract_file_2',
    args     => '-- \'extract.file={_xyzzy.aux}\'',
    prepare  => sub {
      my $fd = new FileHandle("_xyzzy.aux",'w') || die "_xyzzy.aux: $!\n";
      print $fd <<__EOF__;
\\citation{whole-collection}
\\bibstyle{alpha}
\\bibdata{xampl_s.bib}
__EOF__
      $fd->close();
	   },
    post         => sub {
      unlink('_xyzzy.aux');
	   },
    expected_err => '',
    expected_out => <<__EOF__,
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX" }

\@Book{		  whole-collection,
  title		= ""
}
__EOF__
    );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
