/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:04:22 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/03 14:04:35 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "header.h"

int ft_get_digits(int   d)
{
    int digits;

    digits = 0;
    if (d == INT_MIN)
        return (11);
    if (d < 0)
    {
        digits++;
        d *= -1;
    }
    while (d / 10)
    {
        digits++;
        d /= 10;
    }
    digits++;
    return (digits);
}
