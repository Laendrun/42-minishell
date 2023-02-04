/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:41:11 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 14:55:19 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H
# include "structures.h"

// ----------------------------------------------
// syntax/msh_check_syntax.c
// ----------------------------------------------
int			msh_check_syntax(t_msh_data *m_d);

// ----------------------------------------------
// syntax/msh_syntax_helper.c
// ----------------------------------------------
int			msh_count_quotes(t_msh_data *m_d);
int			msh_count_dquote(t_msh_data *m_d);
int			msh_count_squote(t_msh_data *m_d);

#endif