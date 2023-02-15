/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tok_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:24:56 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 18:57:33 by saeby            ###   ########.fr       */
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
	new->prev = NULL;
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
	new->prev = tmp;
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

t_tok_list	*msh_remove_tok(t_tok_list **lst, t_tok_list *tok_to_remove)
{
	if (!(*lst) || !tok_to_remove)
		return (NULL);
	if (*lst == tok_to_remove)
		*lst = tok_to_remove->next;
	if (tok_to_remove->next != NULL)
		tok_to_remove->next->prev = tok_to_remove->prev;
	if (tok_to_remove->prev != NULL)
		tok_to_remove->prev->next = tok_to_remove->next;
	if (tok_to_remove->val != NULL)
		free(tok_to_remove->val);
	free(tok_to_remove);
	return (*lst);
}
