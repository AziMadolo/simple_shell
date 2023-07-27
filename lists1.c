#include "shell.h"

/**
 * list_len - Counts the number of nodes in a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The number of nodes in the linked list.
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);

}

/**
 * free_strs - Frees the array of strings.
 * @strs: Array of strings to free.
 * @count: Number of elements in the array.
 */
void free_strs(char **strs, size_t count)
{
	if (!strs)
		return;

	for (size_t i = 0; i < count; i++)
		free(strs[i]);

	free(strs);
}

/**
 * list_to_strings - Converts a linked list to an array of strings.
 * @head: Pointer to the first node of the list.
 *
 * Return: An array of strings representing the linked list's data.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t node_count = list_len(head);
	char **strs;
	char *str;

	if (!head || !node_count)
		return (NULL);

	strs = malloc(sizeof(char *) * (node_count + 1));
	if (!strs)
		return (NULL);

	for (size_t i = 0; node; node = node->next, i++)
	{
		str = strdup(node->str);
		if (!str)
		{
			free_strs(strs, i);

			return (NULL);
		}

		strs[i] = str;
	}
	strs[node_count] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The number of nodes in the linked list.
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;
	const list_t *node = h;

	while (node)
	{
		_puts(convert_number(node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(node->str ? node->str : "(nil)");
		_puts("\n");
		node = node->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - Finds the first node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match the beginning of nodes' strings.
 * @c: The next character after the prefix to match (or -1 to ignore).
 *
 * Return: The first node whose string matches the criteria, or NULL if not found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Finds the index of a node in the linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node to find the index for.
 *
 * Return: The index of the node in the linked list, or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
