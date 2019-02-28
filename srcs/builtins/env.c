/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:43:30 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/22 22:59:13 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void		add_env(t_env **lst_env, char *env, int x)
{
	t_env	*tmp;
	t_env	*new;
	size_t	len;

	tmp = *lst_env;
	if (!(new = (t_env*)malloc(sizeof(t_env))))
		ft_exit_malloc();
	len = ft_strlen(env);
	new->key = ft_strsub(env, 0, x);
	new->value = ft_strsub(env, x + 1, len - x - 1);
	new->next = NULL;
	if (!(*lst_env))
		*lst_env = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_env	*lst_env_dup(t_env **orig, t_env **add)
{
	t_env *tmp;
	t_env *dup;
	t_env *swap;

	tmp = *orig;
	dup = NULL;
	while (tmp)
	{
		add_elem_env(&dup, tmp->key, tmp->value);
		tmp = tmp->next;
	}
	tmp = *add;
	while (tmp)
	{
		if ((swap = find_elem_env(&dup, tmp->key)))
		{
			free(swap->value);
			(!(swap->value = ft_strdup(tmp->value))) ? ft_exit_malloc() : 0;
		}
		else
			add_elem_env(&dup, tmp->key, tmp->value);
		tmp = tmp->next;
	}
	del_lst_env(add);
	return (dup);
}

int				env_cp(char **env, t_env **lst_env)
{
	int		i;
	int		x;
	char	*buf;

	i = 0;
	if (env[0] == NULL)
	{
		buf = getcwd(0, 0);
		add_elem_env(lst_env, "PWD", buf);
		ft_memdel((void **)&buf);
	}
	else if (!(*lst_env) && env)
		while (env[i])
		{
			x = 0;
			while (env[i][x] && env[i][x] != '=')
				x += 1;
			add_env(lst_env, env[i], x);
			i += 1;
		}
	else if (!(*lst_env))
		return (0);
	add_shlvl(lst_env);
	return (1);
}

int				env_builtins(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int		i;
	int		option;
	char	*s;
	t_env	*tmp;
	char	**save_input;

	s = NULL;
	tmp = NULL;
	save_input = NULL;
	option = (elem->input[1] && ft_strcmp(elem->input[1], "-i") == 0) ? 1 : 0;
	i = option;
	while (++i && elem->input[i] && (s = ft_strchr(elem->input[i], '=')))
		add_env(&tmp, elem->input[i], ft_strlen(elem->input[i]) - ft_strlen(s));
	save_input = elem->input;
	elem->input = &(elem->input[i]);
	if (option == 0)
		tmp = lst_env_dup(lst_env, &tmp);
	(!elem->input[0]) ? g_ret[0] = 0 : 0;
	(elem->input[0]) ? dispatch_cmd(elem, &tmp,
	ft_strsplit(get_env_value(*lst_env, "$PATH"), ':'), alloc) :
	display_env(tmp);
	elem->input = save_input;
	del_lst_env(&tmp);
	return (0);
}
