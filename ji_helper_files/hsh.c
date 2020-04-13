#include "header.h"

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *token, *args[1024], *path, *command = NULL;
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, k = 0, status = 0;
	pid_t child_pid = 0;
	
	if (argc != 1)
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	while (envp[k] != NULL)
	{
		printf("%s\n", envp[k]);
		if (strcmp(strtok(envp[k], "="), "PATH") == 0)
		{
			printf("Found PATH!!!!!\n");
			while ((path = strtok(NULL, ":")) != NULL)
			{
				printf("Path string is : %s\n", path);
			}
		}
		k++;
	}
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");
		characters = getline(&buf, &len, stdin);
		if (characters == -1)
			break;
		j = strlen(buf) - 1;
		buf[j] = '\0';
		i = 0;

		if (strcmp(strtok(envp[k], "="), "PATH") == 0)
		{
			while ((path = strtok(NULL, ":")) != NULL)
			{
		token = strtok(buf, " ");
		command = token;
		printf("command is : %s\n", command);
		/* printf("path is : %s\n", path); */
		/* strcat(path, command); */
		/* printf("path string is : %s\n", path); */
		args[i] = token;
		i++;
		while (token)
		{
			token = strtok(NULL, " ");
			if (token == NULL)
				break;
			args[i] = token;
			i++;
		}
		args[i] = NULL;
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			_exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (execve(args[0], args, envp) == -1)
			{
				perror("./hsh");
				_exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
		}
	}
	free(buf);
	if (isatty(STDIN_FILENO) == 1)
		putchar('\n');
	/* exit(status); */
	return (0);
}
