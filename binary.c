#include "main.h"

/**
* print_binary - prints the given unsigned int in binary
* it prints negative numbers in 2's complement
*
* @args: the arguments list given to _printf()
* @buffer: the buffer
* @flags: unused paramter that was put here to be able
 * to make a generic pointer to printers (don't remove)
* Return: the number of characters printed
*/
int print_binary(va_list args, char *buffer, Flags *flags)
{
	unsigned int n, nCopy, digitCount, digitCountCopy;
	char *binary;

	(void)flags;
	n = va_arg(args, unsigned int), nCopy = n, digitCount = 0;
	/* find #digits needed for binary represenation */
	while (nCopy > 0)
		nCopy /= 2, digitCount++;
	if (n == 0)
		digitCount = 1;

	/* allocate an array to put 0/1 in it */
	binary = malloc(sizeof(*binary) * digitCount + 1);
	if (binary == NULL)
		return (0);
	binary[digitCount] = '\0';

	/* fill in the binary from right to left */
	for (digitCountCopy = digitCount; digitCountCopy > 0; digitCountCopy--)
	{
		binary[digitCountCopy - 1] = (n % 2) + '0';
		n /= 2;
	}

	buffer_string(binary, buffer);
	free(binary);
	return (digitCount);
}
