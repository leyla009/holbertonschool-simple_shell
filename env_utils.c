#include "main.h"

char *env_memory_to_free = NULL;

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the variable to find.
 *
 * Return: A pointer to the value within the environment string, or NULL.
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (NULL);

	name_len = _strlen(name);

	while (environ[i])
	{
		if (_strncmp(environ[i], name, name_len) == 0 &&
		    environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @name: Variable name.
 * @value: Variable value.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value)
{
	char *new_var, **new_environ;
	int i = 0, j;
	size_t name_len, value_len;

	if (!name || !value || _strchr(name, '=') != NULL)
		return (-1);

	name_len = _strlen(name);
	value_len = _strlen(value);

	new_var = malloc(name_len + value_len  + 2);
	if (!new_var)
		return (-1);

	env_memory_to_free = new_var;

	_strcpy(new_var, (char *)name);
	_strcat(new_var, "=");
	_strcat(new_var, (char *)value);

	while (environ[i])
	{
		if (_strncmp(environ[i], name, name_len) == 0 &&
		    environ[i][name_len] == '=')
		{
			environ[i] = new_var;
			return (0);
		}
		i++;
	}

	new_environ = malloc(sizeof(char *) * (i + 2));
	if (!new_environ)
	{
		free(new_var);
		return (-1);
	}

	for (j = 0; j < i; j++)
	{
		new_environ[j] = environ[j];
	}

	new_environ[i] = new_var;
	new_environ[i + 1] = NULL;
	environ = new_environ;

	return (0);
}

/**
 * _unsetenv - Remove an environment variable.
 * @name: The variable name to remove.
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
	int i = 0, j;
	size_t name_len;

	if (!name || *name == '\0' || _strchr(name, '=') != NULL)
		return (-1);

	name_len = _strlen(name);

	while (environ[i])
	{
		if (_strncmp(environ[i], name, name_len) == 0 &&
		    environ[i][name_len] == '=')
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
