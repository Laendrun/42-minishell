/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:19:48 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 20:21:05 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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