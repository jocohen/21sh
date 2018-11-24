/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:43:30 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/24 18:52:59 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

static void		add_env(t_env **lst_env, char *env, int x)
{
	t_env	*tmp;
	t_env	*new;
	size_t	len;

	tmp = *lst_env;
	if (!(new = (t_env*)malloc(sizeof(t_env))))
		return ;
	len = ft_strlen(env);
	new->key = ft_strsub(env, 0, x);
	new->value = ft_strsub(env, x + 1, len - 1);
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
			swap->value = ft_strdup(tmp->value);
		}
		else
			add_elem_env(&dup, tmp->key, tmp->value);
		tmp = tmp->next;
	}
	del_lst_env(add);
	return (dup);
}

void			env_cp(char **env, t_env **lst_env)
{
	int	i;
	int	x;

	i = 0;
	if (!(*lst_env) && env)
	{
		while (env[i])
		{
			x = 0;
			while (env[i][x] && env[i][x] != '=')
				x += 1;
			add_env(lst_env, env[i], x);
			i += 1;
		}
	}
}

void			env_builtins(t_ast *elem, t_env *lst_env)
{
	int		i;
	int		option;
	int		x;
	char	*s;
	t_env	*tmp;

	s = NULL;
	tmp = NULL;
	option = (elem->input[1] && ft_strcmp(elem->input[1], "-i") == 0) ? 1 : 0;
	i = option;
	while (++i && elem->input[i] && (s = ft_strchr(elem->input[i], '=')))
		add_env(&tmp, elem->input[i], ft_strlen(elem->input[i]) - ft_strlen(s));
	x = 0;
	while (x < i)
		free(elem->input[x++]);
	elem->input = &(elem->input[i]);
	if (option == 0)
		tmp = lst_env_dup(&lst_env, &tmp);
	(elem->input[0]) ? dispatch_cmd(elem, tmp,
	ft_strsplit(get_env_value(lst_env, "$PATH"), ':')) : display_env(tmp);
	del_lst_env(&tmp);
}
