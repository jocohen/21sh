/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:07:27 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/05 12:05:51 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	echo_builtins(t_ast *elem, char **tab_env)
{
	(void)elem;
	(void)tab_env;
	ft_printf("echo\n");
}
