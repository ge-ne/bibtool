#!/bin/perl -W
#******************************************************************************
# $Id: rewrite.pl,v 1.4 2011-10-22 06:08:31 gene Exp $
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

rewrite.pl - Test suite for BibTool rewrite.

=head1 SYNOPSIS

rewrite.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_add_field_1',
    args	      => 'x1.bib',
    resource 	      => 'add.field={xyzzy="abc"}',
    expected_out      => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011,
  xyzzy		= {abc}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_add_field_2',
    args	      => 'x1.bib',
    resource 	      => 'add.field={xyzzy={abc}}',
    expected_out      => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011,
  xyzzy		= {abc}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_add_field_3',
    args	      => 'x1.bib',
    resource 	      => 'add.field={xyzzy=abc}',
    expected_out      => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011,
  xyzzy		= {abc}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_delete_field_1',
    args	 => 'x1.bib',
    resource 	 => 'delete.field={xyzzy}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_delete_field_2',
    args	 => 'x1.bib',
    resource 	 => 'delete.field={year}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rewrite_1',
    args	 => 'x1.bib',
    resource 	 => 'rewrite.rule={"01"}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rewrite_2',
    args	 => 'x1.bib',
    resource 	 => 'rewrite.rule={"G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {A.U. Thor},
  year		= 2011
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rewrite_3',
    args	 => 'x1.bib',
    resource 	 => 'rewrite.rule={author title # "G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {A.U. Thor},
  year		= 2011
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rewrite_4',
    args	 => 'x1.bib',
    resource 	 => 'rewrite.rule={title # "G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_1',
    args	 => '--select.by.string=\'{"none"}\' xampl.bib',
    expected_out => <<EOF);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }
EOF

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_2',
    args	 => '--select.by.string=\'{"anual-mi"}\' xampl.bib',
    expected_out => <<EOF);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Manual{	  manual-minimal,
  key		= "Manmaker",
  title		= "The Definitive Computer Manual"
}
EOF

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_3',
    args	 => '--select.by.string=\'{"manmaker"}\' xampl.bib',
    expected_out => <<EOF);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Manual{	  manual-minimal,
  key		= "Manmaker",
  title		= "The Definitive Computer Manual"
}

\@Manual{	  manual-full,
  author	= "Larry Manmaker",
  title		= "The Definitive Computer Manual",
  organization	= "Chips-R-Us",
  address	= "Silicon Valley",
  edition	= "Silver",
  month		= apr # "-"  # may,
  year		= 1986,
  note		= "This is a full MANUAL entry"
}
EOF

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_4',
    args	 => '--select.by.string=\'{"MISC"}\' xampl.bib',
    expected_out => <<EOF);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Misc{		  misc-minimal,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}

\@Misc{		  misc-full,
  author	= "Joe-Bob Missilany",
  title		= "Handing out random pamphlets in airports",
  howpublished	= "Handed out at O'Hare",
  month		= oct,
  year		= 1984,
  note		= "This is a full MISC entry"
}
EOF

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_10',
    args	 => '--select.by.string=\'{"MISC"}\' xampl.bib',
    expected_out => <<EOF);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Misc{		  misc-minimal,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}

\@Misc{		  misc-full,
  author	= "Joe-Bob Missilany",
  title		= "Handing out random pamphlets in airports",
  howpublished	= "Handed out at O'Hare",
  month		= oct,
  year		= 1984,
  note		= "This is a full MISC entry"
}
EOF

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_11',
    args	 => '--select.by.string=\'{note "Kn"}\' xampl.bib',
    expected_out => <<EOF);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Misc{		  random-note-crossref,
  key		= {Volume-2},
  note		= "Volume~2 is listed under Knuth \\cite{book-full}"
}
EOF

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
