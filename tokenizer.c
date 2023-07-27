#include "shell.h"

/**
 * _strchr - Locates a character in a string.
 * @s: The string to search.
 * @c: The character to locate.
 * Return: Pointer to the first occurrence of the character,
 *         or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == c)
		return (s);
	return (NULL);
}

/**
 * count_words - Counts the number of words in a string.
 * @str: The input string.
 * @delim: The delimiter string.
 * Return: The number of words.
 */
static int count_words(char *str, char *delim)
{
	int num_words = 0;
	char *token;

	while (*str)
	{
		/* Skip leading delimiters */
		str += strspn(str, delim);
		
		/* Find the next token or the end of the string */
		token = strpbrk(str, delim);
		
		if (token)
		{
			num_words++;
			/* Move to the next non-delimiter character */
			str = token + strcspn(token, delim);
		}
		else
		{
			/* If no more delimiters are found, consider the rest of the string as a word */
			if (*str)
				num_words++;
			break;
		}
	}
	return (num_words);
}

/**
 * strtow - Splits a string into words. Repeat delimiters are ignored.
 * @str: The input string.
 * @delim: The delimiter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *delim)
{
	int i, j, k;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	/* If the delimiter is NULL or an empty string, use a space as the default delimiter */
	if (delim == NULL || *delim == '\0')
		delim = " ";

	i = count_words(str, delim);
	if (i == 0)
		return (NULL);

	/* Allocate memory for the array of words */
	words = malloc((i + 1) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < i; j++)
	{
		/* Skip leading delimiters */
		str += strspn(str, delim);
		
		/* Find the length of the current word */
		k = strcspn(str, delim);
		
		/* Allocate memory for the word */
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			/* Free previously allocated memory in case of failure */
			for (j = 0; j < i; j++)
				free(words[j]);
			free(words);
			return (NULL);
		}
		
		/* Copy the current word */
		for (k = 0; str[k] && !_strchr(delim, str[k]); k++)
			words[j][k] = str[k];
		words[j][k] = '\0';
		
		/* Move to the next word */
		str += k;
	}

	/* Null-terminate the array of words */
	words[j] = NULL;
	return (words);
}
