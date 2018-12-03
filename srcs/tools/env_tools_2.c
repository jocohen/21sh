/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:27:40 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/13 11:28:18 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void		convert_lst_tab(t_env *lst_env, char ***tab)
{
	t_env	*tmp;
	int		i;

	tmp = lst_env;
	i = 0;
	while (tmp)
	{
		i += 1;
		tmp = tmp->next;
	}
	if (!(*tab = (char**)malloc(sizeof(char*) * (i + 1))))
		return ;
	tmp = lst_env;
	i = 0;
	while (tmp)
	{
		if (!((*tab)[i] = (char*)malloc(sizeof(char) * (ft_strlen(tmp->key) +
		ft_strlen(tmp->value) + 2))))
			return ;
		ft_strcat(ft_strcat(ft_strcpy((*tab)[i], tmp->key), "="), tmp->value);
		i += 1;
		tmp = tmp->next;
	}
	(*tab)[i] = NULL;
}

char		*get_env_value(t_env *lst_env, char *str)
{
	int		i;
	size_t	len;
	t_env	*tmp;

	i = 0;
	tmp = lst_env;
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