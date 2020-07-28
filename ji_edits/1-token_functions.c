#include "shell.h"

/**
 * gettokens - turn a line input into a token array (argv)
 * @token_arr: pointer to array to be filled
 * @line: line to be turned into arguments
 * Return: number of tokens
 **/
size_t gettokens(char *token_arr[], char *line)
{
	size_t i = 0;
	char *delims = "#\t \n";
	char *token = NULL;

	for (i = 0; i < 4096; i++)
		token_arr[i] = 0;

	token = str_to_token(line, delims);

	for (i = 0; token != NULL; i++)
	{
		token_arr[i] = token;
		token = str_to_token(NULL, delims);
	}

	return (i);
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
	{
		if (*string != delims[i])
		{
			i++;
			continue;
		}
		string++;
		i = 0;
	}

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
 * get_program_path - finds and returns full path name of program
 * @program: program name
 * Return: string of full path name of program
 **/
char *get_program_path(char *program)
{
	char *path, *all_paths, *path_plus_program;
	int size;
	struct stat st;

	all_paths = _strdup(NULL, _getenv("PATH"));
	if (all_paths == NULL && *program != '/')
		return (NULL);
	path = str_to_token(all_paths, ":");
	size = _strlen(all_paths) + _strlen(program) + 2;
	path_plus_program = malloc(size);

	if (path_plus_program == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	while (path != NULL)
	{
		_strncpy(path_plus_program, path, size);
		_strcat(path_plus_program, "/");
		_strcat(path_plus_program, program);
		/*printf("%s\n", path_plus_program);*/
		if (stat(path_plus_program, &st) == 0)
		{
			free(all_paths);
			return (path_plus_program);
		}
		path = str_to_token(NULL, ":");
	}

	free(all_paths);
	free(path_plus_program);

	if (stat(program, &st) == 0)
		return (_strdup(NULL, program));

	return (NULL);
}
