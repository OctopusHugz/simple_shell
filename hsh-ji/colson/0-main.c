#include "header.h"

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *args[1024];
	size_t size = 0;
	int i, status = 0;
	pid_t child_pid = 0;

	if (argc != 1)								/* Print usage if argc is off */
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]), exit(EXIT_FAILURE);

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)			/* Print $ if stdin is terminal */
			printf("$ ");

		if (getline(&buf, &size, stdin) == -1)	/* Copy command line to buf */
			break;

		if (buf[0] == '\n')						/* Start over if buf is just '\n' */
			continue;

		i = strlen(buf) - 1;					/* Change newline to null byte */
		buf[i] = '\0';

		args[0] = strtok(buf, " ");				/* CREATE ARGV FOR CHILD EXECVE */
		for (i = 0; args[i++];)
			args[i] = strtok(NULL, " ");
		
		args[0] = find_right_path(args[0]);		/* Add PATH to command */

		child_pid = fork();						/* Fork it! */

		if (child_pid == -1)					/* If fork fails, exit */
		{
			perror("Fork failure");
			free(buf);
			free(args[0]);
			_exit(EXIT_FAILURE);
		}
		if (child_pid == 0)						/* If child process, execute command */
		{
			if (execve(args[0], args, envp) == -1)
			{									/* If exec fails, exit */
				perror("Execution failure");
				free(buf);
				free(args[0]);
				_exit(EXIT_FAILURE);
			}
		}
		if (wait(&status) == -1)				/* If waiting failed, print error */
			perror("Failed to wait");

		free(args[0]);							/* Free command */
	}
	free(buf);									/* Free arguments buffer */
	if (isatty(STDIN_FILENO) == 1)				/* Print newline before exiting */
		putchar('\n');
	return (0);
}
