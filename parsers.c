#include "main.h"

/**
 * is_specifier - checks if a character is specifier
 *
 * @c: the character
 * Return: 1 if c is a specifier, 0 otherwise
 */
char is_specifier(char c)
{
	char *specifiers = SPECIFIERS;
	int i;

	for (i = 0; specifiers[i]; i++)
		if (c == specifiers[i])
			return (1);
	return (0);
}

/**
 * get_specifier - finds the specifier after some index in
 * the format string
 *
 * @format: the format string
 * @startIndex: the index from which we should start searching
 * Return: the spcifier character, or NULL when no specifiers are found
 */
char get_specifier(const char *format, int startIndex)
{
	int i, j, allowed = 0;
	char specifiers[] = SPECIFIERS;
	char allowed_chars[] = SPECIFIERS_AND_FLAGS;

	for (i = startIndex; format[i]; i++, allowed = 0)
	{
		/* Make sure this character is allowed (flag / specifier) */
		for (j = 0; allowed_chars[j]; j++)
			if (format[i] == allowed_chars[j])
			{
				allowed = 1;
				break;
			}
		if (!allowed)
			break;

		/* If this character is a specifier return it */
		for (j = 0; specifiers[j]; j++)
			if (format[i] == specifiers[j])
				return (specifiers[j]);
	}

	return ('\0');
}

/**
 * set_flags - sets the flags for depending on the specifier
 *
 * @flags: the flags object to be set
 * @format: the format string of _printf()
 * @currentIndex: the index at wich a '%' was found
 * Return: #characters _printf should increment its index
 * -1: a '%' was found after the '%'
 * 1: when we want to print the % we found and there is no conversions to do
 * 2: a specifier was found right after the '%'
 * more: depending on the number of valid flags that was put and
 * followed by a specifier
 */
int set_flags(Flags *flags, const char *format, int currentIndex)
{
	int i = currentIndex + 1, proceed = 2;
	Flags zeroFlags = DEFAULT_FLAGS;

	/* set flags to 1 (if any) till you find a non-flag character */
	*flags = zeroFlags;
	for (; format[i]; i++)
	{
		proceed++;
		if (format[i] == '+')
			flags->plus = 1;
		else if (format[i] == '-')
			flags->minus = 1;
		else if (format[i] == ' ')
			flags->space = 1;
		else if (format[i] == '#')
			flags->hash = 1;
		else
		{
			if (format[i] == '%')
				return (-1);
			if (is_specifier(format[i]))
				return (--proceed);
			break;
		}
	}
	return (1);
}
