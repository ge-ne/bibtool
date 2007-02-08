%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 
%% This file is part of BibTool.
%% It is distributed under the GNU General Public License.
%% See the file COPYING for details.
%% 
%% (c) 1995-2001 Gerd Neugebauer
%% 
%% Net: gene@gerd-neugebauer.de
%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Semantic checks for year fields
%

check.rule { year "^[\"{]?[0-9][0-9][\"}]?$"   }
check.rule { year "^[\"{]?1[89][0-9][0-9][\"}]?$"   }
check.rule { year ""  
	          "\@ \$: Semantic error. Year has to be a suitable number" }

