#ifndef GUARD
#define GUARD

/* Header files go here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/* Typedefs go here */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} dir_t;

/* Colson Prototypes go here */
char *rev_string(char *s);
void free_grid(char **grid, int height);
/* Prototypes go here */
char *_getenv(char *name);
char *find_right_path(char *command);
dir_t *make_path_list(char *path);
dir_t *add_dir(dir_t **head, const char *dir);
void free_list(dir_t *head);

#endif

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *args[1024], *command;
	size_t size = 0;
	int i, status = 0;
	pid_t child_pid = 0;

	if (argc != 1) /* Print usage if argc is off */
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]), exit(EXIT_FAILURE);

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1) /* Print $ if stdin is terminal */
			printf("$ ");

		if (getline(&buf, &size, stdin) == -1) /* Copy command line to buf */
			break;

		if (buf[0] == '\n') /* Start over if buf is just '\n' */
			continue;

		i = strlen(buf) - 1; /* Change newline to null byte */
		buf[i] = '\0';




		command = strtok(buf, " ");
		args[0] = strdup(command); /* CREATE ARGV FOR CHILD EXECVE */
		for (i = 1; args[i++];)
		{
			command = strtok(NULL, " ");
			args[i] = strdup(command);
		}

		args[0] = strdup(find_right_path(args[0])); /* Add PATH to command */





		child_pid = fork(); /* Fork it! */

		if (child_pid == -1) /* If fork fails, exit */
		{
			perror("Fork failure");
			free(buf);
			free(args[0]);
			_exit(EXIT_FAILURE);
		}
		if (child_pid == 0) /* If child process, execute command */
		{
			if (execve(args[0], args, envp) == -1)
			{ /* If exec fails, exit */
				perror("Execution failure");
				free(buf);
				free(args[0]);
				_exit(EXIT_FAILURE);
			}
		}
		if (wait(&status) == -1) /* If waiting failed, print error */
			perror("Failed to wait");

		free(args[0]); /* Free command */
	}
	free(buf);					   /* Free arguments buffer */
	if (isatty(STDIN_FILENO) == 1) /* Print newline before exiting */
		putchar('\n');
	return (0);
}

char *_getenv(char *name)
{
	extern char **environ;
	size_t size = sizeof(char) * strlen(name) + 1;
	char *matcher = malloc(size);
	int i;

	/* matcher = '\0'; */
	for (i = 0; environ[i]; i++)
	{
		strncpy(matcher, environ[i], size - 1);
		if (strcmp(matcher, name) == 0)
			break;
	}
	free(matcher);
	return (environ[i]);
}

char *find_right_path(char *command)
{
	struct stat st;
	char *path = NULL, *dir = NULL, *ptr = NULL;
	size_t size;
	int i = 0, j = 0;

	if (command == NULL)
		return (NULL);
	ptr = _getenv("PATH");
	while (ptr[i] != '=')
		i++;
	dir = ptr + i + 1;
	for (i = 0; dir[i] != '\0'; i++)
	{
		ptr = dir + i;
		for (j = 0; dir[i] != ':' && dir[i] != '\0'; j++, i++)
			;
		if (dir[i] == '\0')
			break;
		size = sizeof(char) * (j + strlen(command) + 2);
		path = realloc(path, size);
		strncpy(path, ptr, j);
		path[j] = '\0';
		path = strcat(strcat(path, "/"), command);
		if (stat(path, &st) == 0)
			return (path);
	}
	free(path);
	return (command);
}
