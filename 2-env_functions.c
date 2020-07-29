#include "shell.h"

/**
 * print_env - prints environment if program is env
 * @tokens: unused attribute
 * Return: 1 if env printed | 0 if not
 **/
int print_env(char *tokens[])
{
	int i;

	(void)tokens;

	for (i = 0; environ[i]; i++)
	{
		print(environ[i]);
		print("\n");
	}
	return (1);
}

/**
 * _getenv - returns environment info for key
 * @key: environment variable to search for
 * Return: env var info in a string of type key=value
 **/
char *_getenv(char *key)
{
	int i = 0;
	char *value = NULL, *delim;

	for (; environ[i]; i++)
		if (key_match(key, environ[i]))
		{
			delim = environ[i] + _strlen(key);
			if (*delim == '=')
			{
				value = delim + 1;
				break;
			}
		}

	return (value);
}

/* SET ENV */

/* UNSET ENV */
