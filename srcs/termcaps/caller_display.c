/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caller_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:53:10 by jocohen           #+#    #+#             */
/*   Updated: 2018/11/26 15:15:37 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		window_width_size(void)
{
	struct winsize	wind;

	ioctl(0, TIOCGWINSZ, &wind);
	return ((int)wind.ws_col);
}

int		display_sizing(int size)
{
	static int	g;

	if (!size)
		return (g);
	g = size;
	return (0);
}

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
		display_sizing(ft_strlen(pwd) + 6);
		write(1, pwd, ft_strlen(pwd));
	}
	ft_putstr_fd(ANSI_RESET, 1);
	write(1, " > ", 3);
}

void	caller_display(t_list *fp, t_buf *input, int change_pos)
{
	char	path[PATH_MAX];
	char	*pwd;

	ft_bzero(path, PATH_MAX);
	if (!(pwd = find_var_value(fp, "PWD")))
		pwd = getcwd(path, PATH_MAX);
	fancy_display(pwd);
	if (change_pos)
	{
		input->pos.l = (display_sizing(0)) / window_width_size();
		input->pos.c = display_sizing(0) % (window_width_size());
	}
}
