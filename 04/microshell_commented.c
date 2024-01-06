#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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

int ft_exe(char *argv[], int index, int stdin, char *env[])
{
	argv[index] = NULL;
	// fd management here
	dup2(stdin, 0); // duplicate stdin on STDIN
	close(stdin); // delete the original
	// execution is now set to read from the previous chunk of command
	execve(argv[0], argv, env); // when execve returns, it just quits the child process. FD changes are deleted
	return (ft_error("error: cannot execute ", argv[0]));
}

int main(int argc, char *argv[], char *env[])
{
	int index, stdin, pipes[2];

	(void)argc;
	stdin = dup(0);
	index = 0;
	while (argv[index] && argv[index + 1])
	{
		argv = &argv[index + 1];
		index = 0;
		while (argv[index] && strcmp(argv[index], ";") && strcmp(argv[index], "|"))
			index++;
		if (!strcmp(argv[0], "cd"))
		{
			if (index != 2)
				ft_error("error: cd: bad arguments", NULL);
			else if (chdir(argv[1]) != 0)
				ft_error("error: cd: cannot change directory to ", argv[1]);
		}
		else if (!argv[index] || !strcmp(argv[index], ";"))
		{
			if (fork() == 0)
			{
				if (ft_exe(argv, index, stdin, env))
					return (1);
			}
			else
			{
				// fd management here
				close(stdin); // delete the duplicate of STDIN
				waitpid(-1, NULL, WUNTRACED); // execute child process
				stdin = dup(0); // re-duplicate the current STDIN in tmp stdin
			}
		}
		else if (!strcmp(argv[index], "|"))
		{
			pipe(pipes);
			if (fork() == 0)
			{
				// fd management here
				dup2(pipes[1], 1); // overwrite STDOUT with duplicate of pipes[1]
				close(pipes[1]); // close the original pipes[1]
				close(pipes[0]); // close the input fd of pipes
				// the child process is set to write in pipes[1]
				if (ft_exe(argv, index, stdin, env))
					return (1);
			}
			else
			{
				// fd management here
				close(stdin); // free stdin to replace it
				close(pipes[1]); // we won't use the write fd of pipes
				stdin = pipes[0]; // the next command will read from pipes[0]
			}
		}
	}
	close(stdin); // close stdin completely
	return (0);
}