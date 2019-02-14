/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:18:44 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/14 12:29:18 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void		join_inputs(char **input, char *s)
{
	char	*tmp;

	if (*input == NULL)
		*input = ft_strdup(s);
	else
	{
		tmp = ft_strjoin(*input, "\n");
		free(*input);
		*input = ft_strjoin(tmp, s);
		free(tmp);
	}
	free(s);
}

static int		pipe_exec(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int		ret;
	t_ast	*tmp;

	tmp = elem;
	while (!ft_strcmp("<<", tmp->input[0]))
		tmp = tmp->left;
	close(elem->back->fd[1]);
	dup2(elem->back->fd[0], STDIN_FILENO);
	close(elem->back->fd[0]);
	ret = analyzer(tmp, lst_env, alloc);
	exit(ret);
}

static int		heredoc_content(t_alloc *alloc, t_ast *elem,
								char **file, char *s)
{
	*file = 0;
	set_terminal(0);
	while (1)
	{
		if (!(s = recall_prompt(alloc, 1)))
		{
			ft_memdel((void **)file);
			break;
		}
		if (ft_strcmp(elem->right->input[0], s))
			join_inputs(file, s);
		else
		{
			free(s);
			s = ft_strjoin(*file, "\n");
			free(*file);
			*file = s;
			break ;
		}
	}
	set_terminal(-1);
	if (!*file)
		return (0);
	return (1);
}

static void		write_pipe(char *file, t_ast *elem)
{
	close(elem->fd[0]);
	dup2(elem->fd[1], STDOUT_FILENO);
	close(elem->fd[1]);
	write(STDOUT_FILENO, file, ft_strlen(file));
	exit(0);
}

void			heredoc(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	char	*file;
	int		pid1;
	int		pid2;

	if (!heredoc_content(*alloc, elem, &file, 0))
		return ;
	pipe(elem->fd);
	pid1 = fork();
	if (!pid1)
		write_pipe(file, elem);
	else
	{
		g_pid = pid1;
		pid2 = fork();
		if (!pid2)
			pipe_exec(elem->left, lst_env, alloc);
		else
		{
			g_pid = pid2;
			close(elem->fd[1]);
			close(elem->fd[0]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
}
