/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:49:36 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/18 17:17:07 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_21sh.h"

// int		main(int argc, char **argv, char **env)
// {
// 	char	*s;
// 	char	**tab_env;
// 	int		r;
//
// 	s = NULL;
// 	tab_env = NULL;
// 	r = 1;
// 	(void)argv;
// 	(void)argc;
// 	env_cp(env, &tab_env);
// 	while (r > 0)
// 	{
// 		write(1, "prompt > ", 9);
// 		r = get_next_line(0, &s);
// 		if (ft_strcmp("exit", s) == 0)
// 			break ;
// 		lexer(s, tab_env);
// 	}
// 	free(s);
// 	return (0);
// }
