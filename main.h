#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;
extern char *env_memory_to_free;
extern char **env_array_to_free;

/* --- Alias Structure --- */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

extern alias_t *aliases;

/* --- Alias Functions --- */
int shell_alias(char **argv);
char *get_alias_value(char *name);
void free_aliases(alias_t *head);

/* --- Variable Replacement --- */
void replace_variables(char **argv, int *status);

/* --- Core Logic --- */
ssize_t _getline(char **lineptr, size_t *n, int fd);
int execute_command(char *full_path, char **argv);
int shell_cd(char **argv);
void process_logical(char *line, int *status);

/* --- Environment --- */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value);
int _unsetenv(const char *name);
void print_env(void);

/* --- Path Finding --- */
char *find_path(char *command);

/* --- String Helpers --- */
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *src);
char *_strchr(const char *s, char c);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);
void _puts(char *str);
int _putchar(char c);

/* --- Memory Helpers --- */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void cleanup_all(char *line, char **argv);

#endif
