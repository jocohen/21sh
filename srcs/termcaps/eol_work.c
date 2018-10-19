/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eol_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:58:55 by jocohen           #+#    #+#             */
/*   Updated: 2018/10/19 10:58:34 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	historic_entry(t_buf *input, t_historic **history, int read)
{
	while ((*history)->next)
		(*history) = (*history)->next;
	ft_memdel((void **)&((*history)->origin));
	ft_memdel((void **)&((*history)->modif));
	reset_hist((*history)->prev);
	if (!input->s[0] || read || ((*history)->prev && !ft_strcmp(input->s, ((*history)->prev)->origin)))
		return ;
	if (!((*history)->origin = ft_strdup(input->s)) || !(((*history)->next) = ft_new_cmd_hist()))
		ft_exit(EXIT_FAILURE);
	((*history)->next)->prev = (*history);
	(*history) = (*history)->next;
}

void	enter_section(t_buf *input, t_list **lst, t_historic **history, int read)
{
	struct winsize	size;
	int				move;

	ioctl(0, TIOCGWINSZ, &size);
	move = size.ws_col;
	tputs(tgetstr("do", 0), 1, ft_writestdin);
	while (move)
	{
		tputs(tgetstr("le", 0), 1, ft_writestdin);
		move -= 1;
	}
	historic_entry(input, history, read);
	lexer(input->s, lst);
	// input start fct
	input->x = 0;
	ft_bzero(input->s, ft_strlen(input->s));
	caller_display(*lst);
}
