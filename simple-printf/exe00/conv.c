/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:06:26 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/19 15:09:06 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int conv(va_list ap, char c, int mfw, int prec)
{
	int r;

	r = 0;
	if (c == 'd')
		r = conv_d(ap, mfw, prec);
	if (c == 'x')
		r = conv_x(ap, mfw, prec);
	if (c == 's')
		r = conv_s(ap, mfw, prec);
	return (r);
}
