/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:10:10 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/20 14:01:48 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	conv_x(va_list ap, int mfw, int prec)
{
	unsigned int	x;
	int				r_num;
	int				zeros;
	int				size;

	x = va_arg(ap, unsigned int);
	r_num = 0;
	if (x == 0 && prec == 0)
		r_num += put_c_n(' ', mfw);
	else
	{
		zeros = max(0, prec - digits_x(x) - (x == 0 ? 1 : 0));
		size = zeros + digits_x(x) + (x == 0 ? 1 : 0);
		put_c_n(' ', max(0, mfw - size));
		put_c_n('0', zeros);
		put_nbr_x(x);
		r_num = max(mfw, size);
	}
	return (r_num);
}
