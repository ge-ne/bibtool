#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2020 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#*=============================================================================

=head1 NAME

extract_file.t - Test suite for BibTool extract.file.

=head1 SYNOPSIS

extract_file.t 

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally files
*.out and *.err are left if the expected result does not match the
actual result.

=head1 OPTIONS

none

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;use warnings;



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
\\bibdata{bib/xampl_s.bib}
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
BUnit::run(name => '_x_3',
    args     => '-x _xyzzy.aux',
    prepare  => sub {
      my $fd = new FileHandle("_xyzzy.aux",'w') || die "_xyzzy.aux: $!\n";
      print $fd <<__EOF__;
\\citation{whole-collection}
\\bibstyle{alpha}
\\bibdata{bib/xampl_s.bib}
\\relax
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
\\bibdata{bib/xampl_s.bib}
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

#------------------------------------------------------------------------------
BUnit::run(name => 'extract_file_3',
    args => '-- \'extract.file={xyzzy}\'',
    expected_out => '',
    expected_err => <<__EOF__,

*** BibTool ERROR: aux file xyzzy not found.
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name => 'extract_file_4',
    args     => '-- \'extract.file={_xyzzy.aux}\'',
    prepare  => sub {
      my $fd = new FileHandle("_xyzzy.aux",'w') || die "_xyzzy.aux: $!\n";
      print $fd <<__EOF__;
\\citation{whole-collection}
\\bibstyle{alpha}
\\bibdata{bib/xampl_s.bib}
\\relax
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

#------------------------------------------------------------------------------
BUnit::run(name => 'extract_file_5',
    args     => '-- \'extract.file={_xyzzy.aux}\'',
    prepare  => sub {
      my $fd = new FileHandle("_xyzzy.aux",'w') || die "_xyzzy.aux: $!\n";
      print $fd <<__EOF__;
\\citation{a}
\\bibstyle{alpha}
\\bibdata{_test.bib}
__EOF__
      $fd->close();
      $fd = new FileHandle("_test.bib",'w') || die "_test.bib: $!\n";
      print $fd <<__EOF__;
\@string{sss="T" # t}
\@string{t="ttt"#t2}
\@string{t2="ttt"}
\@Article{ a,
  author = 	 sss,
}
__EOF__
      $fd->close();
	   },
    post         => sub {
      unlink('_xyzzy.aux');
      unlink('_test.aux');
	   },
    expected_err => '',
    expected_out => <<__EOF__,
\@STRING{t	= "ttt" # t2 }
\@STRING{t2	= "ttt" }
\@STRING{sss	= "T" # t }

\@Article{	  a,
  author	= sss
}
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name => 'extract_file_6',
    args     => '-- \'extract.file={_xyzzy.aux}\'',
    prepare  => sub {
      my $fd = new FileHandle("_xyzzy.aux",'w') || die "_xyzzy.aux: $!\n";
      print $fd <<__EOF__;
\\citation{a}
\\bibstyle{alpha}
\\bibdata{_test.bib}
\\relax
__EOF__
      $fd->close();
      $fd = new FileHandle("_test.bib",'w') || die "_test.bib: $!\n";
      print $fd <<__EOF__;
\@string{sss="T" # t}
\@string{t="ttt"#t2}
\@string{t2="ttt"}
\@Article{ a,
  author = 	 sss,
}
__EOF__
      $fd->close();
	   },
    post         => sub {
      unlink('_xyzzy.aux');
      unlink('_test.aux');
	   },
    expected_err => '',
    expected_out => <<__EOF__,
\@STRING{t	= "ttt" # t2 }
\@STRING{t2	= "ttt" }
\@STRING{sss	= "T" # t }

\@Article{	  a,
  author	= sss
}
__EOF__
    );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
