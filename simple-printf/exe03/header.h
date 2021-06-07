/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:15:37 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 15:41:15 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H_
# define HEADER_H_

#define CONV "dxs"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

typedef struct  s_args
{
    int c;
    int width;
    int has_width;
    int precision;
    int has_precision;
}               t_args;

int ft_isdigit(char  c);
int ft_atoi(char    *str);
int ft_get_digits(int d);
int ft_putchar(char c);
int ft_putstr(char *str);
int ft_put_d(t_args *args, va_list  ap);
int ft_put_x(t_args *args, va_list  ap);
int ft_put_s(t_args *args, va_list  ap);
int ft_put_conv(t_args    *args, va_list  ap);
int ft_printf(const char * restrict format, ...);
char    *ft_read_args(t_args *args, char *itr);
char *ft_strchr(char  c, char *str);

#endif