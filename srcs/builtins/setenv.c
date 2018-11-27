/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:08:41 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/27 13:43:33 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	setenv_builtins(t_ast *elem, t_env *lst_env)
{
	t_env *tmp;

	tmp = lst_env;
	if (!elem->input[1] || !elem->input[2] || ft_strchr(elem->input[1], '='))
		return (-1);
	while (tmp)
	{
		if (ft_strcmp(elem->input[1], tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp && elem->input[3] && ft_atoi(elem->input[3]) != 0)
	{
		free(tmp->value);
		tmp->value = ft_strdup(elem->input[2]);
	}
	else if (!tmp)
		add_elem_env(&lst_env, elem->input[1], elem->input[2]);
	return (0);
}
