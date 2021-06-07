/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:54:48 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 16:10:29 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_putstr(char *str)
{
    int res;

    res = 0;
    while (*str)
    {
        res += ft_putchar(*str);
        str++;
    }
    return (res);
}