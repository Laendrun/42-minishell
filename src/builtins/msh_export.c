/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:24:41 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 22:50:33 by saeby            ###   ########.fr       */
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
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void	replace(t_msh_data *m_d, char *key, char *val)
{
	msh_replace_val(m_d, key, ft_strdup(val));
}

static int	create(t_msh_data *m_d, char *key, char *val)
{
	t_env_list	*new;

	new = msh_env_lstnew(ft_strdup(key), ft_strdup(val));
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_env_lstaddb(&m_d->env, new);
	return (EXIT_SUCCESS);
}

static void	set_out(t_cmd *cmd, int *out)
{
	*out = STDOUT_FILENO;
	if (cmd->out_app >= 0)
		*out = cmd->out_app;
	if (cmd->out_trunc >= 0)
		*out = cmd->out_trunc;
}

int	msh_export(t_msh_data *m_d, t_cmd *cmd)
{
	int		out;
	char	*val;

	set_out(cmd, &out);
	if (count_args(cmd) == 1)
		return (print_declared_vars(m_d, out));
	if (!str_isalnum(cmd->args[1]) && m_d->nb_cmd == 1)
		return (export_key_error(cmd->args[1], cmd->args[2]));
	else if (!str_isalnum(cmd->args[1]) && m_d->nb_cmd > 1)
		exit(export_key_error(cmd->args[1], cmd->args[2]));
	if (cmd->args[2][0] == '\'')
		val = ft_strtrim(cmd->args[2], "\'");
	else if (cmd->args[2][0] == '\"')
		val = ft_strtrim(cmd->args[2], "\"");
	else
		val = cmd->args[2];
	if (msh_env_ptr(m_d, cmd->args[1]))
		replace(m_d, cmd->args[1], val);
	else
		create(m_d, cmd->args[1], val);
	if (m_d->nb_cmd == 1)
		return (EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}
