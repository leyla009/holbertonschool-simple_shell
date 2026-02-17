#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * shell_cd - Changes the current working directory.
 * @argv: Array of arguments (argv[0] is "cd").
 * Return: 0 on success, 1 on failure.
 */
int shell_cd(char **argv)
{
	char *target = NULL, cwd[1024];
	char *h_val = _getenv("HOME");
	char *o_val = _getenv("OLDPWD");

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (0);

	if (!argv[1] || _strcmp(argv[1], "$HOME") == 0)
	{
		target = h_val;
	}
	else if (_strcmp(argv[1], "-") == 0)
	{
		target = o_val;
		if (!target)
			target = cwd;
		_puts(target);
		_putchar('\n');
	}
	else
	{
		target = argv[1];
	}

	if (target && chdir(target) == 0)
	{
		_setenv("OLDPWD", cwd);
		if (getcwd(cwd, sizeof(cwd)))
			_setenv("PWD", cwd);
	}
	else
	{
		fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", argv[1]);
	}
	return (0);
}

/**
 * print_env - prints the environment.
 * Return: void.
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		_puts(environ[i]);
		_putchar('\n');
		i++;
	}
}
