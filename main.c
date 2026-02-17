#include "main.h"

/* --- GLOBAL VARIABLE DEFINITIONS --- */
/* Bu sətirlər mütləq olmalıdır ki, linker xəta verməsin */
char *env_memory_to_free = NULL;
char **env_array_to_free = NULL;

void cleanup_all(char *line, char **argv);
int execute_segment(char *command, int *status);
void process_logical(char *line, int *status);

/**
 * main - Entry point for the simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * Return: The last exit status
 */
int main(int argc, char **argv)
{
	char *line = NULL, *cmd_start;
	size_t len = 0;
	ssize_t nread;
	int status = 0;
	int i;
	int fd = STDIN_FILENO; 

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
			return (127);
		}
	}

	while (1)
	{
		if (isatty(STDIN_FILENO) && fd == STDIN_FILENO)
			_puts(":) ");

		nread = _getline(&line, &len, fd);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO) && fd == STDIN_FILENO)
				_putchar('\n');
			free(line);
			cleanup_all(NULL, NULL);
			if (fd != STDIN_FILENO)
				close(fd);
			return (status);
		}
		
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

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
	
	if (fd != STDIN_FILENO)
		close(fd);
	free(line);
	return (status);
}

void process_logical(char *line, int *status)
{
	char *start = line;
	char *next = NULL;
	int op = 0; 
	int prev_op = 0;
	int i;

	while (start)
	{
		next = NULL;
		op = 0;
		for (i = 0; start[i]; i++)
		{
			if (start[i] == '&' && start[i + 1] == '&')
			{
				op = 1;
				start[i] = '\0';
				next = start + i + 2;
				break;
			}
			if (start[i] == '|' && start[i + 1] == '|')
			{
				op = 2;
				start[i] = '\0';
				next = start + i + 2;
				break;
