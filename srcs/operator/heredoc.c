/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:18:44 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/20 16:29:15 by jocohen          ###   ########.fr       */
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

static int		heredoc_content(t_alloc *alloc, t_ast *elem, char *s)
{
	set_terminal(0);
	while (1)
	{
		if (!(s = recall_prompt(alloc, 1)))
		{
			ft_memdel((void **)&(elem->heredoc));
			break ;
		}
		if (ft_strcmp((elem->right) ? elem->right->input[0] :
		elem->input[1], s))
			join_inputs(&elem->heredoc, s);
		else
		{
			free(s);
			s = ft_strjoin(elem->heredoc, "\n");
			free(elem->heredoc);
			elem->heredoc = s;
			break ;
		}
	}
	set_terminal(1);
	if (elem->heredoc)
		return (1);
	return (0);
}

static void		write_pipe(t_ast *elem)
{
	close(elem->fd[0]);
	dup2(elem->fd[1], STDOUT_FILENO);
	close(elem->fd[1]);
	write(STDOUT_FILENO, elem->heredoc, ft_strlen(elem->heredoc));
	exit(0);
}

int				complete_heredoc(t_ast *lst, t_alloc **alloc)
{
	while (lst)
	{
		if (lst->type == HEREDOC)
		{
			if (!heredoc_content(*alloc, lst, 0))
				return (0);
		}
		lst = lst->next;
	}
	return (1);
}

void			heredoc(t_ast *elem, t_env **lst_env, t_alloc **alloc)
{
	int		pid1;
	int		pid2;

	if (!elem->right || !elem->left || !elem->heredoc || pipe(elem->fd) == -1)
		return ;
	if (!(pid1 = fork()))
		write_pipe(elem);
	else
	{
		g_pid = pid1;
		if (!(pid2 = fork()))
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
	ft_memdel((void **)&elem->heredoc);
}
