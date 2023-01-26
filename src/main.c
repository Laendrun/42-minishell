/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:05:50 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 13:09:18 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*rl;

	(void) ac;
	(void) av;
	(void) env;
	printf("\e[1;1H\e[2J");
	while (1)
	{
		rl_on_new_line();
		rl = readline("prompt> ");
		add_history(rl);
	}
	return (EXIT_SUCCESS);
}