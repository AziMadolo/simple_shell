#include "shell.h"

/**
 * custom_history - Display the custom history list.
 *                  Each command is shown with its line number, starting from 0.
 * @info: Pointer to the structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0.
 */
int custom_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * custom_unset_alias - Remove a user-defined alias.
 * @info: Pointer to the parameter structure.
 * @alias_str: The alias to be unset.
 *
 * Return: Always 0 on success, 1 on error.
 */
int custom_unset_alias(info_t *info, char *alias_str)
{
	char *p;
	char c;
	int ret;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = '\0';
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*p = c;
	return (ret);

}

/**
 * custom_set_alias - Set or update an alias to a given string.
 * @info: Pointer to the parameter structure.
 * @alias_str: The alias string to be set.
 *
 * Return: Always 0 on success, 1 on error.
 */
int custom_set_alias(info_t *info, char *alias_str)
{
	char *p;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);

	if (!*++p)
		return (custom_unset_alias(info, alias_str));

	custom_unset_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);

}

/**
 * print_custom_alias - Print an alias string.
 * @node: The alias node to be printed.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_custom_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 * custom_alias - Mimic the alias built-in command (man alias).
 * @info: Pointer to the structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0.
 */
int custom_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_custom_alias(node);


			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			custom_set_alias(info, info->argv[i]);
		else
			print_custom_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
