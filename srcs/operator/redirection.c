/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:14:55 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/20 18:15:48 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

// int	fd_file;
// int	fd_save;
// int	fd_redir;
//
// fd_redir = 1;
// fd_file = 1;
// if (ft_strcmp(elem->input[0], ">") == 0)
// {
// 	ft_printf("redirection simple\n");
// 	if ((fd_file = open(elem->right->input[0], O_WRONLY | O_CREAT
// 		| O_TRUNC, 0644)) == -1)
// 	{
// 		ft_printf("error: redirection 1\n");
// 		return ;
// 	}
// 	elem->right->print = 1;
// }
// else if (ft_isdigit(elem->input[0][0]) == 1)
// {
// 	ft_printf("IS DIGIT\n");
// 	if ((fd_file = open(elem->right->input[0], O_WRONLY | O_CREAT
// 		| O_TRUNC, 0644)) == -1)
// 	{
// 		ft_printf("error: redirection 2\n");
// 		return ;
// 	}
// 	fd_redir = ft_atoi(elem->input[0]);
// 	elem->right->print = 1;
// }
// fd_save = dup(fd_redir);
// dup2(fd_file, fd_redir);
// // close(fd_redir);
// analyzer(elem->left, lst_env, alloc);
// dup2(fd_save, fd_redir);


void	redirection(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int	fd_file;
	int	fd_save;
	int	fd_redir;

	fd_redir = 1;
	fd_file = 1;
	if (ft_strcmp(elem->input[0], ">>") == 0)
	{
		ft_printf("redirection simple\n");
		if ((fd_file = open(elem->right->input[0], O_WRONLY | O_CREAT
			| O_APPEND, 0644)) == -1)
		{
			ft_printf("error: redirection 1\n");
			return ;
		}
		elem->right->print = 1;
	}
	else if (ft_isdigit(elem->input[0][0]) == 1)
	{
		ft_printf("IS DIGIT\n");
		if ((fd_file = open(elem->right->input[0], O_WRONLY | O_CREAT
			| O_APPEND, 0644)) == -1)
		{
			ft_printf("error: redirection 2\n");
			return ;
		}
		fd_redir = ft_atoi(elem->input[0]);
		elem->right->print = 1;
	}
	fd_save = dup(fd_redir);
	dup2(fd_file, fd_redir);
	// close(fd_redir);
	analyzer(elem->left, lst_env, alloc);
	dup2(fd_save, fd_redir);
}
