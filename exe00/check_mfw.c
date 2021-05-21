/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mfw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:41:40 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/19 14:59:46 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_mfw(const char *str, int *mfw)
{
	int	i;

	i = 0;
	if (!str || !is_num(str[0]))
	{
		*mfw = 0;
		return (0);
	}
	*mfw = ft_atoi(str);
	while (is_num(str[i]))
		i++;
	return (i);
}