/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/10 16:12:43 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// heredoc expand VAR

int	handle_var_hdoc(int (*i)[2], char *tok, char **ret, t_msh_data *m_d)
{
	*ret = ft_strjoin_free(*ret, ft_substr(tok, (*i)[1], (*i)[0] - (*i)[1]));
	if (!*ret)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	(*i)[0]++;
	(*i)[1] = (*i)[0];
	while (tok[(*i)[0]] && !msh_isspace(tok[(*i)[0]]) && tok[(*i)[0]] != '$')
		(*i)[0]++;
	*ret = ft_strjoin_free(*ret, msh_get_env_free(m_d, ft_substr(tok, (*i)[1], (*i)[0] - (*i)[1])));
	if (!*ret)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	(*i)[1] = (*i)[0];
	(*i)[0]--;
	return (EXIT_SUCCESS);
}

int	handle_error_code_hdoc(int (*i)[2], char **tok, char **ret)
{
	*ret = ft_strjoin_free(*ret, ft_substr(*tok, (*i)[1], (*i)[0] - (*i)[1]));
	if (!*ret)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	(*i)[0]++;
	(*i)[1] = (*i)[0];
	(*i)[0]++;
	*ret = ft_strjoin_free(*ret, ft_itoa(msh_get_gcode()));
	if (!*ret)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	(*i)[1] = (*i)[0];
	(*i)[0]--;
	return (EXIT_SUCCESS);
}

char	*msh_var_in_hdoc(t_msh_data *m_d, char *tok)
{
	int		i[2];
	char	*ret;

	ret = ft_strdup("");
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
	if (!ret)
		return (NULL);
	return (ret);
}

int	ft_here_doc(t_msh_data *m_d, t_cmd *end)
{
	char	*line;
	char	*read;

	if (pipe(end->hdoc) < 0)
		return(msh_error(1, ERR_PIPE, 1));
	read = readline(">");
	line = msh_var_in_hdoc(m_d, read);
	free(read);
	while (read)
	{
		if (ft_strncmp(end->delim, line, (ft_strlen(end->delim) + 1)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(ft_strcat(line, "\n"), end->hdoc[1]);
		free(line);
		read = readline(">");
		line = msh_var_in_hdoc(m_d, read);
		free(read);
	}
	if (close(end->hdoc[1]) < 0)
		return(msh_error(1, ERR_CLOSE, 1));
	return (EXIT_SUCCESS);
}

// int	check_if_outfile_trunc(t_msh_data *m_d)
// {
// 	t_tok_list	*tmp;

// 	tmp = m_d->trunc_lst[m_d->nb_cmd - 1];
// 	while (tmp)
// 	{
// 		if (tmp->type == GT && (tmp->next->type == REDIR))
// 		{
// 			m_d->outfile_trunc = open(tmp->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			// printf("open trunc : %d\n", m_d->outfile_trunc);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (SUCCESS);
// }

// int	check_if_outfile_app(t_msh_data *m_d)
// {
// 	t_tok_list	*tmp;

// 	tmp = m_d->trunc_lst[m_d->nb_cmd - 1];
// 	while (tmp)
// 	{
// 		// printf("type : %d val : %s\n", tmp->type, tmp->val);
// 		if (tmp->type == DGT && (tmp->next->type == REDIR))
// 		{
// 			m_d->outfile_app = open(tmp->next->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 			// printf("open : %d\n", m_d->outfile_app);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (SUCCESS);
// }

// int	check_if_infile(t_msh_data *m_d)
// {
// 	t_tok_list	*tmp;

// 	tmp = m_d->trunc_lst[0];
// 	while (tmp)
// 	{
// 		// printf("type : %d val : %s\n", tmp->type, tmp->val);
// 		if (tmp->type == LT && (tmp->next->type == REDIR))
// 		{
// 			m_d->infile = open(tmp->next->val, O_RDONLY);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (SUCCESS);
// }

// void	f_here_doc(t_msh_data *m_d)
// {
// 	char	*line;

// 	if (pipe(m_d->hdoc) < 0)
// 		f_error("Error creating pipe :", strerror(errno), m_d);
// 	line = readline(">");
// 	while (line)
// 	{
// 		if (ft_strncmp(m_d->delim, line, (ft_strlen(m_d->delim) + 1)) == 0)
// 			break ;
// 		ft_putstr_fd(ft_strcat(line, "\n"), m_d->hdoc[1]);
// 		line = readline(">");
// 	}
// 	if (close(m_d->hdoc[1]) < 0)
// 		f_error("Close error :", strerror(errno), m_d);
// }

// int	check_if_heredoc(t_msh_data *m_d)
// {
// 	t_tok_list	*tmp;

// 	tmp = m_d->trunc_lst[0];
// 	while (tmp)
// 	{
// 		if (tmp->type == DLT && tmp->next->type == REDIR)
// 		{
// 			m_d->heredoc = 1;
// 			m_d->delim = tmp->next->val;
// 			f_here_doc(m_d);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (SUCCESS);
// }

// int	check_if_ambiguous_redirection(t_msh_data *m_d)
// {
// 	t_tok_list	*tmp;
// 	int			i;

// 	i = 1;
// 	while (i < m_d->nb_cmd - 1)
// 	{
// 		tmp = m_d->trunc_lst[i];
// 		while (tmp)
// 		{
// 			if (tmp->type == GT || tmp->type == DGT || tmp->type == LT || tmp->type == DLT)
// 			{
// 				printf("ambiguous redirection.\n");
// 				return (ERROR);
// 			}
// 			tmp = tmp->next;
// 		}
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// int	msh_redir_op(t_msh_data *m_d)
// {
// 	// if (m_d->nb_cmd > 2)
// 	// 	check_if_ambiguous_redirection(m_d);
// 	check_if_heredoc(m_d);
// 	check_if_infile(m_d);
// 	check_if_outfile_app(m_d);
// 	check_if_outfile_trunc(m_d);
// 	return (SUCCESS);
// }