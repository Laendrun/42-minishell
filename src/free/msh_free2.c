/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:33:23 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 20:04:47 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (tmp)
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

// void	f_error(char *str, char *erno, t_msh_data *d)
// {
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd(erno, 2);
// 	write(2, "\n", 1);
// 	if (d->pid)
// 		free(d->pid);
// 	exit(0);
// }

int	close_fd_tab(int *fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (close(fd[i]) < 0)
			return (msh_error(1, ERR_CLOSE, 1));
		i++;
	}
	return (EXIT_SUCCESS);
}
