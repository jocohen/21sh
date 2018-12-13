/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:32:45 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/13 14:21:35 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	builtins_dispatch(t_ast *elem, t_list **env)
{
	static char	*lst_built[5] = {"cd", "echo", "setenv", "unsetenv", "env"};
	int			i;

	(void)env;
	i = 0;
	while (i < 5)
	{
		if (ft_strcmp(elem->value, lst_built[i]) == 0)
			break ;
		i += 1;
	}
}
