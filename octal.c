#include "main.h"
#include <stdlib.h>

/**
 * print_octal - prints an unsigned int in ocatal system
 *
 * @args: the argument list of printf
 * @buffer: the buffer
 * @flags: a Flags object indicating wich flags were arisen
 * Return: number of digits printed
 */
int print_octal(va_list args, char *buffer, Flags *flags)
{
	unsigned int n = va_arg(args, unsigned int), nCopy = n;
	unsigned int digitCount = 0, printed = 0;
	char *octal;

	if (flags->hash) /* Check for Flags */
	{
		buffer_char('0', buffer);
		printed++;
	}

	/* find #digits needed for octal represenation */
	while (nCopy > 0)
		nCopy /= 8, digitCount++;
	if (n == 0)
		digitCount = 1;

	/* allocate an array to store octal representation in it */
	octal = malloc(sizeof(*octal) * digitCount + 1);
	if (octal == NULL)
		return (0);
	octal[digitCount] = '\0';

	/* fill in the octal string from right to left */
	for (; digitCount > 0; digitCount--)
	{
		octal[digitCount - 1] = (n % 8) + '0';
		n /= 8;
	}

	printed += buffer_string(octal, buffer);
	free(octal);
	return (printed);
}
