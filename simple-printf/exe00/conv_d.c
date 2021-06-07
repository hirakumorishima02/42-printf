/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:10:08 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/20 13:21:28 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int conv_d(va_list ap, int mfw, int prec)
{
	int	d;
	int	r_num;
	int zeros;
	int	size;

	d = va_arg(ap, int);
	r_num = 0;
	if (d == 0 && prec == 0)
		r_num += put_c_n(' ', mfw);
	else
	{
		zeros = max(0, prec - digits_d(d) - (d == 0 ? 1 : 0));
		size = (d < 0 ? 1 : 0) + zeros + digits_d(d) + (d == 0 ? 1 : 0);
		put_c_n(' ', max(0, mfw - size));
		if (d < 0)
			write(1, "-", 1);
		put_c_n(0, zeros);
		put_nbr_d(d);
		r_num = max(mfw, size);
	}
	return (r_num);
}
