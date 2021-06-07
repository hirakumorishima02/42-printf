/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:02:12 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/03 14:06:57 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "header.h"

static char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

static  void initialize_args(t_args *args)
{
    args->width = 0;
    args->has_width = 0;
    args->precision = 0;
    args->has_precision = 0;
    args->c = 0;
}

char    *read_args(t_args *args, char   *itr)
{
    if (!itr || *itr != '%')
        return (itr);
    itr++;
    while (*itr)
    {
        initialize_args(args);
        if (ft_isdigit(*itr))
        {
            args->has_width = 1;
            args->width = ft_atoi(itr);
            itr += ft_get_digits(args->width);
        }
        if (*itr == '.')
        {
            args->has_precision = 1;
            itr++;
        }
        if (ft_isdigit(*itr))
        {
            args->precision = ft_atoi(itr);
            itr += ft_get_digits(args->precision);
        }
        if (ft_strchr(CONV, *itr))
        {
            args->c = *itr;
            itr++;
            return (itr);
        }
        itr++;
    }
    return (itr);
}
