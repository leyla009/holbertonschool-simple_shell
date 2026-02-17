#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

extern char **environ;

/**
 * shell_cd - Changes the current working directory.
 * @argv: Array of arguments (argv[0] is "cd").
 * Return: 0 on success.
 */
int shell_cd(char **argv)
{
    char *target = NULL, cwd[1024], *old_pwd = NULL;
    char *h_val = _getenv("HOME"), *o_val = _getenv("OLDPWD");

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        free(h_val); free(o_val);
        return (1);
    }

    if (!argv[1] || _strcmp(argv[1], "$HOME") == 0)
        target = h_val;
    else if (_strcmp(argv[1], "-") == 0)
    {
        if (!o_val) /* OLDPWD yoxdursa,  */
            target = cwd;
        else
            target = o_val;
        _puts(target);
        _putchar('\n');
    }
    else
        target = argv[1];

    if (target && chdir(target) == 0)
    {
        _setenv("OLDPWD", cwd);
        if (getcwd(cwd, sizeof(cwd)))
            _setenv("PWD", cwd);
    }
    else if (target)
    {

        fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", argv[1]);
    }

    if (h_val) free(h_val);
    if (o_val) free(o_val);

    return (0);
}
