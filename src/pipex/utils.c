/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2022/11/21 18:51:06 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 	void	f_here_doc(t_msh_data *m_d)
// {
// 	char	*line;cat
// 	char	*lim;

// 	lim = ft_strjoin(d->av[2], "\n");
// 	if (pipe(d->here_doc) < 0)
// 		f_error("Error creating pipe :", strerror(errno), d);
// 	// prob with get next line ...
// 	line = get_next_line(0);
// 	while (line)
// 	{
// 		if (ft_strncmp(lim, line, (ft_strlen(d->av[2]) + 1)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putstr_fd(line, d->here_doc[1]);
// 		free(line);
// 		line = get_next_line(0);
// 	}
// 	free(lim);
// 	if (line)
// 		free(line);
// 	if (close(d->here_doc[1]) < 0)
// 		f_error("Close error :", strerror(errno), d);
// }


// void	f_here_doc(t_pipex *d)
// {
// 	char	*line;
// 	char	*lim;

// 	lim = ft_strjoin(d->av[2], "\n");
// 	if (pipe(d->here_doc) < 0)
// 		f_error("Error creating pipe :", strerror(errno), d);
// 	while (1)
// 	{
// 		line = get_next_line(0);
// 		printf("passe ici\n");
// 		if (line == NULL)
// 		{
// 			ft_putstr_fd("\n", 1);
// 			break ;
// 		}
// 		if (ft_strncmp(lim, line, (ft_strlen(d->av[2]) + 1)) == 0)
// 			break ;
// 		ft_putstr_fd(line, d->here_doc[1]);
// 		free(line);
// 	}
// 	free(lim);
// 	if (line)
// 		free(line);
// 	if (close(d->here_doc[1]) < 0)
// 		f_error("Close error :", strerror(errno), d);
// }

void	f_error(char *str, char *erno, t_msh_data *d)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(erno, 2);
	write(2, "\n", 1);
	if (d->pid)
		free(d->pid);
	exit(0);
}

void	free_tab_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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
