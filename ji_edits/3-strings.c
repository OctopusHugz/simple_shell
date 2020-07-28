#include "shell.h"

/**
 * print - prints a string
 * @str: string to printt to stdout
 **/
void print(char *str)
{
	while (*str)
		write(1, str++, 1);
}

/**
 * _strdup - duplicate string (src) onto dest
 * @src: source string to be copied onto dest
 * @dest: where src will be copied
 * Return: pointer to dest
 **/
char *_strdup(char *dest, char *src)
{
	int src_len, dest_len, i;

	if (src == NULL)
		return (NULL);

	src_len = _strlen(src);
	dest_len = _strlen(dest);

	if (dest == NULL || dest_len < src_len)
	{
		free(dest);
		dest = malloc(src_len + 1);
		if (dest == NULL)
		{
			perror("malloc");
			return (NULL);
		}
	}

	for (i = 0; i < src_len; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}

/**
 * _strncpy - copies a string
 * @dest: buffer to append to
 * @src: string to copy
 * @n: number of bytes to copy
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
	char *start = dest;
	int i = 0;

	while (*dest)
		dest++;

	for (; src[i]; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (start);
}

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
		while (s[i] != '\0')
			i++;

	return (i);
}
