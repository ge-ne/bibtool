----------------------------------------------------------------------

        ######            ############
        #######           ############
        ##    ##               ##
        ##    ##  ##  #####    ##    ####      ####    ##
        #######   ##  ######   ##   ######    ######   ##
        #######   ##  ##   ##  ##  ##    ##  ##    ##  ##
        ##    ##  ##  ######   ##  ##    ##  ##    ##  ##
        ##    ##  ##  ##   ##  ##  ##    ##  ##    ##  ##
        ##    ##  ##  ##   ##  ##  ##    ##  ##    ##  ##
        #######   ##  ######   ##   ######    ######   #######
        ######    ##  #####    ##    ####      ####    #######

----------------------------------------------------------------------


          BibTool: A Tool for Manipulating BibTeX Data Bases


BibTeX provides    an easy to  use means   to integrate  citations and
bibliographies into LaTeX documents.  But the user  is left alone with
the management of the BibTeX files. The program BibTool is intended to
fill this gap.  BibTool allows the  manipulation of BibTeX files which
goes  beyond the possibilities --- and intentions  --- of BibTeX.  The
possibilities of BibTool include

* Pretty-printing BibTeX data bases adjustable by lots of parameters.

* Syntactic checks with error recovery superior to BibTeX and helpful
  error messages.

* Semantic checks can be specified by the user.

* Sorting  and  merging of  BibTeX  data  bases according   to a  free
  definable sort key.

* Generation  of uniform reference keys  according to predefined rules
  or according to an own specification.

* Selecting references  used in  one  publication  which are found  by
  analyzing an .aux file.

* Selecting references by a set of criteria (regular expressions).

* Controlled  rewriting  of  fields utilizing  regular expressions  to
  specify the rewriting rules.

* Macro  (String)  expansion to  eliminate the  need  of  extra string
  definitions.

* Collecting statistics about one or more BibTeX data bases.


BibTool  contains a  documentation written  in  LaTeX of  more than 75
pages (and still growing).

BibTool is written  in C and  has  been compiled on  various operating
systems like flavors of UNiX and MSDOG machines.  It is distributed in
source code.   No compiled  versions  are  available from  the  author
(Useless to ask!).


# CTAN Download


BibTool can be obtained from the CTAN archives:

* http://mirrors.ctan.org/biblio/bibtex/utils/bibtool

Get  the  file BibTool-x.xx.tar.gz  where  x.xx is the version number.
Unpack it with the command (on UNiX)

    gunzip < BibTool-x.xx.tar.gz | tar -xvf -

It  will   create  a  directory  named  BibTool   which  contains  the
installation instructions in the file install.tex.

A signature for  the source bundle is provided as  well. My public key
can be  found on http://pgp.mit.edu/.  You should search for  my email
address.


# Licenses


The sources of BibTool are distributed under the GNU General Public
License version 2 or later.

The documentation is distributed under the Creative Commons
Attributation-Share Alike 3.0 License.

The distribution of BibTool contains the following third-party
software which is released under their own licenses:


* GNU regex library 0.12 is located in the directory regex-0.12. It is
  distributed under the GNU General Public License version 2 or later.

* mkdirchain consists of the file mkdirchain. It is in the public domain.

* install-sh consists of the file install-sh. It is distributed under
  the MIT license contained in this file.

----------------------------------------------------------------------
Enjoy it!

Gerd Neugebauer
mailto:gene@gerd-neugebauer.de

