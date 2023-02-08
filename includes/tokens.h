/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:46:09 by saeby             #+#    #+#             */
/*   Updated: 2023/02/08 11:47:11 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include "structures.h"

enum	e_token_types
{
	MSH_SEP = 100,
	MSH_STR,
	MSH_WORD,
	MSH_SYMBOL,
	MSH_DQUOTE,
	MSH_SQUOTE,
	MSH_PIPE,
	MSH_DPIPE,
	MSH_LT,
	MSH_DLT,
	MSH_GT,
	MSH_DGT,
	MSH_AMP,
	MSH_DAMP,
	MSH_DOLLAR,
	MSH_L_BR,
	MSH_R_BR,
	MSH_L_CBR,
	MSH_R_CBR,
	MSH_L_SBR,
	MSH_R_SBR,
	MSH_MINUS,
	MSH_DMINUS,
	MSH_END,
	MSH_FILENAME,
	MSH_PARAM,
	MSH_PATH,
	MSH_VAR,
	MSH_DELIM
};

/*
	MSH_SEP // separator => isspace / 100
	MSH_STR, // string / 101
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