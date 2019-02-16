/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_val_ret.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 14:15:17 by jocohen           #+#    #+#             */
/*   Updated: 2019/02/16 14:17:16 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		replace_val_ret(char **str, int i, int x)
{
	char	*value;

	ft_delete_inside(str, i, x + 1);
	value = ft_itoa(ret_status());
	replace_str(str, value, i);
	ft_memdel((void **)&value);
	return (0);
}
