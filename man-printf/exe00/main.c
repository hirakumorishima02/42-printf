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

#define BASE_10 "0123456789"
#define BASE_16 "0123456789abcdef"
#define BASE_16B "0123456789ABCDEF"
#define BASE_8 "01234567"

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

void    ft_bzero(char   *str, unsigned int n)
{
    unsigned int i;
    char *ptr;

    i = 0;
    ptr = str;
    while (i < n)
    {
        ptr[i] = 0;
        i++;
    }
}

char    *ft_calloc(size_t   num, size_t size)
{
    void    *res;

    if (!(res = malloc(num * size)))
        return (0);
    ft_bzero(res, num * size);
    return (res);
}

int ft_putfloat_fd(char *s, int len, int    fd)
{
    int i;

    i = 0;
    if (!s || !len)
        return (i);
    if (len == -1)
        len = 7;
    while (s[i] && (len >= 0))
    {
        write(fd, &s[i], 1);
        i++;
        len--;
    }
    while (len-- >= 0)
        write(fd, "0", 1);
    return (i);
}

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
        return (i);
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
    if (g_ret->s_flag)
    {
        g_ret->printed += ft_putchar_fd('%', 1);
        g_ret->width--;
        ft_pad(0);
        return ;
    }
    else if (g_ret->z_flag && g_ret->width--)
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
    if ((g_ret->tagflag) && g_ret->precision < 0)
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

void     ft_free(char    *data, int  sign)
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
        while ((g_ret->precision--) - offset > 0)
            h += ft_putchar_fd('0', 1);
        h += ft_putstr_fd(data, -1 , 1);
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

void    ft_onwidprec(char   *data, int  offset, char    type)
{
    int sign;

    sign = 0;
    if (ft_zeroprec(data))
        return ;
    else
    {
        if (*data == '-')
        {
            g_ret->width--;
            offset--;
            sign = 1;
        }
        else
            g_ret->printed += ft_dobonflag(0, type, data);
        ft_pad(ft_max(offset));
        if (*data == '-')
            g_ret->printed += ft_putchar_fd(*(data++), 1);
        while ((g_ret->precision--) - offset > 0)
            g_ret->printed += ft_putchar_fd('0', 1);
        g_ret->printed += ft_putstr_fd(data, -1, 1);
    }
    ft_free(data, sign);
}

void    ft_prechandle(char  *data, int  offset, char    type)
{
    int sign;

    sign = 0;
    if (ft_zeroprec(data))
        return ;
    if (*data == '-')
    {
        offset--;
        sign = 1;
        g_ret->printed += ft_putchar_fd(*(data++), 1);
    }
    else
        g_ret->printed += ft_dobonflag(0, type, data);
    while (g_ret->precision-- > offset)
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
        ft_onwidprec(data, offset, type);
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

int		len_num(int n)
{
	int cifre;

	cifre = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		cifre++;
		n /= 10;
	}
	return (cifre);
}

char	*ft_itoa(int n)
{
	int					cifre;
	char				*ret;
	unsigned int		u_n;

	cifre = len_num(n);
	if (n < 0)
	{
		u_n = -(unsigned int)n;
		cifre++;
	}
	else
		u_n = n;
	if (!(ret = (char*)malloc(cifre + 1)))
		return (0);
	ret[cifre] = 0;
	if (n < 0)
		ret[0] = '-';
	ret[--cifre] = (u_n % 10) + '0';
	while (u_n /= 10)
		ret[--cifre] = (u_n % 10) + '0';
	return (ret);
}

char    *ft_givebase(char   flag)
{
    if (flag == 'd')
        return (BASE_10);
    if (flag == 'h')
        return (BASE_16);
    if (flag == 'H')
        return (BASE_16B);
    if (flag == 'o')
        return (BASE_8);
    else
        return (0);
}

int nlen(size_t n , int base)
{
    return ((n == 0) ? 0 : 1 + nlen(n / base, base));
}

char    *ft_stoa_b(size_t n, char   flag)
{
    char    *base;
    char    *out;
    size_t  ncpy;
    int     lenbase;
    int     len;

    if (!(base = ft_givebase(flag)))
        return (0);
    lenbase = ft_strlen(base);
    len = 1 + nlen(n / lenbase, lenbase);
    out = 0;
    ncpy = n;
    if (!(out = ft_calloc(len + 1, sizeof(char))))
        return (0);
    out[len] = 0;
    while (ncpy)
    {
        out[--len] = base[ncpy % lenbase];
        ncpy /= lenbase;
    }
    if (!out[0])
        out[0] = '0';
    return (out);
}

