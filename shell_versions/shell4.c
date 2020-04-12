#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *rev_string(char *s);

void free_grid(char **grid, int height);

int is_valid_command(char *buf);

char *_getenv(char *name);

int main(int argc, char *argv[])
{
	extern char **environ;
	char *buf = NULL, *token, *args[4096], *dirs[4096], *path = _getenv("PATH"), *path_dup = strdup(path), *command, *dir, *slash, *dir_string;
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, l = 0, status = 0, valid = 0;
	pid_t child_pid = 0;
	struct stat st;

	if (argc != 1)
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");
		characters = getline(&buf, &len, stdin);
		if (characters == -1)
		{
			printf("Received EOF\n");
			free(command);
			free(slash);
			free(*args);
			break;
		}

		/* Add if buf is empty string or if command is not found by stat*/
		/* if (buf[0] == '\n' || buf[0] == '')
			continue; */

		/* IMPLEMENT IS_VALID_COMMAND HERE */
		valid = is_valid_command(buf);
		/* printf("valid is: %d\n", valid); */
		if (valid == -1)
			continue;
		if (valid == 1)
		{
			;
		}
		/* ONLY COMMAND HAS BEEN PROVIDED SO NO NEED TO REV STRING, SIMPLY CONCAT */

		j = strlen(buf) - 1;
		buf[j] = '\0';
		i = 0;
		token = strtok(buf, " ");
		args[i] = strdup(token);
		command = strdup(args[0]);
		if ((strcmp(command, "exit") == 0))
		{
			free(command);
			break;
		}
		/* printf("args[0] is: %s\n", args[0]); */
		i++;
		while (token)
		{
			token = strtok(NULL, " ");
			/* printf("token is: %s\n", token); */
			if (token == NULL)
				break;
			args[i] = strdup(token);
			/* printf("args[1] is: %s\n", args[1]); */
			i++;
		}
		args[i] = NULL;

		if (valid == 0)
		{
			command = rev_string(command);
			strtok(command, "/");
			strcat(command, "/");
			rev_string(command);
			/* printf("command is: %s\n", command); */
		}
		else if (valid == 1)
		{
			slash = malloc(strlen(command) + 2);
			strcpy(slash, "/");
			strcat(slash, command);
			/* printf("command is: %s\n", command);
			printf("slash is: %s\n", slash); */
		}
		printf("----------------------------\n");

		/* dir_string = strtok(path, ":"); */
		/* strcat(dir_string, "/"); */
		/* strcat(dir_string, command); */
		/* strcat(dir_string, slash);
		printf("dir_string is: %s\n", dir_string);
		dirs[l] = strdup(dir_string); */

		dir_string = strtok(path_dup, ":");
		dir = strdup(dir_string);

		/* dirs[l] = strdup(strcat(dir, slash));
		printf("dirs[0] is: %s\n", dirs[0]);
		l++; */

		dir = malloc(strlen(dir_string) + strlen(slash) + 1);
		if (dir == NULL)
			return (0);
		strcpy(dir, dir_string);
		strcat(dir, slash);
		dirs[l] = strdup(dir);
		printf("dirs[%d] is: %s\n", l, dirs[l]);
		l++;

		while ((dir_string = strtok(NULL, ":")))
		{
			dir = malloc(strlen(dir_string) + strlen(slash) + 1);
			if (dir == NULL)
				return (0);
			strcpy(dir, dir_string);
			strcat(dir, slash);
			dirs[l] = strdup(dir);
			printf("dirs[%d] is: %s\n", l, dirs[l]);
			if ((stat(dirs[l], &st) == 0))
			{
				printf("command found!\n");
				child_pid = fork();
				if (child_pid == -1)
				{
					perror("fork");
					free(buf);
					free_grid(dirs, l);
					free(command);
					free(*args);
					_exit(EXIT_FAILURE);
				}
				if (child_pid == 0)
				{
					/* if (args[0] == NULL)
								break; */
					if (execve(args[l], args, environ) == -1)
					{
						perror("./hsh");
						free(buf);
						free_grid(dirs, l);
						free(command);
						free(*args);
						free(slash);
						printf("Command didn't run and is done freeing\n");
						_exit(EXIT_FAILURE);
					}
				}
				else
				{
					if (wait(&status) == -1)
						perror("wait");
				}
				free(command);
				command = NULL;
				/* command = ""; */
				free(slash);
				slash = NULL;
				free(*args);
				*args = NULL;
				free(dirs[l]);
				printf("Child finished and is done freeing\n");
				/* free(slash); */
				break;
			}
			l++;
		}

		/* l++; */
		/* } */

		printf("----------------------------\n");

		printf("Child has finished executing\n");

		printf("----------------------------\n");

		/* child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			free(buf);
			free_grid(dirs, l);
			free(command);
			free(*args);
			_exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (args[0] == NULL)
				break;
			if (execve(args[0], args, envp) == -1)
			{
				perror("./hsh");
				free(buf);
				free_grid(dirs, l);
				free(command);
				free(*args);
				_exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		} */
		/* free(command);
		command = NULL;
		free(*args);
		*args = NULL; */
	}
	printf("Exited while loop\n");
	/* command = NULL; */
	free(buf);
	free_grid(dirs, l);
	/* free(command); */
	/* free(*args); */
	/* free(slash); */
	if (isatty(STDIN_FILENO) == 1)
		putchar('\n');
	return (0);
	/* exit(status); */
}

char *rev_string(char *s)
{
	int i, len;
	char *beg, *end, tmp;

	for (len = 0; s[len] != '\0'; len++)
	{
		;
	}
	beg = s;
	end = s;

	for (i = 0; i < len - 1; i++)
	{
		end++;
	}

	/* swap chars until halfway */

	for (i = 0; i < len / 2; i++)
	{
		tmp = *beg;
		*beg = *end;
		*end = tmp;
		beg++;
		end--;
	}
	return (s);
}

void free_grid(char **grid, int height)
{
	int rows;

	if (height > 0)
	{
		for (rows = 0; rows < height; rows++)
			free(grid[rows]);
	}
	/* free(grid); */
}

int is_valid_command(char *buf)
{
	if (buf[0] == '\n')
		return (-1);

	if (buf[0] == '/')
		printf("path included\n");
	else
	{
		printf("path not included\n");
		return (1);
	}
	return (0);
}

char *_getenv(char *name)
{
	extern char **environ;
	int i = 0;

	while (environ[i])
		if (strcmp(strtok(environ[i++], "="), name) == 0)
			return (strtok(NULL, "\n"));

	return (NULL);
}
