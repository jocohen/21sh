/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:32:04 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/11 17:09:01 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		ft_is_redir1(t_ast *elem, int fd[3], int fd_redir, int fd_open)
{
	static char		*tab_redir[7] = {">", ">>", ">>&", "<", "<<<", "<>", "<<"};
	int				i;
	int				dig;

	i = -1;
	dig = 0;
	if (!elem)
		return (0);
	while (i++ < 6)
		if (ft_strcmp(elem->input[0], tab_redir[i]) == 0
			|| ft_strcmp(elem->input[1], tab_redir[i]) == 0)
		{
			dig = ft_isdigit(elem->input[0][0]);
			fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
			fd_open = open(elem->right->input[0], O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
			if (fd_redir < 3 && fd_redir >= 0 && fd[fd_redir] == -1)
				fd[fd_redir] = fd_open;
			else
				close(fd_open);
			return (1);
		}
	if (fd_redir == -1 && ft_is_agreg(elem, fd, 1) == 1)
		return (1);
	return (0);
}

// int		ft_is_redir2(t_ast *elem, int fd[3], int fd_redir, int fd_open)
// {
// 	static char		*tab_redir[7] = {">", ">>", ">>&", "<", "<<<", "<>", "<<"};
// 	int				i;
// 	int				dig;
//
// 	i = -1;
// 	dig = 0;
// 	if (!elem)
// 		return (0);
// 	while (i++ < 7)
// 		if (ft_strcmp(elem->input[0], tab_redir[i]) == 0
// 			|| ft_strcmp(elem->input[1], tab_redir[i]) == 0)
// 		{
// 			dig = ft_isdigit(elem->input[0][0]);
// 			fd_redir = (dig == 1) ? ft_atoi(elem->input[0]) : 1;
// 			fd_open = open(elem->right->input[0], O_WRONLY | O_CREAT
// 				| O_APPEND, 0644);
// 			if (fd_redir < 3 && fd_redir >= 0 && fd[fd_redir] == -1)
// 				fd[fd_redir] = fd_open;
// 			else
// 				close(fd_open);
// 			return (1);
// 		}
// 	return (0);
// }

void	reinit_fd(int fd[3], int fd_save1, int fd_save2)
{
	if (fd[1] != -1)
	{
		dup2(fd_save1, 1);
		close(fd[1]);
	}
	if (fd[2] != -1)
	{
		dup2(fd_save2, 2);
		close(fd[2]);
	}
}
