/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:23:29 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/20 14:58:51 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(void)
{
	/*printf("p0 % .3s\n", "cccc");
	ft_printf("p0 % .3s\n", "cccc");
	printf("pp %.50d\n", 10000);
	ft_printf("pp %.50d\n", 10000);*/
	printf("p1 %.4s\n", "cccc");
	ft_printf("p1 %.4s\n", "cccc");
	/*printf("p2 %.10s\n", "cccc");
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
    ft_printf("p78 ret = %d\n", printf("%%p::[%0100.50d]\n", 8473));*/
	return (0);
}