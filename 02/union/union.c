#include <unistd.h>

int verify(char *string, char character, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (string[i] == character)
			return (0);
		i++;
	}
	return (1);
}

void ft_union(char *str1, char *str2)
{
	int index;
	int length;

	index = 0;
	while (str1[index] != '\0')
	{
		if (verify(str1, str1[index], index) == 1)
			write(1, &str1[index], 1);
		index++;
	}
	length = index;
	index = 0;
	while (str2[index] != '\0')
	{
		if (verify(str2, str2[index], index) == 1)
		{
			if (verify(str1, str2[index], length) == 1)
				write(1, &str2[index], 1);
		}
		index++;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	return (0);
}
