/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:19:18 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/08 12:09:57 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

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
