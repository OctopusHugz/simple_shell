#include "shell.h"
/**
 * _getline - creates a string buffer of a line from the given file stream
 * @lineptr: pointer that points to line to be copied
 * @n: buffer size (adjusted by function if buffer size needs to be different)
 * @stream: file stream to copy line from
 * Return: number of characters read | -1 if read fails
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i = 0, size = 2, len;
	char buf[1024];

	if (read(fileno(stream), buf, 1024) == -1)
		return (-1);

	for (len = 0; buf[len] != '\n'; len++)
		;

	if (len)
	{
		size += len;
		if (*n < size)
			*n = size;
		*lineptr = realloc(*lineptr, *n * sizeof(char));
		for (i = 0; i + 1 < size; i++)
			*(*lineptr + i) = buf[i];
		*(*lineptr + i) = '\0';
	}

	return (i);
}
	/*
	* while (i < 100)
	* {
	* 	printf("Loop #%d\n", (int)i);
	* 	if (i >= *n)
	* 	{
	* 		printf("Reallocating memory to %d blocks...\n", (int)i + 1);
	* 		*lineptr = realloc(*lineptr, (i + 1) * sizeof(char));
	* 		*n += 1;
	*	}
	*
	*
	*
	*	if (read(fileno(stream), *(lineptr + i), *n) == -1)
	*	{
	*		printf("===ERROR===\n");
	*		return (-1);
	*	}
	*
	*	if (*lineptr[i++] == '\n')
	*	{
	*		printf("Reading complete!\n");
	* 		return (i);
	* 	}
	* }
	*
	* return (-1);
	**/
