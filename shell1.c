#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *rev_string(char *s);

void free_grid(char **grid, int height);

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *token, *args[1024], *dirs[1024], *path, *command, *dir;
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, k = 0, l = 0, /* m = 0,  */ status = 0;
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

		printf("buf[0] is: %d\n", buf[0]);
		printf("characters is: %d\n", (int)characters);

		if (characters == -1)
			break;
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

		/* DO SOMETHING IF ARGS[0] == \n */

		command = rev_string(command);
		strtok(command, "/");
		strcat(command, "/");
		rev_string(command);
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
			if (args[0] == NULL /*  || args[0][0] == 10 */)
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
