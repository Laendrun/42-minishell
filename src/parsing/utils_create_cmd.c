/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_create_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:59:28 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/16 18:05:30 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	calculate_nb_cmds(t_msh_data *m_d)
{
	t_tok_list	*cur;
	int			cpt;

	cpt = 0;
	cur = m_d->tokens;
	while (cur)
	{
		if (cur->type == PIPE || cur->type == END)
			cpt++;
		cur = cur->next;
	}
	m_d->nb_cmd = cpt;
}

int	get_nb_args(t_tok_list *d)
{
	int			cpt;
	t_tok_list	*tmp;

	cpt = 0;
	tmp = d;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == STR)
			cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}

int	check_redir_outfile(t_tok_list *tmp, t_cmd *end)
{
	if (tmp->type == GT)
	{
		end->out_trunc = open(tmp->next->val,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (end->out_trunc < 0)
			return (open_error(tmp->next->val));
	}
	else if (tmp->type == DGT)
	{
		end->out_app = open(tmp->next->val,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (end->out_app < 0)
			return (open_error(tmp->next->val));
	}
	return (EXIT_SUCCESS);
}

int	check_redir_type(t_msh_data *m_d, t_tok_list *tmp, t_cmd *end)
{
	if (tmp->type == LT)
	{
		end->infile = open(tmp->next->val, O_RDONLY);
		if (end->infile < 0)
			return (msh_error_no_such_file(tmp->next->val, 1));
	}
	else if (tmp->type == DLT)
	{
		end->heredoc = 1;
		end->delim = tmp->next->val;
		if (ft_here_doc(m_d, end) != 0)
			return (EXIT_FAILURE);
	}
	if (check_redir_outfile(tmp, end) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_redir_in_cmd_lst(t_msh_data *m_d, int i)
{
	t_tok_list	*tmp;
	t_cmd		*end;

	end = m_d->cmds;
	while (end->next)
		end = end->next;
	tmp = m_d->trunc_lst[i];
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == END)
			break ;
		if ((tmp->type == LT || tmp->type == DLT || tmp->type == GT
				|| tmp->type == DGT) && tmp->next->type == REDIR)
		{
			if (check_redir_type(m_d, tmp, end) != 0)
				return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
