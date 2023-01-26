/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:06:06 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 21:03:18 by saeby            ###   ########.fr       */
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
	MSH_SEP = 100, // separator => isspace
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
	MSH_END // end of line / 123
};

// ----------------------------------------------
// Structures
// ----------------------------------------------
typedef struct	s_env_list
{
	char				*key;
	char				*val;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}	t_env_list;

typedef struct	s_tok_list
{
	int					type;
	char				*val;
	struct s_tok_list	*next;
}	t_tok_list;

typedef struct	s_msh_data
{
	char				*name;
	char				*prompt;
	t_env_list			*env;
	t_tok_list			*tokens;
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
// msh_lex_quotes.c
// ----------------------------------------------
int			msh_lex_quotes(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_lex_squote(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_lex_dquote(t_msh_data *m_data, char *line, unsigned int *i);

// ----------------------------------------------
// msh_lex_operator.c
// ----------------------------------------------
int			msh_lex_operator(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_get_op_type(int c);
int			msh_get_double_op_type(int type);

// ----------------------------------------------
// msh_lex_symbol.c
// ----------------------------------------------
int			msh_lex_symbol(t_msh_data *m_data, char *line, unsigned int *i);
int			msh_get_spec_type(int c);

// ----------------------------------------------
// msh_lex_word.c
// ----------------------------------------------
int			msh_lex_word(t_msh_data *m_data, char *line, unsigned int *i);

// ----------------------------------------------
// msh_lex_dollar.c
// ----------------------------------------------
int			msh_lex_dollar(t_msh_data *m_data, char *line, unsigned int *i);

// ----------------------------------------------
// msh_free.c
// ----------------------------------------------
void		msh_free_env(t_msh_data *m_data);
void		msh_free_tok(t_msh_data *m_data);

// ----------------------------------------------
// msh_is.c
// ----------------------------------------------
int			msh_isspace(int c);
int			msh_isoperator(int c);
int			msh_isspec(int c);

// ----------------------------------------------
// msh_utils.c
// ----------------------------------------------
char		*msh_chrdup(int c);

// ----------------------------------------------
// builtins/msh_env.c
// ----------------------------------------------
int			msh_env(t_msh_data *m_data);

#endif