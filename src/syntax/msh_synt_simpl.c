/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_synt_simpl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:26:53 by saeby             #+#    #+#             */
/*   Updated: 2023/01/27 16:53:42 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gcc -c main.c -o main.o
// original tokens
// word sep minus word symbol word sep minus word sep word symbol word end
// goal tokens
// word sep param sep filename sep param filename

void	print_simpl_tok(t_msh_data *m_data)
{ // tmp function to see the lexer result
	t_tok_list	*token;

	printf("Simpler tokens: \n");
	token = m_data->simpl_tok;
	while (token)
	{
		printf("Type: %d - Value: %s\n", token->type, token->val);
		token = token->next;
	}
}

int	msh_simplify_tokens(t_msh_data *m_data)
{
	t_tok_list	*tmp;
	t_tok_list	*next;

	tmp = m_data->tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == MSH_WORD)
			tmp = msh_simpl_word(m_data, tmp, next);
		else if (tmp->type == MSH_MINUS)
			tmp = msh_simpl_minus(m_data, tmp, next);
		else
		{
			msh_tok_lstaddb(&m_data->simpl_tok, msh_tok_lstnew(tmp->type, tmp->val));
			tmp = tmp->next;
		}
	}
	print_simpl_tok(m_data);
	return (SUCCESS);
}

t_tok_list	*msh_simpl_word(t_msh_data *m_data, t_tok_list *token, t_tok_list *next)
{
	if (next->type == MSH_SYMBOL && !ft_strncmp(".", next->val, 2) && next->next->type == MSH_WORD)
	{
		msh_tok_lstaddb(&m_data->simpl_tok, msh_tok_lstnew(MSH_FILENAME, msh_fn_from_tok(token->val, next->next->val)));
		return (next->next->next);
	}
	else
	{
		msh_tok_lstaddb(&m_data->simpl_tok, msh_tok_lstnew(token->type, token->val));
		return (next);
	}
	return (SUCCESS);
}

t_tok_list	*msh_simpl_minus(t_msh_data *m_data, t_tok_list *token, t_tok_list *next)
{
	if (token->type == MSH_MINUS && next->type == MSH_WORD)
	{
		msh_tok_lstaddb(&m_data->simpl_tok, msh_tok_lstnew(MSH_PARAM, msh_par_from_tok(next->val)));
		return (next->next);
	}
	else
	{
		msh_tok_lstaddb(&m_data->simpl_tok, msh_tok_lstnew(token->type, token->val));
		return (next);
	}
}

char	*msh_par_from_tok(char *val)
{
	char	*res;

	res = "-";
	res = ft_strjoin(res, val);
	return (res);
}

char	*msh_fn_from_tok(char *fn, char *ext)
{
	char	*res;

	res = ft_strjoin(fn, ".");
	res = ft_strjoin(res, ext);
	return (res);
}
