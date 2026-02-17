#include "main.h"

/**
 * _itoa - Converts integer to string
 * @n: The integer
 * Return: The string representation
 */
char *_itoa(int n)
{
	char buffer[20];
	int i = 0;
	
	if (n == 0)
		return (_strdup("0"));

	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	buffer[i] = '\0';

	/* Reverse string */
	{
		char *res = _strdup(buffer);
		int start = 0, end = i - 1;
		char temp;

		while (start < end)
		{
			temp = res[start];
			res[start] = res[end];
			res[end] = temp;
			start++;
			end--;
		}
		return (res);
	}
}

/**
 * replace_variables - Replaces variables in argv
 * @argv: Argument vector
 * @status: Pointer to the last exit status
 */
void replace_variables(char **argv, int *status)
{
	int i;
	char *val = NULL;
	char *var_name;

	for (i = 0; argv[i]; i++)
	{
		if (argv[i][0] != '$' || argv[i][1] == '\0')
			continue;

		if (_strcmp(argv[i], "$?") == 0)
		{
			val = _itoa(*status);
		}
		else if (_strcmp(argv[i], "$$") == 0)
		{
			val = _itoa(getpid());
		}
		else
		{
			/* Env variable, e.g. $PATH */
			var_name = argv[i] + 1; /* Skip '$' */
			val = _getenv(var_name);
			if (val)
				val = _strdup(val);
			else
				val = _strdup(""); /* Empty if not found */
		}

		if (val)
		{
			free(argv[i]);
			argv[i] = val;
		}
	}
}

/**
 * free_argv - Frees the argv array and strings inside
 * @argv: The argument array
 */
void free_argv(char **argv)
{
	int i;

	if (!argv)
		return;

	for (i = 0; argv[i]; i++)
		free(argv[i]);
	
	free(argv);
}
