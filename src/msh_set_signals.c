/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:54:27 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 15:42:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SIGINT (ctrl-c)
// SIGQUIT (ctrl-\)
// SIGHUP  (ctrl-d) 
// SIG_IGN to ignore the signals

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sighup(int sig)
{
	(void)sig;
	write(1, "exit\n", 6);
	exit(1);
}

void	msh_sighup()
{
	struct sigaction	action;
	action.sa_handler = &handle_sighup;
	sigaction(SIGHUP, &action, NULL);
}

void	msh_sigint(void)
{
	struct sigaction	action;
	action.sa_handler = &handle_sigint;
	sigaction(SIGINT, &action, NULL);
}

void	msh_sigquit()
{
	struct sigaction	action;
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}

void	msh_set_signals(void)
{
	msh_sigint();
	msh_sigquit();
	msh_sighup();
}