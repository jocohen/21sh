/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:07:27 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/06 14:43:30 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	echo_builtins(t_ast *elem, char **tab_env)
{
	int i;
	int option;

	(void)tab_env;
	option = (ft_strcmp(elem->input[1], "-n") == 0) ? 1 : 0;
	i = (option == 1 || ft_strcmp(elem->input[1], "-") == 0) ? 2 : 1;
	while (elem->input[i])
	{
		write (1, elem->input[i], ft_strlen(elem->input[i]));
		i += 1;
		if (elem->input[i])
			write (1, " ", 1);
	}
	if (option == 0)
		write (1, "\n", 1);
	return (0);
}
