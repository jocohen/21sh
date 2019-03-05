/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:32:04 by tcollard          #+#    #+#             */
/*   Updated: 2019/03/05 18:30:04 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	redir_to_file(t_ast *elem, t_alloc *alloc, int fd[3], int i)
{
	int		fd_redir;
	int		fd_open;
	int		dig;

	fd_redir = -1;
	fd_open = -1;
	dig = (ft_isdigit(elem->input[0][0]) == 1) ? 1 : 0;
	fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
	fd_open = open((dig == 1) ? elem->input[2] :
	elem->input[1], O_WRONLY | O_CREAT | ((i == 0) ? O_TRUNC :
	O_APPEND), 0644);
	if (fd_redir >= 0 && fd[fd_redir] == -1
		&& alloc->fd[fd_redir] == 0)
	{
		fd[fd_redir] = fd_open;
		alloc->fd[fd_redir] = dup(fd_redir);
		dup2(fd_open, fd_redir);
	}
	else
		close(fd_open);
}

static void	redir_stdin(t_ast *elem, t_alloc *alloc, int fd[3])
{
	int		fd_file;
	int		fd_redir;
	char	*tmp;

	fd_redir = 0;
	tmp = (elem->right) ? elem->right->input[0] : elem->input[1];
	if ((fd_file = open(tmp, O_RDONLY)) == -1)
	{
		if (access(tmp, F_OK) == -1)
			return (error_access(tmp));
		else
			return (error_redir(tmp));
	}
	if (fd_redir >= 0 && fd[fd_redir] == -1
		&& alloc->fd[fd_redir] == 0)
	{
		fd[fd_redir] = fd_file;
		alloc->fd[fd_redir] = dup(fd_redir);
		dup2(fd_file, fd_redir);
	}
	else
		close(fd_file);
}

int			ft_is_redir(t_ast *elem, int fd[3], t_alloc *alloc,
			t_env **lst_env)
{
	static char		*tab_redir[6] = {">", ">>", ">>&", "<", "<<<", "<>"};
	int				i;

	(void)lst_env;
	i = -1;
	if (!elem || !elem->input)
		return (0);
	while (i++ < 6)
		if (ft_strcmp(elem->input[0], tab_redir[i]) == 0
			|| ft_strcmp(elem->input[1], tab_redir[i]) == 0)
		{
			if (i == 3)
				redir_stdin(elem, alloc, fd);
			else
				redir_to_file(elem, alloc, fd, i);
			return (1);
		}
	return (0);
}

void		reinit_fd(int fd[3], t_alloc *alloc)
{
	if (fd[0] != -1)
	{
		dup2(alloc->fd[0], 0);
		alloc->fd[0] = 0;
		if (fd[0] != 0 && fd[0] != 1 && fd[0] != 2)
			close(fd[0]);
	}
	if (fd[1] != -1)
	{
		dup2(alloc->fd[1], 1);
		alloc->fd[1] = 0;
		if (fd[1] != 0 && fd[1] != 1 && fd[1] != 2)
			close(fd[1]);
	}
	if (fd[2] != -1)
	{
		dup2(alloc->fd[2], 2);
		alloc->fd[2] = 0;
		if (fd[2] != 0 && fd[2] != 1 && fd[2] != 2)
			close(fd[2]);
	}
}
