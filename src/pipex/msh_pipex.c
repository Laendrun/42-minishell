/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/13 12:16:09 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipe(t_msh_data *m_d)
{
	int	i;

	i = 0;
	while (i < m_d->nb_cmd - 1)
	{
		if (pipe(&m_d->fd[2 * i]) == -1)
			return(msh_error(1, ERR_PIPE, 1));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	launch_process(t_msh_data *m_d)
{
	t_cmd	*tmp;

	tmp = m_d->cmds;
	while (m_d->process < m_d->nb_cmd)
	{
		f_fork(m_d, tmp);
		if (tmp->next != NULL)
			tmp = tmp->next;
		m_d->process++;
	}
	if (close_fd_tab(m_d->fd, 2 * (m_d->nb_cmd - 1)) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	pipex(t_msh_data *m_d)
{
	int		status;
	// int		i;
	// t_cmd	*tmp;

	// i = 0;
	// while (i < m_d->nb_cmd - 1)
	// {
	// 	if (pipe(&m_d->fd[2 * i]) == -1)
	// 		f_error("Error creating pipe :", strerror(errno), m_d);
	// 	i++;
	// }
	if (open_pipe(m_d) != 0)
		return (EXIT_FAILURE);
	if (launch_process(m_d) != 0)
		return (EXIT_FAILURE);
	// tmp = m_d->cmds;
	// while (m_d->process < m_d->nb_cmd)
	// {
	// 	f_fork(m_d, tmp);
	// 	if (tmp->next != NULL)
	// 		tmp = tmp->next;
	// 	m_d->process++;
	// }
	// printf("process: %d\n", m_d->process);
	while (m_d->process--)
	{
		waitpid(m_d->pid[m_d->process], &status, 0);
	}
	// printf("status : %d\n", status);
	// free(m_d->pid);
	// free_tab_char(m_d->path);
	// free_tab_char(m_d->env_upd);
	// free_t_cmd(m_d);
	// free(m_d->trunc_lst);
	if(WIFEXITED(status))
		msh_set_gcode(WEXITSTATUS(status));
	// msh_set_gcode(status);
	return (EXIT_SUCCESS);
	// return (WEXITSTATUS(status));
}

int	msh_pipex(t_msh_data *m_d)
{
	
	// msh_set_gcode(pipex(m_d));
	// return (msh_get_gcode());
	if (pipex(m_d) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
