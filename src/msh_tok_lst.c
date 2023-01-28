/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tok_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:24:56 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 11:00:35 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok_list	*msh_tok_lstnew(int type, char *val)
{
	t_tok_list	*new;

	new = (t_tok_list *) malloc(sizeof(t_tok_list));
	new->type = type;
	new->val = val;
	new->next = NULL;
	return (new);
}

void	msh_tok_lstaddb(t_tok_list **lst, t_tok_list *new)
{
	t_tok_list	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = msh_tok_lstlast(*lst);
	tmp->next = new;
}

t_tok_list	*msh_tok_lstlast(t_tok_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	msh_tok_lstsize(t_tok_list *lst)
{
	t_tok_list	*tmp;
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
