#include "main.h"

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *token;
	char *argv[32];
	int i;


	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			break;
		}

		i = 0;
		token = strtok(line, " \t\n");

		while (token != NULL && i < 31)
		{
			argv[i] = token;
			token = strtok(NULL, " \t\n");
			i++;
		}

		argv[i] = NULL;

		if (argv[0] != NULL)
		{
			execute_command(argv);
		}

	}

	return (0);
}
