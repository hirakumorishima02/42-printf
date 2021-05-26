/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:16:36 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 15:36:55 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static  int ft_strlen(char *str)
{
    int res;

    res = 0;
    while (*str++)
        res++;
    return (res);
}

static  int ft_putstrl(char *s, int len)
{
    int res;
    int i;

    if (!s)
        return (0);
    res = 0;
    i = 0;
    while (s[i] && i < len)
    {
        res += ft_putchar(s[i]);
        i++;
    }
    return (res);
}

int ft_put_s(t_args *args, va_list  ap)
{
    int res;
    int width;
    int precision;
    int len;
    int putlen;
    char *s;

    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    s = va_arg(ap, char *);
    if (!s)
        s = "(null)";
    len = ft_strlen(s);
    if (args->has_precision)
        putlen = (len > precision) ? precision : len;
    else
        putlen = len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    return (res + ft_putstrl(s, putlen));
}