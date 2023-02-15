/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:50:39 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 13:45:28 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exit(t_msh_data *m_data, t_cmd *cmd)
{
	int	ac;

	(void) m_data;
	ac = count_args(cmd);
	if (ac > 2)
		return (msh_error(1, ERR_EXIT_ARGS, 1));
	ft_putstr_fd("exit", STDERR_FILENO);
	if (ac == 2)
		exit (ft_atoi(cmd->args[1]) % 256);
	exit(msh_get_gcode() % 256);
}
