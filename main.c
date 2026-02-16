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
		token = _strtok(line, " ");
		while (token != NULL && i < 31)
		{
			argv[i++] = token;
			token = _strtok(NULL, " ");
		}
		argv[i] = NULL;

		if (argv[0] != NULL)
		{
			char *full_path = NULL;
			
			if (_strcmp(argv[0], "exit") == 0)
			{
				int exit_code = status;
				int j;

				for (j = 0; argv[1][j]; j++)
				{

				if (argv[1] != NULL)
				{
					for (j = 0; argv[1][j]; j++)
					{
						if (argv[1][j] < '0' || argv[1][j] > '9')
						{
							fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", argv[1]);
							free(line);
							exit(2);
						}
					}
					exit_code = _atoi(argv[1]);
				}
				free(line);
				exit(exit_code);
			}

			for (j = 0; environ[j]; j++)
			{
				if (_strncmp(environ[j], "VARIABLE=", 9) == 0)
				{
					free(environ[j]);
				}
			}

			free(line);
			exit(exit_code);
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

			if (_strcmp(argv[0], "setenv") == 0)
			{
				if (argv[1] && argv[2])
				{
					if (_setenv(argv[1], argv[2]) == -1)
						fprintf(stderr, "setenv: Error occurred\n");
				}
				else 
					fprintf(stderr, "setenv: Too few arguments\n");

				continue; /* Return to start of loop */
			}

			if (_strcmp(argv[0], "unsetenv") == 0)
			{
				if (argv[1])
				{
					if (_unsetenv(argv[1]) == -1)
						fprintf(stderr, "unsetenv: Error occurred\n");
				}
				else
					fprintf(stderr, "unsetenv: Too few arguments\n");
				continue; /* Return to start of loop */
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
	}
	free(line);
	return (status);
}
