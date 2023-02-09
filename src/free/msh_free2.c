/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:33:23 by saeby             #+#    #+#             */
/*   Updated: 2023/02/08 18:02:52 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_cmd(t_msh_data *d)
{
	t_cmd	*tmp;

	tmp = d->cmds;
	if (!tmp)
		return ;
	while(tmp)
	{
		if (tmp->args != NULL)
		{
			free_tab_char(tmp->args);
			// free_args(tmp->args);
			tmp->args = NULL;
		}
		tmp = tmp->next;
	}
	free(d->cmds);
}

void	free_trunc_list(t_tok_list **trunc_lst, int len)
{
	// int i;

	(void)len;

	// i = 0;
	// if (len > 1)
	// {
	// 	while (i < len)
	// 	{
	// 		free(trunc_lst[i]);
	// 		i++;
	// 	}
	// }
	free(trunc_lst);
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

void	free_args(char **tab)
{
	int	i;

	i = 1;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free_ptr(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

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