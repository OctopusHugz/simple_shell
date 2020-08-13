#include "shell.h"

/**
 * _getline - custom getline
 * @line: buffer where line is stored
 * @size: buffer where line size is stored
 * @stream: file pointer to stdin
 * Return: number of characters read | -1 on failure or EOF
 **/
ssize_t _getline(char **line, size_t *size, FILE *stream)
{
	int line_length, rewind_length, bytes_read, fd = fileno(stream);
	char *line_end = NULL;
	ssize_t count;

	if (!line || !(*line))
	{
		*line = malloc(MEM_CHUNK);
		if (!(*line))
			return (-1);
		*size = MEM_CHUNK;
	}

	bytes_read = 0;
	while (!line_end)
	{
		count = read(fd, *line + bytes_read, *size);
		if (count <= 0)
			return (-1);

		if ((size_t)count == *size)
		{
			*line = realloc(*line, *size + MEM_CHUNK);
			if (!(*line))
				return (-1);
			*size += MEM_CHUNK;
		}

		line_end = _strchr(*line + bytes_read, '\n');
		bytes_read += count;
	}

	line_length = (int)(line_end - *line);
	rewind_length = -1 * (count - line_length - 1);
	lseek(fd, rewind_length, SEEK_CUR);
	*(line_end + 1) = '\0';
	return (bytes_read);
}

/**
 * _strchr - finds first instance of a specific char in a string
 * @str: string
 * @chr: character to find
 * Return: pointer to first instance of chr
 **/
char *_strchr(char *str, int chr)
{
	if (str == NULL)
		return (NULL);

	for (; *str; str++)
		if (*str == chr)
			return (str);

	return (NULL);
}

/* int main(void)
{
	FILE *stream = fopen("test_file", "r");
	ssize_t num_of_chars;
	size_t n = 0;
	char *lineptr = NULL;
	int i = 0;

	if (stream == NULL)
	{
		return (0);
	}

	num_of_chars = _getline(&lineptr, &n, stream);

	while (num_of_chars != -1 && i++ < 100)
	{
		printf("%s", lineptr);
		num_of_chars = _getline(&lineptr, &n, stream);
	}
	free(lineptr);
	return fclose(stream);
} */
