#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int ft_error(char *str1, char *str2)
{
	while (*str1)
		write(2, str1++, 1);
	if (str2)
		while (*str2)
			write(2, str2++, 1);
	write(2, "\n", 1);
	return (1);
}

int ft_exe(char *argv[], int index, int tmp, char *env[])
{
	argv[index] = NULL;
	dup2(tmp, 0);
	close(tmp);
	execve(argv[0], argv, env);
	return (ft_error("error: cannot execute ", argv[0]));
}

int main(int argc, char *argv[], char *env[])
{
	int index, tmp, pipes[2];

	(void)argc;
	tmp = dup(0);
	index = 0;
	while (argv[index] && argv[index + 1])
	{
		argv = &argv[index + 1];
		index = 0;
		while (argv[index] && strcmp(argv[index], "|") && strcmp(argv[index], ";"))
			index++;
		if (!strcmp(argv[0], "cd"))
		{
			if (index != 2)
				ft_error("error: cd: bad arguments", NULL);
			else if (chdir(argv[1]) != 0)
				ft_error("error: cd: cannot change directory to ", argv[1]);
		}
		else if (index != 0 && (!argv[index] || !strcmp(argv[index], ";")))
		{
			if (!fork())
			{
				if (ft_exe(argv, index, tmp, env))
					return (1);
			}
			else
			{
				close(tmp);
				waitpid(-1, NULL, WUNTRACED);
				tmp = dup(0);
			}
		}
		else if (index != 0 && !strcmp(argv[index], "|"))
		{
			pipe(pipes);
			if (!fork())
			{
				dup2(pipes[1], 1);
				close(pipes[1]);
				close(pipes[0]);
				if (ft_exe(argv, index, tmp, env))
					return (1);
			}
			else
			{
				close(tmp);
				close(pipes[1]);
				waitpid(-1, NULL, WUNTRACED);
				tmp = pipes[0];
			}
		}
	}
	close(tmp);
	return (0);
}