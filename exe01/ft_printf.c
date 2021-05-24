/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:40:00 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/24 14:34:24 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#define CONV "dxs"

char	*ft_strchr(char c, char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (c == *str)
			return (str);
		str++;
	}
	return (NULL);
}

int	ft_putchar(char c)
{
	return write(1, &c, 1);
}

int	ft_putstr(char *str)
{
	int	res;

	if (!str)
		return (0);
	res = 0;
	while(*str)
	{
		res += ft_putchar(*str);
		str++;
	}
	return (res);
}

int	ft_putstrl(char *str, int putlen)
{
	int	res;
	int i;

	if (!str)
		return (0);
	res = 0;
	i = 0;
	while(str[i] && i < putlen)
	{
		res += ft_putchar(str[i]);
		i++;
	}
	return (res);
}

typedef	struct s_args
{
	int	c;
	int	width;
	int	has_width;
	int	precision;
	int	has_precision;
}				t_args;

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_isspace(char	c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
//calloc互換可能
void	initialize_args(t_args	*args)
{
	args->c = 0;
	args->width = 0;
	args->has_width = 0;
	args->precision = 0;
	args->has_precision = 0;
}

int		ft_atoi(char *str)
{
	long	res;
	long	max;
	int		sign;

	res = 0;
	max = INT_MAX;
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (res < max - (*str - '0') / 10)
			res = 10 * res + (*str - '0');
		else
			res = (sign == -1) ? (max + 1) : max;
		str++;
	}
	return ((int)res * sign);
}

int		ft_get_digits(int	d)
{
	int	digits;

	if (d == INT_MIN)
		return (11);
	digits = 0;
	if (d < 0)
	{
		digits++;
		d *= -1;
	}
	while (d / 10)
	{
		d /= 10;
		digits++;
	}
	digits++;
	return (digits);
}

char	*read_args(t_args *args, char *itr)
{
	if (!itr || *itr != '%')
		return (itr);
	itr++;
	while (*itr)
	{
		initialize_args(args);
		//width
		if (ft_isdigit(*itr))
		{
			args->has_width = 1;
			args->width = ft_atoi(itr);
			itr += ft_get_digits(args->width);
		}
		//.
		if (*itr == '.')
		{
			args->has_precision = 1;
			itr++;
		}
		//precision
		if (ft_isdigit(*itr))
		{
			args->has_precision = 1;
			args->precision = ft_atoi(itr);
			itr += ft_get_digits(args->precision);
		}
		//dxs
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

int	ft_strlen(char *s)
{
	int len;

	if (!s)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}

int	ft_put_s(t_args *args, va_list ap)
{
	int		res;
	int		width;
	int		precision;
	int		len;
	int		putlen;
	char	*s;

	width = args->has_width ? args->width : 0;
	precision = args->has_precision ? args->precision : 0;
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
	return (res + ft_putstrl(s, putlen));
}

int	ft_put_conv(t_args *args, va_list ap)
{
	// if (args->c == 'd')
	// 	return ft_put_d(args, ap);
	// if (args->c == 'x')
	// 	return ft_put_x(args, ap);
	if (args->c == 's')
		return ft_put_s(args, ap);
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
			itr = read_args(&args, itr);
			res += ft_put_conv(&args, ap);
			continue;
		}
		res += ft_putchar(*itr);
		itr++;
	}
	va_end(ap);
	return (res);
}
	
#ifdef TEST

#include <stdio.h>

#ifdef FT_PRINTF
#define F(...) \
res = ft_printf(__VA_ARGS__);
#else
#define F(...) \
res = printf(__VA_ARGS__);
#endif

int	main(void)
{
	int	res;
	F("1:[%s]\n", "hoge");
	F("2:[%9.4s]\n", "hoge");
	F("3:[%3.2s]\n", "hoge");
	F("4:[%10.4s]\n", "hoge");
	F("5:[%0.5s]\n", "hoge");
	F("6:[%s]\n", NULL);
	F("6:[%s]\n", "                       ");
	return (0);
}
#endif