/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caller_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:53:10 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/14 14:47:01 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

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

void	classic_display(char *prompt)
{
	write(1, prompt, ft_strlen(prompt));
	write(1, "> ", 2);
	display_sizing(ft_strlen(prompt) + 2);
}

void	caller_display(t_env *fp, t_buf *input, int change_pos)
{
	char		path[PATH_MAX];
	char		*pwd;
	int			mode;

	mode = 1;
	ft_bzero(path, PATH_MAX);
	if ((pwd = recall_prompt(0, -1)))
		mode = 0;
	else if (!(pwd = get_env_value(fp, "$PWD")))
		pwd = getcwd(path, PATH_MAX);
	(mode) ? fancy_display(pwd) : 0;
	(!mode) ? classic_display(pwd) : 0;
	if (change_pos)
	{
		input->pos.l = (display_sizing(0)) / window_width_size();
		input->pos.c = display_sizing(0) % (window_width_size());
	}
}
