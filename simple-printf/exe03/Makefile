# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 13:38:28 by hmorishi          #+#    #+#              #
#    Updated: 2021/05/26 15:43:17 by hmorishi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c ft_printf.c ft_isdigit.c ft_read_args.c ft_atoi.c ft_get_digits.c \
		ft_strchr.c ft_put_conv.c ft_putchar.c ft_putstr.c \
		ft_put_d.c ft_put_x.c ft_put_s.c

GCC = gcc -Wno-format -D TEST 

TEST = -D FT_PRINTF
printf:
	 $(GCC) $(SRCS) -o printf

ft_printf:
	$(GCC) $(TEST)  $(SRCS) -o ft_printf

test:
	./test.sh

clean:
	rm printf ft_printf