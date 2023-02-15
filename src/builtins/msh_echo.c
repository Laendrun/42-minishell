/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:30:03 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 19:23:20 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_out(t_cmd *cmd, int *out);
static void	print_args(t_cmd *cmd, int *out);

int	msh_echo(t_msh_data *m_d, t_cmd *cmd)
{
	unsigned int	i;
	int				out;

	set_out(cmd, &out);
	if (count_args(cmd) == 1)
		write(out, "\n", 1);
	else if (count_args(cmd) >= 2 && !ft_strncmp(cmd->args[1], "-n", 3))
	{
		i = 2;
		while (cmd->args[i])
		{
			write(out, cmd->args[i], ft_strlen(cmd->args[i]));
			if (cmd->args[i + 1] && ft_strlen(cmd->args[i + 1]))
				write(out, " ", 1);
			i++;
		}
	}
	else if (count_args(cmd) >= 2)
		print_args(cmd, &out);
	msh_set_gcode(EXIT_SUCCESS);
	if (m_d->nb_cmd == 1)
		return (EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}

static void	print_args(t_cmd *cmd, int *out)
{
	unsigned int	i;

	i = 1;
	while (cmd->args[i])
	{
		write(*out, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1] && ft_strlen(cmd->args[i + 1]))
			write(*out, " ", 1);
		i++;
	}
	write(*out, "\n", 1);
}

static void	set_out(t_cmd *cmd, int *out)
{
	*out = STDOUT_FILENO;
	if (cmd->out_app >= 0)
		*out = cmd->out_app;
	if (cmd->out_trunc >= 0)
		*out = cmd->out_trunc;
}
