#ifndef MAIN_H
#define MAIN_H
#define BUF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Environment */
extern char **environ;

/* Custom String Functions */
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *src);
char *_strchr(const char *s, char c);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strtok(char *str, const char *delim);
char *_getenv(const char *name);
int _atoi(char *s);
/* Function Prototypes */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int execute_command(char **argv);
char *find_path(char *command);
int _setenv(const char *name, const char *value);
int _unsetenv(const char *name);

/* Memory Management */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_argv(char **argv);

#endif /* MAIN_H */
