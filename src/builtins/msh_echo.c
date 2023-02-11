/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:30:03 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 16:33:26 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_echo(t_msh_data *m_d, t_cmd *cmd)
{
	unsigned int	i;
	int				out;


	out = STDOUT_FILENO;
	if (cmd->out_app >= 0)
		out = cmd->out_app;
	if (cmd->out_trunc >= 0)
		out = cmd->out_trunc;

	if (count_args(cmd) == 1)
	{
		write(out, "\n", 1);
		if (m_d->nb_cmd == 1)
			return (SUCCESS);
		exit(SUCCESS);
	}

	if (count_args(cmd) == 2  && !ft_strncmp(cmd->args[1], "-n", 3))
	{
		if (m_d->nb_cmd == 1)
			return (SUCCESS);
		exit(SUCCESS);
	}

	if (count_args(cmd) >= 2 && !ft_strncmp(cmd->args[1], "-n", 3))
	{
		i = 2;
		while (cmd->args[i])
		{
			write(out, cmd->args[i], ft_strlen(cmd->args[i]));
			if (cmd->args[i + 1] && ft_strlen(cmd->args[i + 1]))
				write(out, " ", 1);
			i++;
		}
		if (m_d->nb_cmd == 1)
			return (SUCCESS);
		exit(SUCCESS);
	}

	if (count_args(cmd) >= 2)
	{
		i = 1;
		while (cmd->args[i])
		{
			write(out, cmd->args[i], ft_strlen(cmd->args[i]));
			if (cmd->args[i + 1] && ft_strlen(cmd->args[i + 1]))
				write(out, " ", 1);
			i++;
		}
		write(out, "\n", 1);
		if (m_d->nb_cmd == 1)
			return (SUCCESS);
		exit(SUCCESS);
	}

	return (SUCCESS);
}