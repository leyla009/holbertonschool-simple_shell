#include "main.h"

/**
 * shell_cd - Changes the current directory of the process
 * @argv: Arguments array (argv[1] is the directory)
 * Return: 0 on success, 1 on failure
 */
int shell_cd(char **argv)
{
	char *dir;
	char buffer[1024];
	char *cwd;

	if (argv[1] == NULL)
	{
		dir = _getenv("HOME");
		if (!dir)
			dir = _getenv("PWD");
	}
	else if (_strcmp(argv[1], "-") == 0)
	{
		dir = _getenv("OLDPWD");
		if (!dir)
		{
			_puts(getcwd(buffer, 1024));
			return (0);
		}
		_puts(dir);
	}
	else
	{
		dir = argv[1];
	}

	if (chdir(dir) == -1)
	{
		fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", argv[1]);
		return (2); /* Error status for cd failure */
	}

	/* Update PWD and OLDPWD */
	cwd = getcwd(buffer, 1024);
	if (cwd)
	{
		_setenv("OLDPWD", _getenv("PWD"));
		_setenv("PWD", cwd);
	}
	
	return (0);
}
