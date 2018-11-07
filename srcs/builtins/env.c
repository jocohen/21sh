/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:43:30 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/07 18:05:02 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

static void	add_env(t_env **lst_env, char *env, int x)
{
	t_env	*tmp;
	t_env	*new;
	size_t	len;

	tmp = *lst;
	if (!(new = (t_env*)malloc(sizeof(t_env))))
		return;
	len = ft_strlen(env);
	new->key = ft_strsub(env, 0, x);
	new->value = ft_strsub(env, x + 1,len - 1);
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

void	env_cp(char **env, t_env **lst_env)
{
	int	i;
	int	x;

	i = 0;
	if (!(*lst_env))
	{
		while (env[i])
		{
			x = 0;
			while (env[i][x] && env[i][x] != '=')
				x += 1;
			add_env(lst_env, env, x);
			i += 1;
		}
	}
}

char	**convert_lst_tab(t_env **lst)
{
	t_env	*tmp;
	char	**tab;
	int		i;

	tmp = *lst;
	tab = NULL;
	i = 0;
	while (tmp)
	{
		i += 1;
		tmp = tmp->next;
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (i + 1))))
		return (tab);
	tmp = *lst;
	i = 0;
	while (tmp)
	{
		if (!(tab[i] = (char*)malloc(sizeof(char) * (ft_strlen(tmp->key) +
		ft_strlen(tmp->value) + 2))))
			return (tab);

//////////////////////////////////////////////////////////
///////// HERE
////////////////////////////////////

		ft_strcat(tab[i], (ft_strcat()))
////////////////////////////////////////////////
		ft_printf("tab[%d]: |%s|\n", i, tab[i]);
		i += 1;
	}
	return (tab);
}

char	*get_env_value(t_env **lst, char *str)
{
	int		i;
	size_t	len;
	t_env	*tmp;

	i = 0;
	tmp = *lst;
	len = ft_strlen(str) - 1;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, &str[1]) == 0)
			break ;
		else
			tmp = tmp->next;
	}
	return ((tmp) ? tmp->value : "");
}

void	env_builtins(t_ast *elem, t_env **lst_env)
{
	(void)elem;
	(void)tab_env;
	ft_printf("env\n");
}
