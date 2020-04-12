#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *rev_string(char *s);

void free_grid(char **grid, int height);

int is_valid_command(char *buf);

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *token, *args[1024], *dirs[1024], *path, *command, *dir;
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, k = 0, l = 0, /* m = 0,  */ status = 0, valid = 0;
	pid_t child_pid = 0;

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
			break;

		/* Add if buf is empty string or if command is not found by stat*/
		/* if (buf[0] == '\n' || buf[0] == '')
			continue; */

		/* IMPLEMENT IS_VALID_COMMAND HERE */
		valid = is_valid_command(buf);
		printf("valid is: %d\n", valid);
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
		i++;
		while (token)
		{
			token = strtok(NULL, " ");
			if (token == NULL)
				break;
			args[i] = strdup(token);
			i++;
		}
		args[i] = NULL;
		command = strdup(args[0]);

		if (valid == 0)
		{
			command = rev_string(command);
			strtok(command, "/");
			strcat(command, "/");
			rev_string(command);
		}
		else if (valid == 1)
		{
			;
		}
		printf("command is: %s\n", command);
		printf("----------------------------\n");

		while (envp[k] != NULL)
		{
			if (strcmp(strtok(envp[k], "="), "PATH") == 0)
			{
				path = strtok(NULL, ":");
				while ((path = strtok(NULL, ":")))
				{
					dir = malloc(strlen(path) + strlen(command) + 1);
					if (dir == NULL)
						return (0);
					strcpy(dir, path);
					strcat(dir, command);
					dirs[l] = strdup(dir);

					/* ADD STAT() CALL HERE WITH DIRS[L]????? */
					/* AND THEN FORK IF IT'S FOUND? */

					free(dir);
					l++;
				}
				break;
			}
			k++;
		}

		printf("----------------------------\n");

		/* if ((stat(dirs[l], &st) == 0) */

		printf("----------------------------\n");

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
		}
		free(command);
		command = NULL;
		free(*args);
		*args = NULL;
	}
	command = NULL;
	free(buf);
	free_grid(dirs, l);
	free(command);
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
