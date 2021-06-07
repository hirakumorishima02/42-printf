/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:48:23 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/20 14:20:18 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		put_single_x(unsigned int num)
{
	if (0 <= num && num <= 9)
		put_c_n('0' + num, 1);
	if (num >= 10)
		put_c_n('a' + num - 10, 1);
}

void			put_nbr_x(unsigned int x)
{
	unsigned int	num;

	num = x;
	if (num / 16 != 0)
		put_nbr_x(x / 16);
	put_single_x(x % 16);
}
