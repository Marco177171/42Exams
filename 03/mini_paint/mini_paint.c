#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

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

void ft_free(char **matrix, int h)
{
	int index;

	index = 0;
	while (index < h)
	{
		free(matrix[index]);
		index++;
	}
	free(matrix);
}

int ft_check(float i, float j, float cx, float cy, float radius)
{
	float distance;

	distance = sqrtf(powf(cx - j, 2) + powf(cy - i, 2));
	if (distance <= radius)
	{
		if (radius - distance < 1.0000)
			return (1);
		return (2);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	FILE *file;
	int i, j, w, h, scan;
	float cx, cy, radius;
	char back, id, fill;
	char **result;

	if (argc != 2)
		return (ft_error("Error: argument\n"));
	file = fopen(argv[1], "r");
	if (!file)
		return (ft_error("Error: Operation file corrupted\n"));
	if (fscanf(file, "%d %d %c\n", &w, &h, &back) != 3)
		return (ft_error("Error: Operation file corrupted\n"));
	if (w > 300 || w < 1 || h > 300 || h < 1)
		return (ft_error("Error: Operation file corrupted\n"));
	result = malloc (sizeof(char *) * h + 1);
	if (!result)
		return (ft_error("Error: Operation file corrupted\n"));
	result[h] = NULL;
	i = 0;
	while (i < h)
	{
		result[i] = malloc(sizeof(char) * w + 1);
		if (!result[i])
		{
			ft_free(result, h);
			return (ft_error("Error: Operation file corrupted\n"));
		}
		memset(result[i], back, w);
		result[i][w] = '\0';
		i++;
	}
	scan = fscanf(file, "%c %f %f %f %c\n", &id, &cx, &cy, &radius, &fill);
	while (scan == 5)
	{
		if (radius <= 0 || (id != 'C' && id != 'c'))
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
				if (ft_check((float)i, (float)j, cx, cy, radius) == 1 ||
					(ft_check((float)i, (float)j, cx, cy, radius) == 2 && id == 'C'))
					result[i][j] = fill;
				j++;
			}
			i++;
		}
		scan = fscanf(file, "%c %f %f %f %c\n", &id, &cx, &cy, &radius, &fill);
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