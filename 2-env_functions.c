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

	for (; environ[i]; i++)
		if (key_match(key, environ[i]))
			return (environ[i] + _strlen(key) + 1);

	return (NULL);
}

/* SET ENV */
void _setenv(char *key, char *value)
{
	size_t i, j;
	char *prev_value = _getenv(key);
	int len_new = _strlen(key), len_old = _strlen(prev_value);

	if (prev_value)
	{
		/* Flush prev_value */
		for (i = 0; i < _strlen(prev_value); i++)
			prev_value[i] = '\0';

		/* If len_new > len_old */
		if (len_new > len_old)
		{
			/* code */
		}

		/* Copy over environment variable */
		_strncpy(prev_value, value, len_new);
	}

	for (i = 0; environ[i]; i++)
		;

	environ[i] = malloc(len_new + 1);
	environ[i + 1] = NULL;
	for (j = 0; value[j]; j++)
		environ[i][j] = value[j];
	environ[i][j] = '\0';
}

/* UNSET ENV */
void _unsetenv(char *key)
{
	int i;
	char *tmp;

	for (i = 0; environ[i]; i++)
		if (key_match(key, environ[i]))
		{
			tmp = environ[i];
			break;
		}

	if (tmp)
	{
		free(tmp);
		for (; environ[i]; i++)
			environ[i] = environ[i + 1];
	}
}
