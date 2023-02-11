/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:24:41 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 16:37:48 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://www.gnu.org/software/bash/manual/bash.html#index-export

int	print_declared_vars(t_msh_data *m_d, int out)
{
	t_env_list	*tmp;

	tmp = m_d->env;
	while (tmp)
	{
		write(out, "declare -x ", 12);
		write(out, tmp->key, ft_strlen(tmp->key));
		write(out, "=", 1);
		write(out, tmp->val, ft_strlen(tmp->val));
		write(out, "\n", 1);
		// printf("declare -x %s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void	replace(t_msh_data *m_d, char *key, char *val)
{
	msh_replace_val(m_d, key, val);
	free(val);
	free(key);
}

void	create(t_msh_data *m_d, char *key, char *val)
{
	msh_env_lstaddb(&m_d->env, msh_env_lstnew(ft_strdup(key), ft_strdup(val)));
	free(val);
	free(key);
}

int	msh_export(t_msh_data *m_d, t_cmd *cmd)
{
	size_t		i;
	char		*key;
	char		*val;
	t_env_list	*tmp;
	int			out;

	out = STDOUT_FILENO;
	if (cmd->out_app >= 0)
		out = cmd->out_app;
	if (cmd->out_trunc >= 0)
		out = cmd->out_trunc;

	if (count_args(cmd) == 1)
		return (print_declared_vars(m_d, out));
	if (!ft_strchr(cmd->args[1], '='))
		return (SUCCESS);
	i = 0;
	while (cmd->args[1][i] != '=' && cmd->args[1][i])
		i++;

	key = ft_substr(cmd->args[1], 0, i);

	val = ft_substr(cmd->args[1], i + 1, ft_strlen(cmd->args[1]) - (i + 1));
	
	tmp = msh_env_ptr(m_d, key);
		
	if (tmp)
		replace(m_d, key, val);
	else
		create(m_d, key, val);
	if (m_d->nb_cmd == 1)
		return (SUCCESS);
	exit(SUCCESS);
}

// 1. take a substring from 0 to the first = without the =
// store that as the key for the var
// 2. take a substring from the first = + 1 to the end of the line
// store that as the value for the var
// 3. check if the key already exists
// if the key exists, 
// if the key does not exist,
// add a new element to the env, with the new strdup(key) and new strdup(value)
// free the new key and new value