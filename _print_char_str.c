#include "main.h"

/*
 * _printf - function that produces output
 * according to a format.
 * @format: format specifier.
 * Return: number of bytes printed.
 */

int _printf(const char *format, ...)
{
	unsigned int i, str_count, count = 0;
	va_list args;

	va_satrt(args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			putchar(format[i]);

		}

		else if (format[i] == '%' && format[i + 1] == 'c')
		{
			putchar(va_arg(args, int));
			i++;

		}
		else if (format[i] == '%' && format[i + 1] == 's')
		{
			str_count = putss(va_arg(args, *char));
			i++;
			count += (str_count - 1);
		}
		else if (format[i] == '%' && format[i + 1] == '%')
		{
			putchar('%');
		}
		count += 1;

	}

	va_end(args);
	return (count);

}
