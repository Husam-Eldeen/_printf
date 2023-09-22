#include "main.h"
#include <limits.h>

/**
 * print_prepared_int - prints a string under some conditions
 * Description: the provided number should be a non-negative
 * unsigned int. It doesn't check for flags, width, or precision
 *
 * @n: the number to be printed
 * @buffer: the buffer
 * Return: #characters printed = #digits of the number
 */
int print_prepared_int(unsigned int n, char *buffer)
{
	unsigned int nCopy = n;
	int digitCount = 0, i;
	char *reversed;

	if (n == 0) /* the zero corner case */
	{
		buffer_char('0', buffer);
		return (1);
	}

	/* count the digits */
	for (nCopy = n; nCopy > 0; nCopy /= 10)
		digitCount++;

	/* fill in a string with the digits reversed */
	reversed = malloc(sizeof(*reversed) * digitCount + 1);
	reversed[digitCount] = '\0';
	for (i = 0, nCopy = n; nCopy > 0; i++, nCopy /= 10)
		reversed[i] = (nCopy % 10) + '0';

	/* then reverse it to be as expected */
	reversed = reverse_string(reversed);
	buffer_string(reversed, buffer);
	free(reversed);
	return (digitCount);
}

/**
 * print_int - Prints a number
 *
 * @args: the arguments list given to _printf()
 * @buffer: the buffer
 * @flags: a Flags object indicating wich flags were arisen
 * before the specifier
 * Return: the number of digits printed
 */
int print_int(va_list args, char *buffer, Flags *flags)
{
	int n = va_arg(args, int), extraDigit = '#', printed = 0;

	if (n >= 0) /* Check for Flags */
	{
		if (flags->plus)
		{
			buffer_char('+', buffer);
			printed++;
		}
		else if (flags->space)
		{
			buffer_char(' ', buffer);
			printed++;
		}
	}
	if (n == INT_MIN) /* avoiding overflow (take a digit in your pocket)*/
		extraDigit = -1 * (n % 10), n /= 10;
	if (n < 0) /* for negative values */
	{
		buffer_char('-', buffer);
		printed++, n = -n;
	}

	printed += print_prepared_int(n, buffer);

	if (extraDigit != '#') /* if I saved a digit in my pocket before */
		printed += buffer_char('0' + extraDigit, buffer);
	return (printed);
}

/**
 * print_unsigned_int - prints an unsigned integer
 *
 * @args: the arguments list given to _printf()
 * @buffer: the buffer
 * @flags: unused paramter that was put here to be able
 * to make a generic pointer to printers (don't remove)
 * Return: the number of digits printed
*/
int print_unsigned_int(va_list args, char *buffer, Flags *flags)
{
	unsigned int n;

	(void)flags;
	n = va_arg(args, unsigned int);
	return (print_prepared_int(n, buffer));
}
