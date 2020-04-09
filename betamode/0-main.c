#include "header.h"

int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *av[1024];
	size_t size = 0;
	int status = 0;
	pid_t child_pid = 0;

	if (argc != 1)						/* Print usage if argc is off */
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	av[0] = NULL;					/* I don't know why I have to do this frankly */

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)			/* Print $ if stdin is terminal */
			printf("$ ");

		if (getline(&buf, &size, stdin) == -1)		/* Copy command line to buf */
			break;

		if (buf[0] == '\n')				/* Start over if buf is just '\n' */
			continue;

		make_av(&av, buf);				/* Make argv[] for next exec */
		child_pid = fork();					/* Fork this shit */
		if (child_pid == -1)
			perror("Fork failure");
		else if (child_pid == 0)
		{
			if (execve(av[0], av, envp) == -1)
				perror("Execution failure");
		}
		else
			if (wait(&status) == -1)
				perror("Failed to wait");
			else
				continue;

		_exit(EXIT_FAILURE);
	}
	free(buf);									/* Free arguments buffer */
	if (isatty(STDIN_FILENO) == 1)				/* Print newline before exiting */
		putchar('\n');
	return (0);
}
