/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:42:07 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/19 15:01:36 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_prec(const char *str, int *prec)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] != '.')
	{
		*prec = -1;
		return (0);
	}
	if (!is_num(str[1]))
	{
		*prec = 0;
		return (1);
	}
	*prec = ft_atoi(&(str[1]));
	while (is_num(str[i]))
		i++;
	return (i);
}
