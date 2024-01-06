#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 1

static char *gnl(int fd)
{
	char line[9999];
	char read_line[1];
	char *result;
	int index;

	index = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[0] = '\0';
	while (read(fd, read_line, 1) == 1)
	{
		line[index] = read_line[0];
		line[index + 1] = '\0';
		if (line[index] == '\n')
			break ;
		index++;
	}
	if (line[index] == '\0')
		return (NULL);
	result = malloc(sizeof(char) * index + 1);
	index = 0;
	while (line[index] != '\0')
	{
		result[index] = line[index];
		index++;
	}
	result[index + 1] = '\0';
	return (result);
}

int main(int argc, char *argv[])
{
	int fd;

	if (argc != 2)
		return (0);
	else
		fd = open(argv[1], O_RDONLY);
	printf("fd opened\n");
	printf("%s", gnl(fd));
	printf("%s", gnl(fd));
	printf("%s", gnl(fd));
	printf("%s", gnl(fd));
	printf("%s", gnl(fd));
	printf("%s", gnl(fd));
	return (0);
}
