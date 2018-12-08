/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:19:17 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/08 16:59:41 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

// HAVE TO SECURE FUNCTION:
// 	- pipe
// 	- fork

static int	process_pipe(t_ast *elem, t_env *lst_env, int pfd[2], int fd)
{
	int	fd_other;
	int	ret;
	// ft_printf("pid elem %s\n", elem->input[0]);
	fd_other = (fd == 1) ? 0 : 1;
	close(pfd[fd_other]);
	if (pfd[fd] != -1)
		dup2(pfd[fd], fd);
	// close(pfd[0]);
	// close(pfd[1]);
	ret = analyzer(elem, lst_env);
	exit(ret);
}

int			do_pipe(t_ast *elem, t_env *lst_env)
{
	int	pid1;
	int	pid2;
	int	fd;


// ecrit sur 1 sort sur 0

	pipe(elem->fd);
	pid1 = fork();
	if (!pid1)
	{
		fd = 1;
		process_pipe(elem->left, lst_env, elem->fd, fd);
	}
	else
	{
		pid2 = fork();
		if (!pid2)
		{
		    // if (elem->back && ft_strcmp(elem->back->input[0], "|") == 0)
			// 	fd = elem->back->fd[0];
			// else
			    fd = 0;
			process_pipe(elem->right, lst_env, elem->fd, fd);
		}
		else
		{
			if (elem->back && ft_strcmp(elem->back->input[0], "|") == 0)
				return (1);
			close(elem->fd[0]);
			close(elem->fd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
	return (1);
}
