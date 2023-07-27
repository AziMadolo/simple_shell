#include "shell.h"

/**
 * string_length - Calculates the length of a string.
 * @s: The string whose length is to be determined.
 *
 * Return: The length of the string (excluding the null terminator).
 */
size_t string_length(const char *s)
{
	size_t length = 0;

	if (!s)
		return (0);

	while (s[length])
		length++;

	return (length);
}

/**
 * string_compare - Compares two strings lexicographically.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, 0 if s1 == s2.
 */
int string_compare(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * string_starts_with - Checks if a string starts with a given substring.
 * @haystack: The string to search within.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of haystack if found, or NULL.
 */
const char *string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return (haystack);
}

/**
 * string_concatenate - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *string_concatenate(char *dest, const char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';

	return (ret);
}
