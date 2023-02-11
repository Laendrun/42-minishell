/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:46:09 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 16:14:06 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include "structures.h"

enum	e_token_types
{
	SEP = 100,
	STR,
	WORD,
	DQUOTE,
	SQUOTE,
	REDIR,
	END,
	PIPE,
	LT,
	DLT,
	GT,
	DGT
};

#endif