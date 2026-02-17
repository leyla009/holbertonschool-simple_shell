#include "main.h"

extern char *env_memory_to_free;
extern char **env_array_to_free;

void cleanup_all(char *line, char **argv);
int execute_segment(char *command, int *status);
void process_logical(char *line, int *status);

/**
 * main - Entry point for the simple shell
 * Return: The last exit status
 */
int main(void)
{
	char *line = NULL, *cmd_start;
	size_t len = 0;
	ssize_t nread;
	int status = 0;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_puts(":) ");

		nread = _getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			free(line);
			cleanup_all(NULL, NULL);
			return (status);
		}
		
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Semicolon handling: split by ; first */
		cmd_start = line;
		for (i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == ';')
			{
				line[i] = '\0';
				process_logical(cmd_start, &status);
				cmd_start = &line[i + 1];
			}
		}
		process_logical(cmd_start, &status);
	}
	free(line);
	return (status);
}

/**
 * process_logical - Handles && and || operators
 * @line: The command line segment (already split by ;)
 * @status: Pointer to the last status
 */
void process_logical(char *line, int *status)
{
	char *start = line;
	char *next = NULL;
	int op = 0; /* 0: None, 1: &&, 2: || */
	int prev_op = 0;
	int i;

	while (start)
	{
		/* Find the next logical operator */
		next = NULL;
		op = 0;
		for (i = 0; start[i]; i++)
		{
			if (start[i] == '&' && start[i + 1] == '&')
			{
				op = 1;
				start[i] = '\0'; /* Split string */
				next = start + i + 2;
				break;
			}
			if (start[i] == '|' && start[i + 1] == '|')
			{
				op = 2;
				start[i] = '\0'; /* Split string */
				next = start + i + 2;
				break;
			}
		}

		/* Logic execution decision */
		if (prev_op == 1 && *status != 0)
		{
			/* Prev was && and failed -> Skip current */
		}
		else if (prev_op == 2 && *status == 0)
		{
			/* Prev was || and success -> Skip current */
		}
		else
		{
			execute_segment(start, status);
		}

		start = next;
		prev_op = op;
	}
}

/**
 * execute_segment - Parses and executes a single command part
 * @command: The command string
 * @status: Pointer to status
 * Return: 0 (Always, status is updated via pointer)
 */
int execute_segment(char *command, int *status)
{
	char **argv;
	char *token, *full_path = NULL;
	int i, j, exit_code;

	if (command == NULL || *command == '\0')
		return (0);

	argv = malloc(sizeof(char *) * 32);
	if (argv == NULL)
		return (-1);

	i = 0;
	token = _strtok(command, " \t\n\r");
	while (token != NULL && i < 31)
	{
		argv[i++] = token;
		token = _strtok(NULL, " \t\n\r");
	}
	argv[i] = NULL;

	if (argv[0] == NULL)
	{
		free(argv);
		return (0);
	}

	if (_strcmp(argv[0], "exit") == 0)
	{
		exit_code = *status;
		if (argv[1] != NULL)
		{
			for (j = 0; argv[1][j]; j++)
			{
				if (argv[1][j] < '0' || argv[1][j] > '9')
				{
					fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", argv[1]);
					*status = 2;
					free(argv);
					return (0);
				}
			}
			exit_code = _atoi(argv[1]);
		}
		free(argv);
		cleanup_all(NULL, NULL); /* argv freed above */
		if (env_memory_to_free) free(env_memory_to_free);
		exit(exit_code);
	}
	if (_strcmp(argv[0], "env") == 0)
	{
		print_env();
		*status = 0;
		free(argv);
		return (0);
	}
	if (_strcmp(argv[0], "setenv") == 0)
	{
		if (argv[1] && argv[2])
		{
			if (_setenv(argv[1], argv[2]) == -1)
			{
				fprintf(stderr, "setenv: Error occurred\n");
				*status = -1;
			}
			else
				*status = 0;
		}
		else
		{
			fprintf(stderr, "setenv: usage: setenv VAR VALUE\n");
			*status = 1;
		}
		free(argv);
		return (0);
	}
	if (_strcmp(argv[0], "unsetenv") == 0)
	{
		if (argv[1])
			*status = _unsetenv(argv[1]);
		else
		{
			fprintf(stderr, "unsetenv: Too few arguments\n");
			*status = 1;
		}
		free(argv);
		return (0);
	}
	if (_strcmp(argv[0], "cd") == 0)
	{
		*status = shell_cd(argv);
		free(argv);
		return (0);
	}

	full_path = find_path(argv[0]);
	if (full_path != NULL)
	{
		*status = execute_command(full_path, argv);
		if (full_path != argv[0])
			free(full_path);
	}
	else
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		*status = 127;
	}

	free(argv);
	return (0);
}

/**
 * cleanup_all - Frees all allocated memory
 * @line: Input line buffer
 * @argv: Arguments array
 */
void cleanup_all(char *line, char **argv)
{
	int i;

	if (argv)
		free(argv);
	if (line)
		free(line);
	if (env_memory_to_free)
		free(env_memory_to_free);

	if (env_array_to_free)
	{
		for (i = 0; env_array_to_free[i]; i++)
			free(env_array_to_free[i]);
		free(env_array_to_free);
	}
}
