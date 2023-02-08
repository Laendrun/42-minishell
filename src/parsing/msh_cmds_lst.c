/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmds_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/01/31 13:40:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*msh_cmd_lstnew(char *cmd, char **args)
{
	t_cmd	*new;

	new = (t_cmd *) malloc(sizeof(t_cmd));
	new->cmd = cmd;
	new->args = args;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	msh_cmd_lstaddb(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = msh_cmd_lstlast(*lst);
	tmp->next = new;
	new->prev = tmp;
}

t_cmd	*msh_cmd_lstlast(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	msh_cmd_lstsize(t_cmd *lst)
{
	t_cmd	*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}