void    ft_adrzflag(char    *data, int  len)
{
    if (*data == '0' && g_ret->precision == 0)
        len = 0;
    ft_pad(len + 2);
    g_ret->printed += ft_putstr_fd("0x", -1, 1);
    if (*data == '0' && g_ret->precision == 0 && len == 0)
        return ;
    while ((g_ret->precision--) - len > 0)
        g_ret->printed += ft_putchar_fd('0', 1);
    if (!(*data == '0' && len == 1 && g_ret->precision != 0))
        g_ret->printed += ft_putstr_fd(data, -1, 1);
    if (*data == '0' && len == 1)
    {
        while ((g_ret->precision--) > 0)
            g_ret->printed += ft_putchar_fd('0', 1);
        if (g_ret->precision < -1)
            g_ret->printed += ft_putchar_fd('0', 1);
    }
}

void    ft_convadrr(char    *data)
{
    int h;
    int len;


    len = ft_strlen(data);
    if (g_ret->s_flag)
    {
        h = ft_putstr_fd("0x", -1, 1);
        h += ft_putstr_fd(data, -1, 1);
        ft_pad(h);
        g_ret->printed += h;
    }
    else
        ft_adrzflag(data, len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (!src)
		return (0);
	if (size > 0)
	{
		while (src[i] && (i < size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		i = 0;
	}
	while (src[i])
		i++;
	return (i);
}

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;

	i = 0;
	while (*dest && i < size)
	{
		i++;
		dest++;
	}
	while (*src && i + 1 < size)
	{
		*dest++ = *src++;
		i++;
	}
	if (i < size)
		*dest = 0;
	while (*src++)
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(ret = malloc(len)))
		return (0);
	ft_strlcpy(ret, s1, len);
	ft_strlcat(ret, s2, len);
	return (ret);
}

int ft_arrotondo(int    len)
{
    int i;
    char    *check;

    i = g_ret->precision;
    check = !i ? "C" : 0;
    if (g_ret->decpart[i + 1] >= '5')
    {
        while (((!check) && (g_ret->decpart[i] = (g_ret->decpart[i] - '0' + 1) % 10 + '0') == '0'))
            if (g_ret->decpart[--i] == '.')
                check = "C";
        if (check)
        {
            while (((--len >= 0) && (g_ret->intpart[len] = (g_ret->intpart[len] - '0' + 1) % 10 + '0') == '0'));
            if (len < 0)
            {
                check = ft_strjoin("1", g_ret->intpart);
                free(g_ret->intpart);
                g_ret->intpart = check;
            }
        }
    }
    return (1);
}

void    ft_flosflag(int intlen)
{
    int h;
    int sign;

    sign = 0;
    h = 0;
    if (*(g_ret->intpart) == '-')
    {
        g_ret->printed += ft_putchar_fd(*(g_ret->intpart++), 1);
        sign = 1;
        g_ret->width--;
        intlen--;
    }
    else
        h += ft_dobonflag(h, 'z', g_ret->intpart);
    h += ft_putstr_fd(g_ret->intpart, -1, 1);
    if (!(g_ret->precision == 0 && (*(g_ret->intpart) = '0')))
        h += ft_putfloat_fd(g_ret->decpart, g_ret->precision, 1);
    (g_ret->precision > 0) ? g_ret->width-- : sign * 1;
    (g_ret->plflag || g_ret->spflag) ? g_ret->width++ : sign * 1;
    ft_pad(h);
    g_ret->printed += h;
    ft_free(g_ret->intpart, sign);
    free(g_ret->decpart);
}

void    ft_flozflag(int intlen, int offset)
{
    int sign;

    sign = 0;
    if (*(g_ret->intpart) == '-')
        g_ret->precision++;
    g_ret->printed = ft_dobonflag(0, 'z', g_ret->intpart);
    (g_ret->precision > 0) ? g_ret->width-- : sign * 1;
    while ((g_ret->precision > 0) && ((g_ret->width--) - ft_max(ft_min(offset) + intlen > 0)))
        g_ret->printed += ft_putchar_fd('0', 1);
    if (*(g_ret->intpart) == '-')
    {
        g_ret->printed += ft_putchar_fd(*(g_ret->intpart++), 1);
        g_ret->precision--;
        sign = 1;
    }
    while ((g_ret->precision < 0) && ((g_ret->width--) - ft_max(offset + intlen) > 0))
        g_ret->printed += ft_putchar_fd('0', 1);
    g_ret->printed += ft_putstr_fd(g_ret->intpart, -1, 1);
    if (g_ret->precision == -1)
        g_ret->precision = 6;
    g_ret->printed += ft_putfloat_fd(g_ret->decpart, g_ret->precision, 1);
    ft_free(g_ret->intpart, sign);
    free(g_ret->decpart);
}

void    ft_flwidprec(int    intlen, int offset)
{
    int sign;

    sign = 0;
    if ((g_ret->precision == 0) && ((*(g_ret->intpart) == '0') && (g_ret->width)))
        ft_pad(0);
    else
    {
        if (*(g_ret->intpart) == '-')
        {
            g_ret->width--;
            intlen--;
            sign = 1;
        }
        (g_ret->precision > 0) ? g_ret->width-- : sign * 1;
        (g_ret->plflag || g_ret->spflag) ? g_ret->width-- : sign * 1;
        ft_pad(ft_max(ft_min(offset) + intlen));
        g_ret->printed += ft_dobonflag(0, 'z', g_ret->intpart);
        if (*(g_ret->intpart) == '-')
            g_ret->printed += ft_putchar_fd(*(g_ret->intpart++), 1);
        g_ret->printed += ft_putstr_fd(g_ret->intpart, -1, 1);
        g_ret->printed += ft_putfloat_fd(g_ret->decpart, g_ret->precision, 1);
    }
    ft_free(g_ret->intpart, sign);
    free(g_ret->decpart);
}

void    ft_floatprec(int    intlen)
{
    int sign;

    sign = 0;
    if (*(g_ret->intpart) == '-')
    {
        intlen--;
        sign = 1;
        g_ret->printed += ft_putchar_fd(*(g_ret->intpart++), 1);
    }
    else
        g_ret->printed += ft_dobonflag(0, 'z', g_ret->intpart);
    g_ret->printed += ft_putstr_fd(g_ret->intpart, -1, 1);
    g_ret->printed += ft_putfloat_fd(g_ret->decpart, g_ret->precision, 1);
    ft_free(g_ret->intpart, sign);
    free(g_ret->decpart);
}

void    ft_floatconv(int    intlen)
{
    int offset;

    if (ft_arrotondo(intlen) && !intlen)
        return ;
    offset = ft_strlen(g_ret->decpart);
    if (g_ret->s_flag)
        ft_flosflag(intlen);
    else if (g_ret->z_flag)
        ft_flozflag(intlen, offset);
    else if((g_ret->width > g_ret->precision) && g_ret->precision >= 0)
        ft_flwidprec(intlen, offset);
    else if (g_ret->width && g_ret->precision == -1)
    {
        ft_pad(offset + intlen);
        g_ret->printed += ft_putstr_fd(g_ret->intpart, -1, 1);
        g_ret->printed += ft_putfloat_fd(g_ret->decpart, 6, 1);
    }
    else if (g_ret->precision > 0)
        ft_floatprec(intlen);
    else if (g_ret->precision == 0)
        g_ret->printed += ft_putstr_fd(g_ret->intpart, g_ret->precision - 1, 1);
    if (g_ret->precision < 0)
        g_ret->printed += ft_putstr_fd(g_ret->intpart, g_ret->precision - 1, 1);
    if (g_ret->precision < 0)
        g_ret->printed += ft_putfloat_fd(g_ret->decpart, 6, 1);
}

void    ft_ntype(int    *num)
{
    num = g_ret->ptr;
}

double  gestsign(double num, char *ret)
{
    if (num < 0)
    {
        ret[0] = '-';
        return (-num);
    }
    return (num);
}

int ft_dtoa(double num, char **intpart, char **decpart)
{
    char    ret[2];
    int     i;
    double  f;
    int     x;

    if (!num)
    {
        *intpart = 0;
        *decpart = 0;
        return (0);
    }
    f = gestsign(num, ret);
    *intpart = ft_stoa_b(f, 'd');
    i = ft_strlen(*intpart);
    f *= 10000000000000000;
    *decpart = ft_stoa_b(f, 'd');
    *decpart = ft_strjoin(".", *decpart + i);
    x = ft_strlen(*decpart);
    while (*((*decpart) + x - 1) == '0')
        *(*decpart + x--) = 0;
    *intpart = ft_strjoin(ret, *intpart);
    return (i);

}

void    ft_bonus(char   **cpy)
{
    if (**cpy == 'n')
        ft_ntype(va_arg(g_ret->arg, int*));
    else if (**cpy == 'f')
        ft_floatconv(ft_dtoa(va_arg(g_ret->arg, double), &(g_ret->intpart), &(g_ret->decpart)));
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
            if (ft_start_conv(&itr) == -1)
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

int	main(void)
{
	printf("p0 % .3s\n", "cccc");
	ft_printf("p0 % .3s\n", "cccc");
	printf("pp %.50d\n", 10000);
	ft_printf("pp %.50d\n", 10000);
	printf("p1 %.4s\n", "cccc");
	ft_printf("p1 %.4s\n", "cccc");
	printf("p2 %.10s\n", "cccc");
	ft_printf("p2 %.10s\n", "cccc");
	printf("p3 %.4s\n", NULL);
	ft_printf("p3 %.4s\n", NULL);
	printf("p4 %.5s\n", "aaaaa");
	ft_printf("p4 %.5s\n", "aaaaa");
	printf("p5 %.3d\n", 100);
	ft_printf("p5 %.3d\n", 100);
	printf("p6 %.0d\n", 100);
	ft_printf("p6 %.0d\n", 100);
	printf("p7 %.4d\n", 100);
	ft_printf("p7 %.4d\n", 100);
	printf("p8 %.10d\n", 100);
	ft_printf("p8 %.10d\n", 100);
	printf("p9 %.50d\n", 100);
	ft_printf("p9 %.50d\n", 100);
	printf("p10 %.1d\n", 100);
	ft_printf("p10 %.1d\n", 100);
	printf("p11 %.3d\n", 100);
	ft_printf("p11 %.3d\n", 100);
	printf("p12 %.0d\n", 0);
	ft_printf("p12 %.0d\n", 0);
	printf("p19 %.3x\n", 100);
	ft_printf("p19 %.3x\n", 100);
	printf("p20 %.0x\n", 0);
	ft_printf("p20 %.0x\n", 0);
	printf("p21 %.3x\n", 100);
	ft_printf("p21 %.3x\n", 100);
	printf("p22 %.0x\n", 100);
	ft_printf("p22 %.0x\n", 100);
	printf("p23 %.4x\n", 100);
	ft_printf("p23 %.4x\n", 100);
	printf("p24 %.10x\n", 100);
	ft_printf("p24 %.10x\n", 100);
	printf("p25 %.50x\n", 100);
	ft_printf("p25 %.50x\n", 100);
	printf("p26 %.1x\n", 100);
	ft_printf("p26 %.1x\n", 100);
	printf("p27 %.3x\n", 100);
	ft_printf("p27 %.3x\n", 100);
	printf("p28 %.0x\n", 0);
	ft_printf("p28 %.0x\n", 0);
	printf("p30 Hello 42 school! %s\n", NULL);
	ft_printf("p30 Hello 42 school! %s\n", NULL);
	printf("p32 %d\n", 2147483647);
	ft_printf("p32 %d\n", 2147483647);
	printf("p33 %d\n", -2147483648);
	ft_printf("p33 %d\n", -2147483648);
	printf("p34 %x\n", 2147483647);
	ft_printf("p34 %x\n", 2147483647);
	printf("p35 %x\n", -2147483648);
	ft_printf("p35 %x\n", -2147483648);
	printf("p36 %X\n", 2147483647);
	ft_printf("p36 %X\n", 2147483647);
	printf("p37 %X\n", -2147483648);
	ft_printf("p37 %X\n", -2147483648);
	printf("p38 %x\n", 0);
	ft_printf("p38 %x\n", 0);
	printf("p39 %010x\n", 0);
	ft_printf("p39 %010x\n", 0);
	printf("p40 %010x\n", 20);
	ft_printf("p40 %010x\n", 20);
	printf("p41 %010x\n", -20);
	ft_printf("p41 %010x\n", -20);
	printf("p42 %10x\n", 20);
	ft_printf("p42 %10x\n", 20);
	printf("p43 %10.2x\n", -20);
	ft_printf("p43 %10.2x\n", -20);
	printf("p44 %-10x\n", 50);
	ft_printf("p44 %-10x\n", 50);
	printf("p45 %-15x\n", 0);
	ft_printf("p45 %-15x\n", 0);
	printf("p46 %.1x\n", 500);
	ft_printf("p46 %.1x\n", 500);
	printf("p47 %*.*x\n", 50, 10, 2);
	ft_printf("p47 %*.*x\n", 50, 10, 2);
	printf("p48 %x\n", -1);
	ft_printf("p48 %x\n", -1);
	printf("p49 %\n");
	ft_printf("p49 %\n");
	printf("p50 %40.50d\n", 50);
	ft_printf("p50 %40.50d\n", 50);
    printf("p51 %d\n", -589);
    ft_printf("p51 %d\n", -589);
    printf("p52 %--4d\n", -2464);
    ft_printf("p52 %--4d\n", -2464);
    printf("p53 %.5d\n", -2372);
    ft_printf("p53 %.5d\n", -2372);
    printf("p54 ret = %d\n", printf("%%p::[%010d]\n", -8473));
    ft_printf("p54 ret = %d\n", printf("%%p::[%010d]\n", -8473));
    printf("p55 ret = %d\n", printf("%%p::[%10d]\n", -8473));
    ft_printf("p55 ret = %d\n", printf("%%p::[%10d]\n", -8473));
    printf("p56 ret = %d\n", printf("%%p::[%.5d]\n", -8473));
    ft_printf("p56 ret = %d\n", printf("%%p::[%.5d]\n", -8473));
    printf("p57 ret = %d\n", printf("%%p::[%01.1d]\n", -8473));
    ft_printf("p57 ret = %d\n", printf("%%p::[%01.1d]\n", -8473));
    printf("p58 ret = %d\n", printf("%%p::[%010.1d]\n", -8473));
    ft_printf("p58 ret = %d\n", printf("%%p::[%010.1d]\n", -8473));
    printf("p59 ret = %d\n", printf("%%p::[%01.50d]\n", -8473));
    ft_printf("p59 ret = %d\n", printf("%%p::[%01.50d]\n", -8473));
    printf("p60 ret = %d\n", printf("%%p::[%1.50d]\n", -8473));
    ft_printf("p60 ret = %d\n", printf("%%p::[%1.50d]\n", -8473));
    printf("p61 ret = %d\n", printf("%%p::[%1.50d]\n", -8473));
    ft_printf("p61 ret = %d\n", printf("%%p::[%1.50d]\n", -8473));
    printf("p62 ret = %d\n", printf("%%p::[%010d]\n", 8473));
    ft_printf("p62 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    printf("p63 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    ft_printf("p63 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    printf("p64 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    ft_printf("p64 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    printf("p65 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    ft_printf("p65 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    printf("p66 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    ft_printf("p66 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    printf("p67 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    ft_printf("p67 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    printf("p68 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    ft_printf("p68 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    printf("p69 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    ft_printf("p69 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    printf("p70 ret = %d\n", printf("%%p::[%0100.50d]\n", -8473));
    ft_printf("p70 ret = %d\n", printf("%%p::[%10d]\n", 8473));
    printf("p71 ret = %d\n", printf("%%p::[%10d]\n", 8473));
    ft_printf("p71 ret = %d\n", printf("%%p::[%10d]\n", 8473));
    printf("p72 ret = %d\n", printf("%%p::[%.5d]\n", 8473));
    ft_printf("p72 ret = %d\n", printf("%%p::[%10d]\n", 8473));
    printf("p73 ret = %d\n", printf("%%p::[%01.1d]\n", 8473));
    ft_printf("p73 ret = %d\n", printf("%%p::[%10d]\n", 8473));
    printf("p74 ret = %d\n", printf("%%p::[%10d]\n", 8473));
    ft_printf("p74 ret = %d\n", printf("%%p::[%010.1d]\n", 8473));
    printf("p75 ret = %d\n", printf("%%p::[%010.1d]\n", 8473));
    ft_printf("p75 ret = %d\n", printf("%%p::[%01.50d]\n", 8473));
    printf("p76 ret = %d\n", printf("%%p::[%01.50d]\n", 8473));
    ft_printf("p76 ret = %d\n", printf("%%p::[%1.50d]\n", 8473));
    printf("p77 ret = %d\n", printf("%%p::[%1.50d]\n", 8473));
    ft_printf("p77 ret = %d\n", printf("%%p::[%0100.50d]\n", 8473));
    printf("p78 ret = %d\n", printf("%%p::[%0100.50d]\n", 8473));
    ft_printf("p78 ret = %d\n", printf("%%p::[%0100.50d]\n", 8473));
	return (0);
}