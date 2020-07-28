#include "shell.h"

/**
 * main - run UNIX simple shell command interpreter
 * @argc: number of arguments provided to main (void)
 * @argv: array of strings containing arguments to main
 * @envp: array of strings containing environment variables
 * Return: exit status
 **/
int main(int argc, char *argv[], char *envp[])
{
	char *line = NULL, *program = NULL, *program_path = NULL, *token_arr[4096];
	int line_num = 0, status = 0, interactive = isatty(STDIN_FILENO);
	size_t line_size = 0;
	/*int i;*/
	(void)argc;
	(void)envp;

	while (1)
	{
		line_num += 1;

		if (interactive)
			print("$ ");
		if (getline(&line, &line_size, stdin) == -1)
			break;
		if (gettokens(token_arr, line) == 0)
			continue;
		program = token_arr[0];
		if (key_match(program, "env"))
		{
			print_env();
			continue;
		}
		if (key_match(program, "exit"))
			break;
		free(program_path);
		program_path = get_program_path(program);
		status = fork_and_execute(program_path, token_arr, envp);
		if (status == -1)
		{
			status = print_error_message(argv[0], line_num, program);
			break;
		}
	}
	free(line);
	free(program_path);
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
