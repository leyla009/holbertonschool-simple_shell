#include "main.h"
#include <sys/stat.h>

/**
 * find_path - Finds the full path of a command.
 * @command: The command to find (e.g., "ls").
 *
 * Return: The full path if found, or a copy of command if not.
 */
char *find_path(char *command)
{
	char *path, *path_copy, *token, *file_path;
	struct stat st;
	int cmd_len, dir_len;

	/* If command is already an absolute path, checks it directly */
	if (stat(command, &st) == 0)
		return (strdup(command));

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	cmd_len = strlen(command);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		dir_len = strlen(token);
		file_path = malloc(dir_len + cmd_len + 2);
		if (!file_path)
			break;

		strcpy(file_path, token);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, &st) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
