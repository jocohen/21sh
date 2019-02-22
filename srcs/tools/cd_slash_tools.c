/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_slash_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:24:10 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/22 20:12:17 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

char		*cd_slash(char *dir, int options, char *buf_pwd)
{
	char	*path;
	char	**tmp;
	size_t	x;

	x = -1;
	tmp = 0;
	if (!(path = ft_strdup("/")) || !(tmp = ft_strsplit(dir + 1, '/')))
		ft_exit_malloc();
	while (tmp[++x])
	{
		if (ft_strcmp(tmp[x], "..") == 0
			&& ft_strcmp(tmp[x], ".") == 0 && options == 2)
			ft_memdel((void **)&path);
		else if (ft_strcmp(tmp[x], "..") == 0)
		{
			(options == 2) ? path = ft_strdup(buf_pwd) : 0;
			delete_last_folder(path);
		}
		else if (ft_strcmp(tmp[x], ".") == 0)
			(options == 2) ? path = ft_strdup(buf_pwd) : 0;
		else
			add_new_folder(&path, tmp[x]);
		(!dir) ? ft_exit_malloc() : 0;
	}
	delete_str_tab(tmp);
	return (path);
}
