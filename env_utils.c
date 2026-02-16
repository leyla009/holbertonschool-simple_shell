#include "main.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: the name of the variable (e.g., "PATH")
 * Return: pointer to the value part, or NULL if not found
 */
char *_getenv(const char *name)
{
    int i = 0;
    size_t name_len = _strlen((char *)name);

    while (environ[i])
    {
	    if (_strncmp(environ[i], (char *)name, name_len) == 0 &&
            environ[i][name_len] == '=')
	    {
		    return (environ[i] + name_len + 1);
	    }
	    i++;
    }
    return (NULL);
}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 * @name: The variable name
 * @value: The variable value
 * * Return: 0 on success, -1 on failure
 */

int _setenv(const char *name, const char *value)
{
	char *new_var, **new_environ;
	int i = 0, j, found = -1;
	size_t name_len = _strlen(name);
	static char **heap_environ = NULL;

	if (!name || !value)
		return (-1);
	name_len = _strlen(name);

	new_var = malloc(name_len + _strlen(value) + 2);
	if (!new_var) return (-1);
	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);

	while (environ[i])
	{
		if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
			found = i;
		i++;
	}
	new_environ = malloc(sizeof(char *) * (i + (found == -1 ? 2 : 1)));
	if (!new_environ) { free(new_var); return (-1); }

	for (j = 0; j < i; j++)
		new_environ[j] = environ[j];

	if (found != -1) 
	{
		new_environ[found] = new_var;
		new_environ[i] = NULL;
	}
	else 
	{
		new_environ[i] = new_var;
		new_environ[i + 1] = NULL;
	}
	if (heap_environ != NULL)
		free(heap_environ);

	heap_environ = new_environ;
	environ = new_environ;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @name: The variable name to remove
 * * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
    int i = 0, j;
    size_t name_len = _strlen(name);

    if (!name || _strchr(name, '=')) return (-1);

    while (environ[i])
    {
        if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            for (j = i; environ[j]; j++)
            {
                environ[j] = environ[j + 1];
            }
            return (0);
        }
        i++;
    }
    return (0);
}
