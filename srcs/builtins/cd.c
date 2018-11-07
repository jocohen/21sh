/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:07:19 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/07 14:43:26 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

static int	find_path(char **tab_env, t_ast *elem, char path[PATH_MAX])
{
	size_t	len;
}

void	cd_builtins(t_ast *elem, char **tab_env)
{
	char		path[PATH_MAX];
	struct stat	buf;

	ft_bzero(path, PATH_MAX);
	if (find_path(tab_env, elem, path) != 0)
		return ;

	(void)elem;
	(void)tab_env;
	ft_printf("cd\n");
}
