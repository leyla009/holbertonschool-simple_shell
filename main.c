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
	int status = 0;

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
			char *full_path = find_path(argv[0]);
			if (full_path != NULL)
			{
				char *temp_cmd = argv[0];
				argv[0] = full_path;
				
				execute_command(argv);
				
				argv[0] = temp_cmd;
				free(full_path);
			}
			else
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
				status = 127;
			}
		}

	}

	return(status);
}
