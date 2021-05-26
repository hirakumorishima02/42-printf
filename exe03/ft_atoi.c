/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:43:58 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 13:59:29 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int ft_isspace(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

int ft_atoi(char    *str)
{
    long    res;
    long    max;
    int     sign;

    res = 0;
    max = INT_MAX;
    while (ft_isspace(*str))
        str++;
    sign = 1;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign *= -1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        if (res < max - (*str - '0') / 10)
            res = res * 10 + (*str - '0');
        else
            res = (sign == -1) ? max + 1 : max;
        str++;
    }
    return (res * sign);
}