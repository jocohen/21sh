/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:17:43 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/07 11:37:45 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	dispatch_cmd(t_ast *elem, char **tab_env)
{
	int					i;
	static char			*lst_built[5] = {"cd", "echo", "setenv", "unsetenv",
	"env"};
	static t_dispatch	dispatch[5];

	i = 0;
	ft_printf("CMD:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
	dispatch[0] = cd_builtins;
	dispatch[1] = echo_builtins;
	dispatch[2] = setenv_builtins;
	dispatch[3] = unsetenv_builtins;
	dispatch[4] = env_builtins;
	while (i < 5)
	{
		if (ft_strcmp(elem->input[0], lst_built[i]) == 0)
			break ;
		i += 1;
	}
	if (i < 5)
		dispatch[i](elem, tab_env);
	else
	{
		ft_printf("go to execve\n");
		exec_input(tab_env, elem);
	}
}

void	dispatch_logic(t_ast *elem, char **tab_env)
{
	(void)tab_env;
	ft_printf("LOGIC:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
}

void	dispatch_redir(t_ast *elem, char **tab_env)
{
	(void)tab_env;
	ft_printf("REDIR:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
}

void	dispatch_operator(t_ast *elem, char **tab_env)
{
	(void)tab_env;
	ft_printf("OPERATOR:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
}

void	dispatch_agreg(t_ast *elem, char **tab_env)
{
	(void)tab_env;
	ft_printf("AGREG:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
}
