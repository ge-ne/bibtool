#!/usr/local/bin/wish -f
###----------------------------------------------------------------------------
### $Id: main.tcl,v 1.1.1.1 2007-02-07 21:28:56 gene Exp $
###----------------------------------------------------------------------------

set infiles {}
set outfile {}
set macrofile {}
set the_db [new]

for {set i 0} {$i<$argc} {incr i} {
  set arg [lindex $argv $i]
  if { $arg == "-o" } {
    incr i
    set outfile [lindex $argv $i]
  } else if { $arg == "-q" } {
    bibtool quiet=[eval ![bibtool quiet]]
  } else if { $arg == "-s" } {
    bibtool sort=[eval ![bibtool sort]]
  } else if { $arg == "-S" } {
    bibtool sort=[eval ![bibtool sort]]
    bibtool sort.reverse=[eval ![bibtool sort.reverse]]
  } else {
    lappend infiles $arg
  }
}


foreach file $infiles {
  bibtool read $the_db $file
}

if {[bibtool make.key]} {
} else {
}

if {[bibtool sort]} {
  bibtool sort $the_db
}

bibtool write $outfile
