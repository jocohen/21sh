/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:17:43 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/06 16:49:28 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	dispatch_cmd(t_ast *elem, t_env *lst_env, char **tab_path)
{
	int					i;
	int					ret;
	static char			*lst_built[5] = {"cd", "echo", "setenv", "unsetenv",
	"env"};
	static t_builtins	dispatch[5];

	i = 0;
	ret = 0	;
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
		ret = dispatch[i](elem, lst_env);
	else
		ret = exec_input(elem, lst_env, tab_path);
	// ft_printf("ret = %d\n", ret);
	return (ret);
}

int	dispatch_logic(t_ast *elem, t_env *lst_env, char **tab_path)
{
	int	ret;

	ret = -1;
	(void)tab_path;
	if (ft_strcmp(elem->input[0], "&&") == 0)
	{
		ret = analyzer(elem, lst_env);
		if (ret == 0)
			ret = analyzer(elem, lst_env);
		if (ret == 0)
			return (0);
	}
	else if (ft_strcmp(elem->input[0], "||") == 0)
	{
		while (ret != 0)
			ret = analyzer(elem, lst_env);
		if (ret == 0)
			return (0);
	}
	return (-1);
}

int	dispatch_redir(t_ast *elem, t_env *lst_env, char **tab_path)
{
	(void)lst_env;
	(void)tab_path;
	ft_printf("REDIR:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
	return (1);
}

int	dispatch_operator(t_ast *elem, t_env *lst_env, char **tab_path)
{
	// if (elem->input[0][0] == '|')
	// 	do_pipe(elem);
	(void)lst_env;
	(void)tab_path;
	(void)elem;
	ft_printf("OPERATOR:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
	return (1);
}

int	dispatch_agreg(t_ast *elem, t_env *lst_env, char **tab_path)
{
	(void)lst_env;
	(void)tab_path;
	ft_printf("AGREG:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
	return (1);
}
