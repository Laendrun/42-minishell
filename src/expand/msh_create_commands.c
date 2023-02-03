/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/01/31 13:40:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to create commands we need to provide good format for execve function:
// 1. cmd with path (char *)
// 2. cmd with args (char **)
// 3. env (char**)


// int	msh_create_commmands(t_msh_data *m_d)
// {
// 	t_tok_list	*cur;

// 	cur = m_d->s_tok;
// 	while (cur)
// 	{
// 		if (cur->type == MSH_PIPE || cur->type == MSH_END)
// 			msh_remove_tok(&m_d->s_tok, cur);
// 		cur = cur->next;
// 	}
// 	return (SUCCESS);
// }

char	**msh_make_env_str(t_msh_data *m_d)
{
	int i;
	int size;
	t_env_list *tmp;

	i = 0;
	tmp = m_d->env;
	size = msh_env_lstsize(m_d->env);
	char **env_str = malloc(sizeof(char *) * (size + 1));
	if (!env_str)
		return NULL;
	while (tmp)
	{
		env_str[i] = malloc(strlen(tmp->key) + strlen(tmp->val) + 2);
		ft_strcpy(env_str[i], tmp->key);
		ft_strcat(env_str[i], "=");
		ft_strcat(env_str[i], tmp->val);
		i++;
		tmp = tmp->next;
	}
	env_str[size] = 0;
	return (env_str);
}
