/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/04 13:13:29 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_outfile_trunc(t_msh_data *m_d)
{
	t_tok_list	*tmp;

	tmp = m_d->trunc_lst[m_d->nb_cmd - 1];
	while (tmp)
	{
		if (tmp->type == MSH_GT && (tmp->next->next->type == MSH_WORD || tmp->next->next->type == MSH_FILENAME))
		{
			m_d->outfile_trunc = open(tmp->next->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			printf("open trunc : %d\n", m_d->outfile_trunc);
			break ;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_if_outfile_app(t_msh_data *m_d)
{
	t_tok_list	*tmp;

	tmp = m_d->trunc_lst[m_d->nb_cmd - 1];
	while (tmp)
	{
		// printf("type : %d val : %s\n", tmp->type, tmp->val);
		if (tmp->type == MSH_DGT && (tmp->next->next->type == MSH_WORD || tmp->next->next->type == MSH_FILENAME))
		{
			m_d->outfile_app = open(tmp->next->next->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
			printf("open : %d\n", m_d->outfile_app);
			break ;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_if_infile(t_msh_data *m_d)
{
	t_tok_list	*tmp;

	tmp = m_d->trunc_lst[0];
	while (tmp)
	{
		// printf("type : %d val : %s\n", tmp->type, tmp->val);
		if (tmp->type == MSH_LT && (tmp->next->next->type == MSH_WORD || tmp->next->next->type == MSH_FILENAME))
		{
			m_d->infile = open(tmp->next->next->val, O_RDONLY);
			break ;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void	f_here_doc(t_msh_data *m_d)
{
	char	*line;

	if (pipe(m_d->hdoc) < 0)
		f_error("Error creating pipe :", strerror(errno), m_d);
	line = readline(">");
	while (line)
	{
		if (ft_strncmp(m_d->delim, line, (ft_strlen(m_d->delim) + 1)) == 0)
			break ;
		ft_putstr_fd(ft_strcat(line, "\n"), m_d->hdoc[1]);
		line = readline(">");
	}
	if (close(m_d->hdoc[1]) < 0)
		f_error("Close error :", strerror(errno), m_d);
}

int	check_if_heredoc(t_msh_data *m_d)
{
	t_tok_list	*tmp;

	tmp = m_d->trunc_lst[0];
	while (tmp)
	{
		if (tmp->type == MSH_DLT && tmp->next->type == MSH_DELIM)
		{
			m_d->heredoc = 1;
			m_d->delim = tmp->next->val;
			f_here_doc(m_d);
			break ;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_if_ambiguous_redirection(t_msh_data *m_d)
{
	t_tok_list	*tmp;
	int			i;

	i = 1;
	while (i < m_d->nb_cmd - 1)
	{
		tmp = m_d->trunc_lst[i];
		while (tmp)
		{
			if (tmp->type == MSH_GT || tmp->type == MSH_DGT || tmp->type == MSH_LT || tmp->type == MSH_DLT)
			{
				printf("ambiguous redirection.\n");
				return (ERROR);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}

int	msh_redir_op(t_msh_data *m_d)
{
	if (m_d->nb_cmd > 2)
		check_if_ambiguous_redirection(m_d);
	check_if_heredoc(m_d);
	// check_if_infile(m_d);
	// check_if_outfile_app(m_d);
	// check_if_outfile_trunc(m_d);
	return (SUCCESS);
}