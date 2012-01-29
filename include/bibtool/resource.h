/******************************************************************************
** $Id: resource.h,v 1.11 2012-01-29 17:04:08 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2012 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This file is the central component of the resource evaluator.
**	To reduce redundancy everything in this file is encapsulated
**	with macros. Thus it is possible to adapt the meaning
**	according to the task to be performed.
**	
**	This file is included several times from different places. One
**	task is the definition of certain variables used in this
**	file. Another task is the execution of the commands associated
**	with a command name.
**
**	This is one place where the power and the beauty of the C
**	preprocessor makes live easy. It should also be fun to figure out
**	the three ways in which this file is used.  Read the sources and
**	enjoy it! 
**
**	For the normal user this file is consulted automatically when
**	the header file |rsc.h| is used.
**
******************************************************************************/

#ifndef RSC_FIRST
#define RSC_FIRST(C)
#endif
#ifndef RSC_NEXT
#define RSC_NEXT(C)
#endif

RSC_FIRST('a')
  RscByFct(   "add.field"	      , r_af  ,add_field(val)		    )
  RscBoolean( "apply.alias"	      , r_aa  ,rsc_apply_alias	  , FALSE   )
  RscBoolean( "apply.modify"	      , r_am  ,rsc_apply_modify	  , FALSE   )
  RscBoolean( "apply.include"	      , r_ai  ,rsc_apply_include  , FALSE   )
RSC_NEXT('b')
  RscString(  "bibtex.env.name"	      , r_ben ,rsc_e_bibtex , RSC_BIBINPUTS ) 
  RscString(  "bibtex.search.path"    , r_bsp ,rsc_v_bibtex 
	    					     ,RSC_BIBINPUTS_DEFAULT ) 
RSC_NEXT('c')
  RscBoolean( "check.double"	      , r_cd  ,rsc_double_check	  , FALSE   )
  RscBoolean( "check.double.delete"   , r_cdd ,rsc_del_dbl	  , FALSE   )
  RscByFct(   "check.rule"	      , r_cr  ,add_check_rule(val)	    )
  RscBoolean( "check.case.sensitive"  , r_ccs ,rsc_case_check	  ,  TRUE   )
  RscByFct(   "clear.ignored.words"   , r_ciw ,clear_ignored_words()	    )
  RscBoolean( "count.all"	      , r_ca  ,rsc_cnt_all	  , FALSE   ) 
  RscBoolean( "count.used"	      , r_cu  ,rsc_cnt_used	  , FALSE   ) 
  RscNumeric( "crossref.limit"	      , r_cl  ,rsc_xref_limit     ,    32   )
RSC_NEXT('d')
  RscByFct(   "default.key"	      , r_dk  ,set_separator(0,val)	    )
  RscByFct(   "delete.field"	      , r_df  ,add_rewrite_rule(val)	    )
  RscString(  "dir.file.separator"    , r_dfs ,rsc_dir_file_sep	  , DIR_SEP )
  RscBoolean( "dump.symbols"	      , r_ds  ,rsc_dump_symbols	  , FALSE   )
RSC_NEXT('e')
  RscString(  "env.separator"	      , r_es  ,rsc_env_sep	  , ENV_SEP ) 
  RscByFct(   "extract.file"	      , r_ef  ,read_aux(val,save_input_file,FALSE))
  RscByFct(   "extract.regex"	      , r_er  ,save_regex(val)		    )
  RscBoolean( "expand.macros"	      , r_em  ,rsc_expand_macros  , FALSE   )
  RscBoolean( "expand.crossref"	      , r_ex  ,rsc_expand_crossref, FALSE   )
RSC_NEXT('f')
  RscByFct(   "fmt.inter.name"	      , r_fin ,set_separator(1,val)	    )
  RscByFct(   "fmt.name.pre"	      , r_fnp ,set_separator(2,val)	    )
  RscByFct(   "fmt.name.name"	      , r_fnn ,set_separator(3,val)	    )
  RscByFct(   "fmt.name.title"	      , r_fnt ,set_separator(4,val)	    )
  RscByFct(   "fmt.title.title"	      , r_ftt ,set_separator(5,val)	    )
  RscByFct(   "fmt.et.al"	      , r_fea ,set_separator(7,val)	    )
  RscByFct(   "fmt.word.separator"    , r_fws ,add_word_sep(val)	    )
  RscByFct(   "field.type"	      , r_ft  ,set_symbol_type((char*)val)  )
RSC_NEXT('i')
RscByFct(   "input"		      , r_i   ,save_input_file((char*)val)  )
  RscByFct(   "ignored.word"	      , r_iw  ,add_ignored_word(val)	    )
RSC_NEXT('k')
  RscBoolean( "key.generation"	      , r_kg  ,rsc_make_key	  , FALSE   ) 
  RscByFct(   "key.base"	      , r_kb  ,set_base(val)		    )
  RscByFct(   "key.format"	      , r_kf  ,add_format(val)		    )
  RscBoolean( "key.make.alias"	      , r_ma  ,rsc_make_alias	  , FALSE   ) 
  RscByFct(   "key.number.separator"  , r_kns ,set_separator(6,val)	    )
  RscBoolean( "key.expand.macros"     , r_kem ,rsc_key_expand_macros,TRUE   )
RSC_NEXT('m')
RscByFct(   "macro.file"	      , r_mf  ,save_macro_file((char*)val)  )
RSC_NEXT('n')
  RscByFct(   "new.entry.type"	      , r_net ,def_entry_type(val)	    )
  RscByFct(   "new.field.type"	      , r_nft ,def_field_type(val)	    )
  RscByFct(   "new.format.type"	      , r_nfmt,def_format_type(val)	    )
