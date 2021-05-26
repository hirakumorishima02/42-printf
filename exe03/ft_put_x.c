/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:59:28 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 15:35:38 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int  ft_get_digits_x(unsigned int x)
{
    int digits;

    digits = 0;
    while (x / 16)
    {
        digits++;
        x /= 16;
    }
    digits++;
    return (digits);
}

static int  ft_putx(unsigned int    x, int  padding)
{
    int res;

    res = 0;
    while (padding-- > 0)
        res += ft_putchar('0');
    if (x / 16)
        res += ft_putx(x / 16, padding);
    if (x % 16 < 10)
        res += ft_putchar((x % 16) + '0');
    else
        res += ft_putchar((x % 16) - 10 + 'a');
    return (res);
}

int ft_put_x(t_args *args, va_list  ap)
{
    int width;
    int precision;
    int len;
    int padding;
    int putlen;
    int res;
    int x;

    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    x = va_arg(ap, int);
    len = ft_get_digits_x(x);
    if (args->has_precision && args->precision == 0 && x == 0)
        len = 0;
    padding = (len < precision) ? precision - len : 0;
    putlen = padding + len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    if (args->has_precision && args->precision == 0 && x == 0)
        return (res);
    return (res + ft_putx(x, padding));
}