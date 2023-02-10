/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/10 21:39:05 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(t_msh_data *m_d)
{
	int		status;
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (i < m_d->nb_cmd - 1)
	{
		if (pipe(&m_d->fd[2 * i]) == -1)
			f_error("Error creating pipe :", strerror(errno), m_d);
		i++;
	}
	tmp = m_d->cmds;
	while (m_d->process < m_d->nb_cmd)
	{
		f_fork(m_d, tmp);
		if (tmp->next != NULL)
			tmp = tmp->next;
		m_d->process++;
	}
	// if (m_d->fd != NULL)
	// 	free(m_d->fd);
	close_fd_tab(m_d->fd, 2 * (m_d->nb_cmd - 1), m_d);
	while (m_d->process--)
	{
		// printf("process : %d \n", m_d->process);
		waitpid(m_d->pid[m_d->process], &status, 0);
		// printf("status : %d\n", status);
	}
	free(m_d->pid);
	free_tab_char(m_d->path);
	free_tab_char(m_d->env_upd);
	// t_cmd *tmp2;
	// tmp2 = m_d->cmds;
	// while(tmp2)
	// {
	// 	i = 0;
	// 	while (tmp2->args[i])
	// 	{
	// 		printf("%d : %s\n", i, tmp2->args[i]);
	// 		i++;
	// 	}
	// 	tmp2 = tmp2->next;
	// }

	free_t_cmd(m_d);
	free(m_d->trunc_lst);
	return (WEXITSTATUS(status));
}

int	msh_pipex(t_msh_data *m_d)
{
	msh_set_gcode(pipex(m_d));
	// printf("error code : %d\n", msh_get_gcode());
	return (msh_get_gcode());
}
