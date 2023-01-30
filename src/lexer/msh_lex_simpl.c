/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_simpl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:26:53 by saeby             #+#    #+#             */
/*   Updated: 2023/01/30 15:23:21 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gcc -c main.c -o objs/main.o
// original tokens
// word sep minus word symbol word sep minus word sep word symbol word end
// goal tokens
// word sep param sep filename sep param path

void	print_simpl_tok(t_msh_data *m_data)
{
	t_tok_list	*token;

	printf("Simplified tokens: \n");
	token = m_data->s_tok;
	while (token)
	{
		printf("Type: %d - Value: %s\n", token->type, token->val);
		token = token->next;
	}
}

int	msh_simplify_tokens(t_msh_data *m_d)
{
	// if type == << set next token(s) to type delim
	// if type != << set $WORD to type VAR

	t_tok_list	*tmp;
	t_tok_list	*next;
	t_tok_list	*new;

	tmp = m_d->tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == MSH_WORD && ft_strncmp(next->val, "/", 2))
			tmp = msh_simpl_word(m_d, tmp, next);
		else if (tmp->type == MSH_MINUS)
			tmp = msh_simpl_minus(m_d, tmp, next);
		else if (msh_is_path_comp(tmp))
			tmp = msh_simpl_path(m_d, tmp, next);
		else
		{
			new = msh_tok_lstnew(tmp->type, tmp->val);
			msh_tok_lstaddb(&m_d->s_tok, new);
			tmp = tmp->next;
		}
	}
	print_simpl_tok(m_d);
	return (SUCCESS);
}

t_tok_list	*msh_simpl_word(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne)
{
	char	*new;
	/*int		s;
	int		p;
	int		n;
	
	s = ne->type == MSH_SYMBOL;
	p = !ft_strncmp(".", ne->val, 2);
	n = ne->next->type == MSH_WORD;*/
	if (ne->type == MSH_SYMBOL && !ft_strncmp(".", ne->val, 2) && ne->next->type == MSH_WORD)
	{
		new = msh_fn_from_tok(tok->val, ne->next->val);
		msh_tok_lstaddb(&m_d->s_tok, msh_tok_lstnew(MSH_FILENAME, new));
		return (ne->next->next);
	}
	else
	{
		msh_tok_lstaddb(&m_d->s_tok, msh_tok_lstnew(tok->type, tok->val));
		return (ne);
	}
	return (SUCCESS);
}

t_tok_list	*msh_simpl_minus(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne)
{
	char	*new;

	if (tok->type == MSH_MINUS && ne->type == MSH_WORD)
	{
		new = msh_par_from_tok(ne->val);
		msh_tok_lstaddb(&m_d->s_tok, msh_tok_lstnew(MSH_PARAM, new));
		return (ne->next);
	}
	else
	{
		msh_tok_lstaddb(&m_d->s_tok, msh_tok_lstnew(tok->type, tok->val));
		return (ne);
	}
}

t_tok_list	*msh_simpl_path(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne)
{
	char	*path;

	path = ft_strdup("");
	while (msh_is_path_comp(tok))
	{
		if (tok->type == MSH_WORD)
			path = ft_strjoin(path, tok->val);
		if (tok->type == MSH_SYMBOL)
				path = ft_strjoin(path, tok->val);
		tok = ne;
		ne = ne->next;
	}
	if (path)
		msh_tok_lstaddb(&m_d->s_tok, msh_tok_lstnew(MSH_PATH, path));
	return (tok);
}
