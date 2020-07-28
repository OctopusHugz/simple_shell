#include "shell.h"

/**
 * main - run UNIX simple shell command interpreter
 * @argc: number of arguments provided to main (void)
 * @argv: array of strings containing arguments to main
 * Return: exit status
 **/
int main(int argc __attribute__((unused)), char *argv[])
{
	char *program = NULL, *path = NULL, *tokens[4096];
	int line_number = 1, status = 0, num_of_tokens = 0;

	while (gettokens(tokens, &num_of_tokens))
	{
		line_number++;
		if (num_of_tokens != 0)
		{
			program = tokens[0];
			if (print_env(program))
				continue;
			if (key_match(program, "exit"))
				break;
			getpath(&path, program);
			status = fork_and_execute(path, tokens, environ);
			if (status == -1)
			{
				status = print_error_message(argv[0], line_number, program);
				break;
			}
		}
	}
	free(path);
	exit(status);
}

/**
 * fork_and_execute - fork and execute
 * @program: program
 * @tokens: token array
 * @envp: environment
 * Return: status
 **/
int fork_and_execute(char *program, char **tokens, char **envp)
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

	return (execve(program, tokens, envp));
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
