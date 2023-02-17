/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:05:50 by saeby             #+#    #+#             */
/*   Updated: 2023/02/17 11:03:59 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_code = 0;

int	main(int ac, char **av, char **env)
{
	char		*rl;
	t_msh_data	m_data;
	int			ret;

	(void) ac;
	(void) av;
	ret = msh_init(&m_data, env);
	printf("\e[1;1H\e[2J");
	while (1 && ret == EXIT_SUCCESS)
	{
		msh_set_signals();
		rl_on_new_line();
		rl = readline(m_data.prompt);
		add_history(rl);
		if (rl)
		{
			if (new_line(&m_data, rl) >= ERR_MALLOC)
				break ;
			msh_free_tok(&m_data);
		}
		if (!rl)
			break ;
	}
	return (ret);
}

int	msh_parsing(t_msh_data *m_d)
{
	if (msh_expand_var(m_d) != 0)
		return (EXIT_FAILURE);
	if (msh_escape_char(m_d) != 0)
		return (EXIT_FAILURE);
	if (msh_handle_quotes(m_d) != 0)
		return (EXIT_FAILURE);
	// print_tok(m_d);
	if (msh_err_near_token(m_d) != 0)
		return (EXIT_FAILURE);
	if (msh_create_commmands(m_d) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	new_line(t_msh_data *m_d, char *line)
{
	if (msh_lex(m_d, line) != 0)
	{
		free(line);
		return (EXIT_FAILURE);
	}
	free(line);
	msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(END, 0));
	if (msh_parsing(m_d) != 0)
	{
		msh_pip_reset(m_d);
		return (EXIT_FAILURE);
	}
	if (msh_pipex(m_d) != 0)
	{
		msh_pip_reset(m_d);
		return (EXIT_FAILURE);
	}
	msh_pip_reset(m_d);
	return (EXIT_SUCCESS);
}

int	msh_get_gcode(void)
{
	return (g_code);
}

void	msh_set_gcode(int val)
{
	g_code = val;
}
