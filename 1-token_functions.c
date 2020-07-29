#include "shell.h"
#define PROMPT "$ "
#define getprompt() (isatty(STDIN_FILENO) ? PROMPT : "")

/**
 * gettokens - read stdin, tokenize it, store in tokens
 * @tokens: pointer to array to be filled
 * @num_of_tokens: pointer to store size of tokens array
 * Return: number of tokens
 **/
int gettokens(char *tokens[], int *num_of_tokens)
{
	char *delims = "#\t \n", *token = NULL, *prompt = getprompt();
	static size_t line_size;
	static char *line;
	int i = 0;

	if (tokens != NULL)
		print(prompt);

	if (tokens == NULL || getline(&line, &line_size, stdin) == -1)
	{
		free(line);
		line = NULL;
		return (0);
	}

	for (i = 0; i < 4096; i++)
		tokens[i] = 0;

	token = str_to_token(line, delims);

	for (i = 0; token != NULL; i++)
	{
		tokens[i] = token;
		token = str_to_token(NULL, delims);
	}

	*num_of_tokens = i;
	return (1);
}

/**
 * str_to_token - custom strtok
 * @new_str: string
 * @delims: delimiters
 * Return: pointer to token
 **/
char *str_to_token(char *new_str, const char *delims)
{
	char *token = NULL;
	static char *string;
	int i = 0, j = 0;

	if (new_str != NULL)
		string = new_str;

	if (string == NULL || *string == '\0')
		return (NULL);

	while (delims[i] != '\0')
		if (*string != delims[i])
			i++;
		else
			string++, i = 0;

	if (*string == '\0')
		return (NULL);

	for (i = 0; string[i] != '\0'; i++)
		for (j = 0; delims[j] != '\0'; j++)
			if (string[i] == delims[j])
			{
				string[i] = '\0';
				token = string;
				if (delims[j] == '#')
					string = NULL;
				else
					string = string + i + 1;
				return (token);
			}

	token = string;
	string = NULL;
	return (token);
}

/**
 * getpath - finds and returns full path name of program
 * @program: program name
 * @path_plus_program: where full path name is stored
 * Return: string of full path name of program
 **/
void getpath(char **path_plus_program, char *program)
{
	char *path, *all_paths;
	int i, size;
	struct stat st;

	all_paths = _strdup(NULL, _getenv("PATH"));
	if (all_paths == NULL && *program != '/')
		return;
	path = str_to_token(all_paths, ":");
	size = _strlen(all_paths) + _strlen(program) + 2;
	free(*path_plus_program);
	*path_plus_program = malloc(size);
	for (i = 0; i < size; i++)
		(*path_plus_program)[i] = 0;

	if (*path_plus_program == NULL)
	{
		perror("malloc");
		return;
	}

	while (path != NULL)
	{
		_strncpy(*path_plus_program, path, size);
		_strcat(*path_plus_program, "/");
		_strcat(*path_plus_program, program);
		if (stat(*path_plus_program, &st) == 0)
		{
			free(all_paths);
			return;
		}
		path = str_to_token(NULL, ":");
	}

	free(all_paths);
	*path_plus_program = _strdup(*path_plus_program, program);
}
