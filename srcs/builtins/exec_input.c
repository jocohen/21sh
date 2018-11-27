/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:10:04 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/27 12:42:44 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	exec_input(t_ast *elem, t_env *lst_env, char **tab_path)
{
	char	path[PATH_MAX];
	pid_t	father;
	int		err;
	int		i;
	char	**tab_env;

	tab_env = NULL;
	err = -1;
	i = 0;
	convert_lst_tab(lst_env, &tab_env);
	(!tab_path) ? tab_path = ft_strsplit(get_env_value(lst_env,
	"$PATH"), ':') : 0;
	father = fork();
	wait(0);
	if (!father)
	{
		err = execve(elem->input[0], elem->input, tab_env);
		if (tab_path != NULL && ft_strcmp(tab_path[0], "") != 0)
			while (tab_path[i] && err == -1)
				err = execve(ft_strcat(ft_strcat(ft_strcpy(path,
				tab_path[i++]), "/"), elem->input[0]), elem->input, tab_env);
		delete_str_tab(tab_path);
		delete_str_tab(tab_env);
		(err == -1) ? (exit(exec_error(0, elem->input[0]))) : 0;
	}
	(tab_path) ? delete_str_tab(tab_path) : 0;
	(tab_env) ? delete_str_tab(tab_env) : 0;
}
