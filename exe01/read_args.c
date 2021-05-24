/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:37:33 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/24 16:38:06 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	initialize_args(t_args	*args)
{
	args->c = 0;
	args->width = 0;
	args->has_width = 0;
	args->precision = 0;
	args->has_precision = 0;
}

char	*read_args(t_args *args, char *itr)
{
	if (!itr || *itr != '%')
		return (itr);
	itr++;
	while (*itr)
	{
		initialize_args(args);
		//width
		if (ft_isdigit(*itr))
		{
			args->has_width = 1;
			args->width = ft_atoi(itr);
			itr += ft_get_digits(args->width);
		}
		//.
		if (*itr == '.')
		{
			args->has_precision = 1;
			itr++;
		}
		//precision
		if (ft_isdigit(*itr))
		{
			args->has_precision = 1;
			args->precision = ft_atoi(itr);
			itr += ft_get_digits(args->precision);
		}
		//dxs
		if (ft_strchr(*itr, CONV))
		{
			args->c = *itr;
			itr++;
			return (itr);
		}
		itr++;
	}
	return (itr);
}