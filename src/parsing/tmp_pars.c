/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:59:28 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/10 12:28:14 by egauthey         ###   ########.fr       */
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
		return NULL;
	while (tmp)
	{
		env_str[i] = malloc(strlen(tmp->key) + strlen(tmp->val) + 2);
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
	cur = m_d->tokens;
	while (cur)
	{
		array[i] = cur;
		while (cur->next && cur->type != PIPE)
			cur = cur->next;
		if (cur->next !=  NULL)
		{
			cur = cur->next;
			// cur->prev->next = NULL;
			//the connection with prev is still there and the list is still connected I guess
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
		if (tmp->type == VAR || tmp->type == WORD || tmp->type == STR)
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
	// printf("%d\n", nb_arg);
	args = ft_calloc(sizeof(char *), (nb_arg + 1));
	tmp = m_d->trunc_lst[i];
	j = 0;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == END)
			break ;
		if (tmp->type == VAR || tmp->type == WORD || tmp->type == STR)
		{
			// args[j] = ft_calloc(sizeof(char), (ft_strlen(tmp->val) + 1));
			args[j] = ft_strdup(tmp->val);
			// args[j] = tmp->val;
			// printf("%s\n", args[j]);
			j++;
		}
		tmp = tmp->next;
	}
	new = msh_cmd_lstnew(NULL, args);
	msh_cmd_lstaddb(&m_d->cmds, new);
	return (SUCCESS);
}

void	ft_here_doc(t_cmd *end, t_msh_data *m_d)
{
	char	*line;

	if (pipe(end->hdoc) < 0)
		f_error("Error creating pipe :", strerror(errno), m_d);
	line = readline(">");
	while (line)
	{
		if (ft_strncmp(end->delim, line, (ft_strlen(end->delim) + 1)) == 0)
			break ;
		ft_putstr_fd(ft_strcat(line, "\n"), end->hdoc[1]);
		line = readline(">");
	}
	if (close(end->hdoc[1]) < 0)
		f_error("Close error :", strerror(errno), m_d);
}

int	check_redir_type(t_tok_list *tmp, t_cmd *end, t_msh_data *m_d)
{
	if (tmp->type == LT)
		end->infile = open(tmp->next->val, O_RDONLY);
	else if (tmp->type == DLT)
	{
		end->heredoc = 1;
		end->delim = tmp->next->val;
		ft_here_doc(end, m_d);
	}
	else if (tmp->type == GT)
		end->out_trunc = open(tmp->next->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (tmp->type == DGT)
		end->out_app = open(tmp->next->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (SUCCESS);
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
				check_redir_type(tmp, end, m_d);
			}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	msh_create_commmands(t_msh_data *m_d)
{
	int		i;

	calculate_nb_cmds(m_d);
	m_d->env_upd = msh_make_env_tabstr(m_d);
	m_d->pid = malloc(sizeof(int) * m_d->nb_cmd);
	m_d->fd = malloc(sizeof(int) * (m_d->nb_cmd - 1) * 2);
	m_d->trunc_lst = create_array_of_toklst(m_d);
	m_d->path = pip_get_path(m_d->env_upd);
	i = 0;
	// printf("nb cmd : %d\n", m_d->nb_cmd);
	while (i < m_d->nb_cmd)
	{
		// print_tok_trunclst(m_d->trunc_lst[i]);
		create_cmd_lst(m_d, i);
		set_redir_in_cmd_lst(m_d, i);
		i++;
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
	return (SUCCESS);
}