/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:48:48 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/08 15:58:17 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	set_terminal(int reset)
{
	static struct termios	old;
	struct termios			term;
	int						term_valid;
	char					*termtype;

	if (!reset)
	{
		if (!(termtype = ttyname(ttyslot())))
			termtype = "xterm-256color";
		if ((term_valid = tgetent(0, termtype)) == -1 || !term_valid)
			ft_exit(0);
		if ((tcgetattr(STDIN_FILENO, &old)) == -1 || (tcgetattr(STDIN_FILENO, &term)) == -1)
			ft_exit(0);
		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &term)) == -1)
			ft_exit(0);
	}
	else
	{
		if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &old)) == -1)
			ft_exit(0);
		write(0, "\r", 1);
	}
}
