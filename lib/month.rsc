%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 
%% This file is part of BibTool.
%% It is distributed under the GNU General Public License.
%% See the file COPYING for details.
%% 
%% (c) 1995-2013 Gerd Neugebauer
%% 
%% Net: gene@gerd-neugebauer.de
%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% This resource file tries to introduce BibTeX strings for month names.
% Provisions are made to preserve other information contained in the 
% month field.
%


rewrite.rule { month
		= "^[\"{] *\(.*\)january\(.*\) *[\"}]$"
		# "{\1} # jan # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)february\(.*\) *[\"}]$" 
		# "{\1} # feb # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)march\(.*\) *[\"}]$" 
		# "{\1} # mar # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)april\(.*\) *[\"}]$" 
		# "{\1} # apr # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)may\(.*\) *[\"}]$" 
		# "{\1} # may # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)june\(.*\) *[\"}]$" 
		# "{\1} # jun # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)july\(.*\) *[\"}]$" 
		# "{\1} # jul # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)august\(.*\) *[\"}]$" 
		# "{\1} # aug # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)september\(.*\) *[\"}]$" 
		# "{\1} # sep # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)october\(.*\) *[\"}]$" 
		# "{\1} # oct # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)november\(.*\) *[\"}]$" 
		# "{\1} # nov # {\2}" }
rewrite.rule { month
		= "^[\"{] *\(.*\)december\(.*\) *[\"}]$" 
		# "{\1} # dec # {\2}" }

rewrite.rule { month = "^{ *} # " = ""}
rewrite.rule { month = " # { *}$" = ""}
