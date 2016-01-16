%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 
%% This file is part of BibTool.
%% It is distributed under the GNU General Public License.
%% See the file COPYING for details.
%% 
%% (c) 1995-2016 Gerd Neugebauer
%% 
%% Net: gene@gerd-neugebauer.de
%% 
%% This program is free software; you can redistribute it and/or modify
%% it under the terms of the GNU General Public License as published by
%% the Free Software Foundation; either version 2, or (at your option)
%% any later version.
%%
%% This program is distributed in the hope that it will be useful,
%% but WITHOUT ANY WARRANTY; without even the implied warranty of
%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%% GNU General Public License for more details.
%%
%% You should have received a copy of the GNU General Public License
%% along with this program; if not, write to the Free Software
%% Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Sort order for fields
%

sort.order{article =
	 author
	#title
	#journal
	#year
	#volume
	#number
	#pages
	#month
	#note }
sort.order{book =
	 author
	#editor
	#title
	#publisher
	#year
	#volume
	#series
	#address
	#edition
	#month
	#note}
sort.order{booklet =
	 author
	#title
	#howpublished
	#address
	#month
	#year
	#note}
sort.order{conference =
	 author
	#title
	#editor
	#booktitle
	#year
	#series
	#volume
	#pages
	#address
	#month
	#organization
	#publisher
	#note}
sort.order{inproceedings =
	 author
	#title
	#editor
	#booktitle
	#year
	#series
	#volume
	#pages
	#address
	#month
	#organization
	#publisher
	#note}
sort.order{inbook =
	 author
	#editor
	#title
	#chapter
	#pages
	#publisher
	#year
	#volume
	#number
	#series
	#type
	#address
	#edition
	#month
	#note}
sort.order{incollection=
	 author
	#title
	#editor
	#booktitle
	#publisher
	#year
	#volume
	#number
	#series
	#type
	#chapter
	#pages
	#address
	#edition
	#month
	#note}
sort.order{manual=
	 author
	#title
	#organization
	#address
	#edition
	#month
	#year
	#note }
sort.order{mastersthesis=
	 author
	#title
	#school
	#year
	#type
	#address
	#month
	#note}
sort.order{misc=
	 author
	#title
	#howpublished
	#year
	#month
	#note}
sort.order{phdthesis =
	 author
	#title
	#school
	#year
	#type
	#address
	#month
	#note
	}
sort.order{proceedings =
	 title
	#year
	#editor
	#volume
	#number
	#series
	#address
	#month
	#organization
	#publisher
	#note}
sort.order{techreport =
	 author
	#title
	#institution
	#year
	#type
	#number
	#address
	#month
	#note}
sort.order{unpublished =
	 author
	#title
	#year
	#month
	#note}
