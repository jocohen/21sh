/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:07:27 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/15 18:33:43 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	echo_builtins(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int i;
	int option;

	(void)lst_env;
	(void)alloc;
	if (!elem->input[1])
	{
		write_str("\n", 0);
		g_ret[0] = 0;
		return (0);
	}
	option = (ft_strcmp(elem->input[1], "-n") == 0) ? 1 : 0;
	i = (option == 1 || ft_strcmp(elem->input[1], "-") == 0) ? 2 : 1;
	while (elem->input[i])
	{
		if (ft_strcmp(elem->input[i], "") != 0)
		{
			write_str(elem->input[i], 0);
			i += 1;
			(elem->input[i]) ? write_str(" ", 0) : 0;
		}
		else
			i += 1;
	}
	(option == 0) ? write_str("\n", 0) : 0;
	g_ret[0] = 0;
	return (0);
}
