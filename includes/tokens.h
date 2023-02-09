/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:46:09 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 16:08:53 by saeby            ###   ########.fr       */
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
};

/*
	SEP // separator => isspace / 100
	STR, // string / 101
	MSH_WORD, // word => text not between quote / 102
	MSH_SYMBOL, // symbol => special characters (. .. , ! + _ @) / 103
	MSH_DQUOTE, // double quote / 104
	MSH_SQUOTE, // single quote / 105
	MSH_PIPE, // pipe / 106
	MSH_DPIPE, // double pipe / 107
	MSH_LT, // < / 108
	MSH_DLT, // << / 109
	MSH_GT, // > / 110
	MSH_DGT, // >> / 111
	MSH_AMP, // & / 112
	MSH_DAMP, // && / 113
	MSH_DOLLAR, // $ / 114
	MSH_L_BR, // ( / 115
	MSH_R_BR, // ) / 116
	MSH_L_CBR, // { / 117
	MSH_R_CBR, // } / 118
	MSH_L_SBR, // [ / 119
	MSH_R_SBR, // ] / 120
	MSH_MINUS, // - / 121
	MSH_DMINUS, // -- / 122
	MSH_END, // end of line / 123
	MSH_FILENAME, // MSH_WORD.MSH_WORD / 124
	MSH_PARAM, // MSH_MINUSMSH_WORD / 125
	MSH_PATH // .. . / 126
	MSH_VAR // $WORD / 127
	MSH_DELIM // symbol|word after here_doc // 128
*/

#endif