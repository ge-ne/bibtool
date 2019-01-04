#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2016-2019 Gerd Neugebauer
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

keep_field.t - Test suite for BibTool keep.field.

=head1 SYNOPSIS

keep_field.t 

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
BUnit::run(name => 'keep_field_err_01',
    resource 	 => <<__EOF__,
keep.field{}
__EOF__
    args	 => 'bib/x1.bib',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_err => <<__EOF__


^
*** BibTool ERROR: List of symbols expected.
__EOF__
);

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_err_02',
    resource 	 => <<__EOF__,
keep.field{"abc"}
__EOF__
    args	 => 'bib/x1.bib',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_err => <<__EOF__

"abc"
^
*** BibTool ERROR: List of symbols expected.
__EOF__
);

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_err_03',
    resource 	 => <<__EOF__,
keep.field{title 123}
__EOF__
    args	 => 'bib/x1.bib',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_err => <<__EOF__

title 123
______^
*** BibTool ERROR: Unexpected characters at end of string.
__EOF__
);

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_err_04',
    resource		=> <<__EOF__,
keep.field{title if abc}
__EOF__
    args	 => 'bib/x1.bib',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_err => <<__EOF__

title if abc
____________^
*** BibTool ERROR: Symbol expected.
__EOF__
);

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_err_05',
    resource		=> <<__EOF__,
keep.field{title if abc = }
__EOF__
    args	 => 'bib/x1.bib',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_err => <<__EOF__

title if abc = 
_______________^
*** BibTool ERROR: Symbol expected.
__EOF__
);

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_01',
    resource 	 => <<__EOF__,
keep.field{title}
__EOF__
    bib		 => <<__EOF__,
\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_out => <<__EOF__,

\@Article{	  bibtool,
  title		= {The BibTool Manual}
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual}
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_02',
    resource 	 => <<__EOF__,
keep.field{{title author}}
__EOF__
    bib		 => <<__EOF__,
\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_out => <<__EOF__,

\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer}
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_11',
    resource    => <<__EOF__,
keep.field{title}
keep.field{author if \$type = "article"}
__EOF__
    bib		 => <<__EOF__,
\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_out => <<__EOF__,

\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer}
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual}
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_21',
    resource 	 => <<__EOF__,
keep.field{*}
__EOF__
    bib		 => <<__EOF__,
\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_out => <<__EOF__,

\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_22',
    resource	=> <<__EOF__,
keep.field{* if \$type = article}
__EOF__
    bib		 => <<__EOF__,
\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_out => <<__EOF__,

\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'keep_field_23',
    resource	=> <<__EOF__,
keep.field{{abc *} if \$type = article}
__EOF__
    bib		 => <<__EOF__,
\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_out => <<__EOF__,

\@Article{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2018
}

\@Manual{	  bibtool2
}
__EOF__
    expected_err => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
