/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:49:36 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/13 16:45:11 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** static void	display_env_lst_and_table(t_env *lst_env, char **tab_env)
** {
** 	int i;
**
** 	i = 0;
** 	ft_printf("\n====== TAB ENV ======\n\n");
** 	while (tab_env[i])
** 	{
** 		ft_printf("tab[%d]: %s\n", i, tab_env[i]);
** 		i += 1;
** 	}
** 	ft_printf("\n======== END ========\n\n");
** 	i = 0;
** 	ft_printf("\n====== LST ENV ======\n\n");
** 	while(lst_env)
** 	{
** 		ft_printf("elem %d: %s=%s\n", i, lst_env->key, lst_env->value);
** 		lst_env = lst_env->next;
** 		i += 1;
** 	}
** 	ft_printf("\n======== END ========\n\n");
** }
*/

// int		main(int argc, char **argv, char **env)
// {
// 	char	*s;
// 	t_env	*lst_env;
// 	int		r;
// 	int		i;
// 	int 	nb;
// 	t_alloc	*alloc;
//
// 	s = NULL;
// 	lst_env = NULL;
// 	alloc = NULL;
// 	nb = 0;
// 	r = 1;
// 	i = 0;
// 	(void)argv;
// 	(void)argc;
// 	if (!(alloc = (t_alloc*)malloc(sizeof(t_alloc))))
// 		return (-1);
// 	env_cp(env, &lst_env);
// 	add_shlvl(&lst_env);
// 	alloc->ast = NULL;
// 	alloc->env = &lst_env;
// 	while (r > 0)
// 	{
// 		write(1, "prompt > ", 9);
// 		r = get_next_line(0, &s);
// 		if (s && ft_strncmp("exit", s, 4) == 0)
// 			break ;
// 		// ft_printf("*s = |%c|\n", *s);
// 		if (r != 0 && ft_strcmp(s, "") != 0)
// 			lexer(s, &lst_env, &alloc);
// 		else if (ft_strcmp(s, "") == 0)
// 			free(s);
// 	}
// 	if (r != 0 && ft_isspace(s[4]) == 1)
// 	{
// 		while (s[4 + i])
// 		{
// 			if (ft_isdigit(s[4 + i]) == 1)
// 			{
// 				nb = ft_atoi(&s[4 + i]);
// 				break ;
// 			}
// 			i += 1;
// 		}
// 	}
// 	(s && r != 0) ? free(s) : 0;
// 	del_lst_env(&lst_env);
// 	free(alloc);
// 	return (nb);
// }
