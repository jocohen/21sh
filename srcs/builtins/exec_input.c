/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:10:04 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/05 11:54:32 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	do_exec(char **tab_path, t_ast *elem, t_alloc **alloc,
			t_env *lst_env)
{
	int		i;
	int		err;
	char	path[PATH_MAX];
	char	**tab_env;

	i = 0;
	err = -1;
	convert_lst_tab(lst_env, &tab_env);
	err = execve(elem->input[0], elem->input, tab_env);
	if (tab_path && tab_path[0] != NULL && ft_strcmp(tab_path[0], "") != 0)
		while (tab_path[i] && err == -1)
			err = execve(ft_strcat(ft_strcat(ft_strcpy(path,
				tab_path[i++]), "/"), elem->input[0]), elem->input, tab_env);
	del_double_tab(tab_path, tab_env);
	(err == -1) ? (exit(exec_error(-1, elem->input[0], alloc))) : 0;
}

int			exec_input(t_ast *elem, t_env *lst_env, char **tab_path,
			t_alloc **alloc)
{
	pid_t	father;
	int		err;
	char	**tab_env;

	tab_env = NULL;
	err = -1;
	(!tab_path) ? tab_path = ft_strsplit(get_env_value(lst_env,
	"$PATH"), ':') : 0;
	if (!(father = fork()))
	{
		if (g_pid == -1)
		{
			//set return color prompt value
			exit(1);
		}
		g_in_exec = 1;
		do_exec(tab_path, elem, alloc, lst_env);
	}
	g_pid = father;
	waitpid(father, &err, 0);
	del_double_tab(tab_path, tab_env);
	(err != 0) ? err = 1 : 0;
	return (err);
}
