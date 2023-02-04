/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Makefile                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2022/11/21 18:51:06 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(t_msh_data *m_d)
{
	int		status;
	int		i;

	i = 0;
	while (i < m_d->nb_cmd - 1)
	{
		if (pipe(&m_d->fd[2 * i]) == -1)
			f_error("Error creating pipe :", strerror(errno), m_d);
		i++;
	}
	while (m_d->process < m_d->nb_cmd)
	{
		f_fork(m_d);
		if (m_d->cmds->next != NULL)
			m_d->cmds = m_d->cmds->next;
		m_d->process++;
	}
	close_fd_tab(m_d->fd, 2 * (m_d->nb_cmd - 1), m_d);
	waitpid(-1, &status, 0);
	free(d->pid);
	return (WEXITSTATUS(status));
}

int	msh_pipex(t_msh_data *m_d)
{
	return (pipex(m_d));
}
