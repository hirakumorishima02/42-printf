/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:30:46 by hmorishi          #+#    #+#             */
/*   Updated: 2021/06/01 18:26:10 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define CONV "dxs"

#ifdef TEST
#ifdef FT_PRINTF
#define F(...) \
    res = ft_printf(__VA_ARGS__);
#else
#define F(...) \
    res = printf(__VA_ARGS__);
#endif

typedef struct s_args
{
    int width;
    int precision;
    int has_width;
    int has_precision;
    int c;
}               t_args;

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
    int res;

    if (!s)
        return (0);
    res = 0;
    while (*s)
    {
        res += ft_putchar(*s);
        s++;
    }
    return (res);
}

int ft_strlen(char *s)
{
    int res;

    if (!s)
        return (0);
    res = 0;
    while (*s++)
        res++;
    return (res);
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

void initialize_args(t_args *args)
{
    args->width = 0;
    args->has_width = 0;
    args->precision = 0;
    args->has_precision = 0;
    args->c = 0;
}

int ft_skip(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

int ft_atoi(char *s)
{
    long res;
    long max;
    int sign;

    res = 0;
    max = INT_MAX;
    sign = 1;
    while (ft_skip(*s))
        s++;
    if (*s == '-' || *s == '+')
    {
        sign = *s == '-' ? -1 : 1;
        s++;
    }
    while (ft_isdigit(*s))
    {
        if (res < max - (*s + '0') / 10)
            res = res * 10 + (*s - '0');
        else
            res = sign == -1 ? max + 1 : max;
        s++;
    }
    return (res * sign);
}

int ft_get_digits(int   d)
{
    int digits;

    digits = 0;
    if (d == INT_MIN)
        return (11);
    if (d < 0)
    {
        digits++;
        d *= -1;
    }
    while (d / 10)
    {
        digits++;
        d /= 10;
    }
    digits++;
    return (digits);
}

int ft_get_digits_x(unsigned int   d)
{
    int digits;

    digits = 0;
    while (d / 16)
    {
        digits++;
        d /= 16;
    }
    digits++;
    return (digits);
}

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

char    *read_args(t_args *args, char   *itr)
{
    if (!itr || *itr != '%')
        return (itr);
    itr++;
    while (*itr)
    {
        initialize_args(args);
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
    res += ft_putchar(d % 10 + '0');
    return (res);
}

int ft_put_d(t_args *args, va_list   ap)
{
    int width;
    int precision;
    int len;
    int padding;
    int putlen;
    int res;
    int d;

    res = 0;
    d = va_arg(ap, int);
    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    len = ft_get_digits(d);
    if (args->has_precision && args->precision == 0 && d == 0)
        len = 0;
    if (d < 0)
        padding = ((len - 1) < precision) ? precision - (len - 1) : 0;
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

int ft_putx(unsigned int d, int  padding)
{
    int res;

    res = 0;
    while (padding-- > 0)
        res += ft_putchar('0');
    if (d / 16)
        res += ft_putx(d / 16, padding);
    if (d % 16 >= 10)
        res += ft_putchar('a' + (d % 16) - 10);
    else
        res += ft_putchar(d % 16 + '0');
    return (res);
}

int ft_put_x(t_args *args, va_list   ap)
{
    int width;
    int precision;
    int len;
    int padding;
    int putlen;
    int res;
    int d;

    res = 0;
    d = va_arg(ap, int);
    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    len = ft_get_digits_x(d);
    if (args->has_precision && args->precision == 0 && d == 0)
        len = 0;
    padding = (len < precision) ? precision - len : 0;
    putlen = padding + len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    if (args->has_precision && args->precision == 0 && d == 0)
        return (res);
    return (res + ft_putx(d, padding));
}

int ft_putstrl(char *s, int len)
{
    int res;
    int i;

    i = 0;
    res = 0;
    while (s[i] && i < len)
    {
        res += ft_putchar(s[i]);
        i++;
    }
    return (res);
}

int ft_put_s(t_args *args, va_list   ap)
{
    int width;
    int precision;
    int len;
    int putlen;
    int res;
    char *s;

    res = 0;
    s = va_arg(ap, char *);
    if (!s)
        s = "(null)";
    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    len = ft_strlen(s);
    if (args->has_precision)
        putlen = len > precision ? precision : len;
    else
        putlen = len;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    return (res + ft_putstrl(s, putlen));
}

int ft_put_conv(t_args *args, va_list   ap)
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
    int res;
    char    *itr;
    va_list ap;
    t_args  args;

    va_start(ap, format);
    itr = (char *)format;
    res = 0;
    while (*itr)
    {
        if (*itr == '%')
        {
            itr = read_args(&args, itr);
            res += ft_put_conv(&args, ap);
            continue;
        }
        res += ft_putchar(*itr);
        itr++;
    }
    return (res);
}

int main(void)
{
    int res;
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