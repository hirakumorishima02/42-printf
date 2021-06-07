/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:09:05 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/26 14:18:10 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *ft_strchr(char  c, char *str)
{
    if (!str)
        return (NULL);
    while (*str)
    {
        if (*str == c)
            return (str);
        str++;
    }
    return (NULL);
}