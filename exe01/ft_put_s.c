/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:43:19 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/24 16:43:33 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_put_s(t_args *args, va_list ap)
{
	int		res;
	int		width;
	int		precision;
	int		len;
	int		putlen;
	char	*s;

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