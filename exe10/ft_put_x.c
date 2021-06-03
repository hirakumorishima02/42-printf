/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:05:09 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/03 14:05:37 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "header.h"

static  int ft_get_digits_x(unsigned int   d)
{
    int digits;

    digits = 0;
    while (d / 16)
    {
        digits++;
        d /= 16;
    }
    digits++;
    return (digits);
}

static  int ft_putx(unsigned int d, int  padding)
{
    int res;

    res = 0;
    while (padding-- > 0)
        res += ft_putchar('0');
    if (d / 16)
        res += ft_putx(d / 16, padding);
    if (d % 16 >= 10)
        res += ft_putchar('a' + (d % 16) - 10);
    else
        res += ft_putchar(d % 16 + '0');
    return (res);
}

int ft_put_x(t_args *args, va_list   ap)
{
    int width;
    int precision;
    int len;
    int padding;
    int putlen;
    int res;
    int d;

    res = 0;
    d = va_arg(ap, int);
    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    len = ft_get_digits_x(d);
    if (args->has_precision && args->precision == 0 && d == 0)
        len = 0;
    padding = (len < precision) ? precision - len : 0;
    putlen = padding + len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    if (args->has_precision && args->precision == 0 && d == 0)
        return (res);
    return (res + ft_putx(d, padding));
}
