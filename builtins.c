#include "main.h"

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

    getcwd(cwd, sizeof(cwd)); /* Capture current for OLDPWD update */
    if (chdir(target) != 0)
    {
        /* Use your custom error printer here */
        perror("hsh"); 
        return (-1);
    }

    _setenv("OLDPWD", cwd); /* Update OLDPWD with where we were */
    getcwd(cwd, sizeof(cwd)); /* Get new location */
    _setenv("PWD", cwd); /* Update PWD with where we are now */

    return (0);
}
