#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

char *_getenv(char *key);
int key_match(char *s1, char *s2);
size_t _strlen(char *s);
char *_strdup(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
char *str_to_token(char *new_str, const char *delims);
char *get_program_path(char *program);
size_t gettokens(char *token_arr[], char *line);
int print_error_message(char *shell_name, int line_num, char *program);
void stderr_int_print(int n);
void stderr_print(char *str);
void print_env(void);
void print(char *str);
int fork_and_execute(char *command, char **token_arr, char **envp);

#endif /* SHELL_H */
