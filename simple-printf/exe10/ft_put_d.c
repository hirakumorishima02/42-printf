/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:07:17 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/03 14:07:52 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "header.h"

static  int ft_puti(int d, int  padding)
{
    int res;

    res = 0;
    if (d == INT_MIN)
    {
        res += ft_putchar('-');
        while (padding-- > 0)
            res += ft_putchar('0');
        res += ft_putstr("2147483648");
        return (res);
    }
    if (d < 0)
    {
        res += ft_putchar('-');
        d *= -1;
    }
    while (padding-- > 0)
        res += ft_putchar('0');
    if (d / 10)
        res += ft_puti(d / 10, padding);
    res += ft_putchar(d % 10 + '0');
    return (res);
}

int ft_put_d(t_args *args, va_list   ap)
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
    len = ft_get_digits(d);
    if (args->has_precision && args->precision == 0 && d == 0)
        len = 0;
    if (d < 0)
        padding = ((len - 1) < precision) ? precision - (len - 1) : 0;
    else
        padding = (len < precision) ? precision - len : 0;
    putlen = padding + len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    if (args->has_precision && args->precision == 0 && d == 0)
        return (res);
    return (res + ft_puti(d, padding));
}
