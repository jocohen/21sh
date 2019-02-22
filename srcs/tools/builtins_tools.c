/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:02:51 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/22 12:07:47 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*delete_last_folder(char *dir)
{
	int	i;

	i = ft_strlen(dir) - 1;
	if (i < 0)
		return (dir);
	while (i > 0 && dir[i] != '/')
	{
		dir[i] = '\0';
		i -= 1;
	}
	if (i != 0)
		dir[i] = '\0';
	return (dir);
}

static void	add_new_folder(char *dir, char *folder)
{
	char	*new_dir;

	new_dir = ft_strjoin(dir, "/");
	ft_memdel((void **)&dir);
	dir = ft_strjoin(new_dir, folder);
	ft_memdel((void **)&new_dir);
}

char		*get_dir(char *pwd, char **tab_path, int options, char *buf_pwd)
{
	char	*dir;
	int		i;

	i = 0;
	dir = ft_strdup(pwd);
	while (tab_path[i])
	{
		if (ft_strcmp(tab_path[i], "..") == 0
			&& ft_strcmp(tab_path[i], ".") == 0 && options == 2)
			ft_memdel((void **)&dir);
		else if (ft_strcmp(tab_path[i], "..") == 0)
		{
			(options == 2) ? dir = ft_strdup(buf_pwd) : 0;
			delete_last_folder(dir);
		}
		else if (ft_strcmp(tab_path[i], ".") == 0)
			(options == 2) ? dir = ft_strdup(buf_pwd) : 0;
		else
			add_new_folder(dir, tab_path[i]);
		if (!dir)
			ft_exit(1);
		i += 1;
	}
	delete_str_tab(tab_path);
	return (dir);
}
