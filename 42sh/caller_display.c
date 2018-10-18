/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caller_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:53:10 by jocohen           #+#    #+#             */
/*   Updated: 2018/09/27 15:28:53 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

char	*get_end_pwd(char *pwd)
{
	int		x;

	if (!pwd)
		return (0);
	if (pwd[1] == '/' && !pwd[1])
		return (pwd);
	x = ft_strlen(pwd);
	(x) ? x -= 1 : 0;
	while (x && pwd[x] != '/')
		x -= 1;
	return (pwd + x + 1);
}

void	fancy_display(char *pwd)
{
	ft_putstr_fd(ANSI_RESET, 1);
	ft_putstr_fd(ANSI_BOLD, 1);
	ft_putstr_fd(ANSI_GREEN, 1);
	write(1, "δ  ", 4);
	if (pwd)
	{
		ft_putstr_fd(ANSI_RESET, 1);
		ft_putstr_fd(ANSI_BOLD, 1);
		ft_putstr_fd(ANSI_WHITE, 1);
		pwd = get_end_pwd(pwd);
		write(1, pwd, ft_strlen(pwd));
	}
	ft_putstr_fd(ANSI_RESET, 1);
	write(1, " > ", 3);
}

void	caller_display(t_list *fp)
{
	char	path[PATH_MAX];
	char	*pwd;

	ft_bzero(path, PATH_MAX);
	if (!(pwd = find_var_value(fp, "PWD")))
		pwd = getcwd(path, PATH_MAX);
	fancy_display(pwd);
}
