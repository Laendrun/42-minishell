/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2022/11/21 18:51:06 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	fill_data_hd(t_pipex *data, int ac, char **av, char **envp)
// {
// 	data->av = av;
// 	data->envp = envp;
// 	data->path = pip_get_path(envp);
// 	f_here_doc(data);
// 	data->infile = -1;
// 	data->ac = ac - 4;
// 	data->av = &av[1];
// 	data->process = 0;
// 	data->outfile = open(av[ac - 1], O_CREAT | O_WRONLY, 0644);
// 	if (data->outfile < 0)
// 		exit(1);
// 	data->pid = malloc(sizeof(int) * data->ac);
// 	if (data->pid == NULL)
// 		exit(1);
// 	data->fd = malloc(sizeof(int) * (data->ac - 1) * 2);
// 	if (data->fd == NULL)
// 	{
// 		free(data->pid);
// 		exit(1);
// 	}
// }

// void	fill_data(t_pipex *data, int ac, char **av, char **envp)
// {
// 	data->ac = ac - 3;
// 	data->av = av;
// 	data->envp = envp;
// 	data->path = pip_get_path(envp);
// 	data->infile = open(av[1], O_RDONLY);
// 	data->process = 0;
// 	data->outfile = open(av[ac - 1], O_CREAT | O_WRONLY, 0644);
// 	if (data->outfile < 0 || data->infile < 0)
// 		exit(1);
// 	data->pid = malloc(sizeof(int) * data->ac);
// 	if (data->pid == NULL)
// 		exit(1);
// 	data->fd = malloc(sizeof(int) * (data->ac - 1) * 2);
// 	if (data->fd == NULL)
// 	{
// 		free(data->pid);
// 		exit(1);
// 	}
// }