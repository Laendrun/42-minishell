/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/15 20:20:26 by saeby            ###   ########.fr       */
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
