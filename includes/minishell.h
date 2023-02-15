/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/12 16:34:26 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <signal.h>
# include "libft.h"
# include "syntax.h"
# include "lexer.h"
# include "builtins.h"
# include "tokens.h"
# include "free.h"
# include "debug.h"
# include "errors.h"

# define SUCCESS 0
# define ERROR 1

# define RESET "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"

extern int	g_code;

void	msh_pip_reset(t_msh_data *m_data);


// ----------------------------------------------
// main.c
// ----------------------------------------------
void	msh_set_gcode(int val);
int		msh_get_gcode(void);
int		new_line(t_msh_data *m_d, char *line);

// ----------------------------------------------
// msh_tok_list.c
// ----------------------------------------------
t_tok_list	*msh_tok_lstnew(int type, char *val);
void		msh_tok_lstaddb(t_tok_list **lst, t_tok_list *new);
t_tok_list	*msh_tok_lstlast(t_tok_list *lst);
int			msh_tok_lstsize(t_tok_list *lst);
t_tok_list *msh_remove_tok(t_tok_list **lst, t_tok_list *tok_to_remove);

// ----------------------------------------------
// msh_set_signals.c
// ----------------------------------------------

void	msh_set_signals(void);
void	sigint_update(void);
void	handle_sighup(void);

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
void		insert_token(t_msh_data *m_d, int type, char *val, int *err);

// ----------------------------------------------
// msh_parser.c
// ----------------------------------------------
int			msh_parser(t_msh_data *m_data);

// ----------------------------------------------
// msh_cmds_lst.c
// ----------------------------------------------

t_cmd	*msh_cmd_lstnew(char *cmd, char **args);
void	msh_cmd_lstaddb(t_cmd **lst, t_cmd *new);
t_cmd	*msh_cmd_lstlast(t_cmd *lst);
int		msh_cmd_lstsize(t_cmd *lst);

// ----------------------------------------------
// msh_expand_var.c
// ----------------------------------------------

int	msh_expand_var(t_msh_data *m_d);
int	msh_replace_var_in_var(t_msh_data *m_d);
int	msh_replace_var_in_str(t_msh_data *m_d);
// int	msh_flag_in_str_var(t_msh_data *m_d, t_tok_list *str_tok);
int	msh_flag_in_str_var(t_msh_data *m_d, t_tok_list *str_tok, char *ret);
int	msh_malloc_new_str(t_msh_data *m_d, t_tok_list *str_tok, int flg[3]);
int	msh_handle_quotes(t_msh_data *m_d);
int	msh_escape_char(t_msh_data *m_d);
char	**msh_make_env_tabstr(t_msh_data *m_d);
int	msh_create_commmands(t_msh_data *m_d);
int	msh_redir_op(t_msh_data *m_d);
int	msh_err_near_token(t_msh_data *d);

// ----------------------------------------------
// parsing
// ----------------------------------------------

char	*msh_var_in_hdoc(t_msh_data *m_d, char *tok);
int		get_nb_args(t_tok_list *d);
void	calculate_nb_cmds(t_msh_data *m_d);
int	set_redir_in_cmd_lst(t_msh_data *m_d, int i);
int	ft_here_doc(t_msh_data *m_d, t_cmd *end);

// ----------------------------------------------
// msh_pipex.c
// ----------------------------------------------

int	msh_pipex(t_msh_data *m_d);
int	pipex(t_msh_data *m_d);
// void	f_fork(t_msh_data *m_d);
int	f_fork(t_msh_data *m_d, t_cmd *tmp);
// void	f_error(char *str, char *erno, t_msh_data *d);
// void	free_tab_char(char **str);
// void	close_fd_tab(int *fd, int size, t_msh_data *d);
char	**pip_get_path(char **env);

// ----------------------------------------------
// msh_is.c
// ----------------------------------------------
int			msh_isspace(int c);
int			msh_isoperator(int c);
int			msh_isspec(int c);
int			msh_is_builtin(char *str);
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
char	*msh_get_env_free(t_msh_data *m_data, char *key);

// ----------------------------------------------
// msh_terminate.c
// ----------------------------------------------
void		msh_terminate(t_msh_data *m_data);

#endif