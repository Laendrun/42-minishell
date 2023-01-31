/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:41:59 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 11:43:29 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "structures.h"

// ----------------------------------------------
// lexer/msh_lex_quotes.c
// ----------------------------------------------
int			msh_lex_quotes(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_lex_squote(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_lex_dquote(t_msh_data *m_data, char *line, unsigned int *i);

// ----------------------------------------------
// lexer/msh_lex_operator.c
// ----------------------------------------------
int			msh_lex_operator(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_get_op_type(int c);
int			msh_dop_type(int type);

// ----------------------------------------------
// lexer/msh_lex_symbol.c
// ----------------------------------------------
int			msh_lex_symbol(t_msh_data *m_data, char *line, unsigned int *i);

// ----------------------------------------------
// lexer/msh_lex_word.c
// ----------------------------------------------
int			msh_lex_word(t_msh_data *m_data, char *line, unsigned int *i);

// ----------------------------------------------
// lexer/msh_lex_simpl.c
// ----------------------------------------------
int			msh_simplify_tokens(t_msh_data *m_d);
t_tok_list	*msh_simpl_word(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne);
t_tok_list	*msh_simpl_minus(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne);
t_tok_list	*msh_simpl_path(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne);
t_tok_list	*msh_set_delim(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne);
t_tok_list	*msh_set_var(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne);

// ----------------------------------------------
// lexer/msh_lex_simpl_helper.c
// ----------------------------------------------
char		*msh_fn_from_tok(char *fn, char *ext);
char		*msh_par_from_tok(char *val);

#endif