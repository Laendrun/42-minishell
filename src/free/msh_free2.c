/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:33:23 by saeby             #+#    #+#             */
/*   Updated: 2023/02/13 12:06:21 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	msh_free_trunc(t_tok_list *trunc)
// {
// 	t_tok_list	*tmp;
 
// 	while (trunc)
// 	{
// 		tmp = trunc->next;
// 		free(trunc->val);
// 		trunc->val = NULL;
// 		free(trunc);
// 		trunc = NULL;
// 		trunc = tmp;
// 	}
// }
 
// void	free_lst_in_trunc(t_msh_data *m_d)
// {
// 	int i = 0;
// 	while (i < m_d->nb_cmd)
// 	{
// 		print_tok_trunclst(m_d->trunc_lst[i]);
// 		// msh_free_trunc(m_d->trunc_lst[i]);
// 		i++;
// 	}
// 	// free(m_d->trunc_lst);
// }

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_tab_char(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		// printf("%s\n", tab[i]);
		free_ptr(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_t_cmd(t_msh_data *d)
{
	t_cmd	*tmp;
	t_cmd	*to_free;

	tmp = d->cmds;
	if (!tmp)
		return ;
	while(tmp)
	{
		if (tmp->args != NULL)
		{
			free_tab_char(tmp->args);
			tmp->args = NULL;
		}
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	d->cmds = NULL;
}

void	f_error(char *str, char *erno, t_msh_data *d)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(erno, 2);
	write(2, "\n", 1);
	if (d->pid)
		free(d->pid);
	exit(0);
}

// void	free_args(char **tab)
// {
// 	int	i;

// 	i = 1;
// 	if (tab)
// 	{
// 		while (tab[i])
// 		{
// 			if (tab[i])
// 			{
// 				free_ptr(tab[i]);
// 				tab[i] = NULL;
// 			}
// 			i++;
// 		}
// 		free(tab);
// 		tab = NULL;
// 	}
// }

void	close_fd_tab(int *fd, int size, t_msh_data *d)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (close(fd[i]) < 0)
			f_error("Close error :", strerror(errno), d);
		i++;
	}
	free(fd);
}

// void	close_fd_tab_builtin(int *fd, int size, t_msh_data *d)
// {
// 	int	i;

// 	(void) d;
// 	i = 0;
// 	while (i < size)
// 	{
// 		close(fd[i]);
// 		i++;
// 	}
// }