/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:43:30 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/17 12:46:31 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_21sh.h"

void	env_cp(char **env)
{
	int	len;

	len = 0;
	while(env[len])
		len += 1;
	if (!(g_env = (char**)malloc(sizeof(char *) * (len + 1))))
		return ;
	len = 0;
	while (env[len])
	{
		g_env[len] = env[len];
		len += 1;
	}
	g_env[len] = NULL;
}
