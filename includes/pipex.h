/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:13:50 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 20:22:17 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "structures.h"

int		child_process(t_msh_data *m_d, t_cmd *tmp);
char	*pip_get_exec(char *cmd, char **paths);
int		msh_pipex(t_msh_data *m_d);
int		pipex(t_msh_data *m_d);
int		f_fork(t_msh_data *m_d, t_cmd *tmp);
char	**pip_get_path(char **env);
int		f_pre_duplicate(t_msh_data *m_d, t_cmd *tmp);
int		f_fork(t_msh_data *m_d, t_cmd *tmp);

int		first_process(t_msh_data *m_d, t_cmd *tmp);
int		middle_process(t_msh_data *m_d, t_cmd *tmp);
int		last_process(t_msh_data *m_d, t_cmd *tmp);
int		f_duplicate(int in, int out);
int		infile_first_process(t_msh_data *m_d, t_cmd *tmp);
int		heredoc_first_process(t_msh_data *m_d, t_cmd *tmp);

#endif