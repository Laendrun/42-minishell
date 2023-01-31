/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:31:08 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 13:39:42 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_simpl_tok(t_msh_data *m_data)
{
	t_tok_list	*token;

	printf("%sSimplified tokens: \n%s", YELLOW, RESET);
	token = m_data->s_tok;
	while (token)
	{
		printf("Type: %d - Value: %s\n", token->type, token->val);
		token = token->next;
	}
}

void	print_tok(t_msh_data *m_data)
{
	t_tok_list	*token;

	token = m_data->tokens;
	printf("%sOriginal tokens: \n%s", YELLOW, RESET);
	while (token)
	{
		printf("Type: %d - Value: %s\n", token->type, token->val);
		token = token->next;
	}
}
