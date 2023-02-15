/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:33:23 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 19:59:56 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_error(int ret, char *msg, int err_code)
{
	if (errno)
	{
		if (msg)
			perror(msg);
		else
			perror("Error: ");
		msh_set_gcode(errno);
		return (ret);
	}
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
		msh_set_gcode(err_code);
	}
	return (ret);
}

void	msh_error_cmd_not_found(char *msg, int err_code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	msh_set_gcode(err_code);
}

int	export_key_error(char *key, char *val)
{
	ft_putstr_fd(ERR_EXP_KEY1, 2);
	ft_putstr_fd(key, 2);
	ft_putchar_fd('=', 2);
	ft_putstr_fd(val, 2);
	ft_putstr_fd(ERR_EXP_KEY2, 2);
	msh_set_gcode(1);
	return (EXIT_FAILURE);
}
