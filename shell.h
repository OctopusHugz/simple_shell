#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

char *_getenv(char *name);

char *find_right_path(char *command);

char *make_av(char *av[], char *line);

void print_env(char *envp[]);

#endif /* SHELL_H */
