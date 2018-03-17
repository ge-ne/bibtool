#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2018 Gerd Neugebauer
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

tex_define.t - Test suite for BibTool tex.define.

=head1 SYNOPSIS

tex_define.t

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally files
*.out and *.err are left if the expected result does not match the
actual result.

=head1 OPTIONS

none

=head1 AUTHOR

Gerd Neugebauer

=head1 BUGS

=over 4

=item *

...

=back

=cut

use strict;
use BUnit;

#------------------------------------------------------------------------------
BUnit::run(name         => 'tex_define_0',
	   resource	=> <<__EOF__ ,
key.format=short
__EOF__
	   bib 	        => <<__EOF__,
\@Misc{		  thor,
  author	= "A. U. Thor",
  title		= "X\\TeX{} rulez"
}
__EOF__
	   expected_out => <<__EOF__ );

\@Misc{		  thor:x,
  author	= "A. U. Thor",
  title		= "X\\TeX{} rulez"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'tex_define_1',
	   resource	=> <<__EOF__ ,
tex.define = {\\TeX=TeX}
key.format=short
__EOF__
	   bib 	        => <<__EOF__,
\@Misc{		  thor,
  author	= "A. U. Thor",
  title		= "X\\TeX{} rulez"
}
__EOF__
	   expected_out => <<__EOF__ );

\@Misc{		  thor:xtex,
  author	= "A. U. Thor",
  title		= "X\\TeX{} rulez"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'tex_define_2',
	   resource	=> <<__EOF__ ,
tex.define = {\\TeX =TeX}
key.format=short
__EOF__
	   bib 	        => <<__EOF__,
\@Misc{		  thor,
  author	= "A. U. Thor",
  title		= "X\\TeX{} rulez"
}
__EOF__
	   expected_out => <<__EOF__ );

\@Misc{		  thor:xtex,
  author	= "A. U. Thor",
  title		= "X\\TeX{} rulez"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'tex_define_3',
	   resource	=> <<__EOF__ ,
tex.define = {\\TeX	= TeX}
key.format=short
__EOF__
	   bib 	        => <<__EOF__,
\@Misc{		  thor,
  author	= "A. U. Thor",
  title		= "X\\TeX{} rulez"
}
__EOF__
	   expected_out => <<__EOF__ );

\@Misc{		  thor:xtex,
  author	= "A. U. Thor",
  title		= "X\\TeX{} rulez"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'tex_define_4',
	   resource	=> <<__EOF__ ,
tex.define = {ü	= ue}
key.format=short
__EOF__
	   bib 	        => <<__EOF__,
\@Misc{		  thor,
  author	= "A. U. Thor",
  title		= "München"
}
__EOF__
	   expected_out => <<__EOF__ );

\@Misc{		  thor:muenchen,
  author	= "A. U. Thor",
  title		= "München"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'tex_define_5',
	   resource	  => <<__EOF__ ,
tex.define = {\\TeX	= TeX}
tex.define = {\\protect[1]=#1}
key.format=short
__EOF__
	   bib 	        => <<__EOF__,
\@Misc{		  thor,
  author	= "A. U. Thor",
  title		= "x\\protect{\\TeX}"
}
__EOF__
	   expected_out => <<__EOF__ );

\@Misc{		  thor:xtex,
  author	= "A. U. Thor",
  title		= "x\\protect{\\TeX}"
}
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
