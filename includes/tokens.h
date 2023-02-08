/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:46:09 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 11:46:44 by saeby            ###   ########.fr       */
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
	DELIM
};

/*
	SEP // separator => isspace / 100
	STR, // string / 101
	WORD, // word => text not between quote / 102
	SYMBOL, // symbol => special characters (. .. , ! + _ @) / 103
	DQUOTE, // double quote / 104
	SQUOTE, // single quote / 105
	PIPE, // pipe / 106
	DPIPE, // double pipe / 107
	LT, // < / 108
	DLT, // << / 109
	GT, // > / 110
	DGT, // >> / 111
	AMP, // & / 112
	DAMP, // && / 113
	DOLLAR, // $ / 114
	L_BR, // ( / 115
	R_BR, // ) / 116
	L_CBR, // { / 117
	R_CBR, // } / 118
	L_SBR, // [ / 119
	R_SBR, // ] / 120
	MINUS, // - / 121
	DMINUS, // -- / 122
	END, // end of line / 123
	FILENAME, // MSH_WORD.MSH_WORD / 124
	PARAM, // MSH_MINUSMSH_WORD / 125
	PATH // .. . / 126
	VAR // $WORD / 127
	DELIM // symbol|word after here_doc // 128
*/

#endif