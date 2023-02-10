/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:31:08 by saeby             #+#    #+#             */
/*   Updated: 2023/02/10 11:59:54 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_env_strarray(t_msh_data *m_d)
{
	char	**env;
	int		i;

	env = msh_make_env_tabstr(m_d);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	print_tok_trunclst(t_tok_list *d)
{
	t_tok_list	*token;

	printf("%strunc token list: \n%s", YELLOW, RESET);
	token = d;
	while (token)
	{
		printf("Type: %d - Value: %s\n", token->type, token->val);
		token = token->next;
	}
}

void	print_array_lst(t_msh_data *m_d)
{
	int	i = 0;
	while(i < m_d->nb_cmd)
	{
		print_tok_trunclst(m_d->trunc_lst[i]);
		i++;
	}
}




// //reverse order to test prev
// void	print_simpl_tok(t_msh_data *m_data)
// {
// 	t_tok_list	*token;

// 	printf("%sSimplified tokens: \n%s", YELLOW, RESET);
// 	token = m_data->s_tok;
// 	token = msh_tok_lstlast(token);

// 	while (token)
// 	{
// 		printf("Type: %d - Value: %s\n", token->type, token->val);
// 		token = token->prev;
// 	}
// }
