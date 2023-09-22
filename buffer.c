#include "main.h"
#include <unistd.h>

/**
 * flush - print the buffer contents to the standard output
 *
 * @buffer: the buffer to flush
 * Return: nothing
 */
void flush(char *buffer)
{
	int i, size = 0;

	for (i = 0; buffer[i]; i++)
		size++;
	write(STDOUT_FILENO, buffer, size);
	buffer[0] = '\0';
}

/**
 * buffer_char - adds a character to the buffer
 *
 * @c: the character to be added
 * @buffer: pointer to the buffer
 * Return: 1 when it succeeds, 0 otherwise
 */
int buffer_char(char c, char *buffer)
{
	int i, buferSize = 0;

	for (i = 0; buffer[i]; i++)
		buferSize++;
	if (buferSize < BUFFERSIZE)
	{
		buffer[buferSize] = c;
		buffer[buferSize + 1] = '\0';
	}
	else if (buferSize == BUFFERSIZE)
	{
		flush(buffer);
		buffer_char(c, buffer);
	}
	return (1);
}

/**
 * buffer_string - buffers a string into the given buffer
 *
 * @str: the string to be buffered
 * @buffer: the buffer
 * Return: #characters buffered
 */
int buffer_string(char *str, char *buffer)
{
	int i;

	/* Input Validation */
	if (!str)
		return (0);

	/* Buffering */
	for (i = 0; str[i]; i++)
		buffer_char(str[i], buffer);
	return (i);
}
