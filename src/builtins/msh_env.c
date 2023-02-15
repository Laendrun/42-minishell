/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:37 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 19:25:02 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_out(t_cmd *cmd, int *out);

int	msh_env(t_msh_data *m_d, t_cmd *cmd)
{
	t_env_list	*tmp;
	int			out;

	set_out(cmd, &out);
	if (count_args(cmd) > 1)
	{
		if (m_d->nb_cmd == 1)
			return (msh_error(EXIT_FAILURE, ERR_ENV_ARGS, 1));
		exit (msh_error(EXIT_FAILURE, ERR_ENV_ARGS, 1));
	}
	tmp = m_d->env;
	while (tmp)
	{
		write(out, tmp->key, ft_strlen(tmp->key));
		write(out, "=", 1);
		write(out, tmp->val, ft_strlen(tmp->val));
		write(out, "\n", 1);
		tmp = tmp->next;
	}
	if (m_d->nb_cmd == 1)
		return (SUCCESS);
	exit(SUCCESS);
}

static void	set_out(t_cmd *cmd, int *out)
{
	*out = STDOUT_FILENO;
	if (cmd->out_app >= 0)
		*out = cmd->out_app;
	if (cmd->out_trunc >= 0)
		*out = cmd->out_trunc;
}
