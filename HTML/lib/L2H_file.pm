#!/usr/local/bin/perl
##*****************************************************************************
## $Id: L2H_file.pm,v 1.2 2010-01-10 15:22:36 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

package L2H_file;

use vars qw ( @ISA @EXPORT @EXPORT_OK $VERSION );
use strict;
use FileHandle;
use File::Path;

use L2H;

require Exporter;
@ISA       = qw(Exporter L2H);
@EXPORT    = qw();
@EXPORT_OK = qw();

BEGIN{
  my $VERSION = '$Revision: 1.2 $'; #'
  $VERSION =~ s/[^0-9.]//go;
}


#------------------------------------------------------------------------------
# Function:	new
# Description:	
# Returns:	
#
sub new
{ my $class          = shift;
  my $self           = new L2H;
  $self->{out}	     = undef;
  $self->{page}      = '';
  $self->{last_page} = '';
  $self->{page_head} = '';
  $self->{children}  = '';
  return bless $self,$class;
}

#------------------------------------------------------------------------------
# Function:	button
# Description:	
#		
# Returns:	
#
sub button
{ my $url  = shift;
  my $alt  = shift;
  my $name = shift;
  my $img1 = shift;
  my $img2 = shift;

  return '' if ( not defined($url) or $url eq '' or not -e $url);
  return <<_EOF_;
<a href="$url" id="A$name"
   onMouseOver="document.$name\$\$.src='$img2'"
   onMouseOut="document.$name\$\$.src='$img1'"><img
   src="$img1" border="0" alt="$alt"
   name="$name\$\$" /></a>
_EOF_
}

#------------------------------------------------------------------------------
# Function:	put
# Description:	
# Returns:	
#
sub put (@)
{ my $self = shift;
  return if not defined($self->{out});
  local $_ = join("",@_);
  s/\&\#095;/_/go;
  print {$self->{out}} $_;
}

#------------------------------------------------------------------------------
# Function:	put_footnotes
# Description:	
# Returns:	
#
sub put_footnotes
{ my $self = shift;

  $self->put("<hr width='15%' align='left' noshade/>$self->{footnotes}<br />")
      if $self->{footnotes} ne '';
}

#------------------------------------------------------------------------------
# Function:	redirect
# Description:	
#		
# Returns:	
#
#
sub redirect
{ my $self   = shift;
  my $fname  = shift;
  my $n      = shift;
  local $_  = $fname || '';
  s/\&\#095;/_/go;

  print STDERR "--- redirect output $self->{page} -> $_\n"
      if $self->{debug} & 2;

  $self->{"nav:$n"} = $fname;

  $self->{'last_page'} = $self->{'page'};
  $self->{'page'}      = $_;
  $self->{'next:'.$self->{'last_page'}} = $self->{'page'}
    if defined($self->{'last_page'});
  $self->{'prev:'.$self->{'page'}} = $self->{'last_page'}
    if defined($self->{'page'});

  $self->{footnote_number} = 1;

  my $opt_ext     = $self->opt('ext');
  my $opt_year    = $self->opt('year');
  my $opt_email   = $self->opt('email');
  my $opt_author  = $self->opt('author');
  my $opt_prefix  = $self->opt('prefix');
  my $opt_dirname = $self->opt('dirname');

  mkpath($opt_dirname) if not -e $opt_dirname;

  if ( defined($self->{out}) )
  {
    $self->put($self->{children});
    $self->put_footnotes;

    $self->{page_head} =~ s/\$\$/2/go;

    $self->put(<<_EOF_);
<br /><hr />
<font face="sans-serif" size="1">\&copy; $opt_year
<a href="mailto:$opt_email">$opt_author</a></font>
</body>
</html>
_EOF_
    $self->{out}->close;
  }

  $self->{footnotes} = '';

  if ( not defined($fname) )
  { $self->{out}  = undef;
    $self->{page} = '';
    return;
  }

  $self->{out} = new FileHandle(">$opt_dirname/$fname") || die "$opt_dirname/$fname: $!\n";
  return undef if not defined($self->{out});
  print STDERR "--- Output to $opt_dirname/$fname\n" if $self->{debug} & 2;

  my $Cat = '';
  for (my $i = 0; $i < $n; $i++ )
  { my $s = $self->{'nav:'.$i};
    next if not defined($s);
    my $st	       = $self->{'title:'.$s};
    $Cat .= "<div class=\"cat$i\"><a href=\"$s\">$st</a></div>\n";
  }
  { my $s = $self->{"nav:$n"};
    $Cat .= "<div class=\"cat$n\"><b>".$self->{"title:$s"}."</b></div>\n";
  }

  $self->{children} = '';

  if ( $fname =~ m/$opt_ext$/ )
  { local $_ = $`;
    my $st;

    for (my $i = 1; defined($st=$self->{'title:'."$_\_$i$opt_ext"}); $i++)
    { $self->{children} .= "\n<li> <a href=\"$_\_$i$opt_ext\">$st</a>\n";
    }
  }
  $self->{children} = '<ul class="subtoc">'.$self->{children}.'</ul>'
      if $self->{children} ne '';

  my $Back = button($self->{'prev:'.$fname},'Back','Back',
		    'prev-normal.gif','prev-active.gif');
  my $Next = button($self->{'next:'.$fname},'Next','Next',
		    'next-normal.gif','next-active.gif');
  my $Toc  = button("$opt_prefix\_toc$opt_ext",'TOC','TOC',
		    'toc-normal.gif','toc-active.gif');
  my $Idx  = button("$opt_prefix\_idx$opt_ext",'Index','IDX',
		    'index-normal.gif','index-active.gif');

  $self->{page_head} = <<_EOF_;
<div class="top">
<table width="100%" cellspacing="0" cellpadding="3" border="0">
 <tr>
  <td width="160">
    $Back
    $Toc
    $Idx
    $Next
    &nbsp;
  </td>
  <td style="font-size:70%;">
     $Cat
  </td>
 </tr>
</table>
</div>
_EOF_
  my $tophead = $self->{page_head};
  $tophead =~ s/\$\$//go;

  my $st = $self->{'title:'.$fname} ;
  my $Title = ( $n<=0 ? '' : "<h$n>$st</h$n>" );
  put($self,<<_EOF_);
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML//3.2//EN">
<html>
<head>
  <title>$st</title>
  <meta name="Author" content="$opt_author">
  <meta http_equiv="Content-Type" content="text/html;CHARSET=iso-8859-1">
  <link rev="made" href="mailto:$opt_email">
  <link rel="stylesheet" type="text/css" href="site.css">
  <script src="site.js" type="text/javascript"></script>
</head>
<body>
$tophead
$Title
_EOF_

  return;
}

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
