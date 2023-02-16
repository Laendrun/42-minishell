/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:00:24 by saeby             #+#    #+#             */
/*   Updated: 2023/02/16 18:10:55 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_error(char *cmd)
{
	ft_putstr_fd(SH_NAME, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(ERR_PERM, 2);
	msh_set_gcode(EXIT_FAILURE);
	return (1);
}
