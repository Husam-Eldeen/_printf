#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define BUFFERSIZE 1024
#define DEFAULT_FLAGS {0, 0, 0, 0}
#define SPECIFIERS "csdibuxXSp"
#define SPECIFIERS_AND_FLAGS "+ -#csdibuxXSp"

/**
 * struct Flags - holds a combination of specifier flags
 *
 * @plus: the '+' flag
 * @minus: the '-' flag
 * @space: the ' ' flag
 * @hash: the '#' flag
 * Description: they indicate which flags where provided
 * in the format string (for one '%' presence)
 */
typedef struct Flags
{
	char plus, minus, space, hash;
} Flags;

/**
 * struct Mapping - maps every specifier with its corresponding printer
 *
 * @type: the specifier character
 * @printer: function pointer to the printer
 * Description: used to map every specifier character (d for example)
 * with its corresponding printer (print_int() in this case)
 */
typedef struct Mapping
{
	char type;
	int (*printer)(va_list args, char *buffer, Flags *);
} Mapping;

/* Flags */
int set_flags(Flags *flags, const char *format, int currentIndex);

/* Buffer */
void flush(char *buffer);
int buffer_char(char c, char *buffer);
int buffer_string(char *str, char *buffer);

/* Printers */
int _printf(const char *format, ...);
int print_char(va_list args, char *buffer, Flags *flags);
int print_string(va_list args, char *buffer, Flags *flags);
int print_int(va_list args, char *buffer, Flags *flags);
int print_binary(va_list args, char *buffer, Flags *flags);
int print_unsigned_int(va_list args, char *buffer, Flags *flags);
int print_octal(va_list args, char *buffer, Flags *flags);
int print_hex(unsigned int n, char capital, char *buffer);
int print_small_hex(va_list args, char *buffer, Flags *flags);
int print_capital_hex(va_list args, char *buffer, Flags *flags);
int print_unprintable_string(va_list args, char *buffer, Flags *flags);
int print_address(va_list args, char *buffer, Flags *flags);

/* Testers */
void string_tester(void);
void int_tester(void);
void set_flags_tester(void);

/* Parsers */
char get_specifier(const char *format, int startIndex);
int set_flags(Flags *flags, const char *format, int currentIndex);
char is_specifier(char c);

/* Other */
char *reverse_string(char *str);

#endif
