#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int hex_len(int number)
{
	int length;

	length = 0;
	while (number != 0)
	{
		number /= 16;
		length++;
	}
	return (length);
}

void ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

int ft_print_hex(int number)
{
	if (number >= 16)
	{
		ft_print_hex(number / 16);
		ft_print_hex(number % 16);
	}
	else
	{
		if (number > 9)
			ft_putchar_fd(1, number - 10 + '0');
		else
			ft_putchar_fd(1, number + '0');
	}
	return (hex_len(number));
}

int ft_print_number(int number)
{
	int length;
	int reverse;
	char c;

	length = 0;
	reverse = 0;
	if (number < 0)
	{
		write(1, "-", 1);
		number *= -1;
		length++;
	}
	if (number == 0)
	{
		write(1, "0", 1);
		length++;
		return (length);
	}
	while (number != 0)
	{
		reverse += number % 10;
		number /= 10;
		if (number > 0)
			reverse *= 10;
	}
	while (reverse != 0)
	{
		c = reverse % 10 + '0';
		write(1, &c, 1);
		length++;
		reverse /= 10;
	}
	return (length);
}

int ft_print_string(char *str)
{
	int index;

	index = 0;
	while (str[index])
	{
		write(1, &str[index], 1);
		index++;
	}
	return (index);
}

int ft_format(va_list args, char c)
{
	int length;

	length = 0;
	if (c == 's')
		length += ft_print_string(va_arg(args, char *));
	else if (c == 'd')
		length += ft_print_number(va_arg(args, int));
	else if (c == 'x')
		length += ft_print_hex(va_arg(args, int));
	return (length);
}

int ft_printf(char *str, ...)
{
	va_list args;
	int index;
	int length;

	va_start(args, str);
	index = 0;
	length = 0;
	while (str[index])
	{
		if (str[index] == '%')
		{
			index++;
			length += ft_format(args, str[index]);
		}
		else
		{
			write(1, &str[index], 1);
			length++;
		}
		index++;
	}
	return (length);
}

int main()
{
	printf("%d\n", ft_printf("Ciao, %s, %d, %x\n", "sono una stringa", 0, 100));
	printf("%d\n", printf("Ciao, %s, %d, %x\n", "sono una stringa", 0, 100));
	return (0);
}
