/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:59:28 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/13 11:56:39 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**msh_make_env_tabstr(t_msh_data *m_d)
{
	int			i;
	int			size;
	t_env_list *tmp;
	char 		**env_str;

	i = 0;
	tmp = m_d->env;
	size = msh_env_lstsize(m_d->env);
	env_str = malloc(sizeof(char *) * (size + 1));
	if (!env_str)
		return (NULL);
	while (tmp)
	{
		env_str[i] = malloc(strlen(tmp->key) + strlen(tmp->val) + 2);
		if (!env_str[i])
			return (NULL);
		ft_strcpy(env_str[i], tmp->key);
		ft_strcat(env_str[i], "=");
		ft_strcat(env_str[i], tmp->val);
		i++;
		tmp = tmp->next;
	}
	env_str[size] = 0;
	return (env_str);
}

void	calculate_nb_cmds(t_msh_data *m_d)
{
	t_tok_list	*cur;
	int			cpt;

	cpt = 0;
	cur = m_d->tokens;
	while (cur)
	{
		if (cur->type == PIPE || cur->type == END)
			cpt++;
		cur = cur->next;
	}
	m_d->nb_cmd = cpt;
}

t_tok_list **create_array_of_toklst(t_msh_data *m_d)
{
	t_tok_list	*cur;
	t_tok_list	**array;
	int			i;

	i = 0;
	array = (t_tok_list **)malloc(sizeof(t_tok_list *) * m_d->nb_cmd);
	if (!array)
		return (NULL);
	cur = m_d->tokens;
	while (cur)
	{
		array[i] = cur;
		while (cur->next && cur->type != PIPE)
			cur = cur->next;
		if (cur->next !=  NULL)
		{
			cur = cur->next;
			i++;
		}
		else
			break;
	}
	return (array);
}

int	get_nb_args(t_tok_list *d)
{
	int			cpt;
	t_tok_list	*tmp;

	cpt = 0;
	tmp = d;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == STR)
			cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}

int	create_cmd_lst(t_msh_data *m_d, int i)
{
	t_cmd		*new;
	char		**args;
	int			nb_arg;
	t_tok_list	*tmp;
	int 		j;

	nb_arg = get_nb_args(m_d->trunc_lst[i]);
	args = ft_calloc(sizeof(char *), (nb_arg + 1));
	if (!args)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	tmp = m_d->trunc_lst[i];
	j = 0;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == END)
			break ;
		if (tmp->type == WORD || tmp->type == STR)
		{
			args[j] = ft_strdup(tmp->val);
			if (!args[j])
				return (msh_error(1, ERR_MALMES, ERR_MALLOC));
			j++;
		}
		tmp = tmp->next;
	}
	new = msh_cmd_lstnew(NULL, args);
	msh_cmd_lstaddb(&m_d->cmds, new);
	return (EXIT_SUCCESS);
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

int	check_redir_type(t_msh_data *m_d, t_tok_list *tmp, t_cmd *end)
{
	if (tmp->type == LT)
	{
		end->infile = open(tmp->next->val, O_RDONLY);
		if (end->infile < 0)
			return(msh_error(1, ERR_OPEN, 1));
	}
	else if (tmp->type == DLT)
	{
		end->heredoc = 1;
		end->delim = tmp->next->val;
		if (ft_here_doc(m_d, end) != 0)
			return (EXIT_FAILURE);
	}
	else if (tmp->type == GT)
	{
		end->out_trunc = open(tmp->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (end->out_trunc < 0)
			return(msh_error(1, ERR_OPEN, 1));
	}
	else if (tmp->type == DGT)
	{
		end->out_app = open(tmp->next->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (end->out_app < 0)
			return(msh_error(1, ERR_OPEN, 1));
	}
	return (EXIT_SUCCESS);
}

int	set_redir_in_cmd_lst(t_msh_data *m_d, int i)
{
	t_tok_list	*tmp;
	t_cmd		*end;

	end = m_d->cmds;
	while (end->next)
		end = end->next;
	tmp = m_d->trunc_lst[i];
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == END)
			break ;
		if ((tmp->type == LT || tmp->type == DLT || tmp->type == GT
			|| tmp->type == DGT) && tmp->next->type == REDIR)
			{
				if (check_redir_type(m_d, tmp, end) != 0)
					return (EXIT_FAILURE);
			}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	cmd_preparation(t_msh_data *m_d)
{
	m_d->env_upd = msh_make_env_tabstr(m_d);
	if (!m_d->env_upd)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	m_d->pid = malloc(sizeof(int) * m_d->nb_cmd);
	if (!m_d->pid)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	m_d->fd = malloc(sizeof(int) * (m_d->nb_cmd - 1) * 2);
	if (!m_d->fd)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	m_d->trunc_lst = create_array_of_toklst(m_d);
	if (!m_d->trunc_lst)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	m_d->path = pip_get_path(m_d->env_upd);
	if (!m_d->path)
		return (msh_error(1, ERR_MALMES, ERR_MALLOC));
	return (EXIT_SUCCESS);
}

int	msh_create_commmands(t_msh_data *m_d)
{
	int		i;

	calculate_nb_cmds(m_d);
	if (cmd_preparation(m_d) != 0)
		return (EXIT_FAILURE);
	i = 0;
	while (i < m_d->nb_cmd)
	{
		if (create_cmd_lst(m_d, i) != 0)
			return (EXIT_FAILURE);
		if (set_redir_in_cmd_lst(m_d, i) != 0 )
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

// print_array_lst(m_d);

	// t_cmd *tmp;
	// tmp = m_d->cmds;
	// while(tmp)
	// {
	// 	i = 0;
	// 	while (tmp->args[i])
	// 	{
	// 		printf("%d : %s\n", i, tmp->args[i]);
	// 		i++;
	// 	}
	// 	printf("inf : %d\n", tmp->infile);
	// 	printf("hdoc : %d\n", tmp->heredoc);
	// 	printf("delim : %s\n", tmp->delim);
	// 	printf("out app : %d\n", tmp->out_app);
	// 	printf("out trunc : %d\n", tmp->out_trunc);
	// 	tmp = tmp->next;
	// }