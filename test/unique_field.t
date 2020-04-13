#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2020 Gerd Neugebauer
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

unique_field.t - Test suite for BibTool unique.field.

=head1 SYNOPSIS

unique_field.t 

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
use warnings;
use BUnit;

#------------------------------------------------------------------------------
BUnit::run(name     => 'unique_field_1',
	   resource => <<__EOF__,
	   unique.field {\$key}
__EOF__
	   bib	    => <<__EOF__,
\@Manual{BibTool-a,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@Manual{BibTool-b,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@ARTICLE{article-minimal,
   author = {L[eslie] A. Aamport},
   title = {The Gnats and Gnus Document Preparation System},
   journal = {\\mbox{G-Animal\'s} Journal},
   year = 1986
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'unique_field_10',
	   resource => <<__EOF__,
	   unique.field {\$key}
__EOF__
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@ARTICLE{article-minimal,
   author = {L[eslie] A. Aamport},
   title = {The Gnats and Gnus Document Preparation System},
   journal = {\\mbox{G-Animal\'s} Journal},
   year = 1986
}
__EOF__
    expected_err => "*** BibTool WARNING (line 1 in _test.bib) and (line 6 in _test.bib): field `\$key' is not unique: bibtool\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'unique_field_11',
	   resource => <<__EOF__,
	   unique.field {title}
__EOF__
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@ARTICLE{article-minimal,
   author = {L[eslie] A. Aamport},
   title = {The Gnats and Gnus Document Preparation System},
   journal = {\\mbox{G-Animal\'s} Journal},
   year = 1986
}

__EOF__
    expected_err => "*** BibTool WARNING (line 1 in _test.bib) and (line 6 in _test.bib): field `title' is not unique: {BibTool}\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'unique_field_12',
	   resource => <<__EOF__,
	   unique.field {\$sortkey}
	   sort.format{%s(author)}
__EOF__
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@ARTICLE{article-minimal,
   author = {L[eslie] A. Aamport},
   title = {The Gnats and Gnus Document Preparation System},
   journal = {\\mbox{G-Animal\'s} Journal},
   year = 1986
}
__EOF__
    expected_err => "*** BibTool WARNING (line 1 in _test.bib) and (line 6 in _test.bib): field `\$sortkey' is not unique: Gerd-Neugebauer\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'unique_field_13',
	   resource => <<__EOF__,
	   unique.field {\$sortkey}
__EOF__
	   bib	    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2019"
}
\@ARTICLE{article-minimal,
   author = {L[eslie] A. Aamport},
   title = {The Gnats and Gnus Document Preparation System},
   journal = {\\mbox{G-Animal\'s} Journal},
   year = 1986
}
__EOF__
    expected_err => "*** BibTool WARNING (line 1 in _test.bib) and (line 6 in _test.bib): field `\$sortkey' is not unique: bibtool\n"
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
