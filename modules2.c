#include "shell.h"

/**
 * built_in_check - checks whether command provided by the user
 * is the builtin env or the builtin exit
 * @buf: input string provided by the user
 * @path: directory where executable was found
 * @av: array of strings containing tokenized commands and arguments from buf
 * @argv: array of strings containing arguments to main
 * @envp: array of strings containing environment variables
 * @status: current status of program
 * @line_num: line number of shell
 * Return: exit status
 **/
int built_in_check(char *buf, char *path, char *av[4096], char *argv[],
				   char *envp[], int status, int line_num)
{
	if (_strncmp(av[0], "env", 3) == 0)
	{
		print_env(envp);
		return (EXIT_SUCCESS);
	}
	if (_strncmp(av[0], "exit", 4) == 0)
	{
		if (av[1])
		{
			status = atoi(av[1]);
			if (status < 0 || status > INT_MAX || exit_parser(av[1]))
			{
				_puts(argv[0]), _puts(": "), print_number(line_num);
				_puts(": "), _puts(av[0]), _puts(": Illegal number: ");
				_puts(av[1]), _putchar('\n');
				return (1);
			}
			if (status > 255 && status <= INT_MAX)
				status = status % 256;
		}
		free(buf);
		buf = NULL;
		free(path);
		path = NULL;
		exit(status);
	}
	return (-1);
}

/**
 * fork_exec - forks to create a child process and
 * executes the provided command in that child process
 * @buf: input string provided by the user
 * @path: directory where executable was found
 * @av: array of strings containing tokenized commands and arguments from buf
 * @envp: array of strings containing environment variables
 * Return: exit status
 **/
int fork_exec(char *buf, char *path, char *av[4096], char *envp[])
{
	int status = 0;
	pid_t child_pid = 0;

	child_pid = fork();
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
			free(path);
			path = NULL;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	free(path);
	path = NULL;
	return (status);
}

/**
 * print_number - prints an integer
 * @n: integer to print
 **/
void print_number(int n)
{
	if (n < 0)
	{
		_putchar('-');
		n = -n;
	}

	if (n / 10)
		print_number(n / 10);

	_putchar(n % 10 + '0');
}

/**
 * print_error - prints any error code if necessary and sets status accordingly
 * @path: directory where executable was found
 * @argv: array of strings containing arguments to main
 * @line_num: line number of shell
 * @av: array of strings containing tokenized commands and arguments from buf
 * Return: exit status
 **/
int print_error(char *path, char *argv[], int line_num, char *av[])
{
	if (path == NULL)
	{
		_puts(argv[0]), _puts(": "), print_number(line_num);
		_puts(": "), _puts(av[0]), _puts(": not found\n");
		return (127);
	}
	if (_strncmp(path, "Bad perms", 8) == 0)
	{
		_puts(argv[0]), _puts(": "), print_number(line_num);
		_puts(": "), _puts(av[0]), _puts(": Permission denied\n");
		return (126);
	}
	return (EXIT_SUCCESS);
}

/**
 * sigint_handler - handles SIGINT (CTRL-C) signal for shell
 * @signum: signal number caught by signal, 2 for SIGINT
 **/
void sigint_handler(int signum)
{
	if (signum == 2)
	{
		_putchar('\n');
		_puts("$ ");
	}
}
