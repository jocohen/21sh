/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:14:55 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/20 11:51:19 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	redirection(t_ast *elem)
{
	int	fd_file;
	int	fd_save;
	int	fd_redir;

	fd_file = 0;
	if (ft_strcpm(elem->input[0], ">") == 0)
	{
		ft_printf("redirection simple\n");
		fd_file = open(elem->right->input[0], O_WRONLY | O_CREAT | O_TRUNC);
		if (fd_file == -1)
			return ;

	}
	else if (ft_strcmp(elem->))
}
