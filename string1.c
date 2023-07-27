#include "shell.h"

/**
 * _str_cpy - Copies a string.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *_str_cpy(char *dest, const char *src)
{
    if (dest == src || src == NULL)
        return (dest);

    char *dest_ptr = dest;
    while ((*dest_ptr++ = *src++))
        ;

    return (dest);
}

/**
 * _str_dup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_str_dup(const char *str)
{
    if (str == NULL)
        return (NULL);

    size_t length = strlen(str);
    char *ret = malloc((length + 1) * sizeof(char));

    if (!ret)
        return (NULL);

    _str_cpy(ret, str);
    return (ret);
}

/**
 * _str_puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _str_puts(const char *str)
{
    if (!str)
        return;

    while (*str)
    {
        _str_putchar(*str);
        str++;
    }
}

/**
 * _str_putchar - Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _str_putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return (1);
}
