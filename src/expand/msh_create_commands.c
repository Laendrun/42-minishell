/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/04 15:57:00 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to create commands we need to provide good format for execve function:
// 1. cmd with path (char *)
// 2. cmd with args (char **)
// 3. env (char**)

// make env list back into into a double array of strings with reduced malloc !
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
	cur = m_d->s_tok;
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
	cur = m_d->s_tok;
	while (cur)
	{
		array[i] = cur;
		while (cur->next && cur->type != PIPE)
			cur = cur->next;
		if (cur->next !=  NULL)
		{
			cur = cur->next;
			cur->prev->next = NULL;
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
		if (tmp->type == VAR || tmp->type == WORD || tmp->type == STR || tmp->type == PARAM)
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
		if (tmp->type == VAR || tmp->type == WORD || tmp->type == STR 
			|| tmp->type == PARAM /*|| tmp->type == FILENAME*/ || tmp->type == PATH)
		{
			args[j] = ft_calloc(sizeof(char), (ft_strlen(tmp->val) + 1));
			args[j] = tmp->val;
			//printf("%s\n", args[j]);
			j++;
		}
		tmp = tmp->next;
	}
	new = msh_cmd_lstnew(NULL, args);
	msh_cmd_lstaddb(&m_d->cmds, new);
	return (SUCCESS);
}

int	msh_create_commmands(t_msh_data *m_d)
{
	int	i;

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
		//print_tok_trunclst(m_d->trunc_lst[i]);
		create_cmd_lst(m_d, i);
		i++;
	}
	// print_array_lst(m_d);
	// i = 0;
	// while(m_d->cmds)
	// {
	// 	i = 0;
	// 	while (m_d->cmds->args[i])
	// 	{
	// 		printf("%d : %s\n", i, m_d->cmds->args[i]);
	// 		i++;
	// 	}
	// 	m_d->cmds = m_d->cmds->next;
	// }
	return (SUCCESS);
}


