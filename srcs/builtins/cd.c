/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:44:09 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/18 19:14:23 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

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

int		cd_builtins(t_ast *elem, t_env **lst_env, t_alloc **alloc)
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
	}
	else if (!elem->input[i])
	{
		(ft_strcmp((dir = ft_strdup(get_env_value(*lst_env, "$HOME"))), "") != 0) ? 0 :
		error_cd("HOME", 2);
	}
	else
	{
		get_dir(get_env_value(*lst, "PWD"), ft_strsplit(elem->input[i], '/'), options);
	}
}
