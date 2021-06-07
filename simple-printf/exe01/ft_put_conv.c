/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:39:33 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/24 16:39:47 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_put_conv(t_args *args, va_list ap)
{
	if (args->c == 'd')
		return ft_put_d(args, ap);
	if (args->c == 'x')
		return ft_put_x(args, ap);
	else if (args->c == 's')
		return ft_put_s(args, ap);
	return (0);
}
