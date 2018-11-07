/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:49:36 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/07 17:09:28 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_21sh.h"

int		main(int argc, char **argv, char **env)
{
	char	*s;
	t_env	*lst_env;
	int		r;

	s = NULL;
	lst_env = NULL;
	r = 1;
	(void)argv;
	(void)argc;
	env_cp(env, &lst_env);
	while (r > 0)
	{
		write(1, "prompt > ", 9);
		r = get_next_line(0, &s);
		if (ft_strcmp("exit", s) == 0)
			break ;
		lexer(s, &lst_env);
	}
	free(s);
	return (0);
}
