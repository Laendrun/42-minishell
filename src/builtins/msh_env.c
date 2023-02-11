/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:37 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 16:34:58 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(t_msh_data *m_d, t_cmd *cmd)
{
	t_env_list	*tmp;
	int			out;

	out = STDOUT_FILENO;
	if (cmd->out_app >= 0)
		out = cmd->out_app;
	if (cmd->out_trunc >= 0)
		out = cmd->out_trunc;

	if (count_args(cmd) > 1)
	{
		f_error("env: <args[1]>: ", strerror(ENOENT), m_d);
		return (ERROR);
	}
	tmp = m_d->env;
	while (tmp)
	{
		write(out, tmp->key, ft_strlen(tmp->key));
		write(out, "=", 1);
		write(out, tmp->val, ft_strlen(tmp->val));
		write(out, "\n", 1);
		// printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	if (m_d->nb_cmd == 1)
		return (SUCCESS);
	exit(SUCCESS);
}
