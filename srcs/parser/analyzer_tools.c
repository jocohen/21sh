/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:17:43 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/07 10:40:12 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

int	dispatch_cmd(t_ast *elem, t_env *lst_env, char **tab_path)
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
	// int		fd[2];
	// int		pid;

	(void)tab_path;
	if (ft_strcmp(elem->input[0], "|") == 0)
		return (do_pipe(elem, lst_env));
	else if (ft_strcmp(elem->input[0], "&") == 0)
		return (job_control(elem, lst_env));
	return (1);
	// if (pipe(fd) == -1)
	// {
	// 	ft_printf("Error: pipe failed\n");
	// 	return (-1);
	// }
	// pid = fork();
	// if (!pid)
	// {
	// 	dup2(fd[0], 0);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	analyzer(elem->right, lst_env);
	// 	exit(0);
	// }
	// else
	// {
	// 	pid = fork();
	// 	if (!pid)
	// 	{
	// 		dup2(fd[1], 1);
	// 		close(fd[0]);
	// 		close(fd[1]);
	// 		analyzer(elem->left, lst_env);
	// 		exit(0);
	// 	}
	// 	else
	// 	{
	// 		close(fd[0]);
	// 		close(fd[1]);
	// 		waitpid(-1, NULL, 0);
	// 		waitpid(-1, NULL, 0);
	// 	}
	// }
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
