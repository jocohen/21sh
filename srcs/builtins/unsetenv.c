/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:10:12 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/29 10:21:34 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	unsetenv_builtins(t_ast *elem, t_env *lst_env)
{
	t_env	*tmp;
	t_env	*tmp_next;

	tmp = lst_env;
	tmp_next = tmp->next;
	if (!elem->input[1])
		return (error_unsetenv(2, NULL));
	else if (elem->input[2])
		return (error_unsetenv(1, NULL));
	else if (ft_strcmp(elem->input[1], tmp->key) == 0)
	{
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		lst_env = tmp->next;
		return (0);
	}
	while (tmp_next && ft_strcmp(elem->input[1], tmp_next->key) != 0)
	{
		tmp = tmp_next;
		tmp_next = tmp_next->next;
	}
	if (tmp_next)
	{
		tmp->next = tmp_next->next;
		free(tmp_next->key);
		free(tmp_next->value);
		free(tmp_next);
	}
	else
		return (error_unsetenv(3, elem->input[1]));
	return (0);
}
