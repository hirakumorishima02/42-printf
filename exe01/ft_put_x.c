/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:40:30 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/24 16:41:41 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		ft_get_digits_x(unsigned int	ud)
{
	int	digits;

	digits = 0;
	while (ud / 16)
	{
		ud /= 16;
		digits++;
	}
	digits++;
	return (digits);
}

static int	ft_putx(unsigned int ud, int padding)
{
	int	res;

	res = 0;
	while(padding-- > 0)
		res += ft_putchar('0');
	if (ud / 16)
		res += ft_putx(ud / 16, padding);
	if ((ud % 16) >= 10)
		res += ft_putchar((ud % 16) - 10 + 'a');
	else
		res += ft_putchar((ud % 16) + '0');
	return (res);
}

int	ft_put_x(t_args *args, va_list ap)
{
	int	width;
	int	precision;
	int	d;
	int	len;
	int	putlen;
	int	padding;
	int	res;

	width = args->has_width ? args->width : 0;
	precision = args->has_precision ? args->precision : 0;
	d = va_arg(ap, int);
	len = ft_get_digits_x(d);
	if (args->has_precision && args->precision == 0 && d == 0)
		len = 0;
	padding = (len < precision) ? precision - len : 0;
	putlen = len + padding;
	while ((width - putlen) > 0)
	{
		res += ft_putchar(' ');
		width--;
	}
	if (args->has_precision && args->precision == 0 && d == 0)
		return (res);
	return (res + ft_putx(d, padding));
}