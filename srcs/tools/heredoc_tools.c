/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:02:49 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/21 17:05:04 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void		join_inputs(char **input, char *s)
{
	char	*tmp;

	if (*input == NULL)
	{
		if (!(*input = ft_strdup(s)))
			ft_exit_malloc();
	}
	else
	{
		if (!(tmp = ft_strjoin(*input, "\n")))
			ft_exit_malloc();
		free(*input);
		if (!(*input = ft_strjoin(tmp, s)))
			ft_exit_malloc();
		free(tmp);
	}
	free(s);
}

int				heredoc_content(t_alloc *alloc, t_ast *elem, char *s)
{
	set_terminal(0);
	while (1)
	{
		if (!(s = recall_prompt(alloc, 1)))
		{
			ft_memdel((void **)&(elem->heredoc));
			break ;
		}
		if (ft_strcmp((elem->right) ? elem->right->input[0] :
		elem->input[1], s))
			join_inputs(&elem->heredoc, s);
		else
		{
			free(s);
			if (!(s = ft_strjoin(elem->heredoc, "\n")))
				ft_exit_malloc();
			free(elem->heredoc);
			elem->heredoc = s;
			break ;
		}
	}
	set_terminal(1);
	if (elem->heredoc)
		return (1);
	return (0);
}
