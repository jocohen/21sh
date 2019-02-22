/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:10:02 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/22 16:36:54 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	check_access(char *dir, char *folder)
{
	if (access(dir, F_OK) == -1)
	{
		free(dir);
		return (error_cd(folder, 0));
	}
	if (access(dir, X_OK) == -1)
	{
		free(dir);
		return (error_cd(folder, 1));
	}
	if (chdir(dir) == -1)
	{
		free(dir);
		return (error_cd(folder, 3));
	}
	return (0);
}

static int	check_options(t_ast *elem, int *options, t_alloc **alloc)
{
	int	i;
	int	x;

	(void)alloc;
	i = 1;
	while (elem->input[i] && elem->input[i][0] == '-')
	{
		x = 1;
		while (elem->input[i][x] && (elem->input[i][x] == 'P'
		|| elem->input[i][x] == 'L'))
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

static int	modif_oldpwd(t_env **lst_env, char *buf)
{
	t_env	*tmp;

	tmp = NULL;
	if ((tmp = find_elem_env(lst_env, "OLDPWD"))
		&& (tmp = find_elem_env(lst_env, "PWD")))
	{
		free(tmp->value);
		if (!(tmp->value = ft_strdup(find_elem_env(lst_env, "PWD")->value)))
			ft_exit_malloc();
	}
	else
	{
		if (!(tmp = find_elem_env(lst_env, "PWD")))
			add_elem_env(lst_env, "OLDPWD", buf);
		else
			add_elem_env(lst_env, "OLDPWD", tmp->value);
	}
	return (0);
}

static int	modif_env(char *dir, t_env **lst_env, int options, char *buf)
{
	t_env	*tmp;

	tmp = NULL;
	modif_oldpwd(lst_env, buf);
	if (!(tmp = find_elem_env(lst_env, "PWD")))
		(options == 2) ? add_elem_env(lst_env, "PWD", buf) :
		add_elem_env(lst_env, "PWD", dir);
	else
	{
		free(tmp->value);
		tmp->value = ft_strdup((options == 2) ? buf : dir);
	}
	ft_memdel((void **)&dir);
	ft_memdel((void **)&buf);
	g_ret[0] = 0;
	return (0);
}

int			cd_builtins(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int			i;
	int			options;
	char		*buf_pwd;
	char		*dir;

	options = 0;
	buf_pwd = getcwd(0, PATH_MAX);
	dir = NULL;
	if (!find_elem_env(lst_env, "PWD"))
		add_elem_env(lst_env, "PWD", buf_pwd);
	if ((i = check_options(elem, &options, alloc)) == -1)
		return (1);
	if (elem->input[i] && ft_strcmp(elem->input[i], "-") == 0)
		(ft_strcmp((dir = ft_strdup(get_env_value(*lst_env, "$OLDPWD"))),
		"") != 0) ? 0 : error_cd("OLDPWD", 2);
	else if (!elem->input[i])
		(ft_strcmp((dir = ft_strdup(get_env_value(*lst_env, "$HOME"))),
		"") != 0) ? 0 : error_cd("HOME", 2);
	else if (elem->input[i][0] == '/')
		(!(dir = ft_strdup(elem->input[i]))) ? ft_exit_malloc() : 0;
	else
		dir = get_dir(get_env_value(*lst_env, "$PWD"),
		ft_strsplit(elem->input[i], '/'), options, buf_pwd);
	if (ft_strcmp(dir, "") != 0 && check_access(dir, elem->input[i]) == -1)
	{
		ft_memdel((void **)&buf_pwd);
		return (1);
	}
	(ft_strcmp(elem->input[i], "-") == 0 && ft_strcmp(dir, "") != 0) ? ft_printf("%s\n", dir) : 0;
	return (modif_env(dir, lst_env, options, buf_pwd));
}
