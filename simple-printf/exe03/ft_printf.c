/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:08:57 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 16:05:09 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_printf(const char * restrict format, ...)
{
    char    *itr;
    int     res;
    t_args  args;
    va_list ap;
    
    itr = (char *)format;
    if(!itr)
        return (0);
    res = 0;
    va_start(ap, format);
    while (*itr)
    {
        if (*itr == '%')
        {
            itr = ft_read_args(&args, itr);
            res += ft_put_conv(&args, ap);
            continue;
        }
        res += ft_putchar(*itr);
        itr++;
    }
    va_end(ap);
    return (res);
}
