/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:43:47 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 11:09:21 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*msh_env_lstnew(char *key, char *val)
{
	t_env_list	*new;

	new = (t_env_list *) malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->key = key;
	new->val = val;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	msh_env_lstaddb(t_env_list **lst, t_env_list *new)
{
	t_env_list	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = msh_env_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

t_env_list	*msh_env_lstlast(t_env_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	msh_env_lstsize(t_env_list *lst)
{
	t_env_list	*tmp;
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
