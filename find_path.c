#include "main.h"

/**
 * find_path - Finds the full path of a command using the PATH variable.
 * @command: The command to locate (e.g., "ls").
 *
 * Return: A dynamically allocated string with the full path,
 * or NULL if not found or PATH is unset.
 */
char *find_path(char *command)
{
	char *path, *path_copy, *token, *file_path;
	struct stat st;
	int cmd_len, dir_len;

	if (!command)
		return (NULL);

	if (_strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return (_strdup(command));
		return (NULL);
	}

	path = _getenv("PATH");
	if (!path || strlen(path) == 0)
		return (NULL);

	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	cmd_len = strlen(command);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		dir_len = strlen(token);

		file_path = malloc(dir_len + cmd_len + 2);
		if (!file_path)
		{
			free(path_copy);
			return (NULL);
		}

		_strcpy(file_path, token);
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
