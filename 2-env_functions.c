#include "shell.h"

/**
 * print_env - prints environment if program is env
 * @program: program name. must be env.
 * Return: 1 if env printed | 0 if not
 **/
int print_env(char *program)
{
	int i = 0;

	if (key_match(program, "env"))
	{
		for (; environ[i]; i++)
		{
			print(environ[i]);
			print("\n");
		}
		return (1);
	}

	return (0);
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
