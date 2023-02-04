/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2022/11/21 18:51:06 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/errno.h>

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**envp;
	char	**path;
	int		here_doc[2];
	int		infile;
	int		outfile;
	int		process;
	int		*pid;
	int		*fd;
}				t_pipex;

// parsing

char					**envp_parsing(char **envp);
char					**av_parsing(char *av);
char					**pip_get_path(char **env);

// check inputs

void					check_inputs(int ac, char **av);

// init data

void					fill_data_hd(t_pipex *data,
							int ac, char **av, char **envp);
void					fill_data(t_pipex *data,
							int ac, char **av, char **envp);
void					f_here_doc(t_pipex *d);

// child, process, fork

void					f_duplicate(int in, int out, t_pipex *d);
void					f_pre_duplicate(t_pipex *d);
void					child_process(t_pipex *d);
void					f_fork(t_pipex *d);

// errors & free

void					free_tab_char(char **str);
void					f_error(char *str, char *erno, t_pipex *d);
void					close_fd_tab(int *fd, int size, t_pipex *d);
void					close_2fds(int fd1, int fd2);

#endif