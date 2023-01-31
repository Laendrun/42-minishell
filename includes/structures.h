/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:42:54 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 11:43:18 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_env_list
{
	char				*key;
	char				*val;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}				t_env_list;

typedef struct s_tok_list
{
	int					type;
	char				*val;
	struct s_tok_list	*next;
	struct s_tok_list	*prev;
}				t_tok_list;

typedef struct s_msh_data
{
	char				*name;
	char				*prompt;
	t_env_list			*env;
	t_tok_list			*tokens;
	t_tok_list			*s_tok;
}				t_msh_data;

#endif