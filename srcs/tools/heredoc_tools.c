/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:02:49 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/21 13:40:08 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void		join_inputs(char **input, char *s)
{
	char	*tmp;

	if (*input == NULL)
		*input = ft_strdup(s);
	else
	{
		tmp = ft_strjoin(*input, "\n");
		free(*input);
		*input = ft_strjoin(tmp, s);
		free(tmp);
	}
	free(s);
}

int				heredoc_content(t_alloc *alloc, t_ast *elem, char *s)
{
	int		x = 0;
	set_terminal(0);
	while (1)
	{
		if (!(s = recall_prompt(alloc, 1)))
		{
			ft_memdel((void **)&(elem->heredoc));
			break ;
		}
		if (x < 30 && ft_strcmp((elem->right) ? elem->right->input[0] :
		elem->input[1], s))
		{
			x += 1;
			join_inputs(&elem->heredoc, s);
		}
		else
		{
			free(s);
			s = ft_strjoin(elem->heredoc, "\n");
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
