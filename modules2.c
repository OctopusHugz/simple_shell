#include "shell.h"

/**
 * built_in_check - checks whether command provided by the user
 * is the builtin env or the builtin exit
 * @buf: input string provided by the user
 * @path: directory where executable was found
 * @av: array of strings containing tokenized commands and arguments from buf
 * @envp: array of strings containing environment variables
 * Return: exit status
 **/
int built_in_check(char *buf, char *path, char *av[4096], char *envp[])
{
	int status = 0;

	if (_strncmp(av[0], "env", 3) == 0)
	{
		print_env(envp);
		return (status);
	}
	if (_strncmp(av[0], "exit", 4) == 0)
	{
		/* if (av[1]) */
		/* status = _atoi(av[1]); */
		/* CHECK IF STATUS IS NOT A NUMBER OR OUT OF RANGE */
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
		/* NEED TO ADD FREES AND EXIT AFTER THIS PERROR? */
		/* if (WIFEXITED(status)) */
		/* printf("Child exit status: %d\n", WEXITSTATUS(status)); */
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
