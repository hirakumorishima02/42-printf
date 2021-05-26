/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:00:38 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 14:03:14 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_get_digits(int d)
{
    int digits;

    if (d == INT_MIN)
        return (0);
    digits = 0;
    if (d < 0)
    {
        digits++;
        d *= -1;
    }
    while (d / 10)
    {
        d /= 10;
        digits++;
    }
    digits++;
    return (digits);
}