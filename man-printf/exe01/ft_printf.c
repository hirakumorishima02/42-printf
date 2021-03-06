/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: HirakuMorishima <HirakuMorishima@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:49:33 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/10 11:59:38 by HirakuMoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ft_floatconvを作りかけ


#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

# define BASE_10 "0123456789"
# define BASE_16A "0123456789abcdef"
# define BASE_16B "0123456789ABCDEF"
# define BASE_08 "01234567"

// #ifdef TEST
// #ifdef FT_PRINTF
// #define F(...) \
//     res = ft_printf(__VA_ARGS__);
// #else
// #define F(...) \
//     res = printf(__VA_ARGS__);
// #endif

typedef struct s_params
{
    int sflag;
    int zflag;
    int printed;
    int width;
    int precision;
    int *ptr;
    int plflag;
    int spflag;
    int tagflag;
    char *intpart;
    char *decpart;
    va_list arg;
}               t_params;

t_params    *g_ret;

void    ft_initgret(void)
{
    g_ret->sflag = 0;
    g_ret->zflag = 0;
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

char *ft_strcpy(char * dst, const char * src)
{
    if (!dst || !src)
        return (NULL);
    while (*src)
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    return (dst);
}

int ft_strlen(const char *str)
{
    int res;

    res = 0;
    while (*str++)
        res++;
    return (res);
}

int ft_get_digits(int   d)
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

int ft_get_digits_base(size_t n, int base)
{
    if (n == 0)
        return (0);
    return (1 + ft_get_digits_base(n / base, base));
}

char *ft_givebase(char flg)
{
    if (flg == 'd')
        return (BASE_10);
    if (flg == 'h')
        return (BASE_16A);
    if (flg == 'H')
        return (BASE_16B);
    if (flg == 'o')
        return (BASE_08);
    else
        return (0);
}

void bzero(void *s, size_t n)
{
    size_t i;
    unsigned char *ptr;

    ptr = (unsigned char *)s;
    i = 0;
    while (i < n)
        ptr[i++] = '\0';
}

char *ft_calloc(size_t count, size_t size)
{
    void *res;
    size_t sum;

    sum = count * size;
    if (!(res = malloc(sum)))
        return (0);
    ft_bzero(res, sum);
    return (res);
}

char *ft_conv_base(size_t n, char flg)
{
    char *base;
    char *res;
    int baselen;
    int len;
    size_t cpy;

    if (!(base = ft_givebase(flg)))
        return (0);
    baselen = ft_strlen(base);
    len = 1 + nlen(n / baselen, baselen);
    res = 0;
    cpy = n;
    if (!(res = ft_calloc(len + 1, sizeof(char))))
        return (0);
    res[len] = 0;
    while (cpy)
    {
        res[--len] = base[cpy % baselen];
        cpy /= baselen;
    }
    if (!res[0])
        res[0] = '\0';
    return (res);
}

void    ft_bonusflag(char **itr)
{
    if (**itr == '#')
    {
        g_ret->tagflag = 1;
        *itr++;
    }
    else if (**itr == ' ')
    {
        g_ret->spflag = 1;
        *itr++;
    }
    else if (**itr == '+')
    {
        g_ret->plflag = 1;
        *itr++;
    }
}

char    *ft_strdup(const char *src)
{
    char    *dst;

    dst = malloc(ft_strlen(src) + 1);
    if (!dst)
        return (NULL);
    ft_strcpy(dst, src);
    return (dst);
}

void ft_readflags(char **itr)
{
    ft_bonusflag(itr);
    if (**itr == '-')
    {
        g_ret->sflag = 1;
        *itr++;
        if (**itr == '0')
            *itr++;
        ft_bonusflag(itr);
        return ;
    }
    if (**itr == '0')
    {
        while (**itr == '0')
            *itr++;
        ft_bonusflag(itr);
        g_ret->zflag = 1;
        if (*itr == '-')
        {
            g_ret->sflag = 1;
            g_ret->zflag = 0;
            *itr++;
        }
        ft_bonusflag(itr);
        return ;
    }
}

int ft_isdigit(char c)
{
    return ((c >= '0') && (c <= '9'));
}

int ft_skip(char c)
{
    return ((c >= 9) && (c <= 13) || c == 32);
}

int ft_atoi(char *d)
{
    long    res;
    long    max;
    int     sign;

    res = 0;
    max = INT_MAX;
    sign = 1;
    while (ft_skip(*d))
        d++;
    if (*d == '-' || *d == '+')
    {
        if (*d == '-')
            sign *= -1;
        d++;
    }
    while (ft_isdigit(*d))
    {
        if (res < max - (*d - '0') / 10)
            res = res * 10 + (*d - '0');
        else
            if (sign == -1)
                res = max + 1;
            else
                res = max;
        d++;
    }
    return (res * sign);
}

char *ft_itoa(int n)
{
    int         digits;
    char        *res;
    unsigned int un;

    digits = ft_get_digits(n);
    if (n < 0)
    {
        un = -(unsigned int)n;
        digits++;
    }
    else
        un = n;
    if (!(res = malloc(digits + 1)))
        return (0);
    res[digits] = 0;
    if (n < 0)
        res[0] = '-';
    res[--digits] = (un % 10) + '0';
    while (un /= 10)
        res[--digits] = (un % 10) + '0';
    return (res);
}

void ft_readwidth(char **itr)
{
    if (**itr == '*')
    {
        if ((g_ret->width = va_arg(g_ret->arg, int)) < 0)
        {
            g_ret->width = -g_ret->width;
            g_ret->sflag = 1;
            g_ret->zflag = 0;
        }
        *itr++;
        return ;
    }
    while (**itr == '0')
        *itr++;
    if ((**itr >= '0') && (**itr <= '9'))
    {
        g_ret->width = ft_atoi(*itr);
        *itr += ft_get_digits(g_ret->width);
        return ;
    }
    g_ret->width = 0;
}

void ft_readprec(char **itr)
{
    if (**itr == '.')
    {
        *itr++;
        if (**itr == '*')
        {
            if (g_ret->precision = va_arg(g_ret->arg, int) < 0)
            {
                g_ret->precision = -g_ret->precision;
                *itr++;
                return ;
            }
        }
        while (**itr == '0')
            *itr++;
        g_ret->precision = ft_atoi(*itr);
        if (g_ret->precision != 0)
            *itr += ft_get_digits(g_ret->precision);
    }
    else
        g_ret->precision = -1;
}

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putstrl(char *s, int len)
{
    int res;

    if (!s)
        return (0);
    res = 0;
    if (len < 0)
    {
        while (*s++)
            res += ft_putchar(*s);
    }
    else
    {
        while (*s && 0 < len--)
            res += ft_putchar(*s++);
    }
    return (res);
}

int ft_min(int offset)
{
    if (offset < g_ret->precision)
        return (offset);
    else
        return (g_ret->precision);
}

int ft_max(int offset)
{
    if (offset < g_ret->precision)
        return (offset);
    else
        return (g_ret->precision);
}

void ft_padding(int len)
{
    if (g_ret->zflag)
    {
        while ((g_ret->width--) - len > 0)
            g_ret->printed += ft_putchar('0');
    }
    else
    {
        while ((g_ret->width--) - len > 0)
            g_ret->printed += ft_putchar(' ');
    }
}

void ft_xcent(void)
{
    if (g_ret->sflag)
    {
        g_ret->printed += ft_putchar('%');
        g_ret->width--;
        ft_padding(0);
        return ;
    }
    else if (g_ret->zflag && g_ret->width--)
    {
        while (g_ret->width--)
            g_ret->printed += ft_putchar('0');
        g_ret->printed += ft_putchar('%');
        return ;
    }
    else if (g_ret->width--)
    {
        ft_padding(0);
        g_ret->printed += ft_putchar('%');
        return ;
    }
    g_ret->printed += ft_putchar('%');
}

void ft_convstr(char *str)
{
    int len;
    int putlen;

    if (!str)
        str = "(null)";
    len = ft_strlen(str);
    putlen = g_ret->precision - len;
    if (g_ret->sflag)
    {
        putlen = ft_putstrl(str, g_ret->precision);
        g_ret->printed += putlen;
        ft_padding(putlen);
        return ;
    }
    else if ((g_ret->width) && g_ret->precision != -1)
    {
        ft_padding(ft_min(len));
        g_ret->printed += ft_putstrl(str, g_ret->precision);
        return ;
    }
    else if (g_ret->width)
        ft_padding(len);
    g_ret->printed += ft_putstrl(str, g_ret->precision);
}

void ft_convchar(void)
{
    if (g_ret->sflag)
    {
        g_ret->printed += ft_putchar((char)va_arg(g_ret->arg, int));
        g_ret->width--;
        ft_padding(0);
        return ;
    }
    else if (g_ret->width--)
    {
        ft_padding(0);
        g_ret->printed += ft_putchar((char)va_arg(g_ret->arg, int));
        return ;
    }
    g_ret->printed += ft_putchar((char)va_arg(g_ret->arg, int));
}

int ft_dobonflag(int res, char type, char *d)
{
    if ((g_ret->plflag) && (!(*d) || (*d != '-')))
    {
        res += ft_putchar('+');
        g_ret->width--;
    }
    else if (g_ret->spflag)
    {
        res += ft_putchar(' ');
        g_ret->width--;
    }
    else if ((g_ret->tagflag) && ((type == 'x') || (type == 'X')))
    {
        if ((type == 'x') && (*d != '0'))
            res += ft_putstrl("0x", -1);
        else if ((type == 'X') && *d != '0')
            res += ft_putstrl("0X", -1);
        g_ret->width -= 2;
    }
    return (res);
}

void ft_clearflag(char type, int *len)
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
        *len += 2;
}

