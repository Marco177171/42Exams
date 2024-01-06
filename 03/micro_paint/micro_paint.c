#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int ft_strlen(char *str)
{
	int index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

int ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int ft_check(float i, float j, float ox, float oy, float rh, float rw)
{
	if (i >= oy && i <= oy + rh && j >= ox && j <= ox + rw)
	{
		if (i - oy < 1.0000 || (oy + rh) - i < 1.0000 || j - ox < 1.0000 || (ox + rw) - j < 1.0000)
			return (2); // is on the border
		return (1); // is in the rectangle
	}
	return (0);
}

void ft_free(char **matrix, int h)
{
	int index;

	index = 0;
	while(index < h)
	{
		free(matrix[index]);
		index++;
	}
	free(matrix);
}

int main(int argc, char *argv[])
{
	FILE *file;
	int w, h, i, j, scan;
	float ox, oy, rw, rh;
	char back, fill, id;
	char **result;

	if (argc != 2)
		return (ft_error("Error: argument\n"));
	file = fopen(argv[1], "r");
	if (!file)
		return (ft_error("Error: Operation file corrupted\n"));
	if (fscanf(file, "%d %d %c\n", &w, &h, &back) != 3)
		return (ft_error("Error: Operation file corrupted\n"));
	if (w < 1 || w > 300 || h < 1 || h > 300)
		return (ft_error("Error: Operation file corrupted\n"));
	result = malloc (sizeof(char *) * h + 1);
	result[h] = NULL;
	if (!result)
		return (ft_error("Error: Operation file corrupted\n"));
	i = 0;
	while (i < h)
	{
		result[i] = malloc (sizeof(char) * w + 1);
		if (!result[i])
			return (ft_error("Error: Operation file corrupted\n"));
		memset(result[i], back, w + 1);
		result[i][w] = '\0';
		i++;
	}
	scan = fscanf(file, "%c %f %f %f %f %c\n", &id, &ox, &oy, &rw, &rh, &fill);
	while (scan == 6)
	{
		if (rh <= 0 || rw <= 0 || (id != 'r' && id != 'R'))
		{
			ft_free(result, h);
			return (ft_error("Error: Operation file corrupted\n"));
		}
		i = 0;
		while (i < h)
		{
			j = 0;
			while (j < w)
			{
				if (ft_check((float)i, (float)j, ox, oy, rh, rw) == 2 ||
					(ft_check((float)i, (float)j, ox, oy, rh, rw) == 1 && id == 'R'))
					result[i][j] = fill;
				j++;
			}
			i++;
		}
		scan = fscanf(file, "%c %f %f %f %f %c\n", &id, &ox, &oy, &rw, &rh, &fill);
	}
	if (scan != -1)
	{
		ft_free(result, h);
		return (ft_error("Error: Operation file corrupted\n"));
	}
	i = 0;
	while (i < h)
	{
		write(1, result[i], ft_strlen(result[i]));
		write(1, "\n", 1);
		i++;
	}
	ft_free(result, h);
	return (0);
}