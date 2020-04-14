#include "shell.h"

/**
 * _strncmp - compares first letter of two strings
 * @s1: string 1
 * @s2: string 2
 * @n: number of bytes to check
 * Return: difference between ascii values of first letters
 **/
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	for (i = 0; (s1[i] && s2[i]) && i < n;)
	{
		if (s1[i] == s2[i])
			i++;
		else
			break;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strncpy - copies a string
 * @dest: buffer to append to
 * @src: string to copy
 * @n: number of bytes to copy
 *
 * Return: pointer to the string at dest
 **/
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; src[i] && i < n; i++)
		dest[i] = src[i];
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: base string
 * @src: string to append
 *
 * Return: Pointer to string dest
 **/
char *_strcat(char *dest, char *src)
{
	int i, len;

	for (i = 0; dest[i]; i++)
		;
	for (len = 0; src[len]; len++)
	{
		dest[i] = src[len];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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
