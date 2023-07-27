#include "shell.h"

/**
 * input_buf - Buffers chained commands for processing
 * @info: Parameter struct containing shell information
 * @buf: Address of the buffer to store the input
 * @len: Address of the length variable
 *
 * Return: Number of bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, read new input */
	{
		free(*buf);
		*buf = NULL;

		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove the trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* Check if the input contains a command chain */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Gets a line of input from the user, excluding the newline character
 * @info: Parameter struct containing shell information
 *
 * Return: Number of bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* Buffer for command chain handling */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* Handle end-of-file (EOF) */
		return (-1);
	if (len) /* If there are commands left in the chain buffer */

	{
		j = i; /* Initialize new iterator to the current buffer position */
		p = buf + i; /* Get a pointer for the return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* Iterate to the semicolon or end of buffer */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment to skip past the nullified ';' */
		if (i >= len) /* Reached the end of the buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back the pointer to the current command position */
		return (_strlen(p)); /* Return the length of the current command */
	}

	*buf_p = buf; /* Otherwise, not a chain; pass back the buffer from _getline() */
	return (r); /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - Reads data into a buffer
 * @info: Parameter struct containing shell information
 * @buf: Buffer to store the read data
 * @i: Size of the buffer
 *
 * Return: Number of bytes read
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN
 * @info: Parameter struct containing shell information
 * @ptr: Address of the pointer to the buffer, preallocated or NULL
 * @length: Size of the preallocated buffer if not NULL
 *
 * Return: Number of bytes read
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* Handle malloc failure */
	{
		if (p)
			free(p);
		return (-1);
	}

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Blocks the interrupt signal (Ctrl+C) and provides a prompt
 * @sig_num: The signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
