/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:46:09 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 16:57:50 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include "structures.h"

/*enum	e_token_types
{
	SEP = 100,
	STR,
	WORD,
	SYMBOL,
	DQUOTE,
	SQUOTE,
	PIPE,
	DPIPE,
	LT,
	DLT,
	GT,
	DGT,
	AMP,
	DAMP,
	DOLLAR,
	L_BR,
	R_BR,
	L_CBR,
	R_CBR,
	L_SBR,
	R_SBR,
	MINUS,
	DMINUS,
	END,
	FILENAME,
	PARAM,
	PATH,
	VAR,
	DELIM,
	REDIR
};*/

enum	e_token_types
{
	SEP = 100,
	STR,
	WORD,
	DQUOTE,
	SQUOTE,
	VAR,
	REDIR,
	END,
	PIPE,
	LT,
	DLT,
	GT,
	DGT
};

#endif