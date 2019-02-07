/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:08:44 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/07 12:42:34 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	heredoc(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	char	*s;
	char	*tmp;

	(void)lst_env;
	(void)alloc;
	s = NULL;
	tmp = NULL;

	ft_printf("in[0]: |%s|\n", elem->input[0]);
	if (elem->right)
		ft_printf("r_in[0]: |%s|\n", elem->right->input[0]);

		while (!s || ft_strcmp(s, elem->right->input[0]) != 0)
		{
			ft_memdel((void **)&s);
			if (!(s = recall_prompt(*alloc, 1)))
				return (0);
				ft_printf("END: |%s|\n", s);
		}
	return (1);
}
