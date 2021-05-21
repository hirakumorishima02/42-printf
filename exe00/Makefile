# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/19 14:02:11 by hmorishi          #+#    #+#              #
#    Updated: 2021/05/20 15:01:09 by hmorishi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c check_mfw.c check_prec.c ft_atoi.c \
		ft_printf.c is_num.c \
		max.c min.c digits_d.c digits_x.c\
		put_nbr_d.c put_nbr_x.c put_c_n.c until_pct.c \
		conv.c conv_d.c conv_x.c conv_s.c

OBJS = $(SRCS:.c=.o)

GCC = gcc

INC = -I includes

NAME = libft.a

RM = rm -f

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)
		ranlib $(NAME)

%.o: %.c
		$(GCC) $(INC) -c $< -o $(<:.c=.o)

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re