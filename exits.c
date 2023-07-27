#include "shell.h"

/**
 * custom_strncpy - Copies a string up to a maximum of n characters.
 * @dest: The destination buffer where the string will be copied.
 * @src: The source string to be copied.
 * @n: The maximum number of characters to be copied.
 * Return: A pointer to the destination buffer.
 */
char *custom_strncpy(char *dest, const char *src, size_t n)
{
    char *dest_start = dest;
    
    while (*src && n > 0)
    {
        *dest++ = *src++;
        n--;
    }
    
    while (n > 0)
    {
        *dest++ = '\0';
        n--;
    }
    
    return dest_start;
}

/**
 * custom_strncat - Concatenates two strings up to a maximum of n characters.
 * @dest: The destination buffer where the strings will be concatenated.
 * @src: The source string to be appended.
 * @n: The maximum number of characters to be appended.
 * Return: A pointer to the destination buffer.
 */
char *custom_strncat(char *dest, const char *src, size_t n)
{
    char *dest_start = dest;
    
    while (*dest)
        dest++;
    
    while (*src && n > 0)
    {
        *dest++ = *src++;
        n--;
    }
    
    *dest = '\0';
    
    return dest_start;
}

/**
 * custom_strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of character c in the string s,
 *         or NULL if the character is not found.
 */
char *custom_strchr(char *s, char c)
{
    while (*s)
    {
        if (*s == c)

            return s;
        
        s++;
    }
    
    if (*s == c)
        return s;
    
    return NULL;
}
