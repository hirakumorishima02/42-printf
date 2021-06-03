/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:09:23 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/03 14:09:39 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "header.h"

static int ft_put_conv(t_args *args, va_list   ap)
{
    if (args->c == 'd')
        return (ft_put_d(args, ap));
    if (args->c == 'x')
        return (ft_put_x(args, ap));
    if (args->c == 's')
        return (ft_put_s(args, ap));
    return (0);
}

int ft_printf(const char * restrict format, ...)
{
    int res;
    char    *itr;
    va_list ap;
    t_args  args;

    va_start(ap, format);
    itr = (char *)format;
    res = 0;
    while (*itr)
    {
        if (*itr == '%')
        {
            itr = read_args(&args, itr);
            res += ft_put_conv(&args, ap);
            continue;
        }
        res += ft_putchar(*itr);
        itr++;
    }
    return (res);
}
