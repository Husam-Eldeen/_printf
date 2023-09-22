#include "main.h"

/**
 * get_printer - gets the right printer function
 *
 * @format: the format string given to _printf()
 * @index: the index at which the '%' was found
 * Return: a function pointer to the printer,
 * NULL when specifiers were found
 */
int (*get_printer(const char *format, int index))(va_list, char *, Flags *)
{
	int i;
	Mapping mappings[11] = {
		{'c', print_char},
		{'s', print_string},
		{'d', print_int},
		{'i', print_int},
		{'b', print_binary},
		{'u', print_unsigned_int},
		{'x', print_small_hex},
		{'X', print_capital_hex},
		{'S', print_unprintable_string},
		{'p', print_address},
		{'\0', NULL}
	};
	char c = get_specifier(format, index + 1);

	/* no specifier was found*/
	if (c == '\0')
		return (NULL);

	/* get the corresponding printer */
	for (i = 0; mappings[i].printer; i++)
		if (c == mappings[i].type)
			return (mappings[i].printer);

	/* reaching here means a problem happened (recheck your mappings) */
	return (NULL);
}

/**
 * _printf - prints a formatted string
 *
 * @format: the formatter string
 * Return: the nubmer of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i, proceed = 0, printed = 0;
	char *buffer;
	int (*printer)(va_list, char *, Flags *);
	Flags flags;

	/* Input Validation */
	if (format == NULL)
		return (-1);
	/* Make the local buffer */
	buffer = malloc(sizeof(*buffer) * BUFFERSIZE + 1);
	if (buffer == NULL)
		return (-1);
	buffer[0] = '\0';
	/* Parse the format */
	va_start(args, format);
	for (i = 0, proceed = 0; format[i]; i += proceed)
	{
		if (format[i] == '%')
		{
			proceed = set_flags(&flags, format, i);
			if (proceed == -1 || proceed == 1)
			{
				printed += buffer_char(format[i], buffer);
				proceed = (proceed == -1) ? 2 : 1;
				continue;
			}
			printer = get_printer(format, i);
			printed += printer(args, buffer, &flags);
		}
		else
			proceed = 1, printed += buffer_char(format[i], buffer);
	}
	va_end(args);
	flush(buffer);
	free(buffer);
	return (printed);
}
