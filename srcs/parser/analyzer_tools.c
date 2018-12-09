/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:17:43 by tcollard          #+#    #+#             */
/*   Updated: 2018/12/10 00:57:16 by tcollard         ###   ########.fr       */
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

// void    loop_pipe(char ***cmd)
// {
//   int   p[2];
//   pid_t pid;
//   int   fd_in = 0;
//
//   while (*cmd != NULL)
//     {
//       pipe(p);
//       if ((pid = fork()) == -1)
//         {
//           exit(EXIT_FAILURE);
//         }
//       else if (pid == 0)
//         {
//           dup2(fd_in, 0); //change the input according to the old one
//           if (*(cmd + 1) != NULL)
//             dup2(p[1], 1);
//           close(p[0]);
//           execvp((*cmd)[0], *cmd);
//           exit(EXIT_FAILURE);
//         }
//       else
//         {
//           wait(NULL);
//           close(p[1]);
//           fd_in = p[0]; //save the input for the next command
//           cmd++;
//         }
//     }

int	dispatch_operator(t_ast *elem, t_env *lst_env, char **tab_path)
{
	int		fd_in;
	t_ast	*tmp;
	int		pid;

	fd_in = 0;
	tmp = elem;
	(void)tab_path;
	if (ft_strcmp(elem->input[0], "|") == 0)
	{
		pid = fork();
		if (!pid)
		{
			while (tmp && ft_strcmp(tmp->input[0], "|") == 0)
			{
				if (elem->fd[0] == -1 && elem->fd[1] == -1)
				{
					pipe(elem->fd);
					dup2(fd_in, 0);
					fd_in = elem->fd[0];
					// ft_printf("fd[0] = %d fd[1] = %d\n", elem->fd[0], elem->fd[1]);
				}
				tmp = elem->left;
			}
			do_pipe(elem, lst_env);
		}
		else
		{
			wait(NULL);
			close(elem->fd[1]);
		}
	}
	else if (ft_strcmp(elem->input[0], "&") == 0)
		return (job_control(elem, lst_env));
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
