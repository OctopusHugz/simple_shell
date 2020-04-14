#include "shell.h"

/**
 * main - run UNIX simple shell command interpreter
 * @argc: number of arguments provided to main
 * @argv: array of strings containing arguments to main
 * @envp: array of strings containing environment variables
 * Return: exit status
 **/
int main(int argc, char *argv[], char *envp[])
{
	char *buf = NULL, *av[4096], *path;
	size_t size = 0;
	int status = 0, line_num = 0;
	pid_t child_pid = 0;

	if (argc != 1) /* Print usage if argc is off */
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line_num++;
		if (isatty(STDIN_FILENO) == 1) /* Print $ if stdin is terminal */
			_puts("$ ");
		signal(SIGINT, sigint_handler);
		if (getline(&buf, &size, stdin) == -1) /* Copy command line to buf */
		{
			free(buf);
			buf = NULL;
			break;
		}
		path = make_av(av, buf);			 /* Make argv[] for next exec */
		if ((_strncmp(av[0], "\n", 1) == 0)) /* Start over if buf is just '\n' */
			continue;
		if (_strncmp(av[0], "exit", 4) == 0)
		{
			/*if (av[1])
				status = _atoi(av[1]);*/
			/* CHECK IF STATUS IS NOT A NUMBER OR OUT OF RANGE */
			free(buf);
			buf = NULL;
			free(path);
			path = NULL;
			exit(status);
		}
		if (_strncmp(av[0], "env", 3) == 0)
		{
			print_env(envp);
			free(buf);
			buf = NULL;
			free(path);
			path = NULL;
			continue;
		}
		if (path == NULL)
		{
			printf("%s: %d: %s: not found\n", argv[0], line_num, av[0]);
			status = 127;
			continue;
		}
		child_pid = fork(); /* fork if command is valid */
		if (child_pid == -1)
		{
			perror("fork");
			free(buf);
			buf = NULL;
			free(path);
			path = NULL;
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execve(path, av, envp) == -1)
			{
				perror("execve");
				free(buf);
				buf = NULL;
				/* NEED TO FREE PATH AND NULL IT HERE?! */
				free(path);
				path = NULL;
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
				perror("wait");
			/* if (WIFEXITED(status))
				printf("Child exit status: %d\n", WEXITSTATUS(status)); */
		}
		free(path);
		path = NULL;
	}
	if (isatty(STDIN_FILENO) == 1) /* Print newline before exiting */
		_putchar('\n');
	exit(status);
}
