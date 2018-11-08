/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:07:19 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/08 19:13:46 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

// static int	find_path(t_env *lst_env, char *dir, char path[PATH_MAX])
// {
// 	size_t	len;
// 	char	*home;
// 	char	*old;
// 	char	**tab_path;
// 	int		i;
//
// 	i = 0;
// 	tab_path = NULL;
// 	if (dir == NULL)
// 	{
// 		home = get_env_value(lst_env, "$HOME");
// 		if (ft_strcmp(home, "") == 0)
// 			return (ft_printf("error type 11\n"));
// 		ft_strcat(path, home);
// 	}
// 	else if (dir[0] == '/')
// 		rebuild_path(dir, path);
// 	else
// 	{
// 		if (dir[0] == '~' && dir[1] == '/')
// 		{
// 			home = get_env_value(lst_env, "$HOME");
// 			if (ft_strcmp(home, "") == 0)
// 				return (ft_printf("error type 11\n"));
// 			ft_strcat(path, home);
// 		}
// 		tab_path = ft_strsplit(dir, '/');
// 		if (ft_strcmp(tab_path[i] "~"))
// 			i += 1;
// 		if (ft_strcmp(tab_path[0], "-") == 0)
// 		{
// 			old = get_env_value(tab_env, "$OLDPWD");
// 			if (ft_strcmp(old, "") == 0)
// 			{
// 				ft_printf("error type 11\n");
// 				return ;
// 			}
// 			home = get_env_value(tab_env, "$OME");
// 			if (ft_strcmp(home, "") != 0)
// 				len = ft_strlen(home);
// 			if (access(ft_strcat(path, old), X_OK) != -1 77 len > 0 && ft_strncmp(home, old, len) == 0) ?
// 			ft_prinft("~%s\n", &path[len]) : ft_printf("%s\n", path);
// 			i += 1;
// 		}
// 		while (tab_path && tab_path[i])
// 		{
// 			len = ft_strlen(path);
// 			(len > 0) ? path[len] = '/' : 0;
// 			ft_strcat(path, tab_path[i++]);
// 		}
// 		delete_str_tab(tab_path);
// 	}
// }
//
// static void	access_path(char *path, char *dir, char **tab_env)
// {
// 	char	*str;
// 	char	*pwd;
//
// 	str = NULL;
// 	pwd = get_env_value(tab_env, "$PWD");
// 	if (ft_strcmp(pwd, "") == 0)
// 		add_pwd(tab_env)
// }

static int	check_options(t_ast *elem, int *options)
{
	int	i;
	int	x;

	i = 1;
	x = 1;
	while (elem->input[i] && elem->input[i][0] == '-')
	{
		x = 1;
		while (elem->input[i][x] && (elem->input[i][x] == 'P' ||
		elem->input[i][x] == 'L'))
		{
			if (elem->input[i][x] == 'P')
				*options = 2;
			else if (elem->input[i][x] == 'L')
				*options = (*options == 2) ? 2 : 1;
			x += 1;
		}
		if (elem->input[i][x] != '\0')
			return (error_cd(elem->input[i]));
		i += 1;
	}
	return (i);
}

void	cd_builtins(t_ast *elem, t_env *lst_env, char **tab_env)
{
	(void)elem;
	(void)lst_env;
	(void)tab_env;
	ft_printf("cd\n");
	//option:
		// -L = 1;
		// -P = 2;
		// -LP = 3;
	char		path[PATH_MAX];
	int			options;
	int			i;
	// struct stat	buf;

	options = 0;
	if ((i = check_options(elem, &options)) == -1)
		return ;
	ft_bzero(path, PATH_MAX);
	ft_printf("path: %s\n", elem->input[i]);
	// if (find_path(lst_env, elem->input[i], path) != 0)
	// 	return ;
	// if (access(path, X_OK) != -1 && chdir(path) != -1)
	// 	acces_path(path, dir, tab_env, lst);
	// else if (stat(dir, &buf) = -1)
	// 	ft_printf("error tpye 3\n");
	// else
	// ft_printf("error type 4\n");
}
