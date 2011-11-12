#!/bin/perl -W
#******************************************************************************
# $Id: sort.pl,v 1.2 2011-11-12 13:18:28 gene Exp $
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

sort.pl - Test suite for BibTool sort.

=head1 SYNOPSIS

sort.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name => '_s_1',
    args              => '-s xampl_s.bib',
    expected_out      => <<EOF,
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX" }

\@Article{	  article-crossref,
  title		= ""
}

\@Article{	  article-full,
  title		= ""
}

\@Article{	  article-minimal,
  title		= ""
}

\@Book{		  book-crossref,
  title		= ""
}

\@Book{		  book-full,
  title		= ""
}

\@Book{		  book-minimal,
  title		= ""
}

\@Booklet{	  booklet-full,
  title		= ""
}

\@Booklet{	  booklet-minimal,
  title		= ""
}

\@InBook{	  inbook-crossref,
  title		= ""
}

\@InBook{	  inbook-full,
  title		= ""
}

\@InBook{	  inbook-minimal,
  title		= ""
}

\@InCollection{	  incollection-crossref,
  title		= ""
}

\@InCollection{	  incollection-full,
  title		= ""
}

\@InCollection{	  incollection-minimal,
  title		= ""
}

\@InProceedings{	  inproceedings-crossref,
  title		= ""
}

\@InProceedings{	  inproceedings-full,
  title		= ""
}

\@InProceedings{	  inproceedings-minimal,
  title		= ""
}

\@Manual{	  manual-full,
  title		= ""
}

\@Manual{	  manual-minimal,
  title		= ""
}

\@MastersThesis{	  mastersthesis-full,
  title		= ""
}

\@MastersThesis{	  mastersthesis-minimal,
  title		= ""
}

\@Misc{		  misc-full,
  title		= ""
}

\@Misc{		  misc-minimal,
  title		= ""
}

\@PhDThesis{	  phdthesis-full,
  title		= ""
}

\@PhDThesis{	  phdthesis-minimal,
  title		= ""
}

\@Proceedings{	  proceedings-full,
  title		= ""
}

\@Proceedings{	  proceedings-minimal,
  title		= ""
}

\@Misc{		  random-note-crossref,
  title		= ""
}

\@TechReport{	  techreport-full,
  title		= ""
}

\@TechReport{	  techreport-minimal,
  title		= ""
}

\@Unpublished{	  unpublished-full,
  title		= ""
}

\@Unpublished{	  unpublished-minimal,
  title		= ""
}

\@Book{		  whole-collection,
  title		= ""
}

\@Article{	  whole-journal,
  title		= ""
}

\@Proceedings{	  whole-proceedings,
  title		= ""
}

\@Book{		  whole-set,
  title		= ""
}
EOF
    expected_err => '' );


