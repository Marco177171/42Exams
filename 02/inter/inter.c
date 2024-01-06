#include <unistd.h>

int check_self(char c, char *str, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int check_other(char *str, char c)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (1);
		index++;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	int index;

	index = 0;
	if (argc == 3)
	{
		while (argv[1][index])
		{
			if (check_self(argv[1][index], argv[1], index) == 0)
			{
				if (check_other(argv[2], argv[1][index]) == 0)
					write(1, &argv[1][index], 1);
			}
			index++;
		}
		index = 0;
		while (argv[2][index])
		{
			if (check_self(argv[2][index], argv[2], index) == 0)
			{
				if (check_other(argv[1], argv[2][index]) == 0)
					write(1, &argv[2][index], 1);
			}
			index++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
