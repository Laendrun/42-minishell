/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:54:27 by saeby             #+#    #+#             */
/*   Updated: 2023/02/10 22:38:13 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SIGINT (ctrl-c)
// SIGQUIT (ctrl-\)
// SIGHUP (ctrl-d)

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_code = 1;
}

// if in child +> silence these motherfucking signals
// write a function to set the signal handlers to be "nothing"
// so they will finally shut and let us work in peace

void	nothing(int v)
{
	(void)v;
	rl_redisplay();
}

void	sigint_update(void)
{
	struct sigaction	action;

	action.sa_handler = &nothing;
	sigaction(SIGINT, &action, NULL);
}

// void	handle_sighup(void)
// {
// 	struct sigaction	action;

// 	action.sa_handler = &nothing;
// 	sigaction(SIGHUP, &action, NULL);
// }

void	msh_sigint(void)
{
	struct sigaction	action;

	action.sa_handler = &handle_sigint;
	sigaction(SIGINT, &action, NULL);
}

void	msh_sigquit(void)
{
	struct sigaction	action;

	action.sa_handler = &nothing;
	sigaction(SIGQUIT, &action, NULL);
}

void	msh_set_signals(void)
{
	msh_sigint();
	msh_sigquit();
}
