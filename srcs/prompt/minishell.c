/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 11:49:36 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/08 12:49:17 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_21sh.h"

// static void	display_env_lst_and_table(t_env *lst_env, char **tab_env)
// {
// 	int i;
//
// 	i = 0;
// 	ft_printf("\n====== TAB ENV ======\n\n");
// 	while (tab_env[i])
// 	{
// 		ft_printf("tab[%d]: %s\n", i, tab_env[i]);
// 		i += 1;
// 	}
// 	ft_printf("\n======== END ========\n\n");
// 	i = 0;
// 	ft_printf("\n====== LST ENV ======\n\n");
// 	while(lst_env)
// 	{
// 		ft_printf("elem %d: %s=%s\n", i, lst_env->key, lst_env->value);
// 		lst_env = lst_env->next;
// 		i += 1;
// 	}
// 	ft_printf("\n======== END ========\n\n");
// }


int		main(int argc, char **argv, char **env)
{
	char	*s;
	char	**tab_env;
	t_env	*lst_env;
	int		r;

	s = NULL;
	lst_env = NULL;
	tab_env = NULL;
	r = 1;
	(void)argv;
	(void)argc;
	env_cp(env, &lst_env);
	add_shlvl(&lst_env);
	convert_lst_tab(lst_env, &tab_env);
	// display_env_lst_and_table(lst_env, tab_env);
	while (r > 0)
	{
		write(1, "prompt > ", 9);
		r = get_next_line(0, &s);
		if (ft_strcmp("exit", s) == 0)
			break ;
		lexer(s, lst_env, tab_env);
	}
	free(s);
	return (0);
}
