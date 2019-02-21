/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:02:51 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/21 17:18:54 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static char	*delete_last_folder(char dir[PATH_MAX])
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

static char	*add_new_folder(char dir[PATH_MAX], char *folder)
{
	char	*new_dir;

	new_dir = ft_strcat(dir, "/");
	new_dir = ft_strcat(new_dir, folder);
	return (new_dir);
}

char		*get_dir(char *pwd, char **tab_path, int options, char *buf_pwd)
{
	char	dir[PATH_MAX];
	int		i;
	char	*tmp;

	i = 0;
	ft_bzero(dir, PATH_MAX);
	ft_strcpy(dir, pwd);
	while (tab_path[i])
	{
		if (ft_strcmp(tab_path[i], "..") == 0)
		{
			(options == 2) ? ft_strcpy(dir, buf_pwd) : 0;
			ft_strcpy(dir, delete_last_folder(dir));
		}
		else if (ft_strcmp(tab_path[i], ".") == 0)
			(options == 2) ? ft_strcpy(dir, buf_pwd) : 0;
		else
			ft_strcpy(dir, add_new_folder(dir, tab_path[i]));
		i += 1;
	}
	(buf_pwd) ? free(buf_pwd) : 0;
	delete_str_tab(tab_path);
	(!(tmp = ft_strdup(dir))) ? ft_exit_malloc() : 0;
	return (tmp);
}
