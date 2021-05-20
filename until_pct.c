/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   until_pct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:35:08 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/19 14:59:35 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	until_pct(const char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i] != 0 && str[i] != '%')
	{
		write(1, &(str[i]), 1);
		i++;
	}
	return (i);
}