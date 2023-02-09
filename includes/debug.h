/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:47:18 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 17:02:09 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "structures.h"

// ----------------------------------------------
// debug/msh_print_utils.c
// ----------------------------------------------
void		print_tok(t_msh_data *m_data);
void		print_env_strarray(t_msh_data *m_d);
void		print_array_lst(t_msh_data *m_d);
void		print_tok_trunclst(t_tok_list *d);

#endif