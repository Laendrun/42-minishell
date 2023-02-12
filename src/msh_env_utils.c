/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:29:27 by saeby             #+#    #+#             */
/*   Updated: 2023/02/12 13:09:13 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Loop/browse through the env linked list to
find the value associated with the
key provided and return
the length of the string value.
*/

int	msh_get_env_var_len(t_msh_data *m_data, char *key)
{
	t_env_list	*tmp;
	int			len;

	tmp = m_data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			len = ft_strlen(tmp->val);
			return (len);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
Loop/browse through the env linked list to
find the value associated with the
key provided.
*/

char	*msh_get_env(t_msh_data *m_data, char *key)
{
	t_env_list	*tmp;

	tmp = m_data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(tmp->val));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*msh_get_env_free(t_msh_data *m_data, char *key)
{
	t_env_list	*tmp;

	tmp = m_data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			free(key);
			return (ft_strdup(tmp->val));
		}
		tmp = tmp->next;
	}
	free(key);
	return (ft_strdup(""));
}

int	msh_replace_val(t_msh_data *m_data, char *key, char *new_val)
{
	t_env_list	*var;
	char		*tmp;

	var = msh_env_ptr(m_data, key);
	if (!var)
		return (1);
	tmp = var->val;
	var->val = ft_strdup(new_val);
	free(tmp);
	return (SUCCESS);
}

t_env_list	*msh_env_ptr(t_msh_data *m_data, char *key)
{
	t_env_list	*tmp;

	tmp = m_data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
