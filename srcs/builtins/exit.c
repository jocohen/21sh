/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:28:36 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/06 10:37:40 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	exit_builtins(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	(void)lst_env;
	(void)alloc;
	if (!elem->input[1])
		exit(0);
	exit(ft_atoi(elem->input[1]));
	return (0);
}
