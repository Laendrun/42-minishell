/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/08 11:46:42 by saeby            ###   ########.fr       */
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
	while (m_d->process--)
	{
		// printf("process : %d \n", m_d->process);
		waitpid(m_d->pid[m_d->process], &status, 0);
		// printf("status : %d\n", status);
	}
	free(m_d->pid);
	// free_tab_char(m_d->path);
	// free_tab_char(m_d->env_upd);
	// free_t_cmd(m_d);
	// free_trunc_list(m_d);
	return (WEXITSTATUS(status));
}

int	msh_pipex(t_msh_data *m_d)
{
	return (pipex(m_d));
}
