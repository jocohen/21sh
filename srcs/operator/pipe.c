/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:19:17 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/21 13:10:47 by nicolaslamerenx  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	process_pipe_left(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	ret;

	close(elem->back->fd[0]);
	dup2(elem->back->fd[1], STDOUT_FILENO);
	close(elem->back->fd[1]);
	ret = analyzer(elem, lst_env, alloc);
	exit(ret);
}

static int	process_pipe_right(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	ret;

	close(elem->back->fd[1]);
	dup2(elem->back->fd[0], STDIN_FILENO);
	close(elem->back->fd[0]);
	ret = analyzer(elem, lst_env, alloc);
	exit(ret);
}

int			do_pipe(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	pid1;
	int	pid2;

	if (g_pid == -1)
		return (0);
	pipe(elem->fd);
	pid1 = fork();
	if (!pid1)
		process_pipe_left(elem->left, lst_env, alloc);
	else
	{
		g_pid = pid1;
		pid2 = fork();
		if (!pid2)
			process_pipe_right(elem->right, lst_env, alloc);
		else
		{
			g_pid = pid2;
			close(elem->fd[1]);
			close(elem->fd[0]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
	return (1);
}
