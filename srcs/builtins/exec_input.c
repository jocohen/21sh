/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:10:04 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/17 13:05:34 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		exec_rights(t_ast *elem, char **tab_path)
{
	int		x;
	char	path[PATH_MAX];

	x = 0;
	while (tab_path && tab_path[0] != NULL && ft_strcmp(tab_path[0], "") != 0
			&& tab_path[x])
	{
		ft_strcat(ft_strcat(ft_strcpy(path, tab_path[x++]), "/")
				, elem->input[0]);
		if (access(path, X_OK) == -1 && !access(path, F_OK))
			return (exec_right_error(2, path));
	}
	return (0);
}

void	execute_cmd(t_ast *elem, char **tab_env, char **tab_path)
{
	int		x;
	char	path[PATH_MAX];

	x = 0;
	if (ft_strchr(elem->input[0], '/'))
		execve(elem->input[0], elem->input, tab_env);
	if (tab_path && tab_path[0] != NULL && ft_strcmp(tab_path[0], "") != 0)
		while (tab_path[x])
			execve(ft_strcat(ft_strcat(ft_strcpy(path,
			tab_path[x++]), "/"), elem->input[0]), elem->input, tab_env);
	exit(exec_error(-1, elem->input[0]));
}

int		exec_input(t_ast *elem, t_env *lst_env, char **tab_path)
{
	pid_t	father;
	char	**tab_env;

	if (!tab_path)
	{
		if (!find_elem_env(&lst_env, "PATH"))
			tab_path = ft_strsplit("/usr/bin:/bin:/usr/sbin:/sbin", ':');
		else
			tab_path = ft_strsplit(get_env_value(lst_env, "$PATH"), ':');
	}
	if (exec_rights(elem, tab_path))
		return (ret_status());
	convert_lst_tab(lst_env, &tab_env);
	if (!(father = fork()))
	{
		if (g_pid == -1)
			exit(130);
		g_in_exec = 1;
		execute_cmd(elem, tab_env, tab_path);
	}
	g_pid = father;
	waitpid(father, &(g_ret[0]), 0);
	g_ret[1] = 1;
	del_double_tab(tab_path, tab_env);
	return (ret_status());
}