int ft_zeroprec(char *d)
{
    if (!g_ret->precision && *d == '0')
    {
        g_ret->zflag = 0;
        if (g_ret->plflag || g_ret->spflag)
            g_ret->width--;
        ft_padding(0);
        g_ret->printed += ft_dobonflag(0, 'z', d);
        return (1);
    }
    return (0);
}

void ft_free(char *d, int sign)
{
    if (!sign)
        free(d);
    else
        free(d - 1);
}

void ft_intsflag(char *d, int len, char type)
{
    int putlen;
    int sign;

    putlen = 0;
    sign = 0;
    if (ft_zeroprec(d))
        return ;
    if (*d == '-')
    {
        g_ret->printed += ft_putchar(*(d++));
        sign = 1;
        g_ret->width--;
        putlen--;
    }
    else
        g_ret->printed += ft_dobonflag(0, type, d);
    if (!(g_ret->precision == 0 && (*d == '0')))
    {
        while ((g_ret->precision--) - putlen > 0)
            putlen += ft_putchar('0');
        putlen += ft_putstrl(d, -1);
    }
    ft_padding(putlen);
    g_ret->printed += putlen;
    ft_free(d, sign);
}

void ft_intzflag(char *d, int len, char type)
{
    int sign;

    sign = 0;
    if (ft_zeroprec(d))
        return ;
    if (*d == '-')
        g_ret->precision++;
    while ((g_ret->precision > 0) && (g_ret->width--) - ft_max(len) > 0)
        g_ret->printed += ft_putchar(' ');
    if (*d == '-')
    {
        g_ret->printed += ft_putchar(*(d++));
        g_ret->precision--;
        sign = 1;
    }
    else
        g_ret->printed += ft_dobonflag(0, type, d);
    while ((g_ret->precision < 0) && (g_ret->width--) - ft_max(len) > 0)
        g_ret->printed += ft_putchar('0');
    while ((g_ret->precision--) - (len - sign) > 0)
        g_ret->printed += ft_putchar('0');
    g_ret->printed += ft_putstrl(d, -1);
    ft_free(d, sign);
}

