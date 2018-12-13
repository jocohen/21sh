/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:48:48 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/13 16:54:14 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	set_terminal(t_env *fp, int reset)
{
	static struct termios	old;
	struct termios			term;
	int						term_valid;
	char					*termtype;

	if (!reset)
	{
		if (ft_strcmp((termtype = get_env_value(fp, "$TERM")), "") == 0)
			termtype = "xterm-256color";
		if ((term_valid = tgetent(0, termtype)) == -1 || !term_valid)
			ft_exit(0);
		if ((tcgetattr(0, &old)) == -1 || (tcgetattr(0, &term)) == -1)
			ft_exit(0);
		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		if ((tcsetattr(0, TCSADRAIN, &term)) == -1)
			ft_exit(0);
	}
	else
	{
		if ((tcsetattr(0, TCSADRAIN, &old)) == -1)
			ft_exit(0);
		write(0, "\r", 1);
	}
}