/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:02:51 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/18 19:14:28 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	delete_lst_folder(char **dir)
{
	int	i;

	i = ft_strlen(*dir) - 1;
	if (i < 0)
	{
		ft_printf("Error delete last folder\n");
		return ;
	}
	while (i > 0 && (*dir)[i] != '/')
	{
		(*dir)[i] = '\0';
		i -= 1;
	}
	if (i != 0)
		(*dir)[i] = '\0';
}

/*

	OPTIONS:
		-L = 1
		-P = 2

** if tab[i] == ".."
	=> check options -P
		if true -> check if stat dir = LINK
			if LNK -> get path and replace dir by path
		delete till '/'
	=> check if options -L
		delete till '/'
	else if tab[i] == "."
	=> check options -P
		if true -> check if stat dir = LINK
			if LNK -> get path and replace dir by path
	=> check if options -L
		don't change
	else
		add "/" + tab[i] to dir
*/

static void	replace_path_by_link(char **dir)
{

}

static char	*add_new_folder(char *dir, char *tab_path)
{
	char	*new_dir;

	new_dir
}

char	*get_dir(char *pwd, char **tab_path, int options)
{
	char	dir[PATH_MAX];
	int		i;

	i = 0;
	dir = ft_strcpy(pwd);
	while (tab_path[i])
	{
		if (ft_strcmp(tab_path[i], "..") == 0)
		{
			if (options == 2)
				replace_path_by_link(&dir);
			delete_lst_folder(&dir);
		}
		else if (ft_strcmp(tab_path[i], ".") == 0)
		{
			if (options == 2)
				replace_path_by_link(&dir);
		}
		else
			dir = add_new_folder(dir, tab_path[i]);
		i += 1;
	}
	return ();
}
