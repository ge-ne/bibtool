#!/usr/local/bin/perl
##*****************************************************************************
## $Id: L2H.pm,v 1.8 2011-12-04 13:24:07 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

package L2H;

use vars qw ( @ISA @EXPORT @EXPORT_OK $VERSION );
use strict;

my %opt = (
	   'dirname' => '.',
	   'prefix'  => 'm',
	   'title'   => '',
	   'main'    => 'index.html',
	   'author'  => 'Gerd Neugebauer',
	   'email'   => 'gene@gerd.neugebauer.de',
	   'year'    => '2010',
	   'ext'     => '.html'
	  );
{
  my ($sec,$min,$hour,$day,$mon,$year,$wday,$yday,$isdst) = localtime;
  $opt{year} = $year + 1900;
}

require Exporter;
@ISA       = qw(Exporter);
@EXPORT    = qw(newcommand newenvironment getMacro set_opt hyphenate %Macro);
@EXPORT_OK = qw();

BEGIN{
  my $VERSION = '$Revision: 1.8 $'; #'
  $VERSION =~ s/[^0-9.]//go;
}

#------------------------------------------------------------------------------
# Function:	new
# Description:	
# Returns:	
#
sub new
{ my $class = shift;
  my $this  =
  { 'ignore:p'		=> 0,
    'footnotes'		=> '',
    'footnote_number'	=> 0,
    'NAV'		=> '',
    'TOC'		=> '',
    'IDX'		=> '',
    'BIB'		=> '',
    'current_label'	=> '',
    'label_number'	=> 1,
    'index_number'	=> 1,
    'context'		=> 'text',
    'group'		=> '',
    'result'		=> '',
    'page'		=> '',
    'Group'		=> [],		# stack of the group informations
    'Context'		=> [],		# stack of the contexts
    'SectionMinNo'	=> 1,
    'SectionNumber'	=> [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    'debug'		=> 0,		# bitfield determining the verbosity
    'message:p'		=> 0,		# indicator for the last pass
					# for which messages should be issued.
    'hyphenate'		=> 0,		# indicator to turn on hyphenation
    'hyphenate:skip'	=> 0,		# internal
  };
  bless $this,$class;
  return $this;
}

#------------------------------------------------------------------------------
# Function:	restart
# Description:	
# Returns:	
#
sub restart
{ my $this = shift;
  my %args = @_;
  local $_ = new L2H()->LaTeX2HTML($opt{'title'} || $this->{'title'} || '');
  $this->{'title:'.$opt{'main'}} = $_;
  $this->{'Context'}       = [];
  $this->{'context'}       = 'text';
  $this->{'SectionNumber'} = [0,0,0,0,0,0,0,0,0,0,0,0,0,0];
  $this->{'current_label'} = '';
  $this->{'index_number'}  = 1;
  $this->{'label_number'}  = 1;
  $this->{'page'}          = '';
  $this->{'ignore:p'}      = 1;
  $this->{'NAV'}           = "<div class=\"toc0\"><a href=\"doc.html\" target=\"content\">$_</a></div>\n";
  $this->{'TOC'}           = '';
  while ( my($key,$value) = each %args)
  { $this->{$key} = $value; }
  $this->redirect($opt{'main'}, 0);
}

#------------------------------------------------------------------------------
# Function:	push_context
# Description:	
# Returns:	
#
sub push_context
{ my $this    = shift;
  my $context = shift;
  my @a = $this->{'Context'};
  unshift @a,$context;
  $this->{'Context'} = @a;
  $this->{'context'} = $context;
  return '';
}

#------------------------------------------------------------------------------
# Function:	pop_context
# Description:	
# Returns:	
#
sub pop_context
{ my $this    = shift;
  my @a = $this->{'Context'};
  my $context = shift @a;
  $this->{'Context'} = @a;
  $this->{'context'} = $context;
  return '';
}

#------------------------------------------------------------------------------
# Function:	opt
# Description:	
# Returns:	
#
sub opt
{ local $_ = shift;
  $_ = shift;
  return $opt{$_};
}

#------------------------------------------------------------------------------
# Function:	set_opt
# Description:	
# Returns:	
#
sub set_opt
{ shift;
  my ($key,$value) = @_;
  $opt{$key} = $value;
}

#------------------------------------------------------------------------------
# Variable:	%SectionLevel
# Description:	
#
my %SectionLevel =
  ( 'tableofcontents'	=> 1,
    'bibliography'	=> 1,
    'index'		=> 1,
    'part'		=> 1,
    'chapter'		=> 1,
    'section'		=> 2,
    'subsection'	=> 3,
    'subsubsection'	=> 4,
    'paragraph'		=> 5,
    'subparagraph'	=> 6,
    'subsubparagraph'	=> 7,
    'Summary'		=> 3,
  );

#------------------------------------------------------------------------------
# Variable:	%Macro
# Description:	Hash of array containing the defined macros.
#		The first element is the array is the arity of the macro.
#		The second argument is a modifier for the context. The value
#		undef leaves the context unchanged. The value '/' pops a value
#		from the context stack. All aotehr values are pushed to the
#		context stack.
#		The third element is the replacement text. The strings
#		#1, #2,..., #9 are replaced by the actual parameters. If it is
#		undef then the next element is taken into account.
#		The fourth element is a piece of code (anonymous subroutine)
#		to be evaluated when no replacement text is given. The
#		parameters of the macro are passed to this code in the array
#		@_. The return value is used as replacement text.
#
my %Macro = ();

newcommand('CURRENTDIR',text=>'.');

#------------------------------------------------------------------------------
# Function:	begingroup
# Description:	
# Returns:	
#
sub begingroup
{ my $this = shift;
  unshift @{$this->{Group}},$this->{group};
  $this->{group} = '';
  return '';
}

#------------------------------------------------------------------------------
# Function:	endgroup
# Description:	
# Returns:	
#
sub endgroup
{ my $this = shift;
  local $_ = $this->{group};
  $this->{group} = shift @{$this->{Group}};
  return $_;
}

#------------------------------------------------------------------------------
# Function:	atendgroup
# Description:	
# Returns:	
#
sub atendgroup
{ my $this = shift;
  local $_ = shift;
  $this->{group} = $_.$this->{group};
  return '';
}

#------------------------------------------------------------------------------
# Function:	in_group
# Description:	
# Returns:	
#
sub in_group
{ my $this = shift;
  my $s    = shift;
  local $_ = shift;
  $this->{group} = $_.$this->{group};
  return $s;
}

#------------------------------------------------------------------------------
# Function:	load
# Description:	
# Returns:	
#
sub load
{ my $this   = shift;
  my $file   = shift;
  my $ignore = shift;
  warn "--- Loading $file\n" if $this->{'debug'} & 1;
  if (not defined do $file) {
    if ($@) {
      die "$file: $@\n" if not $ignore;
      warn "Warning for $file: $@\n";
    }
    if ($!) {
      die "$file: $!\n" if not $ignore;
      warn "Warning for $file: $!\n";
    }
  }
}

#------------------------------------------------------------------------------
# Method:	getMacro
# Arguments:	
# Returns:	
# Description:	
#
sub getMacro {
  my $macro = shift;
  return $L2H::Macro{$macro};
}

#------------------------------------------------------------------------------
# Function:	newcommand
# Description:	
# Returns:	
#
sub newcommand
{ my ($macro,%arg) = @_;
  my $arity = ( $arg{arity} || 0 );
  if ( exists $L2H::Macro{$macro} )
  { # warn "*** `$macro' is already defined.\n";
  }
  else
  { $L2H::Macro{$macro} = [$arity,$arg{context},$arg{text}];
  }
  return '';
}

#------------------------------------------------------------------------------
# Function:	renewcommand
# Description:	
# Returns:	
#
sub renewcommand
{ my ($macro,%arg) = @_;
  my $arity = ( $arg{arity} || 0 );
  if ( not defined $arg{noredef} )
  { $L2H::Macro{$macro} = [$arity,$arg{context},$arg{text},$arg{redef}];
  }
  return '';
}

#------------------------------------------------------------------------------
# Function:	newenvironment
# Description:	
# Returns:	
#
sub newenvironment ($@)
{ my ($macro,%arg) = @_;
  newcommand("begin{$macro}",
	     context => $macro,
	     arity   => $arg{arity},
	     text    => $arg{text},
	    );
  newcommand("end{$macro}",
	     context => '/',
	     arity   => 0,
	     text    => $arg{endtext},
	    );
  return '';
}

#------------------------------------------------------------------------------
# Function:	renewenvironment
# Description:	
# Returns:	
#
sub renewenvironment ($@)
{ my ($macro,%arg) = @_;
  renewcommand("begin{$macro}",
	     context => $macro,
	     arity   => $arg{arity},
	     text    => $arg{text},
	    );
  renewcommand("end{$macro}",
	     context => '/',
	     arity   => 0,
	     text    => $arg{endtext},
	    );
  return '';
}

#------------------------------------------------------------------------------
# Function:	put
# Description:	
# Returns:	
#
sub put (@)
{ my $this = shift;
  return if $this->{'ignore:p'};

  my $s = join('',@_);
  return if $s eq '';
  if ($this->{hyphenate}) {
    $s = $this->hyphenate($s);
  }
  $this->{result} .= $s;
}

#------------------------------------------------------------------------------
# Function:	put_raw
# Description:	
# Returns:	
#
sub put_raw (@)
{ my $this = shift;
  return if $this->{'ignore:p'};
  $this->{result} .= join('',@_);
}

#------------------------------------------------------------------------------
# Function:	redirect
# Description:	
# Returns:	
#
sub redirect (@)
{
}

#------------------------------------------------------------------------------
# Function:	finish
# Description:	
# Returns:	
#
sub finish
{ my $this = shift;
  local $_ = shift;
  $this->put($_);
  $_ = $this->{result};
  $this->{result} = '';
  s/<\/blockquote><br>/<\/blockquote>/go;
  s/<p>\n<blockquote>/<blockquote>/go;
  s/<\/blockquote>\n*<blockquote>/<br>/go;
  s/<p><dt>/<dt>/go;
  return $_;
}

#------------------------------------------------------------------------------
# Method:	hyphenate
# Arguments:	
# Returns:	
# Description:	
#
sub hyphenate
{ my $this = shift;
  local $_ = shift;
  my $h	   = $this->{hyphenate};
  eval "require hyph_$h;" || die "hyph_$h.pm: $!$@\n";
  my $hyphenator = "hyph_${h}::hyph";
  my $result 	 = '';
  if ($this->{'hyphenate:skip'}) {
    if ( m/>/ ) {
      $result = $`.$&;
      $_      = $';
    } else {
      return $_;
    }
  }
  $this->{'hyphenate:skip'} = 0;

  while( m/[^a-zäöüßA-ZÄÖÜ]/s ) {
    my $sep = $&;
    $_ = $';
    if ($& eq '<') {
      no strict 'refs';
      $result .= &$hyphenator($`).$sep;
      if ( m/>/ ) {
	$result .= $`.$&;
	$_ 	 = $';
      } else {
	$this->{'hyphenate:skip'} = 1;
	return $result.$_;
      }
    } elsif ($sep eq '&') {
      $result .= $`.$sep;
      if ($_ =~ m/;/) {
	$result = $`.$&;
	$_	= $';
      } else {
	die "unparsable HTML entity: \&$_\n";
      }
    } elsif (length($`)	< 4) {
      $result .= $`.$sep;
    } else {
      no strict 'refs';
#      print "»$`«\n";
      $result .= &$hyphenator($`).$sep;
    }
  }

  return $result.$_ if length($_) < 4;

  no strict 'refs';
#    print "»$_«\n";
  return $result.&$hyphenator($_);
}

#------------------------------------------------------------------------------
# Function:	LaTeX2HTML
# Description:	
# Returns:	
#
sub LaTeX2HTML
{ my $this = shift;
  local $_ = shift;
  $this->{result} = '';

  while ( m/[\~\{\}\^_\%\&'`]|(\\([^a-z@]|[a-z@]+\s*))|---?/oi ) #`'
  { my $token = $&;
    my $pre = $`;
    $_ =  $';
    $pre =~ s|\n[ ]*\n|\n<p>|go;
    $this->put($pre) if not $this->{'ignore:p'};

    if ( substr($token,0,1) eq '\\' ) {
      $token = substr($token,1);
      $token =~ s/\s//go if ( $token =~ m/^[a-z@]/oi );
      if ( ($token eq 'begin' || $token eq 'end') ) {
	if (m/^{[a-z\*]+}/oi) {
	  $_ = $';
	  $token .= $&;
	} else {
	  warn "Missing environment name for $token: $_\n";
	}
      }
      my $macro = $L2H::Macro{$token};
      if (not defined $macro) {
	warn "*** $token undefined\n";
	next;
      }
      my @macro	= @$macro;
      my $arity	= $macro[0];
      my @a     = ();
      if ( $arity ) {
	my $start = 1;
	my $pre   = '\\'.$token;
	if ( $arity =~ m/^\[\](\d)/o ) {
	  $start = 2;
	  $arity = $1+1;
	  ($a[1],$_) = get_optarg($_);
	} elsif ( $arity =~ m/^1\[\](\d)/o ) {
	  $start = 3;
	  $arity = $1 + 2;
	  ($a[1],$_) = get_arg($token,$_);
	  ($a[2],$_) = get_optarg($_);
	  $pre .= "{$a[1]}";
	} elsif ( $arity =~ m/^\*(\d)/o ) {
	  $start = 2;
	  $arity = $1 + 1;
	  s/^\s//go;
	  if ( substr($_,0,1) eq '*' ) {
	    $a[1] = '*';
	    $_ = substr($_,1);
	    $pre .= '*';
	  }
	} elsif ( not $arity =~ m/^\d$/o ) {
	  warn "Arity could not be parsed: $arity\n";
	}
	for ( my $i=$start; $i<=$arity; $i++ ) {
	  ($a[$i],$_) = get_arg($pre,$_);
	  $pre .= "{$a[$i]}";
	}
      }
      
      my $text = $macro[2];
      if (ref($text) eq 'CODE') {
	shift @a;
	$text = &{$text}($this,@a);
	print STDERR "+++ $macro[3]\n" if not defined $text;
	$_ = $text.$_;
      } elsif ( defined($text) and not $this->{'ignore:p'} ) {
	for (my $i=1; $i<=$arity; $i++) { $text =~ s/\#$i/$a[$i]/g; }
	$_ = $text.$_;
#      } else {
#	print ">>> ",$this->{'ignore:p'}," $text\n";
      }
    } elsif ($token eq '---') {
      $this->put('&mdash;');
    } elsif ($token eq '--') {
      $this->put_raw('&ndash;');
    }
    elsif ( $token eq '%' ) { # comments
      s/^.*\n[ \t]*//o;
    } elsif ( $token eq '&' ) { # next column or special character
      if ( m/^((#x?[0-9]{1,3})|[a-z]+);/o ) {
	$_ = $';
	$this->put_raw('&',$&);
      } else {
	$this->put_raw('</td><td>');
      }
    } elsif ( $token eq '^' ) { # superscript
      my $a;
      ($a,$_) = get_arg('^',$_);
      $_ = "<sup>$a</sup>$_";
    } elsif ( $token eq '_' ) { # subscript
      my $a;
      ($a,$_) = get_arg('_',$_);
      $_ = "<sub>$a</sub>$_";
    } elsif ( $token eq '~' ) {
      $this->put_raw('&nbsp;');
    } elsif ( $token eq '{' ) {
      $this->begingroup();
    } elsif ( $token eq '}' ) {
      $this->put_raw($this->endgroup());
    } elsif ( $token eq '\'' ) {
      if (m/^'/) { #'
	$_ = $';
	$this->put_raw('&rdquo;');
      } else {
	$this->put_raw('&rsquo;');
      }
    } elsif ( $token eq '`' ) {
      if (m/^`/) { #`
	$_ = $';
	$this->put_raw('&ldquo;');
      } else {
	$this->put_raw('&lsquo;');
      }
    }
  }
  return $this->finish($_);
}

#------------------------------------------------------------------------------
# Function:	get_arg
# Description:	
#		
# Returns:	
#
#
sub get_arg
{ my $mac  = shift;
  my $arg  = shift;

  return ($&,$') if ( $arg =~ m/^[^{}\\]/oi );
  return ($&,$') if ( $arg =~ m/^\\([^a-z@]|[a-z@]+)/oi );
  die "Wrong start of args for $mac: $arg\n" if substr($arg,0,1) ne '{';

  $arg     = substr($arg,1);
  my $n    = 1;
  local $_ = '';
  while ( $n>0 && $arg =~ m/(\\.|[\{\}])/o )
  { if    ( $& eq '{' ) { $n++; }
    elsif ( $& eq '}' ) { $n--; }
    $_ .= $`;
    $_ .= $&;
    $arg = $';
  } 
  die "missing paren for $mac\n" if ($n>0);
  return (substr($_,0,length($_)-1),$arg);
}

#------------------------------------------------------------------------------
# Function:	get_optarg
# Description:	
#		
# Returns:	
#
#
sub get_optarg
{ my $arg  = shift;
  local $_ = '';
  return (undef,$arg) if ( substr($arg,0,1) ne '[' );
  $arg     = substr($arg,1);
  my $n    = 1;
  while ( $n>0 && $arg =~ m/(\\.|[\[\]\{\}])/o )
  { if    ( $& eq '[' ) { $n++; }
    elsif ( $& eq ']' ) { $n--; }
    elsif ( $& eq '{' ) { $n++; }
    elsif ( $& eq '}' ) { $n--; }
    $_ .= $`;
    $_ .= $&;
    $arg = $';
  } 
  die "missing paren\n" if ($n>0);
  return (substr($_,0,length($_)-1),$arg);
}

#------------------------------------------------------------------------------
# Function:	get_dimen
# Description:	
# Returns:	
#
sub get_dimen
{ local $_ = shift;
  s/^\s*//go;
  while ( s/^%.*//go ) { s/^\s*//go; }
  die "missing data" if ( $_ eq '' );
  return ($1,$') if ( m/^([-]?\s*(\d+|\d+\.\d*|\.\d+)\s*(pt|mm|cm|dd|sp|in))\s*/o );
  die "syntax error\n";
}

#------------------------------------------------------------------------------
# Function:	section
# Description:	
#		
# Returns:	
#
#
sub section
{ my $this   = shift;
  my $name   = shift;
  my $level  = shift;
  my $title  = shift;
  my $post   = shift;

  $level = $SectionLevel{$level} || 1;
  print STDERR '.' if $this->{debug} & 1;
  if ( not defined($name) )
  { $this->{'SectionNumber'}[$level]++;
    for ( my $i = $level + 1; $i < 10; $i++ )
    { $this->{'SectionNumber'}[$i] = 0}
    $name = $opt{'prefix'};
    for ( my $i = $this->{'SectionMinNo'}; $i <= $level; $i++ )
    { $name .= '_'.$this->{'SectionNumber'}[$i]; }
    $name .= $opt{'ext'};
  }
  $name =~ s/&#095;/_/go;

  { my $tr = new L2H();
    $title = $tr->LaTeX2HTML($title);
    $this->{'title:'. $name} = $title;
    $this->{'current_label'} = $title;
  }

  if ( $this->{'ignore:p'} )
  { $name  = undef;
    $level = 0
  }

  $this->redirect($name, $level);
  $this->put($post) if defined $post;

  $this->{TOC} .= "<div class=\"toc$level\"><a href=\"$this->{page}\">$title</a></div>\n";
  $this->{NAV} .= "<div class=\"toc$level\"><a href=\"$this->{page}\" target=\"content\">$title</a></div>\n";

  return "<h$level>$title</h$level>";
}

#------------------------------------------------------------------------------
# Function:	footnote
# Description:	
# Returns:	
#
sub footnote
{ my ($this,$text) = @_;
  my $l2h = new L2H();
  my $no = $this->{'footnote_number'}++;

  $text = $l2h->LaTeX2HTML($text);
  $this->{footnotes} .= "<small><sup><a name='FN$no'>$no</a></sup> $text</small><br />";
  return "<sup><small><a href='#FN$no'>$no</a></small></sup>";
}

#------------------------------------------------------------------------------
# Function:	label
# Description:	
#		
# Returns:	
#
#
sub label
{ my    $this  = shift;
  my    $label = shift;
  my    $tag   = shift;
  local $_     = $this->{'page'};
  s/\.html?$//o;
  s/_/\&\#095;/go;
  $this->{'label_text:'.$label} = $this->{'current_label'};
  if ( $tag )
  { local $_ = 'tag'.($this->{'label_number'}++);
    $this->{'label_url:'.$label} = $this->{'page'}.'#'.$_;
    $this->{'label_url:'.$label} =~ s/_/\&\#095;/go;
    return "<a name=\"$_\"/>";
  }
  $this->{'label_url:'.$label} = $this->{'page'};
  $this->{'label_url:'.$label} =~ s/_/\&\#095;/go;
  return '';
}

#------------------------------------------------------------------------------
# Function:	Index
# Description:	
#		
# Returns:	
#
#
sub Index
{ my $this  = shift;
  my $key   = shift;

  return '' if ( $this->{'message:p'} or $key eq '' );

  my $i     = $this->{'index_number'}++;
  my $page  = $this->{'page'};
  my $title = $this->{'title:'.$page} || '';
  local $_  = $key;

  if ( $key =~ m/@/o )
  { $_ = $`;
    $key = $';
  }
  $_ = lc($_);

  $this->{'index_name:'.$_} = $key;
  $this->{'INDEX'}{$_} .= ", " if ( defined ($this->{'INDEX'}{$_}) and
				    $this->{'INDEX'}{$_} ne '' );
  $this->{'INDEX'}{$_} .= "<a href='$page#IDX$i'>$title</a>";
  return "<a name='IDX$i'>";
}

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
