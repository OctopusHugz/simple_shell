#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: String to return the lenght of
 *
 * Return: length of input string
 **/
size_t _strlen(char *s)
{
	int i = 0;

	if (s)
		for (i = 0; s[i] != '\0'; i++)
			;

	return (i);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 **/
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - puts a string, followed by \n, to stdout
 * @str: string to put to stdout
 **/
void _puts(char *str)
{
	int i = 0;

	for (; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}
/**
 * slash_check - checks if there is a slash in a string
 * @command: command to check
 * Return: 1 if no slash | 0 if slash is found
 **/
int slash_check(char *command)
{
	int i, slash_check = 1;

	for (i = 0; command[i] && slash_check; i++)
		if (command[i] == '/')
			slash_check = 0;

	return (slash_check);
}

/**
 * get_var - expands an environment variable to its value
 * @var: variable to find and replace
 * Return: pointer to value of environment variable
 **/
char *get_var(char *var)
{
	char *env;
	size_t var_len = _strlen(var);

	if (var_len == 1)
		return (var);
	env = _getenv(var + 1);
	if (!env)
		return (NULL);
	while (*env != '=')
		env++;
	env++;
	return (env);
}
