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
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (line[0] != '\0')
			execute_command(line);

		char *start = line;
		while (*start == ' ')
			start++;

		char *end = start + strlen(start) - 1;
		while (end >= start && *end == ' ')
		{
			*end = '\0';
			end--;

		if (*start != '\0')
			execute_command(start);
	}
	return (0);
}
