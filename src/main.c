/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:05:50 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 15:00:27 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_code = 0;

int	main(int ac, char **av, char **env)
{
	char		*rl;
	t_msh_data	m_data;

	(void) ac;
	(void) av;
	msh_init(&m_data, env);
	printf("\e[1;1H\e[2J");
	while (1)
	{
		rl_on_new_line();
		rl = readline(m_data.prompt);
		add_history(rl);
		if (ft_strncmp(rl, "exit", 5) == 0)
			break ;
		if (ft_strncmp(rl, "clear", 5) == 0)
			msh_clear(&m_data);
		msh_lex(&m_data, rl);
		msh_parser(&m_data);
		msh_free_tok(&m_data);
		msh_free_simpl_tok(&m_data);
	}
	free(rl);
	/*msh_free_tok(&m_data);
	msh_free_env(&m_data);*/
	msh_terminate(&m_data);
	return (SUCCESS);
}

int	msh_get_gcode(void)
{
	return (g_code);
}

void	msh_set_gcode(int val)
{
	g_code = val;
}