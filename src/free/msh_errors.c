/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:33:23 by saeby             #+#    #+#             */
/*   Updated: 2023/02/13 09:58:08 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_error(int ret, char *msg, int err_code)
{
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
		msh_set_gcode(err_code);
		return (ret);
	}
	if (errno)
	{
		if (msg)
			perror(msg);
		else
			perror("Error: ");
		msh_set_gcode(1);
	}
	return (ret);
}