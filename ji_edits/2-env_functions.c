#include "shell.h"

/**
 * print_env - prints environment
 **/
void print_env(void)
{
	int i = 0;

	for (; environ[i]; i++)
	{
		print(environ[i]);
		print("\n");
	}
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
