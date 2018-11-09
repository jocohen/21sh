/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:07:19 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/09 19:13:46 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

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
		if (elem->input[i][x] != '\0')
			return (error_cd(elem->input[i], 0));
		i += 1;
	}
	return (i);
}

static void	modif_env(char *path, char **tab_env, t_env *lst_env)
{
	t_env	*tmp;
	char	*buf;

	(void)tab_env;
	(void)path;
	tmp = NULL;
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
	tmp = find_elem_env(&lst_env, "PWD");
	free(tmp->value);
	tmp->value = getcwd(buf, PATH_MAX);
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
	struct stat	buf;
	char		*buf_pwd;

	int ret;

	ret = 1;

	buf_pwd = NULL;
	options = 0;
	if ((i = check_options(elem, &options)) == -1)
		return ;
	ft_printf("input[%d]: |%s|\n", i, elem->input[i]);
	ret = lstat(elem->input[i], &buf);
	if (ret == 0)
	{
		if (S_IFLNK == (S_IFMT & buf.st_mode))
			ft_printf("--> Link\n");
		else
			ft_printf("--> No link\n");
	}
	else if (ret == -1)
	{
		ft_printf("error lstat\n");
	}
	else
		ft_printf("Nothing lstat ret = %d\n", ret);
	ft_bzero(path, PATH_MAX);
	if (check_access(elem->input[i]) == -1 || chdir(elem->input[i]) == -1)
	{
		ft_printf("error here\n");
		return ;
	}
	chdir("./First");
	modif_env(elem->input[i], tab_env, lst_env);
	getcwd(buf_pwd, PATH_MAX);
	ft_printf("PWD: |%s|\n", buf_pwd);
}
