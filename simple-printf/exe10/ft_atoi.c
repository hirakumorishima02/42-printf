/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:03:24 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/03 14:03:44 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "header.h"

static  int ft_skip(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

int ft_atoi(char *s)
{
    long res;
    long max;
    int sign;

    res = 0;
    max = INT_MAX;
    sign = 1;
    while (ft_skip(*s))
        s++;
    if (*s == '-' || *s == '+')
    {
        sign = *s == '-' ? -1 : 1;
        s++;
    }
    while (ft_isdigit(*s))
    {
        if (res < max - (*s + '0') / 10)
            res = res * 10 + (*s - '0');
        else
            res = sign == -1 ? max + 1 : max;
        s++;
    }
    return (res * sign);
}
