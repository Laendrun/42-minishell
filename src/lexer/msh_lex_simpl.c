/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_simpl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:26:53 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 11:31:24 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gcc -c main.c -o objs/main.o
// original tokens
// word sep minus word symbol word sep minus word sep word symbol word end
// goal tokens
// word sep param sep filename sep param path

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
		else if (tmp->type == MSH_DLT)
			tmp = msh_set_delim(m_d, tmp, next);
		else if (!ft_strncmp(tmp->val, "$", 2))
			tmp = msh_set_var(m_d, tmp, next);
		else
		{
			new = msh_tok_lstnew(tmp->type, tmp->val);
			msh_tok_lstaddb(&m_d->s_tok, new);
			tmp = tmp->next;
		}
	}
	msh_expand_var(m_d);
	print_simpl_tok(m_d);
	msh_escape_char(m_d);
	msh_handle_quotes(m_d);
	print_simpl_tok(m_d);
	//print_env_strarray(m_d);
	// msh_create_commmands(m_d);
	return (SUCCESS);
}

t_tok_list	*msh_simpl_word(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne)
{
	char	*new;

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

t_tok_list	*msh_set_delim(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne)
{
	char	*new;

	msh_tok_lstaddb(&m_d->s_tok, msh_tok_lstnew(tok->type, tok->val));
	new = ft_strdup("");
	tok = ne;
	ne = tok->next;

	while (tok->type == MSH_SEP)
		tok = tok->next;
	ne = tok->next;
	while (tok->type == MSH_WORD || tok->type == MSH_SYMBOL)
	{
		new = ft_strjoin(new, tok->val);
		tok = ne;
		ne = tok->next;
	}
	if (new)
		msh_tok_lstaddb(&m_d->s_tok, msh_tok_lstnew(MSH_DELIM, new));
	return (tok);
}

t_tok_list	*msh_set_var(t_msh_data *m_d, t_tok_list *tok, t_tok_list *ne)
{
	// echo $PATH => MSH_VAR(PATH)
	// echo $PATH?_ => MSH_VAR(PATH?_)
	// echo $PATH$ => MSH_VAR(PATH)$
	char	*new;
	(void) m_d;

	new = ft_strdup("");
	tok = ne;
	ne = tok->next;
	while (tok->type == MSH_WORD || (tok->type == MSH_SYMBOL && ft_strncmp(tok->val, "$", 2)))
	{
		new = ft_strjoin(new, tok->val);
		tok = ne;
		ne = tok->next;
	}
	if (new)
		msh_tok_lstaddb(&m_d->s_tok, msh_tok_lstnew(MSH_VAR, new));
	return (tok);
}
