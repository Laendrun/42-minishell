/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:06:06 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 11:47:52 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "syntax.h"
# include "lexer.h"
# include "builtins.h"
# include "tokens.h"
# include "debug.h"

# define SUCCESS 0
# define ERROR 1

// ----------------------------------------------
// msh_tok_list.c
// ----------------------------------------------
t_tok_list	*msh_tok_lstnew(int type, char *val);
void		msh_tok_lstaddb(t_tok_list **lst, t_tok_list *new);
t_tok_list	*msh_tok_lstlast(t_tok_list *lst);
int			msh_tok_lstsize(t_tok_list *lst);

// ----------------------------------------------
// msh_init.c
// ----------------------------------------------
int			msh_init(t_msh_data *m_data, char **env);
int			msh_env_init(t_msh_data *m_data, char **env);

// ----------------------------------------------
// msh_env_lst.c
// ----------------------------------------------
t_env_list	*msh_env_lstnew(char *key, char *val);
void		msh_env_lstaddb(t_env_list **lst, t_env_list *new);
t_env_list	*msh_env_lstlast(t_env_list *lst);
int			msh_env_lstsize(t_env_list *lst);

// ----------------------------------------------
// msh_lexer.c
// ----------------------------------------------
int			msh_lex(t_msh_data *m_data, char *line);

// ----------------------------------------------
// msh_parser.c
// ----------------------------------------------
int			msh_parser(t_msh_data *m_data);
int			msh_exec_builtin(char *str, t_msh_data *m_data);

// ----------------------------------------------
// msh_expand_var.c
// ----------------------------------------------

int	msh_expand_var(t_msh_data *m_d);
int	msh_replace_var_in_var(t_msh_data *m_d);
int	msh_replace_var_in_str(t_msh_data *m_d);
int	msh_flag_in_str_var(t_msh_data *m_d, t_tok_list *str_tok);
int	msh_malloc_new_str(t_msh_data *m_d, t_tok_list *str_tok, int flg[3]);

// ----------------------------------------------
// msh_free.c
// ----------------------------------------------
void		msh_free_env(t_msh_data *m_data);
void		msh_free_tok(t_msh_data *m_data);
void		msh_free_simpl_tok(t_msh_data *m_data);

// ----------------------------------------------
// msh_is.c
// ----------------------------------------------
int			msh_isspace(int c);
int			msh_isoperator(int c);
int			msh_isspec(int c);
int			msh_is_builtin(char *str);
int			msh_is_path_comp(t_tok_list *token);
int			msh_is_envvar_comp(t_tok_list *token);

// ----------------------------------------------
// msh_utils.c
// ----------------------------------------------
char		*msh_chrdup(int c);

// ----------------------------------------------
// msh_env_utils.c
// ----------------------------------------------
int			msh_get_env_var_len(t_msh_data *m_data, char *key);
char		*msh_get_env(t_msh_data *m_data, char *key);
int			msh_replace_val(t_msh_data *m_data, char *key, char *new_val);
t_env_list	*msh_env_ptr(t_msh_data *m_data, char *key);

#endif