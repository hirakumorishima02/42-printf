/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 08:43:15 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/07 11:52:37 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_params
{
    int s_flag;
    int z_flag;
    int printed;
    int width;
    int precision;
    int *ptr;
    char    *intpart;
    char    *decpart;
    int plflag;
    int spflag;
    int tagflag;
    va_list arg;
}               t_params;

t_params    *g_ret;

size_t  ft_strlen(const char *s)
{
    int res;

    res = 0;
    while (*s++)
        res++;
    return (res);
}

int		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int     ft_putstr_fd(char   *s, int len, int    fd)
{
    int i;

    i = 0;
    if (!s || !len)
        reutrn (i);
    if (len < 0)
    {
        while (s[i])
        {
            write (fd, &s[i], 1);
            i++;
        }
    }
    else
    {
        while ((len > 0) && s[i])
        {
            write (fd, &s[i], 1);
            i++;
            len--;
        }
    }
    return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;
	int	c;

	if (!dest || !src)
		return (0);
	i = 0;
	c = 0;
	while (src[i] != '\0')
		dest[i++] = src[c++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = malloc(ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}

void    ft_initgret(void)
{
    g_ret->s_flag = 0;
    g_ret->z_flag = 0;
    g_ret->printed = 0;
    g_ret->width = 0;
    g_ret->precision = -1;
    g_ret->ptr = 0;
    g_ret->intpart = 0;
    g_ret->decpart = 0;
    g_ret->plflag = 0;
    g_ret->tagflag = 0;
    g_ret->spflag = 0;
}

void    ft_bonusflag(char   **itr)
{
    if (**itr == '+')
    {
        g_ret->plflag = 1;
        (*itr)++;
    }
    else if (**itr == ' ')
    {
        g_ret->spflag = 1;
        (*itr)++;
    }
    else if (**itr == '#')
    {
        g_ret->tagflag = 1;
        (*itr)++;
    }
}

int ft_skip(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

int ft_atoi(char    *d)
{
    long    res;
    long    max;
    int     sign;

    res = 0;
    sign = 1;
    max = INT_MAX;
    while (ft_skip(*d))
        d++;
    if (*d == '-' || *d == '+')
    {
        sign = (*d == '-') ? -1 : 1;
        d++;
    }
    while (ft_isdigit(*d))
    {
        if (res < max - (*d - '0') / 10)
            res = res * 10 + (*d - '0');
        else
            res = (sign == -1) ? max + 1 : max;
        d++;
    }
    return (res);
}

int ft_intlen(int   d)
{
    int digits;

    digits = 0;
    while (d / 10)
    {
        d /= 10;
        digits++;
    }
    digits++;
    return (digits);
}

void    ft_readwidth(char **itr)
{
    int len;
    
    len = 0;
    if (**itr == '*')
    {
        if ((g_ret->width = va_arg(g_ret->arg, int)) < 0)
        {
            g_ret->width = -g_ret->width;
            g_ret->s_flag = 1;
            g_ret->z_flag = 0;
        }
        (*itr)++;
        return ;
    }
    while (**itr == '0')
        (*itr)++;
    if ((**itr >= '0') && (**itr <= '9'))
    {
        g_ret->width = ft_atoi(*itr);
        len = ft_intlen(g_ret->width);
        *itr += len;
        return ;
    }
    g_ret->width = 0;
}

void    ft_readflags(char **itr)
{
    ft_bonusflag(itr);
    if (**itr == '-')
    {
        g_ret->s_flag = 1;
        (*itr)++;
        if (**itr == '0')
            (*itr)++;
        ft_bonusflag(itr);
        return ;
    }
    else if (**itr == '0')
    {
        while (**itr == '0')
            (*itr)++;
        ft_bonusflag(itr);
        g_ret->z_flag = 1;
        if (**itr == '-')
        {
            g_ret->s_flag = 1;
            g_ret->z_flag = 0;
            (*itr)++;
        }
        ft_bonusflag(itr);
        return ;
    }
}

void    ft_readprec(char    **itr)
{
    int len;

    len = 0;
    if (**itr == '.')
    {
        (*itr)++;
        if (**itr == '*')
        {
            if ((g_ret->precision = va_arg(g_ret->arg, int)) < 0)
                g_ret->precision = -g_ret->precision;
                (*itr)++;
                return ;
        }
        while (**itr == '0')
            (*itr)++;
        g_ret->precision = ft_atoi(*itr);
        len = ft_intlen(g_ret->precision);
        if (g_ret->precision != 0)
            *itr += len;
    }
    else g_ret->precision = -1;
}

void    ft_pad(int  len)
{
    if (g_ret->z_flag)
    {
        while ((g_ret->width--) - len > 0)
            g_ret->printed += ft_putchar_fd('0', 1);
    }
    else
    {
        while ((g_ret->width--) - len > 0)
            g_ret->printed += ft_putchar_fd(' ', 1);
    }
}

void    ft_xcent(void)
{
    if (g_ret->sflag)
    {
        g_ret->printed += ft_putchar_fd('%', 1);
        g_ret->width--;
        ft_pad(0);
        return ;
    }
    else if (g_ret->zflag && g_ret->width--)
    {
        while (g_ret->width--)
            g_ret->printed += ft_putchar_fd('0', 1);
        g_ret->printed += ft_putchar_fd('%', 1);
        return ;
    }
    else if (g_ret->width--)
    {
        ft_pad(0);
        g_ret->printed += ft_putchar_fd('%', 1);
        return ;
    }
    g_ret->printed += ft_putchar_fd('%', 1);
}

int     ft_min(int  offset)
{
    if (offset < g_ret->precision)
        return (offset);
    else
        return (g_ret->precision);
}

int     ft_max(int  offset)
{
    if (offset > g_ret->precision)
        return (offset);
    else
        return (g_ret->precision);
}

void    ft_convstring(char  *str)
{
    int offset;
    int h;

    if (!str)
        str = "(null)";
    offset = ft_strlen(str);
    h = g_ret->precision - offset;
    if (g_ret->s_flag)
    {
        h = ft_putstr_fd(str, g_ret->precision, 1);
        g_ret->printed += h;
        ft_pad(h);
        return ;
    }
    else if ((g_ret->width) && g_ret->precision != -1)
    {
        ft_pad(ft_min(offset));
        g_ret->printed += ft_putstr_fd(str, g_ret->precision, 1);
        return ;
    }
    else if (g_ret->width)
        ft_pad(offset);
    g_ret->printed += ft_putstr_fd(str, g_ret->precision, 1);
}

void    ft_convchar(void)
{
    if (g_ret->s_flag)
    {
        g_ret->printed += ft_putchar_fd((char)va_arg(g_ret->arg, int), 1);
        g_ret->width--;
        ft_pad(0);
        return ;
    }
    else if (g_ret->width--)
    {
        ft_pad(0);
        g_ret->printed += ft_putchar_fd((char)va_arg(g_ret->arg, int), 1);
        return ;
    }
    g_ret->printed += ft_putchar_fd((char)va_arg(g_ret->arg, int), 1);
}

void    ft_clearflag(char   type, int   *offset)
{
    if (type == 'u')
    {
        g_ret->tagflag = 0;
        g_ret->plflag = 0;
        g_ret->spflag = 0;
    }
    else
    {
        g_ret->plflag = 0;
        g_ret->spflag = 0;
    }
    if ((g_ret->tagflag) && g_ret->precision < 0))
        *offset += 2;
}

int     ft_dobonflag(int h, char    type, char *data)
{
    if ((g_ret->plflag) && (!(*data) || (*data != '-')))
    {
        h += ft_putchar_fd('+', 1);
        g_ret->width--;
    }
    else if (g_ret->spflag)
    {
        h += ft_putchar_fd(' ', 1);
        g_ret->width--;
    }
    else if ((g_ret->tagflag) && ((type == 'x') || (type == 'X')))
    {
        if ((type == 'x') && (*data != '0'))
            h += ft_putstr_fd("0x", -1, 1);
        else if ((type == 'X') && *data != '0')
            h += ft_putstr_fd("0X", -1 , 1);
        g_ret->width -= 2;
    }
    return (h);
}

int     ft_zeroprec(char    *data)
{
    if ((g_ret->precision == 0) && (*data == '0'))
    {
        g_ret->z_flag = 0;
        if (g_ret->plflag || g_ret->spflag)
            g_ret->width--;
        ft_pad(0);
        g_ret->printed += ft_dobonflag(0, 'z', data);
        return (1);
    }
    return (0);
}

int     ft_free(char    *data, int  sign)
{
    if (!sign)
        free(data);
    else
        free(data - 1);
}

void    ft_intsflag(char    *data, int  offset, char    type)
{
    int h;
    int sign;

    h = 0;
    sign = 0;
    if (ft_zeroprec(data))
        return ;
    if (*data == '-')
    {
        g_ret->printed += ft_putchar_fd(*(data++), 1);
        sign = 1;
        g_ret->width--;
        offset--;
    }
    else
        g_ret->printed += ft_dobonflag(0, type, data);
    if (!(g_ret->precision == 0 && (*data == '0')))
    {
        while ((g_ret=>precision--) - offset > 0)
            h += ft_putchar_fd('0', 1);
        h += ft_putchar_fd(data, -1 , 1);
    }
    ft_pad(h);
    g_ret->printed += h;
    ft_free(data, sign);
}

void    ft_intzflag(char    *data, int  offset, char    type)
{
    int     sign;
    
    sign = 0;
    if (ft_zeroprec(data))
        return ;
    if (*data == '-')
        g_ret->precision++;
    while ((g_ret->precision > 0) && (g_ret->width--) - ft_max(offset) > 0)
        g_ret->printed += ft_putchar_fd(' ', 1);
    if (*data == '-')
    {
        g_ret->printed += ft_putchar_fd(*(data++), 1);
        g_ret->precision--;
        sign = 1;
    }
    else
        g_ret->printed += ft_dobonflag(0, type, data);
    while ((g_ret->precision < 0) && (g_ret->width--) - ft_max(offset) > 0)
        g_ret->printed += ft_putchar_fd('0', 1);
    while ((g_ret->precision--) - (offset - sign) > 0)
        g_ret->printed += ft_putchar_fd('0', 1);
    g_ret->printed += ft_putstr_fd(data, -1, 1);
    ft_free(data, sign);
}

void    ft_convint(char *data, char type)
{
    int     offset;

    offset = ft_strlen(data);
    if (type == 'x' || type == 'X' || type == 'u')
        ft_clearflag(type, &offset);
    if (g_ret->s_flag)
        ft_intsflag(data, offset, type);
    else if (g_ret->z_flag)
        ft_intzflag(data, offset, type);
    else if ((g_ret->width > g_ret->precision) && g_ret->precision >= 0)
        ft_ownidprec(data, offset, type);
    else if (g_ret->width && g_ret->precision == -1)
    {
        ft_pad(offset);
        g_ret->printed += ft_dobonflag(0, type, data);
        g_ret->printed += ft_putstr_fd(data, -1, 1);
    }
    else if (g_ret->precision > 0)
        ft_prechandle(data, offset, type);
    else if (!(g_ret->precision == 0 && *data == '0'))
    {
        g_ret->printed += ft_dobonflag(0, type, data);
        g_ret->printed += ft_putstr_fd(data, g_ret->precision - 1, 1);
    }
}

int     ft_start_conv(char  **itr)
{
    if (**itr == '%')
        ft_xcent();
    else if (**itr == 's')
        ft_convstring(va_arg(g_ret->arg, char *));
    else if (**itr == 'c')
        ft_convchar();
    else if ((**itr == 'd' || **itr == 'i'))
        ft_convint(ft_itoa(va_arg(g_ret->arg, int)), 'd');
    else if ((**itr == 'u') || (**itr == 'x') || (**itr == 'X'))
    {
        if (**itr == 'X')
            ft_convint(ft_stoa_b(va_arg(g_ret->arg, unsigned int), 'H'), 'X');
        else if (**itr == 'x')
            ft_convint(ft_stoa_b(va_arg(g_ret->arg, unsigned int), 'h'), 'x');
        else
            ft_convint(ft_stoa_b(va_arg(g_ret->arg, unsigned int), 'd'), 'd');
    }
    else if (**itr == 'p')
        ft_convadrr(ft_stoa_b(va_arg(g_ret->arg, size_t), 'h'));
    else if (**itr == 'n' || **itr == 'f')
        ft_bonus(itr);
    else
        return (g_ret->printed = -1);
    return (g_ret->printed);
}

int ft_start_read(const char    *str)
{
    char    *itr;

    itr = ft_strdup(str);
    g_ret->printed = 0;
    while (*itr)
    {
        if (*itr == '%' && *(itr + 1))
        {
            itr++;
            ft_readflags(&itr);
            ft_readwidth(&itr);
            ft_readprec(&itr);
            if (ft_start_conv(*itr) == -1)
            {
                g_ret->printed = 0;
                return (g_ret->printed);
            }
            itr++;
        }
        else
            g_ret->printed += ft_putchar_fd(*itr++, 1);
    }
    free (itr - ft_strlen(str));
    return (g_ret->printed);
}

int ft_printf(const char *format, ...)
{
    if (!format)
        return (0);
    g_ret = malloc(sizeof(t_params));
    ft_initgret();
    va_start(g_ret->arg, format);
    ft_start_read(format);
    return (0);
}

int main(void)
{
    printf("%d\n", ft_atoi("-2147483648"));
    printf("%d\n", ft_atoi("   +483648"));
    printf("%d\n", ft_atoi(" 483648"));
    return (0);
}