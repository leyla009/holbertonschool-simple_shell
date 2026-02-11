#include "main.h"

/**
 * execute_command - Forks a process and executes a command with arguments.
 * @argv: An array of strings (pointers) containing the command and arguments.
 *
 * Return: 0 on success, 1 if fork fails.
 */
int execute_command(char **argv)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork Error");
		return (1);
	}

	if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("./shell");
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}

	return (0);
}
