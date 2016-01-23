/*** builtin.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

BIND("add.field"		);   		   /* RscByFct	             */
BindBool("apply.alias"		, g_apply_alias, rsc_apply_alias);
BindBool("apply.modify"		, g_apply_modify, rsc_apply_modify);
BindBool("apply.include"		, g_apply_include, rsc_apply_include);
Bind("and"			, sym_and);  	   
BindStr("bibtex.env.name"	     , g_e_bibtex, rsc_e_bibtex);
BindStr("bibtex.search.path"         , g_v_bibtex, rsc_v_bibtex);
BindBool("check.double"		, g_check_double, rsc_double_check);
BindBool("check.double.delete"	, g_check_double_delete, rsc_del_dbl);
BIND("check.rule"		);   		   /* RscByFct	             */
BindBool("check.case.sensitive"	, g_check_case_sensitive, rsc_case_check);
BIND("clear.ignored.words"	);   		   /* RscByFct	             */
BindBool("count.all"		, g_count_all, rsc_cnt_all);
BindBool("count.used"		, g_count_used, rsc_cnt_used);
BindNum( "crossref.limit"	   , g_xref_limit     ,rsc_xref_limit     );
BIND("default.key"		);   		   /* RscByFct	             */
BIND("delete.field"		);   		   /* RscByFct	             */
BindStr("dir.file.separator"         , g_dir_file_sep, rsc_dir_file_sep);
BindBool("dump.symbols"		, g_dump_symbols, rsc_dump_symbols);
BindStr("env.separator"	             , g_env_sep, rsc_env_sep);
BIND("extract.file"		);   		   /* RscByFct	             */
BIND("extract.regex"		);   		   /* RscByFct	             */
BindBool("expand.macros"		, g_expand_macros, rsc_expand_macros);
BindBool("expand.crossref"	, g_expand_crossref, rsc_expand_crossref);
BIND("fmt.inter.name"		);   		   /* RscByFct	             */
BIND("fmt.name.pre"		);   		   /* RscByFct	             */
BIND("fmt.name.name"		);   		   /* RscByFct	             */
BIND("fmt.name.title"		);   		   /* RscByFct	             */
BIND("fmt.title.title"	);   		   /* RscByFct	             */
BIND("fmt.et.al"		);   		   /* RscByFct	             */
BIND("fmt.word.separator"	);   		   /* RscByFct	             */
BIND("field.type"		);   		   /* RscByFct	             */
Bind("false"			, sym_false);	   
BIND("input"			);   		   /* RscByFct	             */
BIND("ignored.word"		);   		   /* RscByFct	             */
Bind("ilike"			, sym_ilike);	   
BindBool("key.generation"	, g_make_key, rsc_make_key);
BIND("key.base"		);   		   /* RscByFct	             */
BIND("key.format"		);   		   /* RscByFct	             */
BindBool("key.make.alias"	, g_key_make_alias, rsc_make_alias);
BIND("key.number.separator"	);   		   /* RscByFct	             */
BindBool("key.expand.macros"	, g_key_expand_macros, rsc_key_expand_macros);
Bind("like"			, sym_like); 	   
BIND("macro.file"		);   		   /* RscByFct	             */
Bind("mod"			, sym_mod);  	   
BIND("new.entry.type"		);   		   /* RscByFct	             */
BIND("new.field.type"		);   		   /* RscByFct	             */
BIND("new.format.type"	);   		   /* RscByFct	             */
Bind("not"			,sym_not);   	   
BIND("nil"			);   		   
BIND("output.file"		);   		   /* RscByFct	             */
Bind("or"			,sym_or);	   
BindBool("pass.comments"	, g_pass_comments, rsc_pass_comment);
BindBool("preserve.key.case"	, g_preserve_key_case, rsc_key_case);
BindBool("preserve.keys"	, g_preserve_keys, rsc_key_preserve);
BindGet("print"		, g_print);	   /* RscByFct	             */
BindNum( "print.align.string"    , g_col_s	  ,rsc_col_s	  );
BindNum( "print.align.comment"   , g_col_c	  ,rsc_col_c	  );
BindNum( "print.align.preamble"  , g_col_p	  ,rsc_col_p	  );
BindNum( "print.align.key"	   , g_col_key	  ,rsc_col_key	  );
BindNum( "print.align"	   , g_col		  ,rsc_col		  );
BindBool("print.all.strings"	, g_print_all_strings, rsc_all_macs);
BindStr("print.entry.types"          , g_print_et, rsc_print_et);
BindBool("print.equal.right"	, g_eq_right, rsc_eq_right);
BindBool("print.braces"	, g_braces, rsc_braces);
BindBool("print.comma.at.end"	, g_print_ce, rsc_print_ce);
BindStr("print.deleted.prefix"       , g_del_pre, rsc_del_pre);
BindBool("print.deleted.entries", g_del_q_entries, rsc_del_q);
BindNum( "print.indent"	   , g_indent	  ,rsc_indent	  );
BindNum( "print.line.length"     , g_linelen	  ,rsc_linelen	  );
BindNum( "print.newline"         , g_newlines	  ,rsc_newlines	  );
BindBool("print.parentheses"	, g_parentheses, rsc_parentheses);
BindBool("print.terminal.comma", g_print_tc, rsc_print_tc);
BindBool("print.use.tab"	, g_use_tabs, rsc_use_tabs);
BindBool("print.wide.equal"	, g_print_we, rsc_print_we);
Bind("quote"			, sym_quote);	   /*	                     */
BindBool("quiet"		, g_quiet, rsc_quiet);
BIND("regexp.syntax"		);   		   /* RscByFct	             */
BIND("rename.field"		);   		   /* RscByFct	             */
BIND("resource"		);   		   /* RscByFct	             */
BIND("resource.search.path"	);   		   /* RscByFct	             */
BIND("rewrite.rule"		);   		   /* RscByFct	             */
BindBool("rewrite.case.sensitive", g_case_rewrite, rsc_case_rewrite);
BindNum( "rewrite.limit"	   , g_rewrite_limit  ,rsc_rewrite_limit  );
BIND("select"			);   		   /* RscByFct	             */
BIND("select.by.string"	);   		   /* RscByFct	             */
BIND("select.by.non.string"	);   		   /* RscByFct	             */
BindStr("select.by.string.ignored"   , g_sel_ignored, rsc_sel_ignored);
BindBool("select.case.sensitive", g_case_select, rsc_case_select);
BindStr("select.fields"	             , g_sel_fields, rsc_sel_fields);
BIND("select.non"		);   		   /* RscByFct	             */
BindBool("select.crossrefs"	, g_xref_select, rsc_xref_select);
BindBool("sort"		, g_sort, rsc_sort);
BindBool("sort.cased"		, g_sort_cased, rsc_sort_cased);
BindBool("sort.macros"	, g_srt_macs, rsc_srt_macs);
BindBool("sort.reverse"	, g_sort_reverse, rsc_sort_reverse);
BIND("sort.order"		);   		   /* RscByFct	             */
BIND("sort.format"		);   		   /* RscByFct	             */
BindBool("suppress.initial.newline", g_no_nl, rsc_no_nl);
BIND("symbol.type"		);   		   /* RscByFct	             */
BIND("tex.define"		);   		   /* RscByFct	             */
Bind("true"			, sym_true);  	   
BindBool("verbose"		, g_verbose, rsc_verbose);
BindGet("version"		, g_version);	   /* RscByFct	             */
						   /*                        */
Bind("function"	, sym_fct);	   	   /*                        */
Bind("="		, sym_set);	   	   /*                        */
Bind("=="		, sym_eq);	   	   /*                        */
Bind("<="		, sym_le);	   	   /*                        */
Bind("<"		, sym_lt);	   	   /*                        */
Bind(">="		, sym_ge);	   	   /*                        */
Bind(">"		, sym_gt);	   	   /*                        */
Bind("!="		, sym_ne);	   	   /*                        */
Bind("+"		, sym_plus);	   	   /*                        */
Bind("-"		, sym_minus);	   	   /*                        */
Bind("*"		, sym_times);	   	   /*                        */
Bind("/"		, sym_div);	   	   /*                        */
Bind("&&"		, sym_and);	   	   /*                        */
Bind("||"		, sym_or);	   	   /*                        */
Bind("!"		, sym_not);	   	   /*                        */
Bind("%"		, sym_mod);	   	   /*                        */
Bind("'"		, sym_quote);	   	   /*                        */
BIND("`"		);			   /*                        */

/*---------------------------------------------------------------------------*/
