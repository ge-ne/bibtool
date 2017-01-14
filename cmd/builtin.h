/*** builtin.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2017 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

Bind(	 "=",			     g_setq,
				     NULL,		SYM_NONE, L_SET	     )
Bind(	 "==",			     g_eq,
				     NULL,		SYM_NONE, L_EQ	     )
Bind(	 "!=",			     g_ne,
				     NULL,		SYM_NONE, L_NE	     )
Bind(	 "<=",			     g_le,
				     NULL,		SYM_NONE, L_LE	     )
Bind(	 "<",			     g_lt,
				     NULL,		SYM_NONE, L_LT	     )
Bind(	 ">=",			     g_ge,
				     NULL,		SYM_NONE, L_GE	     )
Bind(	 ">",			     g_gt,
				     NULL,		SYM_NONE, L_GT	     )
Bind(	 "+",			     g_plus,
				     NULL,		SYM_NONE, L_PLUS     )
Bind(	 "-",			     g_minus,
				     NULL,		SYM_NONE, L_MINUS    )
Bind(	 "*",			     g_times,
				     NULL,		SYM_NONE, L_TIMES    )
Bind(	 "/",			     g_div,
				     NULL,		SYM_NONE, L_DIV	     )
Bind(	 "%",			     g_mod,
				     NULL,		SYM_NONE, L_MOD	     )
Bind(	 "'",			     NULL,
				     NULL,		SYM_NONE, L_QUOTE    )
Bind(	 "&&",			     g_and,
				     NULL,		SYM_NONE, L_AND	     )
Bind(	 "||",			     g_or,
				     NULL,		SYM_NONE, L_OR	     )
Bind(	 "!",			     g_not,
				     NULL,		SYM_NONE, L_NOT	     )
Bind(	 "`",			     NULL,
				     NULL,		SYM_NONE, L_VAR      )
BindFunc("add.field",		     g_add_field,	get_add_fields(),
				     s_add_field,	add_field(val)	     )
BindBool("apply.alias",		     g_apply_alias,
				     s_apply_alias,	rsc_apply_alias	     )
BindBool("apply.modify",	     g_apply_modify,
				     s_apply_modify,	rsc_apply_modify     )
BindBool("apply.include",	     g_apply_include,
				     s_apply_include,	rsc_apply_include    )
Bind(	 "and",			     g_and,
				     g_and,		SYM_NONE, L_AND	     )
BindStr( "bibtex.env.name",	     g_e_bibtex,
				     s_e_bibtex,	rsc_e_bibtex	     )
BindStr( "bibtex.search.path",	     g_v_bibtex,
				     s_v_bibtex,	rsc_v_bibtex	     )
BindBool("check.double",	     g_double_check,
				     s_double_check,	rsc_double_check     )
BindBool("check.double.delete",	     g_del_dbl,
				     s_del_dbl,		rsc_del_dbl	     )
BindFct( "check.rule",		     g_check_rule,
				     s_check_rule,	add_check_rule(val)  )
BindBool("check.case.sensitive",     g_case_check,
				     s_case_check,	rsc_case_check	     )
Bind(	 "class",		     NULL,
				     NULL,		SYM_NONE, L_CLASS    )
Bind(    "clear.ignored.words",	     g_cl_ign_words,
				     g_cl_ign_words,	SYM_BUILTIN, L_VAR   )
BindBool("count.all",		     g_count_all,
				     s_count_all,	rsc_cnt_all	     )
BindBool("count.used",		     g_count_used,
				     s_count_used,	rsc_cnt_used	     )
BindNum( "crossref.limit",	     g_xref_limit,
				     s_xref_limit,	rsc_xref_limit	     )
BindFunc("default.key",		     g_def_key,		StringTerm(get_separator(0)),
	 			     s_def_key,		set_separator(0,val) )
Bind(	 "defun",		     NULL,
				     NULL,		SYM_NONE, L_DEFUN    )
BindFct( "delete.field",	     g_del_f,
				     s_del_f,		add_rewrite_rule(val))
BindStr( "dir.file.separator",	     g_dir_file_sep,
				     s_dir_file_sep,	rsc_dir_file_sep     )
BindBool("dump.symbols",	     g_dump_symbols,
				     s_dump_symbols,	rsc_dump_symbols     )
Bind(	 "each",		     NULL,
				     NULL,		SYM_NONE, L_EACH     )
Bind(	 "else",		     NULL,
				     NULL,		SYM_NONE, L_ELSE     )
BindStr( "env.separator",	     g_env_sep,
				     s_env_sep,		rsc_env_sep	     )
BindFct( "extract.file",	     g_extr_file,
				     s_extr_file,	read_aux(val,save_input_file,FALSE) )
BindFct( "extract.regex",	     g_extr_regex,
				     s_extr_regex,	save_regex(val)	     )
BindBool("expand.macros",	     g_exp_macros,
				     s_exp_macros,	rsc_expand_macros    )
BindBool("expand.crossref",	     g_exp_crossref,
				     s_exp_crossref,	rsc_expand_crossref  )
BindSym( "false",		     sym_false				     )
BindFunc("fmt.inter.name",	     g_f_in,		StringTerm(get_separator(1)),
	 			     s_f_in,		set_separator(1,val) )
BindFunc("fmt.name.pre",	     g_f_n_p,		StringTerm(get_separator(2)),
	 			     s_f_n_p,		set_separator(2,val) )
BindFunc("fmt.name.name",	     g_f_n_n,		StringTerm(get_separator(3)),
	 			     s_f_n_n,		set_separator(3,val) )
BindFunc("fmt.name.title",	     g_f_n_t,		StringTerm(get_separator(4)),
	 			     s_f_n_t,		set_separator(4,val) )
BindFunc("fmt.title.title",	     g_f_t_t,		StringTerm(get_separator(5)),
	 			     s_f_t_t,		set_separator(5,val) )
BindFunc("fmt.et.al",		     g_f_etal,		StringTerm(get_separator(7)),
	 			     s_f_etal,		set_separator(7,val) )
BindFct( "fmt.word.separator",	     g_f_w_sep,
				     s_f_w_sep,		add_word_sep(val)    )
BindFct( "field.type",		     g_fld_type,
				     s_fld_type,	set_symbol_type(val) )
Bind(	 "function",		     NULL,
				     NULL,		SYM_NONE, L_FUNCTION )
Bind(	 "input",		     g_input,
				     s_input,		SYM_BUILTIN, L_VAR   )
Bind(	 "if",			     NULL,
				     NULL,		SYM_NONE, L_IF	     )
BindFunc("ignored.word",	     g_ign_word,	g_ign_(binding,term),
				     s_ign_word,	add_ignored_word(val))
Bind(	 "ilike",		     NULL,
				     NULL,		SYM_NONE, L_ILIKE    )
BindBool("key.generation",	     g_make_key,
				     s_make_key,	rsc_make_key	     )
BindFunc("key.base",		     g_key_base,	StringTerm(get_base()),
				     s_key_base,	set_base(val)	     )
BindFct( "key.format",		     g_key_fmt,
				     s_key_fmt,		add_format((char*)val))
BindBool("key.make.alias",	     g_make_alias,
				     s_make_alias,	rsc_make_alias	     )
BindFunc("key.number.separator",     g_key_num_sep,	StringTerm(get_separator(6)),
				     s_key_num_sep,	set_separator(6,val) )
BindBool("key.expand.macros",	     g_key_exp_macs,
				     s_key_exp_macs,	rsc_key_expand_macros)
Bind(	 "like",		     NULL,
				     NULL,		SYM_NONE, L_LIKE     )
Bind(	 "macro.file",		     g_macro_file,
				     s_macro_file,	SYM_BUILTIN, L_VAR   )
Bind(	 "mod",			     g_mod,
				     NULL,		SYM_NONE, L_MOD	     )
BindFct( "new.entry.type",	     g_entry_type,
				     s_entry_type,	def_entry_type(val)  )
BindFct( "new.field.type",	     g_field_type,
				     s_field_type,	def_field_type(val)  )
BindFct( "new.format.type",	     g_fmt_type,
				     s_fmt_type,	def_format_type(val) )
Bind(	 "not",			     g_not,
				     NULL,		SYM_NONE, L_NOT	     )
Bind(	 "nil",			     g_self,
				     NULL,		SYM_NONE, L_CONS     )
Bind(	 "output.file",		     g_out_file,
				     s_out_file,	SYM_BUILTIN, L_VAR   )
Bind(	 "or",			     g_or,
				     NULL,		SYM_NONE, L_OR	     )
BindBool("pass.comments",	     g_pass_comments,
				     s_pass_comments,	rsc_pass_comment     )
BindBool("preserve.key.case",	     g_key_case,
				     s_key_case,	rsc_key_case	     )
BindBool("preserve.keys",	     g_preserve_keys,
				     s_preserve_keys,	rsc_key_preserve     )
Bind(	 "print",		     g_print,
				     g_print,		SYM_BUILTIN, L_VAR   )
BindNum( "print.align.string",	     g_col_s,
				     s_col_s,		rsc_col_s	     )
BindNum( "print.align.comment",	     g_col_c,
				     s_col_c,		rsc_col_c	     )
BindNum( "print.align.preamble",     g_col_p,
				     s_col_p,		rsc_col_p	     )
BindNum( "print.align.key",	     g_col_key,
				     s_col_key,		rsc_col_key	     )
BindNum( "print.align",		     g_col,
				     s_col,		rsc_col		     )
BindBool("print.all.strings",	     g_all_macs,
				     s_all_macs,	rsc_all_macs	     )
BindStr( "print.entry.types",	     g_print_et,
				     s_print_et,	rsc_print_et	     )
BindBool("print.equal.right",	     g_eq_right,
				     s_eq_right,	rsc_eq_right	     )
BindBool("print.braces",	     g_braces,
				     s_braces,		rsc_braces	     )
BindBool("print.comma.at.end",	     g_print_ce,
				     s_print_ce,	rsc_print_ce	     )
BindStr( "print.deleted.prefix" ,    g_del_pre,
				     s_del_pre,		rsc_del_pre	     )
BindBool("print.deleted.entries",    g_del_q_entries,
				     s_del_q_entries,	rsc_del_q	     )
BindNum( "print.indent",	     g_indent,
				     s_indent,		rsc_indent	     )
BindNum( "print.line.length",	     g_linelen,
				     s_linelen,		rsc_linelen	     )
BindNum( "print.newline",	     g_newlines,
				     s_newlines,	rsc_newlines	     )
BindBool("print.parentheses",	     g_parentheses,
				     s_parentheses,	rsc_parentheses	     )
BindBool("print.terminal.comma",     g_print_tc,
				     s_print_tc,	rsc_print_tc	     )
BindBool("print.use.tab",	     g_use_tabs,
				     s_use_tabs,	rsc_use_tabs	     )
BindBool("print.wide.equal",	     g_print_we,
				     s_print_we,	rsc_print_we	     )
Bind(	 "quote",		     NULL,
				     NULL,		SYM_NONE, L_QUOTE    )
BindBool("quiet",		     g_quiet,
				     s_quiet,		rsc_quiet	     )
Bind(	 "read",		     g_read,
				     g_read,		SYM_NONE, L_VAR      )
BindFunc("regexp.syntax",	     g_regex_syntax,	StringTerm((String)get_regex_syntax()),
				     s_regex_syntax,	set_regex_syntax((char*)val) )
BindFct( "rename.field",	     g_rename_field,
				     s_rename_field,	rename_field(val)    )
Bind(	 "resource",		     NULL,
				     NULL,		SYM_BUILTIN, L_VAR   )
BindFunc("resource.search.path",     g_search_path,	StringTerm(rsc_v_rsc),
				     s_search_path,	set_rsc_path(val)    )
Bind(	 "return",		     NULL,
				     NULL,		SYM_NONE, L_RETURN   )
BindFct( "rewrite.rule",	     g_rewrite_rule,
				     s_rewrite_rule,	add_rewrite_rule(val))
BindBool("rewrite.case.sensitive",   g_case_rewrite,
				     s_case_rewrite,	rsc_case_rewrite     )
BindNum( "rewrite.limit",	     g_rewrite_limit,
				     s_rewrite_limit,	rsc_rewrite_limit    )
BindFct( "select",		     g_select,
				     s_select,		add_extract(val,TRUE,FALSE) )
BindFct( "select.by.string",	     g_sel_str,
				     s_sel_str,		add_extract(val,FALSE,FALSE) )
BindFct( "select.by.non.string",     g_sel_non,
				     s_sel_non,		add_extract(val,FALSE,TRUE) )
BindStr( "select.by.string.ignored", g_sel_ignored,
				     s_sel_ignored,	rsc_sel_ignored	     )
BindBool("select.case.sensitive",    g_case_select,
				     s_case_select,	rsc_case_select	     )
BindStr( "select.fields",	     g_sel_fields,
				     s_sel_fields,	rsc_sel_fields	     )
BindFct( "select.non",		     g_extract,
				     s_extract,		add_extract(val,TRUE,TRUE) )
BindBool("select.crossrefs",	     g_xref_select,
				     s_xref_select,	rsc_xref_select	     )
BindBool("sort",		     g_sort,
				     s_sort,		rsc_sort	     )
BindBool("sort.cased",		     g_sort_cased,
				     s_sort_cased,	rsc_sort_cased	     )
BindBool("sort.macros",		     g_srt_macs,
				     s_srt_macs,	rsc_srt_macs	     )
BindBool("sort.reverse",	     g_sort_reverse,
				     s_sort_reverse,	rsc_sort_reverse     )
BindFct( "sort.order",		     g_sort_order,
				     s_sort_order,	add_sort_order(val)  )
BindFct( "sort.format",		     g_sort_format,
				     s_sort_format,	add_sort_format((char*)val) )
BindBool("suppress.initial.newline", g_no_nl,
				     s_no_nl,		rsc_no_nl	     )
BindFunc("symbol.type",		     g_sym_type,	StringTerm(get_symbol_type()),
				     s_sym_type,	set_symbol_type(val) )
BindFct( "tex.define",		     g_tex_def,
				     s_tex_def,		TeX_def(val)	     )
BindSym( "true",		     sym_true				     )
Bind(	 "var",			     NULL,
				     NULL,		SYM_NONE, L_DEFVAR   )
BindBool("verbose",		     g_verbose,
				     s_verbose,		rsc_verbose	     )
Bind(	 "version",		     g_version,
				     s_version,		SYM_BUILTIN, L_VAR   )
Bind(	 "while",		     NULL,
				     NULL,		SYM_NONE, L_WHILE    )
Bind(	 "with",		     NULL,
				     NULL,		SYM_NONE, L_WITH     )

/*---------------------------------------------------------------------------*/
