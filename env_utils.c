#include "main.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: the name of the variable (e.g., "PATH")
 * Return: pointer to the value part, or NULL if not found
 */
char *_getenv(const char *name)
{
    int i = 0;
    size_t name_len;

    if (name == NULL || name[0] == '\0')
	    return (NULL);
    name_len = _strlen((char *)name);

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
	int i = 0, j;
	
	if (!name || !value)
		return (-1);
	
	new_var = malloc(_strlen(name) + _strlen(value) + 2);
	if (!new_var) return (-1);
	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0 && environ[i][_strlen(name)] == '=')
		{
			environ[i] = new_var;
			return (0);
		}
	}
	
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (!new_environ) return (free(new_var), -1);

	for (j = 0; j < i; j++)
		new_environ[j] = environ[j];

		new_environ[i] = new_var;
		new_environ[i + 1] = NULL;
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
    size_t name_len;

    if (!name || *name == '\0' || _strchr(name, '='))
	    return (-1);
    name_len = _strlen(name);
    while (environ[i])
    {
        if (_strncmp(environ[i], name, name_len) == 0 && 
			environ[i][name_len] == '=')
        {
            for (j = i; environ[j]; j++)
		    environ[j] = environ[j + 1];
	    return (0);
        }
        i++;
    }
    return (0);
}
