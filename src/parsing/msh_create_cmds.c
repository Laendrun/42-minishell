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

t_tok_list **create_array_of_toklst(t_msh_data *m_d)
{
	t_tok_list	*cur;
	t_tok_list	**array;
	int			i;

	i = 0;
	array = (t_tok_list **)malloc(sizeof(t_tok_list *) * m_d->nb_cmd);
	if (!array)
		return (NULL);
	cur = m_d->tokens;
	while (cur)
	{
		array[i] = cur;
		while (cur->next && cur->type != PIPE)
			cur = cur->next;
		if (cur->next !=  NULL)
		{
			cur = cur->next;
			i++;
		}
		else
			break;
	}
	return (array);
}

int	create_cmd_lst(t_msh_data *m_d, int i)
{
	t_cmd		*new;
	char		**args;
	int			nb_arg;
	t_tok_list	*tmp;
	int 		j;

	nb_arg = get_nb_args(m_d->trunc_lst[i]);
	args = ft_calloc(sizeof(char *), (nb_arg + 1));
	if (!args)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	tmp = m_d->trunc_lst[i];
	j = 0;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == END)
			break ;
		if (tmp->type == WORD || tmp->type == STR)
		{
			args[j] = ft_strdup(tmp->val);
			if (!args[j])
				return (msh_error(1, ERR_MALMES, ERR_MALLOC));
			j++;
		}
		tmp = tmp->next;
	}
	new = msh_cmd_lstnew(NULL, args);
	msh_cmd_lstaddb(&m_d->cmds, new);
	return (EXIT_SUCCESS);
}

int	cmd_preparation(t_msh_data *m_d)
{
	m_d->env_upd = msh_make_env_tabstr(m_d);
	if (!m_d->env_upd)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	m_d->pid = malloc(sizeof(int) * m_d->nb_cmd);
	if (!m_d->pid)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	m_d->fd = malloc(sizeof(int) * (m_d->nb_cmd - 1) * 2);
	if (!m_d->fd)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	m_d->trunc_lst = create_array_of_toklst(m_d);
	if (!m_d->trunc_lst)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	m_d->path = pip_get_path(m_d->env_upd);
	if (!m_d->path)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	return (EXIT_SUCCESS);
}

int	msh_create_commmands(t_msh_data *m_d)
{
	int		i;

	calculate_nb_cmds(m_d);
	if (cmd_preparation(m_d) != 0)
		return (EXIT_FAILURE);
	i = 0;
	while (i < m_d->nb_cmd)
	{
		if (create_cmd_lst(m_d, i) != 0)
			return (EXIT_FAILURE);
		if (set_redir_in_cmd_lst(m_d, i) != 0 )
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

// print_array_lst(m_d);

	// t_cmd *tmp;
	// tmp = m_d->cmds;
	// while(tmp)
	// {
	// 	i = 0;
	// 	while (tmp->args[i])
	// 	{
	// 		printf("%d : %s\n", i, tmp->args[i]);
	// 		i++;
	// 	}
	// 	printf("inf : %d\n", tmp->infile);
	// 	printf("hdoc : %d\n", tmp->heredoc);
	// 	printf("delim : %s\n", tmp->delim);
	// 	printf("out app : %d\n", tmp->out_app);
	// 	printf("out trunc : %d\n", tmp->out_trunc);
	// 	tmp = tmp->next;
	// }