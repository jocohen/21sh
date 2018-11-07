/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:10:04 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/07 12:16:38 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	exec_input(char **tab_env, t_ast *elem)
{
		char	**tab_path;
		char	path[PATH_MAX];
		pid_t	father;
		int		err;
		int		i;

		err = -1;
		i = 0;
		tab_path = ft_strsplit(get_env_value(tab_env, "$PATH"), ':');
		father = fork();
		wait(0);
		if (!father)
		{
			err = execve(elem->input[0], elem->input, tab_env);
			if (tab_path != NULL && ft_strcmp(tab_path[0], "") != 0)
				while (tab_path[i] && err == -1)
				{
					ft_strcat(ft_strcpy(path, tab_path[i]), "/");
					err = execve(ft_strcat(path, elem->input[0]), elem->input,
					tab_env);
					i += 1;
				}
			(err == -1) ? (exit(exec_error(0, elem->input[0]))) : 0;
		}
}
