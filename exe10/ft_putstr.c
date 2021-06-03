/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:58:48 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/03 13:59:10 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "header.h"

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
    int res;

    if (!s)
        return (0);
    res = 0;
    while (*s)
    {
        res += ft_putchar(*s);
        s++;
    }
    return (res);
}
