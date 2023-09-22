#include "main.h"

/**
 * print_char - prints a character
 *
 * @args: the argument list of _printf()
 * it's not used but we need it (dont' remove it)
 * @buffer: the buffer
 * @flags: unused paramter that was put here to be able
 * to make a generic pointer to printers (don't remove)
 * Return: always 1
 */
int print_char(va_list args, char *buffer, Flags *flags)
{
	(void)flags;
	return (buffer_char(va_arg(args, int), buffer));
}

/**
 * print_string - prints a string without printf
 *
 * @args: the argument list of printf
 * @buffer: the buffer
 * @flags: unused paramter that was put here to be able
 * to make a generic pointer to printers (don't remove)
 * Return: the number of characters printed
 */
int print_string(va_list args, char *buffer, Flags *flags)
{
	unsigned long int i;
	char *str;

	(void)flags;
	str = va_arg(args, char *);
	if (!str)
	{
		buffer_string("(null)", buffer);
		return (6);
	}
	for (i = 0; str[i]; i++)
		buffer_char(str[i], buffer);
	return (i);
}

/**
 * print_unprintable_string - prints a string with the unprintable
 * characters replaced with their hex represenation
 *
 * @args: the argument list of printf
 * @buffer: the buffer
 * @flags: unused paramter that was put here to be able
 * to make a generic pointer to printers (don't remove)
 * Return: numver of characters printed
 */
int print_unprintable_string(va_list args, char *buffer, Flags *flags)
{
	char *s;
	unsigned long int i, printed = 0;

	(void)flags;
	s = va_arg(args, char *);
	for (i = 0; s[i]; i++)
	{
		if (s[i] < 0)
			return (0);
		if (s[i] > 31 && s[i] < 127) /* a printable character */
			buffer_char(s[i], buffer);
		else /* unprintable */
		{
			buffer_char('\\', buffer);
			buffer_char('x', buffer);
			if (s[i] < 16)
				buffer_char('0', buffer);
			print_hex(s[i], 1, buffer);
			printed += 3;
		}
		printed++;
	}
	return (printed);
}

/**
 * reverse_string - reverses a string
 *
 * @str: the string to be reversed
 * Return: nothing
 */
char *reverse_string(char *str)
{
	int i, size = 0;
	char *reversed;

	for (i = 0; str[i]; i++)
		size++;
	reversed = malloc(sizeof(*reversed) * size + 1);
	if (!reversed)
		return (NULL);
	reversed[size] = '\0';

	for (i = 0; i < size; i++)
		reversed[i] = str[size - i - 1];
	free(str);
	return (reversed);
}
