/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:54:27 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 18:55:24 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SIGINT (ctrl-c)
// SIGQUIT (ctrl-\)
// SIGHUP (ctrl-d)

// if in child +> silence these motherfucking signals
// write a function to set the signal handlers to be "nothing"
// so they will finally shut and let us work in peace

void	sigint_update(void)
{
	struct sigaction	action;

	action.sa_handler = &backslash_n;
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
