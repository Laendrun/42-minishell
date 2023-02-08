/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:35:46 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 19:31:15 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_init(t_msh_data *m_data, char **env)
{
	m_data->name = "shellusion";
	m_data->prompt = "shellusion-0.6> ";
	m_data->env = NULL;
	m_data->tokens = NULL;
	m_data->s_tok = NULL;
	m_data->fd = NULL;
	m_data->pid = NULL;
	m_data->nb_cmd = 0;
	m_data->process = 0;
	m_data->path = NULL;
	m_data->infile = -1;
	m_data->heredoc = -1;
	m_data->delim = NULL;
	m_data->outfile_app = -1;
	m_data->outfile_trunc = -1;
	m_data->env_upd = NULL;
	m_data->trunc_lst = NULL;
	m_data->cmds = NULL;
	msh_env_init(m_data, env);
	return (SUCCESS);
}

int	msh_env_init(t_msh_data *m_data, char **env)
{
	char		**tmp;
	t_env_list	*new;

	while (*env)
	{
		tmp = ft_split(*env, '=');
		new = msh_env_lstnew(ft_strdup(tmp[0]), ft_strdup(tmp[1]));
		msh_env_lstaddb(&m_data->env, new);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		env++;
	}
	return (SUCCESS);
}

void	msh_pip_reset(t_msh_data *m_data)
{
	m_data->fd = NULL;
	m_data->pid = NULL;
	m_data->nb_cmd = 0;
	m_data->process = 0;
	m_data->path = NULL;
	m_data->infile = -1;
	m_data->heredoc = -1;
	m_data->outfile_app = -1;
	m_data->outfile_trunc = -1;
	m_data->env_upd = NULL;
	m_data->trunc_lst = NULL;
	m_data->cmds = NULL;
	msh_free_cmds(m_data);
}
