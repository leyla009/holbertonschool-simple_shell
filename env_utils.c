#include "main.h"
#include <stdlib.h>

char *env_memory_to_free = NULL;
char **env_array_to_free = NULL;

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the variable to find.
 * Return: A pointer to the value, or NULL.
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
			return (environ[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

/**
 * _make_env_copy - Creates a deep copy of environ to allow freeing.
 * Return: 0 on success, -1 on failure.
 */
int _make_env_copy(void)
{
	int i = 0, j;
	char **new_env;

	if (env_array_to_free) /* Already copied */
		return (0);

	while (environ[i])
		i++;

	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (-1);

	for (j = 0; j < i; j++)
	{
		new_env[j] = malloc(_strlen(environ[j]) + 1);
		if (!new_env[j])
		{
			/* Clean up partial allocation if needed */
			return (-1);
		}
		_strcpy(new_env[j], environ[j]);
	}
	new_env[j] = NULL;
	environ = new_env;
	env_array_to_free = new_env; /* Mark for cleanup */
	return (0);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @name: Variable name.
 * @value: Variable value.
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value)
{
	char *new_var, **new_env;
	int i = 0, len;

	if (!name || !value)
		return (-1);
	if (_make_env_copy() == -1) /* Ensure we own the memory */
		return (-1);

	len = _strlen(name) + _strlen(value) + 2;
	new_var = malloc(len);
	if (!new_var)
		return (-1);
	_strcpy(new_var, (char *)name);
	_strcat(new_var, "=");
	_strcat(new_var, (char *)value);

	while (environ[i])
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0 &&
		    environ[i][_strlen(name)] == '=')
		{
			free(environ[i]); /* Safe to free now */
			environ[i] = new_var;
			return (0);
		}
		i++;
	}
	/* Add new variable */
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	for (i = 0; environ[i]; i++)
		new_env[i] = environ[i];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(env_array_to_free); /* Free old array backbone */
	environ = new_env;
	env_array_to_free = new_env;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable.
 * @name: The variable name to remove.
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
	int i = 0, j;
	size_t len;

	if (!name || !env_array_to_free) /* Cannot unset OS env or empty */
	{
		if (_make_env_copy() == -1) return (-1);
	}
	len = _strlen(name);
	while (environ[i])
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
			return (0);
		}
		i++;
	}
	return (0);
}
