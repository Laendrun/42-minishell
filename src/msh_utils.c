/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:54:27 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 15:42:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_chrdup(int c)
{
	char	*res;

	res = malloc(2 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = c;
	res[1] = 0;
	return (res);
}

// move this to a separate msh_error.c file when possible
int	msh_error(t_msh_data *m_d, int err_code, char *err_mes, char *sup)
{
	(void) sup;
	msh_set_gcode(err_code);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(m_d->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_mes, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("\n", 2);
	return (err_code);
}
