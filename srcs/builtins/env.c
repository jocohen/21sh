/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:43:30 by tcollard          #+#    #+#             */
/*   Updated: 2018/11/05 18:25:23 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	env_cp(char **env, char ***tab_env)
{
	int	len;

	len = 0;
	while(env[len])
		len += 1;
	if (!(*tab_env = (char**)malloc(sizeof(char *) * (len + 1))))
		return ;
	len = 0;
	while (env[len])
	{
		(*tab_env)[len] = ft_strdup(env[len]);
		len += 1;
	}
	(*tab_env)[len] = NULL;
}

char	*get_env_value(char **tab, char *str)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], &str[1], len) == 0)
			break ;
		else
			i += 1;
	}
	return (&tab[i][len + 1]);
}

void	env_builtins(t_ast *elem, char **tab_env)
{
	(void)elem;
	(void)tab_env;
	ft_printf("env\n");
}
