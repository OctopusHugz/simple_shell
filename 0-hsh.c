#include "shell.h"

/**
 * main - run UNIX simple shell command interpreter
 * @argc: number of arguments provided to main (void)
 * @argv: array of strings containing arguments to main
 * Return: exit status
 **/
int main(int argc __attribute__((unused)), char *argv[])
{
	char *line = NULL, *program = NULL, *path = NULL, *token_arr[4096];
	char *prompt = isatty(STDIN_FILENO) ? "$ " : "";
	int line_num = 1, status = 0;
	size_t line_size = 0;

	print(prompt);
	while (getline(&line, &line_size, stdin) != -1)
	{
		if (gettokens(token_arr, line))
		{
			program = token_arr[0];
			if (print_env(program))
				continue;
			if (key_match(program, "exit"))
				break;
			getpath(program, &path);
			status = fork_and_execute(path, token_arr, environ);
			if (status == -1)
			{
				status = print_error_message(argv[0], line_num, program);
				break;
			}
		}
		print(prompt);
		line_num += 1;
	}
	free(line);
	free(path);
	exit(status);
}

/**
 * fork_and_execute - fork and execute
 * @program: program
 * @token_arr: token array
 * @envp: environment
 * Return: status
 **/
int fork_and_execute(char *program, char **token_arr, char **envp)
{
	int status = 0;
	pid_t child_pid;

	child_pid = fork();

	if (child_pid != 0)
	{
		if (child_pid == -1 || wait(&status) == -1)
			return (-1);

		return (WEXITSTATUS(status));
	}

	return (execve(program, token_arr, envp));
}

/**
 * key_match - checks if string starts with key
 * @key: sub-string
 * @string: string
 * Return: 1 if string starts with key | 0 if not
 **/
int key_match(char *key, char *string)
{
	if (key == NULL || string == NULL)
		return (0);

	for (; *key; key++, string++)
		if (*key != *string || *string == '\0')
			return (0);

	return (1);
}
