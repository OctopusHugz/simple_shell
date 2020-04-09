#include "header.h"

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *args[1024], *command;
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
		/* Check if stdin is terminal. If so, print $ */
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");
		
		/* Copy command line to buf */
		characters = getline(&buf, &len, stdin);
		if (characters == -1)
		{
			printf("END OF FILE\n");
			break;
		}

		/* Start over if command line is only '\n' */
		if (buf[0] == '\n' /*  || buf[0] == '' */)
			continue;
		
		/* Change '\n' to '\0' */
		j = strlen(buf) - 1;
		buf[j] = '\0';
					/* CREATE ARGV FOR CHILD EXECVE */
		i = 0;
		command = strtok(buf, " ");
		args[0] = command;
		printf("args[%d] = %s\n", i, args[i]);			
		while (args[i++])
		{
			args[i] = strtok(NULL, " ");
			printf("args[%d] = %s\n", i, args[i]);			
		}
		args[0] = find_right_path(command);		
		printf("forking...\n");
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			free(buf);
			free(command);
			free(*args);
			_exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			/*printf("\tcommand = %s\n", args[0]);
			for (i = 0; args[i]; i++)
				printf("\targument %d = %s\n", i, args[i]);
			for (i = 0; envp[i]; i++)
				printf("\t%s\n", envp[i]);*/
			if (args[0] == NULL /*  || args[0][0] == 10 */)
				break;
			if (execve(args[0], args, envp) == -1)
			{
				perror("./hsh");
				free(buf);
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
	if (isatty(STDIN_FILENO) == 1)
		putchar('\n');
	return (0);
	/* exit(status); */
}