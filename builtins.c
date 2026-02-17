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
	char *dir, buffer[1024];
	int ret;
	char *cwd;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		return (-1);

	if (argv[1] == NULL) /* Case: cd (arqumentsiz) */
	{
		dir = _getenv("HOME");
		if (!dir)
		{
			/* HƏLL: Əgər HOME yoxdursa, heç nə etmə, return 0 qaytar */
			return (0);
		}
	}
	else if (_strcmp(argv[1], "-") == 0) /* Case: cd - */
	{
		dir = _getenv("OLDPWD");
		if (!dir)
		{
			_puts(cwd);
			_putchar('\n');
			return (0);
		}
		_puts(dir);
		_putchar('\n');
	}
	else /* Case: cd /path */
	{
		dir = argv[1];
	}

	ret = chdir(dir);

	if (ret == -1)
	{
		fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", argv[1]);
		return (0);
	}
	else
	{
		_setenv("OLDPWD", cwd);
		_setenv("PWD", getcwd(buffer, 1024));
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
