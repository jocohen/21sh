/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:07:27 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/27 16:27:39 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	echo_builtins(t_ast *elem, t_env *lst_env)
{
	int i;
	int option;

	(void)lst_env;
	if (!elem->input[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	option = (ft_strcmp(elem->input[1], "-n") == 0) ? 1 : 0;
	i = (option == 1 || ft_strcmp(elem->input[1], "-") == 0) ? 2 : 1;
	while (elem->input[i])
	{
		if (ft_strcmp(elem->input[i], "") != 0)
		{
			write(1, elem->input[i], ft_strlen(elem->input[i]));
			i += 1;
			(elem->input[i]) ? write(1, " ", 1) : 0;
		}
		else
			i += 1;
	}
	(option == 0) ? write(1, "\n", 1) : 0;
	return (0);
}
