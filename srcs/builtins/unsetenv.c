/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:10:12 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/08 09:49:31 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	unsetenv_builtins(t_ast *elem, t_env *lst_env, char **tab_env)
{
	(void)elem;
	(void)tab_env;
	(void)lst_env;
	ft_printf("unsetenv\n");
}
