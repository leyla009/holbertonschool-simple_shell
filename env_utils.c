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
