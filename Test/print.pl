#!/bin/perl -W
#******************************************************************************
# $Id: print.pl,v 1.1 2011-10-18 16:57:15 gene Exp $
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

print.pl - Test suite for BibTool print.

=head1 SYNOPSIS

print.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name         => 'symbol_type_1',
	   args         => '-- symbol.type=xyz',
	   bib		=> <<EOF,
EOF
	   expected_out => <<EOF,
EOF
    expected_err => <<EOF
*** BibTool: Unknown symbol type ignored.
EOF
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'symbol_type_2',
	   args         => '-- symbol.type=upper',
	   bib		=> <<EOF,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
EOF
	   expected_out => <<EOF,
\@STRING{BT	= "BibTool" }

\@Manual{	  bibtool,
  TITLE		= BT,
  AUTHOR	= {Gerd Neugebauer},
  YEAR		= 2011
}
EOF
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'symbol_type_3',
	   args         => '-- symbol.type=lower',
	   bib		=> <<EOF,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  Title = 	 BT,
  Author =	 {Gerd Neugebauer},
  Year =	 2011
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
BUnit::run(name         => 'symbol_type_4',
	   args         => '-- symbol.type=cased',
	   bib		=> <<EOF,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
EOF
	   expected_out => <<EOF,
\@STRING{Bt	= "BibTool" }

\@Manual{	  bibtool,
  Title		= Bt,
  Author	= {Gerd Neugebauer},
  Year		= 2011
}
EOF
    expected_err => ''
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
