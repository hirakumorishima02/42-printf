# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: event <event@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/25 15:27:51 by event             #+#    #+#              #
#    Updated: 2021/05/25 15:35:34 by event            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: ft_printf

test:
	./test.sh

printf: main.c
	gcc -Wno-format main.c -D TEST -o printf

ft_printf: main.c
	gcc main.c -D TEST -D FT_PRINTF -o ft_printf

clean:
	rm printf ft_printf