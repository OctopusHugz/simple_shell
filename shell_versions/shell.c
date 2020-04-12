#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *token, *args[1024];
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, status = 0;
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
		j = strlen(buf) - 1;
		buf[j] = '\0';
		i = 0;
		token = strtok(buf, " ");
		args[i] = token;
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

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
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
	return (0);
	/* exit(status); */
}
