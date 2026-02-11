#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Environment */
extern char **environ;

/* Function Prototypes */

int execute_command(char **argv);
char *find_path(char *command);
char *_getenv(const char *name);

#endif /* MAIN_H */
