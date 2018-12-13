/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 14:34:12 by jocohen           #+#    #+#             */
/*   Updated: 2018/12/12 14:31:02 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		historic_opening(t_list *lst, int open_type)
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
	if (!open_type)
		fd = open(s, O_RDONLY);
	else
		fd = open(s, O_WRONLY | O_APPEND | O_CREAT);
	ft_memdel((void **)&s);
	return (fd);
}

int		init_hist(t_historic **history, t_list *lst)
{
	int			fd;
	t_historic	*tmp;

	tmp = 0;
	fd = historic_opening(lst, 0);
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

void	historic_entry(t_buf *input, t_historic **history, int read,
						t_list *lst)
{
	int		fd;

	while ((*history)->next)
		(*history) = (*history)->next;
	ft_memdel((void **)&((*history)->origin));
	ft_memdel((void **)&((*history)->modif));
	reset_hist((*history)->prev);
	if (!input->s[0] || read || ((*history)->prev && !ft_strcmp(input->s,
		((*history)->prev)->origin)))
		return ;
	fd = historic_opening(lst, 1);
	write(fd, input->s, ft_strlen(input->s));
	write(fd, "\n", 1);
	close(fd);
	if (!((*history)->origin = ft_strdup(input->s))
		|| !(((*history)->next) = ft_new_cmd_hist()))
		ft_exit(EXIT_FAILURE);
	((*history)->next)->prev = (*history);
	(*history) = (*history)->next;
}
