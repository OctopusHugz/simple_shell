#include "header.h"

int main(int argc, char *argv[], char *envp[])
{
	extern char **environ;
	char *buf = NULL, *args[1024], *path, *command = NULL;
	size_t len = 0;
	ssize_t characters = 0;
	int i = 0, j = 0, status = 0;
	pid_t child_pid = 0;
	dir_t *head;
	
	if (argc != 1)
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	path = _getenv("PATH");
	printf("path = %s\n", path);
	head = make_path_list(path);

	while (1)
	{
		/* Check if terminal is open? */
		if (isatty(STDIN_FILENO) == 1)
			printf("$ ");
		/* Copy command prompt to buffer */
		characters = getline(&buf, &len, stdin);
		if (characters == -1)
			break;
		/* Change newline character to null byte */
		j = strlen(buf) - 1;
		buf[j] = '\0';
						/* CREATE ARGV */
		/* Save first word of command prompt as command */
		command = strtok(buf, " ");
		/* Add path to command before saving... */
		args[0] = find_right_path(head, command);
		/* Save the rest of command prompt as arguments.*/
		i = 0;
		while (args[i++])
			args[i] = strtok(NULL, " ");
						/* CREATE ARGV COMPLETE */
						/* CREATE ENVP */
		/**
		 * envp will need editing once we get to the advanced tasks.
		 * This will require setenv and unsetenv
		 * That code will go here
		 **/
						/* CREATE ENVP COMPLETE */
						/* FORK */
		child_pid = fork();
		/* If fork() = -1, exit */
		if (child_pid == -1)
		{
			perror("fork");
			/* Elucidate me on what's going on here */
			exit(EXIT_FAILURE);
		}
		/* If fork() = 0, you're the child! Head to execve... */
		if (child_pid == 0)
		{
						/* EXECUTE COMMAND */
									/* Check inputs to exec */
			printf("\t\tNEW PROCESS\n");
			printf("\t\tcommand = %s\n", args[0]);
			for (i = 1; args[i]; i++)
				printf("argument %d = %s\n", i, args[i]);
			for (i = 0; envp[i]; i++)
				printf("\t\t\t%s\n", environ[i]);
			if (execve(args[0], args, environ) == -1)
			{
				perror("./hsh");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* You're the parent. Wait for child to end...*/
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
