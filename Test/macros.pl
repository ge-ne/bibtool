#!/bin/perl -W
#******************************************************************************
# $Id: macros.pl,v 1.2 2011-10-17 17:38:43 gene Exp $
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

macros.pl - Test suite for BibTool macros.

=head1 SYNOPSIS

macros.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name         => 'macros_1',
	   args         => '-m - -o null.out xampl.bib',
	   expected_out => <<EOF,
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }
EOF
    expected_err => <<EOF,

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.
EOF
   check => sub {unlink('null.out'); return 0;}
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'expand_macros_1',
	   args         => '-- expand.macros=on',
	   bib				    => <<EOF,
\@String{BT				    ="BibTool"}
\@String{TeX				    ="\\TeX"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
EOF
	   expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= {2011}
}
EOF
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_all_strings_1',
	   args         => '-- print.all.strings=on',
	   bib		=> <<EOF,
\@String{BT  ="BibTool"}
\@String{TeX ="\\TeX"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
EOF
	   expected_out => <<EOF,
\@STRING{bt	= "BibTool" }
\@STRING{tex	= "\\TeX" }

\@Manual{	  bibtool,
  title		= bt,
  author	= {Gerd Neugebauer},
  year		= 2011
}
EOF
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_all_strings_2',
	   args         => '-- print.all.strings=off',
	   bib		=> <<EOF,
\@String{BT  ="BibTool"}
\@String{TeX ="\\TeX"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
EOF
	   expected_out => <<EOF,
\@STRING{bt	= "BibTool" }

\@Manual{	  bibtool,
  title		= bt,
  author	= {Gerd Neugebauer},
  year		= 2011
}
EOF
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_parentheses_1',
	   args         => '-- print.parentheses=on',
	   bib		=> <<EOF,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
EOF
	   expected_out => <<EOF,
\@STRING(bt	= "BibTool" )

\@Manual(	  bibtool,
  title		= bt,
  author	= {Gerd Neugebauer},
  year		= 2011
)
EOF
    expected_err => ''
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
