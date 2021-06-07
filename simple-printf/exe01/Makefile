# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/24 16:45:16 by hmorishi          #+#    #+#              #
#    Updated: 2021/05/24 17:06:01 by hmorishi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c ft_atoi.c ft_get_digits.c ft_isdigit.c ft_printf.c \
		ft_put_conv.c ft_put_d.c ft_put_s.c ft_put_x.c \
		ft_putchar.c ft_putstr.c ft_putstrl.c ft_strchr.c \
		ft_strlen.c read_args.c

OBJS = $(SRCS:.c=.o)

GCC = gcc -D TEST -D FT_PRINTF

INC = -I includes

NAME = libft.a

RM = rm -f

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)
		ranlib $(NAME)

%.o: %.c
		$(GCC) $(INC) -c $< -o $(<:.c=.o)

all:	$(NAME)

test:
	bash test.sh

printf: $(NAME)
	gcc -Wno-format $(NAME) -D TEST -o printf

ft_printf: $(NAME)
	gcc $(NAME) -D TEST -D FT_PRINTF -o ft_printf

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re