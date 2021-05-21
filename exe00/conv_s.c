/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:10:12 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/20 14:19:25 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static size_t	ft_strlen(char	*s)
{
	char	*str;
	size_t		i;

	str = s;
	i = 0;
	while(str[i] != '\0')
		i++;
	return (i);
}

int	conv_s(va_list ap, int mfw, int prec)
{
	char	*s;
	int		r_num;

	s = va_arg(ap, char *);
	r_num = 0;
	if (prec == -1)
		prec = INT_MAX;
	if (s == 0)
	{
		r_num += put_c_n(' ', mfw - min(prec, 6));
		r_num += write(1, "(null)", min(prec, 6));
	}
	else
	{
		r_num += put_c_n(' ', mfw - min(prec, ft_strlen(s)));
		r_num += write(1, s, ft_strlen(s));
	}
	return (r_num);
}