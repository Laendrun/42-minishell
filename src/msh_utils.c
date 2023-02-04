/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:54:27 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 15:00:58 by saeby            ###   ########.fr       */
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
	printf("%s%s: %s%s\n", RED, m_d->name, err_mes, RESET);
	return (err_code);
}
