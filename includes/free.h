/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:42:59 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 19:34:26 by saeby            ###   ########.fr       */
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

// ----------------------------------------------
// free/msh_free2.c
// ----------------------------------------------
void	msh_free_upd(t_msh_data *m_data);

#endif