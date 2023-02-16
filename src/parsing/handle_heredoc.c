/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/16 18:16:50 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// heredoc expand VAR

int	handle_var_hdoc(int (*i)[2], char *tok, char **ret, t_msh_data *m_d)
{
	*ret = ft_strjoin_free(*ret, ft_substr(tok, (*i)[1], (*i)[0] - (*i)[1]));
	if (!*ret)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	(*i)[0]++;
	(*i)[1] = (*i)[0];
	while (tok[(*i)[0]] && !msh_isspace(tok[(*i)[0]]) && tok[(*i)[0]] != '$')
		(*i)[0]++;
	*ret = ft_strjoin_free(*ret, msh_get_env_free(m_d,
				ft_substr(tok, (*i)[1], (*i)[0] - (*i)[1])));
	if (!*ret)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	(*i)[1] = (*i)[0];
	(*i)[0]--;
	return (EXIT_SUCCESS);
}

int	handle_error_code_hdoc(int (*i)[2], char **tok, char **ret)
{
	*ret = ft_strjoin_free(*ret, ft_substr(*tok, (*i)[1], (*i)[0] - (*i)[1]));
	if (!*ret)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	(*i)[0]++;
	(*i)[1] = (*i)[0];
	(*i)[0]++;
	*ret = ft_strjoin_free(*ret, ft_itoa(msh_get_gcode()));
	if (!*ret)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	(*i)[1] = (*i)[0];
	(*i)[0]--;
	return (EXIT_SUCCESS);
}

char	*msh_var_in_hdoc(t_msh_data *m_d, char *tok)
{
	int		i[2];
	char	*ret;

	ret = ft_strdup("");
	if (!tok)
		return (NULL);
	i[0] = -1;
	i[1] = 0;
	while (tok[++i[0]])
	{
		if (tok[i[0]] == '$' && tok[i[0] + 1] != 0 && tok[i[0] - 1] != '\\')
		{
			if (tok[i[0] + 1] == '?')
			{
				if (handle_error_code_hdoc(&i, &tok, &ret) != 0)
					return (NULL);
			}
			else
				if (handle_var_hdoc(&i, tok, &ret, m_d) != 0)
					return (NULL);
		}
	}
	ret = ft_strjoin_free(ret, ft_substr(tok, i[1], i[0] - i[1]));
	return (ret);
}

void	heredoc_loop(char *line, char *read, t_msh_data *m_d, t_cmd *end)
{
	while (read)
	{
		if (ft_strncmp(end->delim, line, (ft_strlen(end->delim) + 1)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(ft_strcat(line, "\n"), end->hdoc[1]);
		free(line);
		if (msh_get_gcode() != 0)
			return ;
		read = readline(">");
		line = msh_var_in_hdoc(m_d, read);
		free(read);
	}
}

int	ft_here_doc(t_msh_data *m_d, t_cmd *end)
{
	char	*line;
	char	*read;

	msh_set_gcode(0);
	if (pipe(end->hdoc) < 0)
		return (msh_error(1, ERR_PIPE, 1));
	read = readline(">");
	line = msh_var_in_hdoc(m_d, read);
	free(read);
	heredoc_loop(line, read, m_d, end);
	if (close(end->hdoc[1]) < 0)
		return (msh_error(1, ERR_CLOSE, 1));
	return (EXIT_SUCCESS);
}
