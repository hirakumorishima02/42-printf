/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:24:37 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/20 15:06:49 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdarg.h>

int	ft_printf(const char * restrict format, ...);
int	check_mfw(const char *str, int *mfw);
int	check_prec(const char *str, int *prec);
int	is_num(char c);
int	until_pct(const char *str);
int	ft_atoi(const char *str);
int conv(va_list ap, char c, int mfw, int prec);
int	conv_d(va_list ap, int mfw, int prec);
int	conv_x(va_list ap, int mfw, int prec);
int	conv_s(va_list ap, int mfw, int prec);
int	max(int a, int b);
int	min(int a, int b);
int	digits_d(int d);
int	digits_x(unsigned int d);
int	put_c_n(char c, int n);
void	put_nbr_d(int d);
void	put_nbr_x(unsigned int x);


#endif