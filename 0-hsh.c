#include "shell.h"

/**
 * main - run UNIX simple shell command interpreter
 * @argc: number of arguments provided to main (void)
 * @argv: array of strings containing arguments to main
 * Return: exit status
 **/
int main(int argc __attribute__((unused)), char *argv[])
{
	int line_number = 0, status = 0, num_of_tokens = 0;
	char *tokens[4096], *path = NULL;

	while (gettokens(tokens, &num_of_tokens))
	{
		line_number++;
		if (num_of_tokens > 0)
		{
			if (builtin_exec(tokens, num_of_tokens, &status) != 0)
			{
				if (status == ILLEGAL_EXIT_STATUS)
					status = print_error_message(argv[0], line_number, tokens);
				continue;
			}

			if (getpath(&path, tokens[0]))
			{
				status = fork_and_execute(path, tokens);
			}
			else
			{
				status = print_error_message(argv[0], line_number, tokens);
				gettokens(NULL, NULL);
				continue;
			}
		}
	}
	exit(status);
}

/**
 * exit_check - if exit, exit
 * @tokens: tokens
 * @num_of_tokens: num of tokens
 * @status: status
 * Return: -1 if error on exit | 0 if no need to exit
 **/
int exit_check(char *tokens[], int num_of_tokens, int *status)
{
	char *program = tokens[0];
	char *exit_status;
	int i;

	if (key_match(program, "exit") == 0)
		return (0);

	if (num_of_tokens == 1)
		return (1);

	exit_status = tokens[1];

	for (i = 0; exit_status[i]; i++)
		if (exit_status[i] < '0' || exit_status[i] > '9')
		{
			*status = ILLEGAL_EXIT_STATUS;
			return (1);
		}

	*status = atoi(exit_status);

	return (1);
}

/**
 * builtin_exec - executes builtins if program is a builtin
 * @tokens: tokens
 * @num_of_tokens: number of tokens
 * @status: pointer to status variable
 * Return: 1 if builtin is executed | 0 if not
 **/
int builtin_exec(char *tokens[], int num_of_tokens, int *status)
{
	builtins_t builtins[] = {{"env", print_env}};
	int i, num_of_builtins = sizeof(builtins) / sizeof(builtins_t);
	char *program = tokens[0];

	if (exit_check(tokens, num_of_tokens, status) != 0)
	{
		if (*status == ILLEGAL_EXIT_STATUS)
			return (1);
		gettokens(NULL, NULL);
		exit(*status);
	}

	for (i = 0; i < num_of_builtins; i++)
		if (key_match(program, builtins[i].name))
			return (builtins[i].func(tokens));

	return (0);
}

/**
 * fork_and_execute - fork and execute
 * @path: program path
 * @tokens: token array
 * Return: status
 **/
int fork_and_execute(char *path, char **tokens)
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

	status = execve(path, tokens, environ);
	free(path);
	return (status);
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
