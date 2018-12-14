/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:17:43 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/14 15:50:39 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	dispatch_cmd(t_ast *elem, t_env **lst_env, char **tab_path,
	t_alloc **alloc)
{
	int					i;
	int					ret;
	static char			*lst_built[5] = {"cd", "echo", "setenv", "unsetenv",
	"env"};
	static t_builtins	dispatch[] = { &cd_builtins, &echo_builtins,
		&setenv_builtins, &unsetenv_builtins, &env_builtins };

	i = 0;
	ret = 0	;
	while (i < 5)
	{
		if (ft_strcmp(elem->input[0], lst_built[i]) == 0)
			break ;
		i += 1;
	}
	if (i < 5)
		ret = dispatch[i](elem, lst_env, alloc);
	else
		ret = exec_input(elem, *lst_env, tab_path, alloc);
	return (ret);
}

int	dispatch_logic(t_ast *elem, t_env **lst_env, char **tab_path,
	t_alloc **alloc)
{
	int	ret;

	ret = -1;
	(void)tab_path;
	if (ft_strcmp(elem->input[0], "&&") == 0)
	{
		ret = analyzer(elem, lst_env, alloc);
		if (ret == 0)
			ret = analyzer(elem, lst_env, alloc);
		if (ret == 0)
			return (0);
	}
	else if (ft_strcmp(elem->input[0], "||") == 0)
	{
		while (ret != 0)
			ret = analyzer(elem, lst_env, alloc);
		if (ret == 0)
			return (0);
	}
	return (-1);
}

int	dispatch_redir(t_ast *elem, t_env **lst_env, char **tab_path,
	t_alloc **alloc)
{
	(void)lst_env;
	(void)tab_path;
	(void)alloc;
	ft_printf("REDIR:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
	return (1);
}

int	dispatch_operator(t_ast *elem, t_env **lst_env, char **tab_path,
	t_alloc **alloc)
{
	(void)tab_path;
	if (ft_strcmp(elem->input[0], "|") == 0)
		return (do_pipe(elem, lst_env, alloc));
	else if (ft_strcmp(elem->input[0], "&") == 0)
		return (job_control(elem, *lst_env));
	return (1);
}

int	dispatch_agreg(t_ast *elem, t_env **lst_env, char **tab_path,
	t_alloc **alloc)
{
	(void)lst_env;
	(void)tab_path;
	(void)alloc;
	ft_printf("AGREG:\n->tpye = %d\n->input: |%s|\n\n", elem->type,
	elem->input[0]);
	return (1);
}
