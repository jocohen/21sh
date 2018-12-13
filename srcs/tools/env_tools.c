/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:19:18 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/13 13:26:24 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_env	*find_elem_env(t_env **lst, char *key)
{
	t_env *tmp;

	tmp = *lst;
	while (tmp && ft_strcmp(key, tmp->key) != 0)
		tmp = tmp->next;
	return (tmp);
}

t_env	*get_last_elem_env(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_elem_env(t_env **lst, char *key, char *value)
{
	t_env	*new;
	t_env	*last;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		return ;
	last = get_last_elem_env(lst);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!(*lst))
		*lst = new;
	else
		last->next = new;
}

void	add_shlvl(t_env **lst)
{
	t_env	*shlvl;
	t_env	*tmp;
	int		lvl;

	tmp = *lst;
	shlvl = NULL;
	lvl = 0;
	if ((shlvl = find_elem_env(lst, "SHLVL")) != NULL)
	{
		lvl = ft_atoi(shlvl->value) + 1;
		free(shlvl->value);
		shlvl->value = ft_itoa(lvl);
	}
	else
	{
		if (!(shlvl = (t_env*)malloc(sizeof(t_env))))
			return ;
		shlvl->key = ft_strdup("SHLVL");
		shlvl->value = ft_strdup("1");
		shlvl->next = NULL;
		if (!tmp)
			*lst = shlvl;
		else
			get_last_elem_env(lst)->next = shlvl;
	}
}

void	display_env(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
