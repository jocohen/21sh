/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:19:17 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/10 23:54:45 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

static int	process_pipe_left(t_ast *elem, t_env *lst_env)
{
	int	ret;

	close(elem->back->fd[0]);
	dup2(elem->back->fd[1], 1);
	ret = analyzer(elem, lst_env);
	close(elem->back->fd[1]);
	exit(ret);
}

static int	process_pipe_right(t_ast *elem, t_env *lst_env)
{
	int	ret;

	close(elem->back->fd[1]);
	dup2(elem->back->fd[0], 0);
	ret = analyzer(elem, lst_env);
	close(elem->back->fd[0]);
	exit(ret);
}

int			do_pipe(t_ast *elem, t_env *lst_env)
{
	int	pid1;
	int	pid2;

	pipe(elem->fd);
	pid1 = fork();
	if (!pid1)
		process_pipe_left(elem->left, lst_env);
	else
	{
		waitpid(pid1, NULL, 0);
		pid2 = fork();
		if (!pid2)
			process_pipe_right(elem->right, lst_env);
		else
		{
			close(elem->fd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
			close(elem->fd[0]);
			// waitpid(pid2, NULL, 0);
		}
	}
	return (1);
}
