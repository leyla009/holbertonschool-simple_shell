#include "main.h"

/**
 * main - Entry point for the simple shell
 *
 * Return: The last exit status
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[32];
	char *token;
	int i;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf(":) ");

		nread = _getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		i = 0;
		token = strtok(line, " ");
		while (token != NULL && i < 31)
		{
			argv[i++] = token;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;

		if (argv[0] != NULL)
		{
			char *full_path = NULL;
			
			if (_strcmp(argv[0], "exit") == 0)
			{
				free(line);
				exit(status);
			}

			if (_strcmp(argv[0], "env") == 0)
			{
				int i = 0;
				while (environ[i])
				{
					printf("%s\n", environ[i]);
					i++;
				}
				status = 0;
				continue;
			}

			full_path = find_path(argv[0]);

			if (full_path != NULL)
			{
				char *temp_cmd = argv[0];
				argv[0] = full_path;
				status = execute_command(argv);
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
	free(line);
	return (status);
}
