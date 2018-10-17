/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:32:45 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/17 12:42:43 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

/*
** LIST BUILTINS:
**		- CD
**		- ECHO
**		- SETENV
**		- UNSETENV
**		- ENV
*/

void	builtins_dispatch(t_ast *elem)
{
	static char	*lst_built[5] = {"cd", "echo", "setenv", "unsetenv", "env"};
	int			i;

	// ft_printf("Value = %s\n", elem->value);
	ft_printf("\n\nENV:\n");
	i = 0;
	while (g_env[i])
	{
		ft_printf("%s\n", g_env[i]);
		i += 1;
	}
	// while (i < 5)
	// {
	// 	if (ft_strcmp(elem->value, lst_built[i]) == 0)
	// 		break ;
	// 	ft_printf("BUILTINS[%d]: %s\n\n\n", i, lst_built[i]);
	// 	i += 1;
	// }
	// (i == 5) ? ft_printf("Execve\n") : ft_printf("builtins[%d]: %s\n", i, lst_built[i]);
}
