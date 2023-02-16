/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:54:27 by saeby             #+#    #+#             */
/*   Updated: 2023/02/16 18:32:20 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_update(void)
{
	struct sigaction	action;

	action.sa_handler = &backslash_n;
	sigaction(SIGINT, &action, NULL);
}

void	msh_sigint(void)
{
	struct sigaction	action;

	action.sa_handler = &handle_sigint;
	sigaction(SIGINT, &action, NULL);
}

void	msh_sigquit(void)
{
	struct sigaction	action;

	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}

void	msh_set_signals(void)
{
	msh_sigint();
	msh_sigquit();
}
