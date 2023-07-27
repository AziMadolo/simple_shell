#include "shell.h"
#include <unistd.h> 

/**
 * _eputs - Writes an input string to the standard error stream.
 * @str: The string to be written.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	if (!str)
		return;

	/* Loop through the string and write each character to stderr */
	while (*str)
	{
		_eputchar(*str);

		str++;
	}
}

/**
 * _eputchar - Writes a character to the standard error stream.
 * @c: The character to be written.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		/* Flush the buffer when the character is BUF_FLUSH or buffer size limit is reached */
		write(2, buf, i);
		i = 0;
	}


	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putfd - Writes a character to the given file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		/* Flush the buffer when the character is BUF_FLUSH or buffer size limit is reached */
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putsfd - Writes an input string to the given file descriptor.
 * @str: The string to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	if (!str)
		return (0);


	int count = 0;

	/* Loop through the string and write each character to the given file descriptor */
	while (*str)
	{
		count += _putfd(*str++, fd);
	}

	return (count);
}
