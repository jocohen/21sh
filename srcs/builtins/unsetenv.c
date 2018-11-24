/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:10:12 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/24 19:11:51 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	unsetenv_builtins(t_ast *elem, t_env *lst_env)
{
	t_env	*tmp;
	t_env	*tmp_next;

	tmp = lst_env;
	tmp_next = tmp->next;
	if (!elem->input[1])
		return ;
	else if (ft_strcmp(elem->input[1], tmp->key) == 0)
	{
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		elem = tmp->next;
		return ;
	}
	// while (ft_strcmp(elem->input[1], tmp->key) != 0)
	// {
	// 	tmp = tmp->next
	//
	// }

	ft_printf("unsetenv\n");
}
