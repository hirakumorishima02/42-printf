/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:08:35 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/28 15:50:49 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

#define CONV "dxs"

#ifdef  TEST
#ifdef  FT_PRINTF
#define F(...) \
    res = ft_printf(__VA_ARGS__);
#else
#define F(...) \
    res = printf(__VA_ARGS__);
#endif

typedef struct  s_args
{
    int has_width;
    int width;
    int has_precision;
    int precision;
    int c;
}               t_args;

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putstr(char  *str)
{
    int res;

    res = 0;
    while (*str)
    {
        res += ft_putchar(*str);
        str++;
    }
    return (res);
}

int ft_strlen(char  *str)
{
    int len;

    len = 0;
    while (*str++)
        len++;
    return (len);
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

int ft_isskip(char  c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

int ft_atoi(char    *d)
{
    long res;
    long max;
    int sign;

    res = 0;
    sign = 1;
    max = INT_MAX;
    while (ft_isskip(*d))
        d++;
    if (*d == '-' || *d == '+')
    {
        sign = (*d == '-') ? -1 : 1;
        d++;
    }
    while (ft_isdigit(*d))
    {
        if (res < max / 10 - (*d - '0'))
            res = res * 10 + (*d - '0');
        else
            res = (sign == -1) ? max + 1 : max;
        d++;
    }
    return (res * sign);
}

void    ft_initialize_args(t_args   *args)
{
    args->has_width = 0;
    args->width = 0;
    args->has_precision = 0;
    args->precision = 0;
    args->c = 0;
}

int ft_get_digits(int   d)
{
    int res;

    res = 0;
    if (d < 0)
        res++;
    while (d / 10)
    {
        res++;
        d /= 10;
    }
    res++;
    return (res);
}

int ft_get_digits_x(unsigned int   x)
{
    int res;

    res = 0;
    while (x / 16)
    {
        res++;
        x /= 16;
    }
    res++;
    return (res);
}

char *ft_strchr(char  c, char *str)
{
    while (*str)
    {
        if (*str == c)
            return (str);
        str++;
    }
    return (0);
}

char    *ft_read_args(t_args    *args, char *itr)
{
    int res;

    res = 0;
    while (*itr)
    {
        ft_initialize_args(args);
        // width
        if (ft_isdigit(*itr))
        {
            args->has_width = 1;
            args->width = ft_atoi(itr);
            itr += ft_get_digits(args->width);
        }
        // .
        if (*itr == '.')
        {
            args->has_precision = 1;
            itr++;
        }
        // precision
        if (ft_isdigit(*itr))
        {
            args->precision = ft_atoi(itr);
            itr += ft_get_digits(args->precision);
        }
        // c
        if(ft_strchr(*itr, CONV))
        {
            args->c = *itr;
            itr++;
            return (itr);
        }
        itr++;
    }
    return (itr);
}

int ft_puti(int d, int  padding)
{
    int res;

    res = 0;
    if (d == INT_MIN)
    {
        res += ft_putchar('-');
        while (padding-- > 0)
            res += ft_putchar('0');
        res += ft_putstr("2147483648");
        return (res);
    }
    if (d < 0)
    {
        res += ft_putchar('-');
        d *= -1;
    }
    while (padding-- > 0)
        res += ft_putchar('0');
    if (d / 10)
        res += ft_puti(d / 10, padding);
    res += ft_putchar((d % 10) + '0');
    return (res);
}

int ft_putx(unsigned int x, int  padding)
{
    int res;

    res = 0;
    while (padding-- > 0)
        res += ft_putchar('0');
    if (x / 16)
        res += ft_putx(x / 16, padding);
    if (x % 16 >= 10)
        res += ft_putchar('a' + (x % 16) - 10);
    else
        res += ft_putchar((x % 16) + '0');
    return (res);
}

int ft_put_d(t_args  *args, va_list  ap)
{
    int width;
    int precision;
    int len;
    int putlen;
    int d;
    int padding;
    int res;

    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    res = 0;
    d = va_arg(ap, int);
    len = ft_get_digits(d);
    if (args->has_precision && args->precision == 0 && d == 0)
        len = 0;
    if (d < 0)
        padding = (len - 1 < precision) ? precision - (len - 1) : 0;
    else
        padding = (len < precision) ? precision - len : 0;
    putlen = padding + len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    if (args->has_precision && args->precision == 0 && d == 0)
        return (res);
    return (res + ft_puti(d, padding));
}

int ft_putstrl(char *s, int len)
{
    int res;
    int i;

    if (!s)
        return (0);
    res = 0;
    i = 0;
    while (s[i] && i < len)
    {
        res += ft_putchar(s[i]);
        i++;
    }
    return (res);
}

int ft_put_s(t_args  *args, va_list  ap)
{
    int width;
    int precision;
    int putlen;
    int len;
    int res;
    char    *s;

    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    res = 0;
    s = va_arg(ap, char *);
    if (!s)
        s = "(null)";
    len = ft_strlen(s);
    if (args->has_precision)
        putlen = (len > precision) ? precision : len;
    else
        putlen = len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    return (res += ft_putstrl(s, putlen));
}

int ft_put_x(t_args  *args, va_list  ap)
{
    int width;
    int precision;
    int len;
    int putlen;
    int x;
    int padding;
    int res;

    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    res = 0;
    x = va_arg(ap, int);
    len = ft_get_digits_x(x);
    if (args->has_precision && args->precision == 0 && x == 0)
        len = 0;
    padding = (len < precision) ? precision - len : 0;
    putlen = padding + len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    if (args->has_precision && args->precision == 0 && x == 0)
        return (res);
    return (res + ft_putx(x, padding));
}

int ft_put_conv(t_args  *args, va_list  ap)
{
    if (args->c == 'd')
        return (ft_put_d(args, ap));
    if (args->c == 'x')
        return (ft_put_x(args, ap));
    if (args->c == 's')
        return (ft_put_s(args, ap));
    return (0);
}

int ft_printf(const char * restrict format, ...)
{
    int     res;
    char    *itr;
    va_list ap;
    t_args  args;

    itr = (char *)format;
    if (!itr)
        return (0);
    res = 0;
    va_start(ap, format);
    while (*itr)
    {
        if (*itr == '%')
        {
            itr = ft_read_args(&args, itr);
            res += ft_put_conv(&args, ap);
            continue;
        }
        res += ft_putchar(*itr);
        itr++;
    }
    va_end(ap);
    return (res);
}

int	main(void)
{
	int	res;
	F(">>>>>>>>>>>>>>>>>>>>STR<<<<<<<<<<<<<<<<<<\n");
	F("1:[%s]\n", "hoge");
	F("2:[%9.4s]\n", "hoge");
	F("3:[%3.2s]\n", "hoge");
	F("4:[%10.4s]\n", "hoge");
	F("5:[%0.5s]\n", "hoge");
	F("6:[%s]\n", NULL);
	F("7:[%s]\n", "                       ");
	F(">>>>>>>>>>>>>>>>>>>>INT<<<<<<<<<<<<<<<<<<\n");
	F("8:[%d]\n", 2147483647);
	F("11:[%3.2d]\n", -2147483648);
	F("12:[%10.5d]\n", 2147483647);
	F("13:[%7.4d]\n", -2147483648);
	F("14:[%0.5d]\n", 2147483647);
	F("15:[%5.0d]\n", -2147483648);
	F("16:[%d]\n", 214);
	F("17:[%3.2d]\n", -2147);
	F("18:[%10.5d]\n", 214);
	F("19:[%7.4d]\n", -2147);
	F("20:[%0.5d]\n", 214);
	F("21:[%5.0d]\n", -2147);
	F("22:[%0.0d]\n", -2147);
	F("23:[%10.d]\n", 214);
	F("24:[%7.d]\n", -2147);
	F("25:[%.5d]\n", 214);
	F("26:[%.0d]\n", -2147);
	F("27:[%.6d]\n", -2147);
	F("28:[%.5d]\n", 0);
	F("29:[%.0d]\n", 0);
	F("30:[%.6d]\n", 0);
	F("31:[%5.d]\n", 0);
	F("32:[%.d]\n", 0);
	F("33:[%3.0d]\n", 0);
	F("34:[%5.d]\n", -12);
	F("35:[%.d]\n", 43);
	F("36:[%3.0d]\n", INT_MIN);
	F(">>>>>>>>>>>>>>>>>>>>XXX<<<<<<<<<<<<<<<<<<\n");
	F("8:[%x]\n", 2147483647);
	F("11:[%3.2x]\n", -2147483648);
	F("12:[%10.5x]\n", 2147483647);
	F("13:[%7.4x]\n", -2147483648);
	F("14:[%0.5x]\n", 2147483647);
	F("15:[%5.0x]\n", -2147483648);
	F("16:[%x]\n", 214);
	F("17:[%3.2x]\n", -2147);
	F("18:[%10.5x]\n", 214);
	F("19:[%7.4x]\n", -2147);
	F("20:[%0.5x]\n", 214);
	F("21:[%5.0x]\n", -2147);
	F("22:[%0.0x]\n", -2147);
	F("23:[%10.x]\n", 214);
	F("24:[%7.x]\n", -2147);
	F("25:[%.5x]\n", 214);
	F("26:[%.0x]\n", -2147);
	F("27:[%.6x]\n", -2147);
	F("28:[%.5x]\n", 0);
	F("29:[%.0x]\n", 0);
	F("30:[%.6x]\n", 0);
	F("31:[%5.x]\n", 0);
	F("32:[%.x]\n", 0);
	F("33:[%3.0x]\n", 0);
	F("34:[%5.x]\n", -12);
	F("35:[%.x]\n", 43);
	F("36:[%3.0x]\n", INT_MIN);
	return (0);
}
#endif