#------------------------------------------------------------------------------
BUnit::run(name => 'sort_1',
    args              => '--sort=on xampl_s.bib',
    expected_out		=> <<EOF,
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX" }

\@Article{	  article-crossref,
  title		= ""
}

\@Article{	  article-full,
  title		= ""
}

\@Article{	  article-minimal,
  title		= ""
}

\@Book{		  book-crossref,
  title		= ""
}

\@Book{		  book-full,
  title		= ""
}

\@Book{		  book-minimal,
  title		= ""
}

\@Booklet{	  booklet-full,
  title		= ""
}

\@Booklet{	  booklet-minimal,
  title		= ""
}

\@InBook{	  inbook-crossref,
  title		= ""
}

\@InBook{	  inbook-full,
  title		= ""
}

\@InBook{	  inbook-minimal,
  title		= ""
}

\@InCollection{	  incollection-crossref,
  title		= ""
}

\@InCollection{	  incollection-full,
  title		= ""
}

\@InCollection{	  incollection-minimal,
  title		= ""
}

\@InProceedings{	  inproceedings-crossref,
  title		= ""
}

\@InProceedings{	  inproceedings-full,
  title		= ""
}

\@InProceedings{	  inproceedings-minimal,
  title		= ""
}

\@Manual{	  manual-full,
  title		= ""
}

\@Manual{	  manual-minimal,
  title		= ""
}

\@MastersThesis{	  mastersthesis-full,
  title		= ""
}

\@MastersThesis{	  mastersthesis-minimal,
  title		= ""
}

\@Misc{		  misc-full,
  title		= ""
}

\@Misc{		  misc-minimal,
  title		= ""
}

\@PhDThesis{	  phdthesis-full,
  title		= ""
}

\@PhDThesis{	  phdthesis-minimal,
  title		= ""
}

\@Proceedings{	  proceedings-full,
  title		= ""
}

\@Proceedings{	  proceedings-minimal,
  title		= ""
}

\@Misc{		  random-note-crossref,
  title		= ""
}

\@TechReport{	  techreport-full,
  title		= ""
}

\@TechReport{	  techreport-minimal,
  title		= ""
}

\@Unpublished{	  unpublished-full,
  title		= ""
}

\@Unpublished{	  unpublished-minimal,
  title		= ""
}

\@Book{		  whole-collection,
  title		= ""
}

\@Article{	  whole-journal,
  title		= ""
}

\@Proceedings{	  whole-proceedings,
  title		= ""
}

\@Book{		  whole-set,
  title		= ""
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => '_S_1',
    args              => '-S xampl_s.bib',
    expected_out      => <<EOF,
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX" }

\@Book{		  whole-set,
  title		= ""
}

\@Proceedings{	  whole-proceedings,
  title		= ""
}

\@Article{	  whole-journal,
  title		= ""
}

\@Book{		  whole-collection,
  title		= ""
}

\@Unpublished{	  unpublished-minimal,
  title		= ""
}

\@Unpublished{	  unpublished-full,
  title		= ""
}

\@TechReport{	  techreport-minimal,
  title		= ""
}

\@TechReport{	  techreport-full,
  title		= ""
}

\@Misc{		  random-note-crossref,
  title		= ""
}

\@Proceedings{	  proceedings-minimal,
  title		= ""
}

\@Proceedings{	  proceedings-full,
  title		= ""
}

\@PhDThesis{	  phdthesis-minimal,
  title		= ""
}

\@PhDThesis{	  phdthesis-full,
  title		= ""
}

\@Misc{		  misc-minimal,
  title		= ""
}

\@Misc{		  misc-full,
  title		= ""
}

\@MastersThesis{	  mastersthesis-minimal,
  title		= ""
}

\@MastersThesis{	  mastersthesis-full,
  title		= ""
}

\@Manual{	  manual-minimal,
  title		= ""
}

\@Manual{	  manual-full,
  title		= ""
}

\@InProceedings{	  inproceedings-minimal,
  title		= ""
}

\@InProceedings{	  inproceedings-full,
  title		= ""
}

\@InProceedings{	  inproceedings-crossref,
  title		= ""
}

\@InCollection{	  incollection-minimal,
  title		= ""
}

\@InCollection{	  incollection-full,
  title		= ""
}

\@InCollection{	  incollection-crossref,
  title		= ""
}

\@InBook{	  inbook-minimal,
  title		= ""
}

\@InBook{	  inbook-full,
  title		= ""
}

\@InBook{	  inbook-crossref,
  title		= ""
}

\@Booklet{	  booklet-minimal,
  title		= ""
}

\@Booklet{	  booklet-full,
  title		= ""
}

\@Book{		  book-minimal,
  title		= ""
}

\@Book{		  book-full,
  title		= ""
}

\@Book{		  book-crossref,
  title		= ""
}

\@Article{	  article-minimal,
  title		= ""
}

\@Article{	  article-full,
  title		= ""
}

\@Article{	  article-crossref,
  title		= ""
}
EOF
    expected_err => '' );


#------------------------------------------------------------------------------
BUnit::run(name => 'sort_reverse_1',
    args              => '--sort=on --sort.reverse=on xampl_s.bib',
    expected_out		=> <<EOF,
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX" }

\@Book{		  whole-set,
  title		= ""
}

\@Proceedings{	  whole-proceedings,
  title		= ""
}

\@Article{	  whole-journal,
  title		= ""
}

\@Book{		  whole-collection,
  title		= ""
}

\@Unpublished{	  unpublished-minimal,
  title		= ""
}

\@Unpublished{	  unpublished-full,
  title		= ""
}

\@TechReport{	  techreport-minimal,
  title		= ""
}

\@TechReport{	  techreport-full,
  title		= ""
}

\@Misc{		  random-note-crossref,
  title		= ""
}

\@Proceedings{	  proceedings-minimal,
  title		= ""
}

\@Proceedings{	  proceedings-full,
  title		= ""
}

\@PhDThesis{	  phdthesis-minimal,
  title		= ""
}

\@PhDThesis{	  phdthesis-full,
  title		= ""
}

\@Misc{		  misc-minimal,
  title		= ""
}

\@Misc{		  misc-full,
  title		= ""
}

\@MastersThesis{	  mastersthesis-minimal,
  title		= ""
}

\@MastersThesis{	  mastersthesis-full,
  title		= ""
}

\@Manual{	  manual-minimal,
  title		= ""
}

\@Manual{	  manual-full,
  title		= ""
}

\@InProceedings{	  inproceedings-minimal,
  title		= ""
}

\@InProceedings{	  inproceedings-full,
  title		= ""
}

\@InProceedings{	  inproceedings-crossref,
  title		= ""
}

\@InCollection{	  incollection-minimal,
  title		= ""
}

\@InCollection{	  incollection-full,
  title		= ""
}

\@InCollection{	  incollection-crossref,
  title		= ""
}

\@InBook{	  inbook-minimal,
  title		= ""
}

\@InBook{	  inbook-full,
  title		= ""
}

\@InBook{	  inbook-crossref,
  title		= ""
}

\@Booklet{	  booklet-minimal,
  title		= ""
}

\@Booklet{	  booklet-full,
  title		= ""
}

\@Book{		  book-minimal,
  title		= ""
}

\@Book{		  book-full,
  title		= ""
}

\@Book{		  book-crossref,
  title		= ""
}

\@Article{	  article-minimal,
  title		= ""
}

\@Article{	  article-full,
  title		= ""
}

\@Article{	  article-crossref,
  title		= ""
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'sort_reverse_2',
    args              => '--sort=on --sort.reverse=off xampl_s.bib',
    expected_out		=> <<EOF,
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX" }

\@Article{	  article-crossref,
  title		= ""
}

\@Article{	  article-full,
  title		= ""
}

\@Article{	  article-minimal,
  title		= ""
}

\@Book{		  book-crossref,
  title		= ""
}

\@Book{		  book-full,
  title		= ""
}

\@Book{		  book-minimal,
  title		= ""
}

\@Booklet{	  booklet-full,
  title		= ""
}

\@Booklet{	  booklet-minimal,
  title		= ""
}

\@InBook{	  inbook-crossref,
  title		= ""
}

\@InBook{	  inbook-full,
  title		= ""
}

\@InBook{	  inbook-minimal,
  title		= ""
}

\@InCollection{	  incollection-crossref,
  title		= ""
}

\@InCollection{	  incollection-full,
  title		= ""
}

\@InCollection{	  incollection-minimal,
  title		= ""
}

\@InProceedings{	  inproceedings-crossref,
  title		= ""
}

\@InProceedings{	  inproceedings-full,
  title		= ""
}

\@InProceedings{	  inproceedings-minimal,
  title		= ""
}

\@Manual{	  manual-full,
  title		= ""
}

\@Manual{	  manual-minimal,
  title		= ""
}

\@MastersThesis{	  mastersthesis-full,
  title		= ""
}

\@MastersThesis{	  mastersthesis-minimal,
  title		= ""
}

\@Misc{		  misc-full,
  title		= ""
}

\@Misc{		  misc-minimal,
  title		= ""
}

\@PhDThesis{	  phdthesis-full,
  title		= ""
}

\@PhDThesis{	  phdthesis-minimal,
  title		= ""
}

\@Proceedings{	  proceedings-full,
  title		= ""
}

\@Proceedings{	  proceedings-minimal,
  title		= ""
}

\@Misc{		  random-note-crossref,
  title		= ""
}

\@TechReport{	  techreport-full,
  title		= ""
}

\@TechReport{	  techreport-minimal,
  title		= ""
}

\@Unpublished{	  unpublished-full,
  title		= ""
}

\@Unpublished{	  unpublished-minimal,
  title		= ""
}

\@Book{		  whole-collection,
  title		= ""
}

\@Article{	  whole-journal,
  title		= ""
}

\@Proceedings{	  whole-proceedings,
  title		= ""
}

\@Book{		  whole-set,
  title		= ""
}
EOF
    expected_err => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
