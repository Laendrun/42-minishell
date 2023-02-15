/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:48:47 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/13 12:31:22 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_duplicate(int in, int out)
{
	if (dup2(in, STDIN_FILENO) < 0)
		return (msh_error(1, ERR_DUP2, 1));
	if (dup2(out, STDOUT_FILENO) < 0)
		return (msh_error(1, ERR_DUP2, 1));
	return (EXIT_SUCCESS);
}

int	infile_first_process(t_msh_data *m_d, t_cmd *tmp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (m_d->nb_cmd == 1)
		ret = f_duplicate(tmp->infile, STDOUT_FILENO);
	else
		ret = f_duplicate(tmp->infile, m_d->fd[1]);
	return (ret);
}

int	heredoc_first_process(t_msh_data *m_d, t_cmd *tmp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (m_d->nb_cmd == 1)
	{
		ret = f_duplicate(tmp->hdoc[0], STDOUT_FILENO);
		if (close(tmp->hdoc[0]) < 0)
			return (msh_error(1, ERR_CLOSE, 1));
	}
	else
		ret = f_duplicate(tmp->hdoc[0], m_d->fd[1]);
	return (ret);
}

int	first_process(t_msh_data *m_d, t_cmd *tmp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (tmp->infile != -1)
		ret = infile_first_process(m_d, tmp);
	else if (tmp->heredoc == 1)
		ret = heredoc_first_process(m_d, tmp);
	else if (tmp->out_app != -1)
		ret = f_duplicate(STDIN_FILENO, tmp->out_app);
	else if (tmp->out_trunc != -1)
		ret = f_duplicate(STDIN_FILENO, tmp->out_trunc);
	else if (m_d->nb_cmd == 1)
		return (ret);
	else
		ret = f_duplicate(STDIN_FILENO, m_d->fd[1]);
	return (ret);
}

int	last_process(t_msh_data *m_d, t_cmd *tmp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (tmp->out_app != -1)
		ret = f_duplicate(m_d->fd[(2 * m_d->process) - 2], tmp->out_app);
	else if (tmp->out_trunc != -1)
		ret = f_duplicate(m_d->fd[(2 * m_d->process) - 2], tmp->out_trunc);
	else if (tmp->infile != -1)
		ret = f_duplicate(tmp->infile, STDOUT_FILENO);
	else if (tmp->heredoc == 1)
	{
		ret = f_duplicate(tmp->hdoc[0], STDOUT_FILENO);
		if (close(tmp->hdoc[0]) < 0)
			return (msh_error(1, ERR_CLOSE, 1));
	}
	else
		ret = f_duplicate(m_d->fd[(2 * m_d->process) - 2], STDOUT_FILENO);
	return (ret);
}

int	middle_process(t_msh_data *m_d, t_cmd *tmp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (tmp->out_app != -1)
		ret = f_duplicate(m_d->fd[(2 * m_d->process) - 2], tmp->out_app);
	else if (tmp->out_trunc != -1)
		ret = f_duplicate(m_d->fd[(2 * m_d->process) - 2], tmp->out_trunc);
	else if (tmp->infile != -1)
		ret = f_duplicate(tmp->infile, m_d->fd[(2 * m_d->process) + 1]);
	else if (tmp->heredoc == 1)
	{
		ret = f_duplicate(tmp->hdoc[0], m_d->fd[(2 * m_d->process) + 1]);
		if (close(tmp->hdoc[0]) < 0)
			return (msh_error(1, ERR_CLOSE, 1));
	}
	else
		ret = f_duplicate(m_d->fd[(2 * m_d->process) - 2],
				m_d->fd[(2 * m_d->process) + 1]);
	return (ret);
}

int	f_pre_duplicate(t_msh_data *m_d, t_cmd *tmp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (m_d->process == 0)
		ret = first_process(m_d, tmp);
	else if (m_d->process == m_d->nb_cmd - 1)
		ret = last_process(m_d, tmp);
	else
		ret = middle_process(m_d, tmp);
	if (close_fd_tab(m_d->fd, 2 * (m_d->nb_cmd - 1)) != 0)
		return (EXIT_FAILURE);
	return (ret);
}

void	pip_no_exec(char *s)
{
	char	*err;

	err = ft_strjoin("shellusion: ", s);
	msh_error_cmd_not_found(err, 127);
	free(err);
	exit(ERR_NOEXEC);
}

char	*pip_get_exec(char *cmd, char **paths)
{
	char	*path;

	if ((ft_strncmp(cmd, "/", 1) == 0)
		&& access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		if (!path)
			return (NULL);
		path = ft_strjoin(path, cmd);
		if (!path)
			return (NULL);
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
	if (!paths)
		return (NULL);
	return (paths);
}

int	child_process(t_msh_data *m_d, t_cmd *tmp)
{
	f_pre_duplicate(m_d, tmp);
	if (!msh_is_builtin(tmp->args[0]))
	{
		tmp->args[0] = pip_get_exec(tmp->args[0], m_d->path);
		execve(tmp->args[0], tmp->args, m_d->env_upd);
	}
	else
		msh_exec_builtin(tmp, m_d);
	return (EXIT_SUCCESS);
}

int	f_fork(t_msh_data *m_d, t_cmd *tmp)
{
	if (m_d->nb_cmd == 1 && msh_is_builtin(tmp->args[0]))
		msh_exec_builtin(tmp, m_d);
	else
	{
		m_d->pid[m_d->process] = fork();
		if (m_d->pid[m_d->process] < 0)
			return (msh_error(1, ERR_FORK, 1));
		if (!m_d->pid[m_d->process])
			child_process(m_d, tmp);
	}
	return (EXIT_SUCCESS);
}
