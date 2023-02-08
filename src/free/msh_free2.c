/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:33:23 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 19:54:20 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_free_upd(t_msh_data *m_data)
{
	printf("msh_free_upd\n");
	t_env_list	*tmp;
	int			i;

	tmp = m_data->env;
	i = 0;
	while (tmp)
	{
		printf("%s\n", m_data->env_upd[i]);
		i++;
		tmp = tmp->next;
	}
}

void	free_t_cmd(t_msh_data *d)
{
	t_cmd	*tmp;

	tmp = d->cmds;
	while(tmp)
	{
		free_tab_char(tmp->args);
		tmp = tmp->next;
	}
	free(d->cmds);
}

void	free_trunc_list(t_tok_list **trunc_lst, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(trunc_lst[i]);
		i++;
	}
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

	// int	i;

	// i = 0;
	// if (!tab)
	// 	return ;
	// while (tab[i])
	// {
	// 	if (tab[i])
	// 	{
	// 		free_ptr(tab[i]);
	// 		tab[i] = NULL;
	// 	}
	// 	i++;
	// }
	// free(tab);
	// tab = NULL;
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