/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: HirakuMorishima <HirakuMorishima@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:34:49 by HirakuMoris       #+#    #+#             */
/*   Updated: 2021/05/27 17:10:33 by HirakuMoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

#define CONV    "dxs"

#ifdef TEST
#ifdef FT_PRINTF
#define F(...) \
    res = ft_printf(__VA_ARGS__);
#else
#define F(...) \
    res = printf(__VA_ARGS__);
#endif

typedef struct  s_args
{
    int c;
    int width;
    int has_width;
    int precision;
    int has_precision;
}               t_args;

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putstr(char  *str)
{
    int res;

    res = 0;
    while   (*str)
    {
        res += ft_putchar(*str);
        str++;
    }
    return (res);
}

void    ft_initialize_args(t_args   *args)
{
    args->c = 0;
    args->width = 0;
    args->has_width = 0;
    args->precision = 0;
    args->has_precision = 0;
}

int ft_isspace(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

int ft_atoi(char    *str)
{
    long    res;
    long    max;
    int     sign;

    res = 0;
    max = INT_MAX;
    sign = 1;
    while (ft_isspace(*str))
        str++;
    if (*str == '-' || *str == '+')
    {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        if (res < max - (*str - '0') / 10)
            res = res * 10 + (*str - '0');
        else
            res = (sign == -1) ? (max + 1) : max;
        str++;
    }
    return (res);
}

int ft_get_digits(int   d)
{
    int digits;

    digits = 0;
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

char    *ft_strchr(char c, char *str)
{
    while (*str)
    {
        if (c == *str)
            return (str);
        str++;
    }
    return (NULL);
}

char    *ft_read_args(t_args    *args, char *itr)
{
    if (!itr || *itr != '%')
        return (itr);
    itr++;
    while (*itr)
    {
        ft_initialize_args(args);
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
        if (ft_strchr(*itr, CONV))
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

int ft_put_d(t_args  *args, va_list  ap)
{
    int width;
    int precision;
    int res;
    int len;
    int putlen;
    int padding;
    int d;

    res = 0;
    width = (args->has_width) ? args->width : 0;
    precision = (args->has_precision) ? args->precision : 0;
    d = va_arg(ap, int);
    len = ft_get_digits(d);
    if (args->has_precision && args->precision == 0 && d == 0)
        len = 0;
    if (d < 0)
        padding = (len - 1 < precision) ? precision - len - 1 : 0;
    else
        padding = len < precision ? precision - len : 0;
    putlen = len + padding;
    while ((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    if (args->has_precision && args->precision == 0 && d == 0)
        return (res);
    return (res + ft_puti(d, padding));
}

int ft_get_digits_x(unsigned int    x)
{
    int digits;

    digits = 0;
    while (x / 16)
    {
        digits++;
        x /= 16;
    }
    digits++;
    return(digits);
}

int ft_putx(unsigned int x, int  padding)
{
    int res;

    res = 0;
    while (padding-- > 0)
        res += ft_putchar('0');
    if (x / 16)
        res += ft_putx(x / 16, padding);
    if (x % 16 <= 10)
        res += ft_putchar((x % 16) + '0');
    else
        res += ft_putchar('a' + (x % 16) - 10);
    return (res);
}

int ft_put_x(t_args  *args, va_list  ap)
{
    int width;
    int precision;
    int x;
    int res;
    int putlen;
    int len;
    int padding;

    res = 0;
    width = args->has_width ? width : 0;
    precision = args->has_precision ? precision : 0;
    x = va_arg(ap, int);
    len = ft_get_digits_x(x);
    if (args->has_precision && args->precision == 0 && x == 0)
        len = 0;
    padding = (len < precision) ? precision - len : 0;
    putlen = len + padding;
    while((width - putlen) > 0)
    {
        res += ft_putchar(' ');
        width--;
    }
    if (args->has_precision && args->precision == 0 && x == 0)
        return (0);
    return (res + ft_putx(x, padding));
}

int ft_strlen(char  *s)
{
    int res;

    res = 0;
    while (*s++)
        res++;
    return (res);
}

int ft_putstrl(char *s, int len)
{
    int res;

    res = 0;
    while (*s && res < len)
        res += ft_putchar(*s);
    return (res);
}

int ft_put_s(t_args  *args, va_list  ap)
{
    int res;
    int width;
    int precision;
    int putlen;
    int len;
    char    *s;

    width = args->has_width ? args->width : 0;
    precision = args->has_precision ? args->precision : 0;
    res = 0;
    s = va_arg(ap, char *);
    if (!s)
        return (res += ft_putstr("(null)"));
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
    return (res + ft_putstrl(s, putlen));
}

int ft_put_conv(t_args  *args, va_list  ap)
{
    if (args->c == 'd')
        return  ft_put_d(args, ap);
    if (args->c == 'x')
        return  ft_put_x(args, ap);
    if (args->c == 's')
        return  ft_put_s(args, ap);
    return (0);
}

int	ft_printf(const char * restrict format, ...)
{
	char 	*itr;
	int		res;
	t_args	args;
	va_list	ap;

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

int main(void)
{
    int res;

    F("%s\n", "aaaaaaaaaa");
    return (0);
}

#endif