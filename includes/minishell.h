/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:06:06 by saeby             #+#    #+#             */
/*   Updated: 2023/01/30 17:21:25 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define SUCCESS 0
# define ERROR 1

enum	e_token_types
{
	MSH_SEP = 100,
	MSH_STR,
	MSH_WORD,
	MSH_SYMBOL,
	MSH_DQUOTE,
	MSH_SQUOTE,
	MSH_PIPE,
	MSH_DPIPE,
	MSH_LT,
	MSH_DLT,
	MSH_GT,
	MSH_DGT,
	MSH_AMP,
	MSH_DAMP,
	MSH_DOLLAR,
	MSH_L_BR,
	MSH_R_BR,
	MSH_L_CBR,
	MSH_R_CBR,
	MSH_L_SBR,
	MSH_R_SBR,
	MSH_MINUS,
	MSH_DMINUS,
	MSH_END,
	MSH_FILENAME,
	MSH_PARAM,
	MSH_PATH,
	MSH_VAR,
	MSH_DELIM
};

/*
	MSH_SEP // separator => isspace / 100
	MSH_STR, // string / 101
	MSH_WORD, //word => text not between quote / 102
	MSH_SYMBOL, // symbol => special characters (. .. , ! + _ @) / 103
	MSH_DQUOTE, // double quote / 104
	MSH_SQUOTE, // single quote / 105
	MSH_PIPE, // pipe / 106
	MSH_DPIPE, // double pipe / 107
	MSH_LT, // < / 108
	MSH_DLT, // << / 109
	MSH_GT, // > / 110
	MSH_DGT, // >> / 111
	MSH_AMP, // & / 112
	MSH_DAMP, // && / 113
	MSH_DOLLAR, // $ / 114
	MSH_L_BR, // ( / 115
	MSH_R_BR, // ) / 116
	MSH_L_CBR, // { / 117
	MSH_R_CBR, // } / 118
	MSH_L_SBR, // [ / 119
	MSH_R_SBR, // ] / 120
	MSH_MINUS, // - / 121
	MSH_DMINUS, // -- / 122
	MSH_END, // end of line / 123
	MSH_FILENAME, // MSH_WORD.MSH_WORD / 124
	MSH_PARAM, // MSH_MINUSMSH_WORD / 125
	MSH_PATH // .. . / 126
	MSH_VAR // $WORD / 127
	MSH_DELIM // symbol|word after here_doc // 128
*/

// ----------------------------------------------
// Structures
// ----------------------------------------------
typedef struct s_env_list
{
	char				*key;
	char				*val;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}	t_env_list;

typedef struct s_tok_list
{
	int					type;
	char				*val;
	struct s_tok_list	*next;
}	t_tok_list;

typedef struct s_msh_data
{
	char				*name;
	char				*prompt;
	t_env_list			*env;
	t_tok_list			*tokens;
	t_tok_list			*s_tok;
}	t_msh_data;

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

// ----------------------------------------------
// msh_parser.c
// ----------------------------------------------
int			msh_parser(t_msh_data *m_data);
int			msh_exec_builtin(char *str, t_msh_data *m_data);

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
char		*msh_get_env(t_msh_data *m_data, char *key);
int			msh_replace_val(t_msh_data *m_data, char *key, char *new_val);
t_env_list	*msh_env_ptr(t_msh_data *m_data, char *key);

// ----------------------------------------------
// builtins/msh_env.c
// ----------------------------------------------
int			msh_env(t_msh_data *m_data);

// ----------------------------------------------
// builtins/msh_pwd.c
// ----------------------------------------------
int			msh_pwd(t_msh_data *m_data);
char		*msh_getpwd(t_msh_data *m_data);
void		msh_setpwd(t_msh_data *m_data, char *new_path);

// ----------------------------------------------
// builtins/msh_cd.c
// ----------------------------------------------
int			msh_cd(t_msh_data *m_data, char *new_path);

// ----------------------------------------------
// builtins/msh_exit.c
// ----------------------------------------------
void		msh_exit(t_msh_data *m_data, int exit_code);

// ----------------------------------------------
// builtins/msh_clear.c
// ----------------------------------------------
int			msh_clear(t_msh_data *m_data);

#endif