RSC_NEXT('o')
RscByFct(   "output.file"	      , r_of  ,save_output_file((char*)val) )
RSC_NEXT('p')
  RscBoolean( "pass.comments"	      , r_pc  ,rsc_pass_comment	  , FALSE   )
  RscBoolean( "preserve.key.case"     , r_pkc ,rsc_key_case	  , FALSE   )
  RscBoolean( "preserve.keys"         , r_pk  ,rsc_key_preserve	  , FALSE   )
  RscByFct(   "print"		      , r_p   ,rsc_print(val)	 	    )
  RscNumeric( "print.align.string"    , r_pas ,rsc_col_s	  ,    18   )
  RscNumeric( "print.align.comment"   , r_pac ,rsc_col_c	  ,    10   )
  RscNumeric( "print.align.preamble"  , r_pap ,rsc_col_p	  ,    11   )
  RscNumeric( "print.align.key"	      , r_pak ,rsc_col_key	  ,    18   ) 
  RscNumeric( "print.align"	      , r_pa  ,rsc_col		  ,    18   )
  RscBoolean( "print.all.strings"     , r_pam ,rsc_all_macs	  ,  TRUE   ) 
  RscString(  "print.entry.types"     , r_pet ,rsc_print_et	  , "pisnmac")
  RscBoolean( "print.equal.right"     , r_per ,rsc_eq_right	  ,  TRUE   )
  RscBoolean( "print.braces"	      , r_pb  ,rsc_braces	  ,  TRUE   )
  RscBoolean( "print.comma.at.end"    , r_pce ,rsc_print_ce	  ,  TRUE   )
  RscString(  "print.deleted.prefix"  , r_pdp ,rsc_del_pre	  , "###"   )
  RscBoolean( "print.deleted.entries" , r_pdr ,rsc_del_q	  ,  TRUE   )
  RscNumeric( "print.indent"	      , r_pi  ,rsc_indent	  ,     2   ) 
  RscNumeric( "print.line.length"     , r_pll ,rsc_linelen	  ,    77   )
  RscNumeric( "print.newline"         , r_pnl ,rsc_newlines	  ,     1   )
  RscBoolean( "print.parentheses"     , r_pp  ,rsc_parentheses	  , FALSE   )
  RscBoolean( "print.terminal.comma"  , r_ptc ,rsc_print_tc	  , FALSE   )
  RscBoolean( "print.use.tab"	      , r_put ,rsc_use_tabs	  ,  TRUE   )
  RscBoolean( "print.wide.equal"      , r_pwe ,rsc_print_we	  , FALSE   )
RSC_NEXT('q')
  RscBoolean( "quiet"		      , r_q   ,rsc_quiet	  , FALSE   )
RSC_NEXT('r')
  RscByFct(   "regexp.syntax"	      , r_rs  ,set_regex_syntax(val)	    )
  RscByFct(   "resource"	      , r_r   ,resource(val)		    )
  RscByFct(   "resource.search.path"  , r_rsp ,set_rsc_path((char*)val)	    )
  RscByFct(   "rewrite.rule"	      , r_rr  ,add_rewrite_rule(val)	    )
  RscBoolean( "rewrite.case.sensitive", r_rcs ,rsc_case_rewrite	  ,  TRUE   )
  RscNumeric( "rewrite.limit"	      , r_rl  ,rsc_rewrite_limit  ,   512   )
RSC_NEXT('s')
  RscByFct(   "select"		      , r_sel ,add_extract(val,TRUE,FALSE)  )
  RscByFct(   "select.by.string"      , r_sbs ,add_extract(val,FALSE,FALSE) )
  RscByFct(   "select.by.non.string"  , r_sbns,add_extract(val,FALSE,TRUE)  )
  RscString(  "select.by.string.ignored",r_seli,rsc_sel_ignored   ,"{}\\[] ") 
  RscBoolean( "select.case.sensitive" , r_scs ,rsc_case_select	  , FALSE   )
  RscString(  "select.fields"	      , r_self,rsc_sel_fields     , "$key"  ) 
  RscByFct(   "select.non"	      , r_seln,add_extract(val,TRUE,TRUE)   )
  RscBoolean( "select.crossrefs"      , r_sxc ,rsc_xref_select	  , FALSE   )
  RscBoolean( "sort"		      , r_s   ,rsc_sort		  , FALSE   )
  RscBoolean( "sort.cased"	      , r_sc  ,rsc_sort_cased     , FALSE   )
  RscBoolean( "sort.macros"	      , r_sm  ,rsc_srt_macs	  , TRUE    )
  RscBoolean( "sort.reverse"	      , r_sr  ,rsc_sort_reverse   , FALSE   )
RscByFct(   "sort.order"	      , r_so  ,add_sort_order(val)          )
RscByFct(   "sort.format"	      , r_sf  ,add_sort_format((char*)val)  )
  RscBoolean( "suppress.initial.newline", r_sin ,rsc_no_nl	  , FALSE   )
  RscByFct(   "symbol.type"	      , r_st  ,set_symbol_type((char*)val)  )
RSC_NEXT('t')
  RscByFct(   "tex.define"	      , r_td  ,TeX_def(val)		    ) 
RSC_NEXT('v')
  RscBoolean( "verbose"		      , r_v   ,rsc_verbose	  , FALSE   ) 
  RscByFct(   "version"		      , r_ver ,show_version()		    ) 

#undef RSC_FIRST
#undef RSC_NEXT
#undef RscNumeric
#undef RscString
#undef RscBoolean
#undef RscByFct
