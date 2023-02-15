/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_create_cmd2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:06:51 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 20:08:02 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**msh_make_env_tabstr(t_msh_data *m_d)
{
	int			i;
	int			size;
	t_env_list	*tmp;
	char		**env_str;

	i = 0;
	tmp = m_d->env;
	size = msh_env_lstsize(m_d->env);
	env_str = malloc(sizeof(char *) * (size + 1));
	if (!env_str)
		return (NULL);
	while (tmp)
	{
		env_str[i] = malloc(strlen(tmp->key) + strlen(tmp->val) + 2);
		if (!env_str[i])
			return (NULL);
		ft_strcpy(env_str[i], tmp->key);
		ft_strcat(env_str[i], "=");
		ft_strcat(env_str[i], tmp->val);
		i++;
		tmp = tmp->next;
	}
	env_str[size] = 0;
	return (env_str);
}
