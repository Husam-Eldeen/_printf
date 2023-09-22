#include "main.h"
#include <stdlib.h>

/**
 * print_address - prints and address
 *
 * @args: the arguments list given to _printf()
 * @buffer: the buffer
 * @flags: unused paramter that was put here to be able
 * to make a generic pointer to printers (don't remove)
 * Return: the number of characters printed
 */
int print_address(va_list args, char *buffer, Flags *flags)
{
	unsigned long int p, pCopy, digitCount, digitCountCopy;
	char *address;

	(void)flags;
	p = va_arg(args, unsigned long int), pCopy = p, digitCount = 0;
	/* Input Validation */
	if (p == 0)
	{
		buffer_string("(nil)", buffer);
		return (5);
	}

	/* find #digits needed for octal represenation */
	while (pCopy > 0)
		pCopy /= 16, digitCount++;
	if (p == 0)
		digitCount = 1;

	/* allocate an array to put 0/1 in it */
	address = malloc(sizeof(*address) * digitCount + 1);
	if (address == NULL)
		return (0);
	address[digitCount] = '\0';

	/* fill in the address string from right to left */
	buffer_char('0', buffer);
	buffer_char('x', buffer);
	for (digitCountCopy = digitCount; digitCountCopy > 0; digitCountCopy--)
	{
		address[digitCountCopy - 1] = p % 16 + ((p % 16 > 9) ? 'a' - 10 : '0');
		p /= 16;
	}

	buffer_string(address, buffer);
	free(address);
	return (digitCount + 2);
}
