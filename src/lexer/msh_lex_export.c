/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:23:15 by saeby             #+#    #+#             */
/*   Updated: 2023/02/17 12:08:25 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	msh_lex_export(t_msh_data *m_d, char *line, unsigned int *i)
{
	int				err;
	char			*tmp;
	unsigned int	t;

	err = EXIT_SUCCESS;
	*i += 7;
	insert_token(m_d, WORD, ft_strdup("export"), &err);
	insert_token(m_d, SEP, 0, &err);
	if (!ft_strchr(line + *i, '='))
		return (EXIT_SUCCESS);
	t = *i;
	while (line[*i] != '=')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	insert_token(m_d, WORD, ft_strdup(tmp), &err);
	free(tmp);
	insert_token(m_d, SEP, 0, &err);
	tmp = ft_substr(line, *i + 1, ft_strlen(line) - t);
	insert_token(m_d, WORD, ft_strdup(tmp), &err);
	free(tmp);
	if (err)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	return (EXIT_SUCCESS);
}*/
static void	key_val(t_msh_data *m_d, char *line, unsigned int *i, int *err);
static int	end(char *tmp, int status);

int	msh_lex_export(t_msh_data *m_d, char *line, unsigned int *i)
{
	int				err;
	char			*tmp;
	unsigned int	t;

	err = EXIT_SUCCESS;
	*i += 7;
	insert_token(m_d, WORD, ft_strdup("export"), &err);
	insert_token(m_d, SEP, 0, &err);
	while (msh_isspace(line[*i]) && line[*i])
		*i += 1;
	t = *i;
	tmp = ft_substr(line, t, ft_strlen(line) - t);
	if (!ft_strlen(tmp))
		return (end(tmp, EXIT_SUCCESS));
	if (!ft_strchr(line + *i, '='))
	{
		insert_token(m_d, WORD, ft_strdup(tmp), &err);
		return (end(tmp, EXIT_SUCCESS));
	}
	free(tmp);
	key_val(m_d, line, i, &err);
	if (err)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	return (EXIT_SUCCESS);
}

static void	key_val(t_msh_data *m_d, char *line, unsigned int *i, int *err)
{
	unsigned int	t;
	char			*tmp;

	t = *i;
	while (line[*i] != '=')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	insert_token(m_d, WORD, ft_strdup(tmp), err);
	free(tmp);
	insert_token(m_d, SEP, 0, err);
	tmp = ft_substr(line, *i + 1, ft_strlen(line) - t);
	insert_token(m_d, WORD, ft_strdup(tmp), err);
	free(tmp);
}

static int	end(char *tmp, int status)
{
	free(tmp);
	return (status);
}
