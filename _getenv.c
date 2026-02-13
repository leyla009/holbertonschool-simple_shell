#include "main.h"

/**
 * _getenv - Searches the environment for a variable name.
 * @name: The name of the environment variable (e.g., "PATH").
 *
 * Return: A pointer to the value string, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i, len;

	if (name == NULL || environ == NULL)
		return (NULL);

	len = 0;
	while (name[len])
		len++;

	for (i = 0; environ[i] != NULL; i++)
	{
		/* Checks if current env string starts with 'name=' */
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			/* Returns the string starting after the '=' */
			return (environ[i] + len + 1);
		}
	}

	return (NULL);
}
