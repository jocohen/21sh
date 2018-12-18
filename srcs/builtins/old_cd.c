/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:07:19 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/18 16:11:03 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	new_path(t_env *elem, char *path, char **tab_path)
{
	char	new[PATH_MAX];
	int		i;
	int		x;

	x = -1;
	ft_bzero(new, PATH_MAX);
	if (path[0] == '/')
		(path[1] == '\0') ? new[0] = '/' : 0;
	else
		ft_strcpy(new, elem->value);
	while (tab_path[++x])
	{
		ft_printf("x = %d\nnew: |%s|\n", x, new);
		if (ft_strcmp(tab_path[x], "..") == 0)
		{
			ft_printf("Go back\n");
			i = ft_strlen(new) - 1;
			while (i >= 0 && new[i] != '/')
				i -= 1;
			ft_printf("i = %d\n", i);
			if (i <= 0 || (i == 0 && new[i] == '/'))
			{
			 	new[0] = '/';
				new[1] = 0;
			}
			else
				new[i] = '\0';
				ft_printf("NEW: |%s|\n", new);
		}
		else if (ft_strcmp(tab_path[x], ".") != 0)
			ft_strcat(ft_strcat(new, "/"), tab_path[x]);
		free(tab_path[x]);
	}
	(tab_path != NULL) ? free(tab_path) : 0;
	free(elem->value);
	elem->value = ft_strdup(new);
}

static int	check_access(char *dir)
{
	if (access(dir, F_OK) == -1)
		return (error_cd(dir, 0));
	if (access(dir, X_OK) == -1)
		return (error_cd(dir, 1));
	return (0);
}

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
		if (ft_strcmp(elem->input[i], "-") == 0)
			return (i);
		else if (elem->input[i][x] != '\0')
			return (error_cd(elem->input[i], 0));
		i += 1;
	}
	return (i);
}

static void	modif_env(char *path, t_env *lst_env, int options)
{
	t_env	*tmp;
	char	*buf;

	buf = NULL;
	if (!(tmp = find_elem_env(&lst_env, "PWD")))
	{
		add_elem_env(&lst_env, "PWD", getcwd(buf, PATH_MAX));
		free(buf);
	}
	if ((tmp = find_elem_env(&lst_env, "OLDPWD")))
	{
		free(tmp->value);
		tmp->value = ft_strdup(find_elem_env(&lst_env, "PWD")->value);
	}
	else
		add_elem_env(&lst_env, "OLDPWD", find_elem_env(&lst_env, "PWD")->value);
	if (options != 2)
		new_path(find_elem_env(&lst_env, "PWD"), path, ft_strsplit(path, '/'));
	else
	{
		free(find_elem_env(&lst_env, "PWD")->value);
		find_elem_env(&lst_env, "PWD")->value =
		ft_strdup(getcwd(buf, PATH_MAX));
		free(buf);
	}
}

int			cd_builtins(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int			options;
	int			i;
	char		*buf_pwd;
	char		*dir;

	(void)alloc;
	buf_pwd = NULL;
	options = 0;
	dir = NULL;
	if ((i = check_options(elem, &options)) == -1)
		return (1);
	if (elem->input[i] && ft_strcmp(elem->input[i], "-") == 0)
	{
		(ft_strcmp((dir = ft_strdup(get_env_value(*lst_env, "$OLDPWD"))), "") != 0) ? 0 :
		error_cd("OLDPWD", 2);
		ft_printf("OLDPWD: |%s|\n", dir);
	}
	else if (!elem->input[i])
	{
		(ft_strcmp((dir = ft_strdup(get_env_value(*lst_env, "$HOME"))), "") != 0) ? 0 :
		error_cd("HOME", 2);
		ft_printf("HOME: |%s|\n", dir);
	}
	else
	{
		// dir = get_dir(ft_strsplit(get_env_value(*lst_env, "$PWD"), '/''), ft_strsplit(elem->input[i], '/'));
		dir = ft_strdup(elem->input[i]);
		modif_env(dir, *lst_env, options);
		free(dir);
		dir = ft_strdup(get_env_value(*lst_env, "$PWD"));
		ft_printf("DIR INPUT: |%s|\n", dir);
	}
	ft_printf("FUCKING DIR: |%s|\n", dir);
	if (ft_strcmp(dir, "") != 0 && (check_access(dir) == -1 ||
	chdir(dir) == -1))
		return (1);
	ft_printf("SEND DIR: |%s|\n", dir);
	modif_env(dir, *lst_env, options);
	(dir) ? free(dir) : 0;
	return (0);
}
