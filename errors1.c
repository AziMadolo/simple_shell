#include "shell.h"

/**
 * _erratoi - Convert a string to an integer.
 * @s: The string to be converted.
 * Return: The converted number if successful, or -1 on error.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* Note: Skipping the leading plus sign, if any */

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{

			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1); /* Error: Integer overflow */
		}
		else
			return (-1); /* Error: Non-numeric character found */
	}
	return (result);
}

/**
 * print_error - Print an error message.
 * @info: Pointer to the parameter & return info struct.
 * @estr: String containing the specified error type.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Print a decimal (integer) number (base 10).
 * @input: The input number to print.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	if (input < 0)
	{


		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}


/**
 * convert_number - Convert a number to a string.
 * @num: The number to be converted.
 * @base: The base for the conversion.
 * @flags: Argument flags for formatting.
 * Return: A string representation of the number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}



	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - Replace the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0'; /* Note: Truncate the string at the comment symbol */
			break;
		}
	}
}