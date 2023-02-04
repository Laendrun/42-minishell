/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2022/11/21 18:51:06 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f_duplicate(int in, int out, t_msh_data *m_d)
{
	if (dup2(in, STDIN_FILENO) < 0)
		f_error("Dup2 error :", strerror(errno), m_d);
	if (dup2(out, STDOUT_FILENO) < 0)
		f_error("Dup2 error :", strerror(errno), m_d);
}

void	f_pre_duplicate(t_msh_data *m_d)
{
	if (m_d->process == 0)
	{
		if (m_d->infile == -1 || m_d->heredoc == -1)
		{
			f_duplicate(STDIN_FILENO, m_d->fd[1], m_d);
		}
		else
			f_duplicate(m_d->infile, m_d->fd[1], m_d);
	}
	else if (m_d->process == m_d->nb_cmd - 1)
		f_duplicate(m_d->fd[(2 * m_d->process) - 2], STDOUT_FILENO, m_d);
	else
		f_duplicate(m_d->fd[(2 * m_d->process) - 2],
			m_d->fd[(2 * m_d->process) + 1], m_d);
	close_fd_tab(m_d->fd, 2 * (m_d->nb_cmd - 1), m_d);
	close(m_d->infile);
	close(m_d->outfile_app);
}

void	pip_no_exec(char *s)
{
	ft_putstr_fd("shellusion: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(" : command not found.\n", STDERR_FILENO);
	exit(1);
}

char	*pip_get_exec(char *cmd, char **paths)
{
	char	*path;

	if ((ft_strncmp(cmd, "./", 2) == 0) \
		&& access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		path = ft_strjoin(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		paths++;
	}
	pip_no_exec(cmd);
	return (NULL);
}

char	**pip_get_path(char **env)
{
	char	**paths;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			break ;
		env++;
	}
	paths = ft_split(*env + 5, ':');
	return (paths);
}

void	child_process(t_msh_data *m_d)
{
	// char	**args;

	f_pre_duplicate(m_d);
	// args = ft_split(m_d->av[d->process + 2], ' '); //need to be adapted
	m_d->cmds->args[0] = pip_get_exec(m_d->cmds->args[0], m_d->path);
	// args[0] = pip_get_exec(args[0], m_d->path);
	execve(m_d->cmds->args[0], m_d->cmds->args, m_d->env_upd);
	// execve(args[0], args, m_d->env_upd);
}

void	f_fork(t_msh_data *m_d)
{
	m_d->pid[m_d->process] = fork();
	if (m_d->pid[m_d->process] < 0)
		f_error("Fork error : ", strerror(errno), m_d);
	if (!m_d->pid[m_d->process])
		child_process(m_d);
}
