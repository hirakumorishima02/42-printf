/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:36:38 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 14:39:16 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_put_conv(t_args    *args, va_list  ap)
{
    if (args->c == 'd')
        return (ft_put_d(args, ap));
    if (args->c == 'x')
        return (ft_put_x(args, ap));
    if (args->c == 's')
        return (ft_put_s(args, ap));
    return (0);
}
