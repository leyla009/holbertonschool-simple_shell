#include "main.h"

extern char **environ;

/**
 * shell_cd - Changes the current working directory.
 * @argv: Array of arguments (argv[0] is "cd").
 * Return: 0 on success, -1 on failure.
 */
int shell_cd(char **argv)
{
    char *target = NULL, cwd[1024];
    char *home = _getenv("HOME"), *oldpwd = _getenv("OLDPWD");

    if (!argv[1]) /* Case: cd */
        target = home;
    else if (_strcmp(argv[1], "-") == 0) /* Case: cd - */
    {
        target = oldpwd;
        if (target)
            _puts(target), _putchar('\n'); /* Requirement: print path on 'cd -' */
    }
    else /* Case: cd [DIRECTORY] */
        target = argv[1];

    if (!target)
        return (0);

    getcwd(cwd, sizeof(cwd));
    if (chdir(target) != 0)
    {
        fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", target);
        return (-1);
    }

    _setenv("OLDPWD", cwd); 
    getcwd(cwd, sizeof(cwd));
    _setenv("PWD", cwd);

    return (0);
}

/**
 * print_env - prints the environment
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
