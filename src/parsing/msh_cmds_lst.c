/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmds_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/10 11:56:24 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*msh_cmd_lstnew(char *cmd, char **args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return NULL;
	new->cmd = cmd;
	new->args = args;
	new->infile = -1;
	new->heredoc = -1;
	new->out_app = -1;
	new->out_trunc = -1;
	new->delim = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	msh_cmd_lstaddb(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

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
		return NULL;
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