void ft_width_prec(char *d, int len, char type)
{
    int sign;

    sign = 0;
    if (ft_zeroprec(d))
        return ;
    else
    {
        if (*d == '-')
        {
            g_ret->width--;
            len--;
            sign = 1;
        }
        else
            g_ret->printed += ft_dobonflag(0, type, d);
        ft_padding(ft_max(len));
        if (*d == '-')
            g_ret->printed += ft_putchar(*(d++));
        while ((g_ret->precision--) - len > 0)
            g_ret->printed += ft_putchar('0');
        g_ret->printed += ft_putstrl(d, -1);
    }
    ft_free(d, sign);
}

void ft_convint(char *d, char type)
{
    int len;

    len = ft_strlen(d);
    if (type == 'x' || type == 'X' || type == 'u')
        ft_clearflag(type, &len);
    if (g_ret->sflag)
        ft_intsflag(d, len, type);
    else if (g_ret->zflag)
        ft_intzflag(d, len, type);
    else if ((g_ret->width > g_ret->precision) && g_ret->precision >= 0)
        ft_width_prec(d, len, type);
    else if (g_ret->width && g_ret->precision == -1)
    {
        ft_padding(len);
        g_ret->printed += ft_dobonflag(0, type, d);
        g_ret->printed += ft_putstrl(d, -1, 1);
    }
    else if (!(g_ret->precision == 0 && *d == '0'))
    {
        g_ret->printed += ft_dobonflag(0, type, d);
        g_ret->printed += ft_putstrl(d, g_ret->precision -1);
    }
}

