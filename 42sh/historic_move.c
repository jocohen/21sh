/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 14:34:12 by jocohen           #+#    #+#             */
/*   Updated: 2018/10/17 17:52:52 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int		historic_opening(t_list *lst)
{
	int		fd;
	char	*home;
	char	*s;

	if (!(home = find_var_value(lst, "HOME")))
		return (-1);
	if (home[ft_strlen(home) - 1] != '/')
		s = ft_strjoin(home, "/.21sh_history");
	else
		s = ft_strjoin(home, ".21sh_history");
	if (!s)
		ft_exit(EXIT_FAILURE);
	fd = open(s, O_RDONLY);
	ft_memdel((void **)&s);
	return (fd);
}

int		init_hist(t_historic **history, t_list *lst)
{
	int			fd;
	t_historic	*tmp;

	tmp = 0;
	fd = historic_opening(lst);
	if (!((*history) = ft_new_cmd_hist()))
		ft_exit(EXIT_FAILURE);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &((*history)->origin)) > 0)
	{
		(*history)->prev = tmp;
		tmp = (*history);
		if (!(((*history)->next) = ft_new_cmd_hist()))
			ft_exit(EXIT_FAILURE);
		(*history) = (*history)->next;
	}
	(*history)->prev = tmp;
	close(fd);
	return (0);
}

int		search_cmd_common(const char *s, const char *sch)
{
	size_t	y;
	size_t	len;

	y = 0;
	len = ft_strlen(sch);
	while (s && s[y] && sch[y] && s[y] == sch[y])
		y += 1;
	if (y == len)
		return (1);
	return (0);
}

void	move_front_or_back(t_historic **lst, int direction)
{
	t_historic	*tmp;

	tmp = (*lst);
	if (direction == -1)
	{
		if (!tmp->prev)
			return ;
		tmp = tmp->prev;
		while (tmp->modif && !(tmp->modif[0]) && tmp->next)
		{
			if (!tmp->prev)
				return ;
			tmp = tmp->prev;
		}
	}
	else
	{
		if (!tmp->next)
			return ;
		tmp = tmp->next;
		while (tmp->modif && !(tmp->modif[0]) && tmp->next)
		{
			if (!tmp->next)
				return ;
			tmp = tmp->next;
		}
	}
	(*lst) = tmp;
}

void	delete_line_pos(t_buf *input, size_t save, size_t size)
{
	size_t	q;
	size_t	e;
	static int x;
	size_t	w;
	int l = 0;

	q = save;
	w = size;
	x += 1;
	while (save < size)
	{
		tputs(tgetstr("nd", 0), 1, ft_writestdin);
		save += 1;
	}
	e = save;
	tputs(tgetstr("dm", 0), 1, ft_writestdin);
	while (save)
	{
		tputs(tgetstr("le", 0), 1, ft_writestdin);
		tputs(tgetstr("dc", 0), 1, ft_writestdin);
		save -= 1;
	}
	tputs(tgetstr("ed", 0), 1, ft_writestdin);
	write(0, input->s, input->x);
	if (x == 2)
		ft_printf("\n index cursor origin =%zu size old input =%zu ind cursor after move =%zu err=%d\n", q, w, e, l);
}

void	cmd_spe_search(t_historic **history, t_buf *input, int direction)
{
	char			c;
	t_historic		*tmp;
	size_t			x[2];
	static char		*search_s;

	x[0] = input->x;
	x[1] = ft_strlen(input->s);
	if (search_s && check_prev_read(0) != -6)
		ft_memdel((void **)&search_s);
	if (!search_s)
	{
		c = input->s[input->x];
		input->s[input->x] = 0;
		if (!(search_s = ft_strdup(input->s)))
			ft_exit(EXIT_FAILURE);
		input->s[input->x] = c;
	}
	tmp = *history;
	while (tmp)
	{
		if (direction == -1)
			tmp = tmp->prev;
		else
			tmp = tmp->next;
		if (tmp && search_cmd_common((tmp->modif) ? tmp->modif : tmp->origin, search_s))
			break ;
	}
	if (!tmp)
		return ;
	(*history) = tmp;
	check_over_buffer(input, (*history)->modif ? (*history)->modif : (*history)->origin);
	ft_strcpy(input->s, (tmp->modif) ? tmp->modif : tmp->origin);
	input->x = ft_strlen(input->s);
	delete_line_pos(input, x[0], x[1]);
}

void	historic_move(t_buf *input, t_historic **history, int direction)
{
	size_t			save;
	size_t			size;
	static int		in_zero;

	check_prev_read(-6);
	save = input->x;
	size = ft_strlen(input->s);
	if (check_prev_read(0) != -6 && in_zero)
		in_zero = 0;
	if (ft_strcmp(input->s, (*history)->origin))
	{
		ft_memdel((void **)&((*history)->modif));
		if (!((*history)->modif = ft_strdup(input->s)))
			ft_exit(EXIT_FAILURE);
	}
	if (input->x && !in_zero)
	{
		in_zero = 0;
		cmd_spe_search(history, input, direction);
		return ;
	}
	in_zero = 1;
	move_front_or_back(history, direction);
	check_over_buffer(input, (*history)->modif ? (*history)->modif : (*history)->origin);
	ft_strcpy(input->s, (*history)->modif ? (*history)->modif : (*history)->origin);
	input->x = ft_strlen(input->s);
	delete_line_pos(input, save, size);
}
