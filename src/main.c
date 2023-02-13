/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:05:50 by saeby             #+#    #+#             */
/*   Updated: 2023/02/12 13:28:01 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_code = 0;
// I think we should use extern int insted of static int
// extern int are defined in the header file

int	main(int ac, char **av, char **env)
{
	char		*rl;
	t_msh_data	m_data;
	int			ret;

	(void) ac;
	(void) av;
	ret = msh_init(&m_data, env);
	if (ret != 0)
		exit(EXIT_FAILURE);
	printf("\e[1;1H\e[2J");
	while (1)
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
	exit(EXIT_SUCCESS);
}

int	msh_parsing(t_msh_data *m_d)
{
	int	ret;

	ret = EXIT_SUCCESS;
	ret = msh_expand_var(m_d);
	if (ret != EXIT_SUCCESS)
		return (ret);
	msh_escape_char(m_d);
	if (ret != EXIT_SUCCESS)
		return (ret);
	msh_handle_quotes(m_d);
	if (ret != EXIT_SUCCESS)
		return (ret);
	msh_err_near_token(m_d);
	if (ret != EXIT_SUCCESS)
		return (ret);
	msh_create_commmands(m_d);
	if (ret != EXIT_SUCCESS)
		return (ret);
	return (EXIT_SUCCESS);
}

int	new_line(t_msh_data *m_d, char *line)
{
	int	ret;

	ret = msh_lex(m_d, line);
	if (ret != EXIT_SUCCESS)
		return (ret);
	// msh_parsing(m_d);
	// if (ret != EXIT_SUCCESS)
	// 	return (ret);
	msh_expand_var(m_d);
	msh_escape_char(m_d);
	msh_handle_quotes(m_d);
	msh_err_near_token(m_d);
	msh_create_commmands(m_d);
	msh_pipex(m_d);
	msh_pip_reset(m_d);
	return (ret);
}

int	msh_get_gcode(void)
{
	return (g_code);
}

void	msh_set_gcode(int val)
{
	g_code = val;
}