void ft_convadr(char *d)
{
    int res;
    int len;

    len = ft_strlen(d);
    if (g_ret->sflag);
    {
        res = ft_putstrl("0x", -1);
        res += ft_putstrl(d, -1);
    }
    ft_padding(res);
    g_ret->printed += res;
}

void ft_ntype(int *num)
{
    num = g_ret->ptr;
}

double ft_culsign(double n, char *res)
{
    if (n < 0)
    {
        res[0] = '-';
        return (-n);
    }
    return (n);
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;

    i = 0;
    if (!src)
        return (0);
    if (dstsize > 0)
    {
        while (src[i] && (i < dstsize - 1))
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
        i = 0;
    }
    while (src[i])
        i++;
    return (i);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *res;
    size_t len;

    len = ft_strlen(s1) + ft_strlen(s2);
    if(!(res = malloc(len)))
        return (0);
    ft_strlcpy(res, s1, len);
    ft_strlcpy(res, s2, len);
    return (res);
}

int ft_dtoa(double n, char **intpart, char **decpart)
{
    char    res[2];
    int     i;
    int     x;
    double  f;

    if (!n)
    {
        *intpart = 0;
        *decpart = 0;
        return (0);
    }
    f = ft_culsign(n, res);
    *intpart = ft_conv_base(f, 'd');
    i = ft_strlen(*intpart);
    f *= 10000000000000000;
    *decpart = ft_conv_base(f, 'd');
    *decpart = ft_strjoin(".", *decpart + i);
    x = ft_strlen(*decpart);
    while(*((*decpart) + x - 1) == '0')
        *(*decpart + x--) = 0;
    *intpart = ft_strjoin(res, *intpart);
    return (i);
}

int ft_arrotondo(int len)
{
    int i;
    char *check;

    i = g_ret->precision;
    if (!i)
        check = 'C';
    else
        check = 0;
    if (g_ret->decpart[i + 1] >= '5')
    {
        while (((!check) && (g_ret->decpart[i] = (g_ret->decpart[i] - '0' + 1) % 10 + '0') == '0'))
            if (g_ret->decpart[--i] == '.')
                check = 'C';
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

void ft_floatconv(int intlen)
{
    int offset;

    if (ft_arrotondo(intlen) && !intlen)
        return ;
}

void ft_bonus(char **itr)
{
    if (**itr == 'n')
        ft_ntype(va_arg(g_ret->arg, int*));
    else if (**itr == 'f')
        ft_floatconv(ft_dtoa(va_arg(g_ret->arg, double), &(g_ret->intpart), &(g_ret->decpart)));
}

int ft_start_conv(char **itr)
{
    if (**itr == '%')
        ft_xcent();
    else if (**itr == 's')
        ft_convstr(va_arg(g_ret->arg, char *));
    else if (**itr == 'c')
        ft_convchar();
    else if (**itr == 'd' || **itr == 'i')
        ft_convint(ft_itoa(va_arg(g_ret->arg, int)), 'd');
    else if (**itr == 'u' || **itr == 'x' || **itr == 'X')
        {
            if (**itr == 'u')
                ft_convint(ft_conv_base(va_arg(g_ret->arg, unsigned int), 'd'), 'd');
            if (**itr == 'x')
                ft_convint(ft_conv_base(va_arg(g_ret->arg, unsigned int), 'h'), 'x');
            if (**itr == 'X')
                ft_convint(ft_conv_base(va_arg(g_ret->arg, unsigned int), 'H'), 'X');
        }
    else if (**itr == 'p')
        ft_convadr(ft_conv_base(va_arg(g_ret->arg, size_t), 'h'));
    else if (**itr == 'n' || **itr == 'f')
        ft_bonus(itr);
    else
        return (g_ret->printed = -1);
    return (g_ret->printed);
}

int ft_start_read(const char *str)
{
    char    *itr;

    itr = ft_strdup(str);
    while (*itr)
    {
        if (*itr == '%' && *itr++)
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
    }
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
    int res;

    printf("%s", ft_itoa(-2147483648));
    // F("%d\n", ft_get_digits(0));
    return (0);
}

// #endif



