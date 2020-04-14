#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: String to return the lenght of
 *
 * Return: length of input string
 **/
size_t _strlen(char *s)
{
	int i;

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
