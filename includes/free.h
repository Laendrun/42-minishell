/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:42:59 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 18:46:33 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "structures.h"

// ----------------------------------------------
// free/msh_free.c
// ----------------------------------------------
void	msh_free_env(t_msh_data *m_data);
void	msh_free_tok(t_msh_data *m_data);
void	msh_free_simpl_tok(t_msh_data *m_data);
void	msh_free_cmds(t_msh_data *m_data);
void	msh_free_trunc_lst(t_msh_data *m_data);
void	f_error(char *str, char *erno, t_msh_data *d);
void	free_tab_char(char **str);
void	free_ptr(void *ptr);
void	free_lst_in_trunc(t_msh_data *m_d);
void	free_t_cmd(t_msh_data *d);
void	free_args(char **tab);
int		close_fd_tab(int *fd, int size);
char	*ft_strjoin_free(char *s1, char *s2);

// ----------------------------------------------
// free/msh_free2.c
// ----------------------------------------------
void	msh_free_upd(t_msh_data *m_data);

// ----------------------------------------------
// free/msh_errors.
// ----------------------------------------------
int		msh_error(int ret, char *msg, int err_code);
void	msh_error_cmd_not_found(char *msg, int err_code);
int		export_key_error(char *key, char *val);

#endif