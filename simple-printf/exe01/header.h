/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:31:27 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/24 17:04:57 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#define CONV "dxs"

typedef	struct s_args
{
	int	c;
	int	width;
	int	has_width;
	int	precision;
	int	has_precision;
}				t_args;

int		ft_strlen(char *s);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_isdigit(char c);
int		ft_atoi(char *str);
int		ft_putstrl(char *str, int putlen);
int		ft_put_conv(t_args *args, va_list ap);
int		ft_put_s(t_args *args, va_list ap);
int		ft_put_d(t_args *args, va_list ap);
int		ft_put_x(t_args *args, va_list ap);
int		ft_get_digits(int	d);
char	*ft_strchr(char c, char *str);
char	*read_args(t_args *args, char *itr);

#endif