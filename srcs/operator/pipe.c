/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:19:17 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/07 10:43:44 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

// HAVE TO SECURE FUNCTION:
// 	- pipe
// 	- fork

static int	process_pipe(t_ast *elem, t_env *lst_env, int pfd[2], int fd)
{
	dup2(pfd[fd], fd);
	close(pfd[0]);
	close(pfd[1]);
	exit(analyzer(elem, lst_env));
}

int			do_pipe(t_ast *elem, t_env *lst_env)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (!pid)
		process_pipe(elem->right, lst_env, fd, 0);
	else
	{
		pid = fork();
		if (!pid)
			process_pipe(elem->left, lst_env, fd, 1);
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(-1, NULL, 0);
			waitpid(-1, NULL, 0);
		}
	}
	return (1);
}
