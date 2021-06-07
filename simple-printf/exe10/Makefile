SRCS = main.c ft_atoi.c ft_get_digits.c ft_isdigit.c ft_printf.c ft_put_d.c \
		ft_put_s.c ft_put_x.c ft_putstr.c read_args.c

ft_printf:
	gcc $(SRCS) -o ft_printf -D TEST -D FT_PRINTF
printf:
	gcc $(SRCS) -o printf -D TEST -Wno-format
test:
	./test.sh
clean:
	rm ft_printf printf