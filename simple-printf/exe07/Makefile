# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmorishi <hmorishi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/31 14:34:21 by hmorishi          #+#    #+#              #
#    Updated: 2021/05/31 16:08:02 by hmorishi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ft_printf:
	gcc  -D TEST -D FT_PRINTF main.c -o ft_printf

printf:
	gcc -D TEST main.c -o printf -Wno-format

test:
	./test.sh

clean:
	rm ft_printf printf