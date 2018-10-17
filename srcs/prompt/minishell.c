/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:49:36 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/01 11:49:39 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_21sh.h"

int		main(int argc, char **argv, char **env)
{
	char	*s;
	int		r;

	s = NULL;
	r = 1;
	(void)argv;
	(void)argc;
	(void)env;
	while (r > 0)
	{
		write(1, "prompt > ", 9);
		r = get_next_line(0, &s);
		if (ft_strcmp("exit", s) == 0)
			break ;
		lexer(s);
	}
	free(s);
	return (0);
}
