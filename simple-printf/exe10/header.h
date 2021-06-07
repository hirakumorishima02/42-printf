/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:56:56 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/03 14:15:36 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define CONV "dxs"

typedef struct s_args
{
    int width;
    int precision;
    int has_width;
    int has_precision;
    int c;
}               t_args;

int ft_putchar(char c);
int ft_putstr(char *s);
int ft_put_s(t_args *args, va_list   ap);
int ft_isdigit(char c);
int ft_atoi(char *s);
int ft_get_digits(int   d);
int ft_put_x(t_args *args, va_list   ap);
int ft_put_d(t_args *args, va_list   ap);
int ft_put_s(t_args *args, va_list   ap);
int ft_printf(const char * restrict format, ...);
char    *read_args(t_args *args, char   *itr);

#endif