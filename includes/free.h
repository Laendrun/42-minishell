/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:42:59 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 14:50:00 by saeby            ###   ########.fr       */
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
void	close_fd_tab(int *fd, int size, t_msh_data *d);
void	free_trunc_list(t_tok_list **trunc_lst, int len);
// void	free_trunc_list(t_msh_data *d);
void	free_t_cmd(t_msh_data *d);
void	free_args(char **tab);
void	free_lst_in_trunc(t_msh_data *m_d);

// ----------------------------------------------
// free/msh_free2.c
// ----------------------------------------------
void	msh_free_upd(t_msh_data *m_data);

#endif