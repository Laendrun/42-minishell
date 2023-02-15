/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:59:28 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/13 11:56:39 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**msh_make_env_tabstr(t_msh_data *m_d)
{
	int			i;
	int			size;
	t_env_list	*tmp;
	char		**env_str;

	i = 0;
	tmp = m_d->env;
	size = msh_env_lstsize(m_d->env);
	env_str = malloc(sizeof(char *) * (size + 1));
	if (!env_str)
		return (NULL);
	while (tmp)
	{
		env_str[i] = malloc(strlen(tmp->key) + strlen(tmp->val) + 2);
		if (!env_str[i])
			return (NULL);
		ft_strcpy(env_str[i], tmp->key);
		ft_strcat(env_str[i], "=");
		ft_strcat(env_str[i], tmp->val);
		i++;
		tmp = tmp->next;
	}
	env_str[size] = 0;
	return (env_str);
}

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
			return (msh_error(1, ERR_OPEN, 1));
	}
	else if (tmp->type == DGT)
	{
		end->out_app = open(tmp->next->val,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (end->out_app < 0)
			return (msh_error(1, ERR_OPEN, 1));
	}
	return (EXIT_SUCCESS);
}

int	check_redir_type(t_msh_data *m_d, t_tok_list *tmp, t_cmd *end)
{
	if (tmp->type == LT)
	{
		end->infile = open(tmp->next->val, O_RDONLY);
		if (end->infile < 0)
			return (msh_error(1, ERR_OPEN, 1));
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
	// else if (tmp->type == GT)
	// {
	// 	end->out_trunc = open(tmp->next->val,
	// 			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// 	if (end->out_trunc < 0)
	// 		return (msh_error(1, ERR_OPEN, 1));
	// }
	// else if (tmp->type == DGT)
	// {
	// 	end->out_app = open(tmp->next->val,
	// 			O_CREAT | O_WRONLY | O_APPEND, 0644);
	// 	if (end->out_app < 0)
	// 		return (msh_error(1, ERR_OPEN, 1));
	// }
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
