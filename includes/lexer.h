/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:41:59 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 16:48:52 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "structures.h"

// ----------------------------------------------
// src/msh_lexer.c
// ----------------------------------------------
int			msh_get_op_type(int c);
int			msh_dop_type(int type);

// ----------------------------------------------
// lexer/msh_lex_pipe.c
// ----------------------------------------------
int	msh_lex_pipe(t_msh_data *m_d, char *line, unsigned int *i);

// ----------------------------------------------
// lexer/msh_lex_quotes.c
// ----------------------------------------------
int			msh_lex_quotes(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_lex_squote(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_lex_dquote(t_msh_data *m_data, char *line, unsigned int *i);

// ----------------------------------------------
// lexer/msh_lex_redir.c
// ----------------------------------------------
int	msh_lex_redir(t_msh_data *m_d, char *line, unsigned int *i);

// ----------------------------------------------
// lexer/msh_lex_vars.c
// ----------------------------------------------
int	msh_lex_vars(t_msh_data *m_d, char *line, unsigned int *i);

// ----------------------------------------------
// lexer/msh_lex_word.c
// ----------------------------------------------
int			msh_lex_word(t_msh_data *m_data, char *line, unsigned int *i);

#endif