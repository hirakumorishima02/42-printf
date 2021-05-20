/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:25:59 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/20 14:22:13 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_printf(const char * format, ...)
{
	int	r_num;
	int	index;
	int	mfw;
	int	prec;
	int	tmp;
	va_list	ap;

	r_num = 0;
	index = 0;
	mfw = 0;
	prec = -1;
	tmp = 0;
	va_start(ap, format);
	while (1)
	{
		tmp = until_pct(&(format[index]));
		index += tmp;
		r_num += tmp;
		if (format[index] != '%')
			break;
		index++;
		index += check_mfw(&(format[index]), &mfw);
		index += check_prec(&(format[index]), &prec);
		r_num += conv(ap, format[index], mfw, prec);
		index++;
	}
	va_end(ap);
	return (r_num);
}