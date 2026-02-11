#include "main.h"

/**
 * execute_command - Forks a process and executes a command.
 * @command: The full path to the executable.
 *
 * Return: 0 on success, 1 on failure.
 */
int execute_command(char *command)
{
	pid_t child_pid;
	int status;
	char *args[2];

	/* Prepare arguments for execve: [0] is command, [1] is NULL */
	args[0] = command;
	args[1] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}

	if (child_pid == 0)
	{
		/* We are in the Child Process */
		if (execve(command, args, environ) == -1)
		{
			perror("./shell");
			exit(1);
		}
	}
	else
	{
		/* We are in the Parent Process */
		wait(&status);
	}

	return (0);
}
