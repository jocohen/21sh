/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:20:13 by tcollard          #+#    #+#             */
/*   Updated: 2019/02/16 11:19:40 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	job_control(t_ast *elem, t_env *lst_env)
{
	(void)elem;
	(void)lst_env;
	write(2, "21sh: error no job control\n", 27);
	return (1);
}
