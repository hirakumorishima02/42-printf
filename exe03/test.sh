make printf
make ft_printf
./printf > printf.txt
./ft_printf > ft_printf.txt
diff -a --suppress-common-lines printf.txt ft_printf.txt
make clean
rm printf.txt ft_printf.txt