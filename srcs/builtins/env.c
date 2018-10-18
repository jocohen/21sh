/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:43:30 by tcollard          #+#    #+#             */
/*   Updated: 2018/10/17 18:18:49 by tcollard         ###   ########.fr       */
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
