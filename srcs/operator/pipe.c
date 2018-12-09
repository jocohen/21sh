/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:19:17 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/09 16:15:17 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

// HAVE TO SECURE FUNCTION:
// 	- pipe
// 	- fork

// static int	process_pipe(t_ast *elem, t_env *lst_env, int pfd[2], int fd)
// {
// 	int	fd_other;
// 	int	ret;
// 	// ft_printf("pid elem %s\n", elem->input[0]);
// 	fd_other = (fd == 1) ? 0 : 1;
// 	close(pfd[fd_other]);
// 	if (pfd[fd] != -1)
// 		dup2(pfd[fd], fd);
// 	ret = analyzer(elem, lst_env);
// 	exit(ret);
// }

static int	process_pipe_left(t_ast *elem, t_env *lst_env)
{
	int	ret;

	close(elem->back->fd[0]);
	// if (ft_strcmp(elem->input[0], "|") == 0)
	// {
	// 	dup2(elem->back->fd[1], elem->right->fd[0]);
	// 	dup2(elem->right->fd[0], elem->back->fd[1]);
	// }
	// if (elem->back->fd[1] != -1)
		dup2(elem->back->fd[1], 1);
	ret = analyzer(elem, lst_env);
	exit(ret);
}

static int	process_pipe_right(t_ast *elem, t_env *lst_env)
{
	int	ret;

	close(elem->back->fd[1]);
	// if (elem->back->back && ft_strcmp(elem->back->back->input[0], "|") == 0)
	// {
	// 	dup2(elem->back->fd[0], elem->back->back->fd[0]);
	// 	close(elem->back->back->fd[0]);
	// }
	// if (elem->back->fd[0] != -1)
	// 	dup2(elem->back->fd[0], 0);
	ret = analyzer(elem, lst_env);
	exit(ret);
}

int			do_pipe(t_ast *elem, t_env *lst_env)
{
	int	pid1;
	int	pid2;
	// int	save_fd;

	// if (elem->fd[0] == -1 && elem->fd[1] == -1)
	// 	pipe(elem->fd);
	// else
	// {
	// 	save_fd = elem->fd[0];
	// 	pipe(elem->fd);
	// 	elem->fd[0] = save_fd;
	// }
	pid1 = fork();
	if (!pid1)
		process_pipe_left(elem->left, lst_env);
	else
	{
		pid2 = fork();
		if (!pid2)
					process_pipe_right(elem->right, lst_env);
		else
		{
			// if (!elem->back || ft_strcmp(elem->back->input[0], "|") != 0)
			// {
				// close(elem->fd[1]);
				close(elem->fd[0]);
			// }
			close(elem->fd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
	return (1);
}
