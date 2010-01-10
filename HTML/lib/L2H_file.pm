#!/usr/local/bin/perl
##*****************************************************************************
## $Id: L2H_file.pm,v 1.1 2010-01-10 11:30:28 gene Exp $
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
  my $VERSION = '$Revision: 1.1 $'; #'
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
   name="$name\$\$" /></A>
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

  my $Back = button($self->{'prev:'.$fname},'Back','Back','back.gif','back2.gif');
  my $Next = button($self->{'next:'.$fname},'Next','Next','next.gif','next2.gif');
  my $Toc  = button("$opt_prefix\_toc$opt_ext",'TOC','TOC','toc.gif','toc2.gif');
  my $Idx  = button("$opt_prefix\_idx$opt_ext",'Index','IDX','idx.gif','idx2.gif');

  $self->{page_head} = <<_EOF_;
<div class="top">
<table width="100%" cellspacing="0" cellpadding="3" border="0">
 <tr>
  <td width="160" style="font-face:sans-serif;">
    $Back
    $Toc
    $Idx
    $Next
    &nbsp;
  </td>
  <td style="font-face:sans-serif;font-size:70%;">
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
  <link rev="made" href="mailto:$opt_email">
  <meta name="Author" content="$opt_author">
  <meta http_equiv="Content-Type" content="text/html;CHARSET=iso-8859-1">
  <style>
body {
  background-color:white;
  font-family:sans-serif;
  margin-top:6em;
  margin-left:4em;
  margin-right:4em;
}
.top {
  background:url(top-bg.png) repeat-x #cccccc;
  position:fixed;
  top:0pt;
  left:0pt;
  width:100%;
  border-top:solid 3pt white;
  border-left:solid 3pt white;
  border-right:solid 3pt gray;
  border-bottom:solid 3px gray;
  font-size:80%;
}
.e {
  text-transform:uppercase;
  font-size:85%;
  vertical-align: -0.5ex;
  margin-left: -0.2em;
  margin-right: -0.1em;
  line-height: 0;
}
.a {
  text-transform:uppercase;
  font-size:75%;
  vertical-align: 0.45ex;
  margin-left: -0.36em;
  margin-right: -0.05em;
}
.t {
  margin-left: -0.15em;
}
.left {
  position:absolute;
  top:0;
  left:0;
}
.dir {
  text-indent:-32px;
  margin-left:32px;
  margin-right:32px;
}
h1,h2,h3 {
  color:firebrick;
}
address {
  font-size:70%;
  margin-top:2.5em;
  padding-top:.5em;
  border-top:1px solid gray;
}
pre {
  background-color:#eeeeee;
  border: 1px solid #999999;
  padding:.15em;
}
.subtoc {
  font-size:90%;
  background-color:#ffeeee;
  border-top:solid 3pt #663333;
  border-left:dotted 1px #663333;
  border-right:dotted 1px #663333;
  border-bottom:dotted 1px #663333;
  padding:2em;
  margin-top:4em;
  margin-left:4em;
  margin-right:4em;
}
.toc1 {
  font-size:90%;
  padding-left:0pt;
}
.toc2 {
  font-size:90%;
  padding-left:2em;
}
.toc3 {
  font-size:90%;
  padding-left:4em;
}
.toc4 {
  font-size:90%;
  padding-left:6em;
}
.toc5 {
  font-size:90%;
  padding-left:8em;
}
.toc6 {
  font-size:90%;
  padding-left:10em;
}
.cat0 {
}
.cat1 {
  padding-left:2em;
}
.cat2 {
  padding-left:4em;
}
.cat3 {
  padding-left:6em;
}
.cat4 {
  padding-left:8em;
}
.cat5 {
  padding-left:10em;
}
.cat6 {
  padding-left:12em;
}
  </style>
  <script type="text/javascript">
function keyPressed (ev) {
  if (!ev)
    ev = window.event;
  if (ev.which) {
    code = ev.which;
  } else if (ev.keyCode) {
    code = ev.keyCode;
  }
  var name;
  if (code == 37) {
    var el = document.getElementById("ABack");
    if (el != null) {
      location.href = el.href;
    }
  } else if (code == 39) {
    var el = document.getElementById("ANext");
    if (el != null) {
      location.href = el.href;
    }
  }
}
document.onkeydown = keyPressed;
  </script>
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
