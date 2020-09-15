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

/**
 * exit_parser - parses a string for non-digits
 * @e_status: string provided to exit as an exit status
 *
 * Return: 1 if non-digits found, 0 if not
 **/
int exit_parser(char *e_status)
{
	int i;

	for (i = 0; e_status[i]; i++)
	{
		if (e_status[i] < '0' || e_status[i] > '9')
			return (1);
	}
	return (0);
}

/**
 * _atoi - translates ascii value to integer
 * @s: string/char to turn into integer
 *
 * Return: integer value of s
 */

int _atoi(char *s)
{
	unsigned int num = 0, i = 0, negs = 0;

	while (s[i])
	{
		if (s[i] == '-')
			negs++;
		if (s[i] >= '0' && s[i] <= '9')
		{
			num = num * 10 + (s[i] - '0');
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
		}
		i++;
	}
	if (negs % 2 != 0)
		num = -num;
	return (num);
}
