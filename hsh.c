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
	int status = 0, line_num = 0, bi_status = 0;

	(void)argc;
	while (1)
	{
		line_num++;
		if (isatty(STDIN_FILENO) == 1)
			_puts("$ ");
		signal(SIGINT, sigint_handler);
		if (getline(&buf, &size, stdin) == -1)
		{
			free(buf);
			buf = NULL;
			break;
		}
		path = make_av(av, buf);
		if ((_strncmp(av[0], "\n", 1) == 0))
			continue;
		bi_status = built_in_check(buf, path, av, argv, envp, status, line_num);
		if (bi_status == 0)
			continue;
		if (bi_status == 1)
		{
			status = 2;
			continue;
		}
		else
			status = 0;
		status = print_error(path, argv, line_num, av);
		if (status >= 126)
			continue;
		status = fork_exec(buf, path, av, envp);
	}
	if (isatty(STDIN_FILENO) == 1)
		_putchar('\n');
	exit(status);
}
