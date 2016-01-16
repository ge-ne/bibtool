#!/usr/local/bin/tclsh
##*****************************************************************************
## 
## This file is part of BibTool.
## It is distributed under the GNU General Public License.
## See the file COPYING for details.
## 
## (c) 1996-1997 Gerd Neugebauer
## 
## Net: gene@gerd-neugebauer.de
## 
##*****************************************************************************
#
#  This sample file shows how bibtool can be interfaced with Tcl(/Tk).
#  BibTool is assumed to be on the search path for executables.
#  BibTool is called with the appropriate parameters. In this examples
#  it is used only for normalization of the BibTeX database.
#  Afterwards it is rather simple for Tcl to parse the result.
#

# take the first argument as file name
set file [lindex $argv 0]

set FD [open "|bibtool -q -- pass.comments=off -- print.line.length=999999 -- print.indent=0 -- print.align=0 $file" r]
set bibtool_is_in_record 0

while { [gets $FD line] >= 0 } {
  if {[regexp {^\@STRING} $line]} {
  } elseif {[regexp {^\@PREAMBLE} $line]} {
  } elseif {[regexp {^\@COMMENT} $line]} {
  } elseif { !$bibtool_is_in_record &&	
    [regexp -nocase {^\@([a-z]*)\{[ 	]*(.*),} $line all type key]} {
    puts "type:  $type\nkey:   $key"
    set bibtool_is_in_record 1
  } elseif {$bibtool_is_in_record &&	
      [regexp -nocase {([a-z]*)=(.*)} $line all item value]} {
    regsub {,$} $value {} value
    puts "entry: $item\nvalue: $value"
  } elseif {$bibtool_is_in_record && $line=="\}"} {
    puts END_OF_RECORD
    set bibtool_is_in_record 0
  }
}
close $FD

