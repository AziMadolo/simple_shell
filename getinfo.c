#include "shell.h"

/**
 * clear_info - Initializes the info_t struct with default values.
 * @info: Pointer to the info_t struct to be initialized.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Sets up the info_t struct with provided data.
 * @info: Pointer to the info_t struct to be set up.
 * @av: Argument vector containing command and arguments.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *));
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		// Perform additional setup tasks
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees memory allocated for fields in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: If true, free all fields, otherwise free only specific ones.
 */
void free_info(info_t *info, int all)
{
	if (info->argv)
	{
		ffree(info->argv);
		info->argv = NULL;
	}
	info->path = NULL;
	if (all)
	{

		if (!info->cmd_buf)
		{
			free(info->arg);
			info->arg = NULL;
		}
		if (info->env)
		{
			free_list(&(info->env));
			info->env = NULL;
		}
		if (info->history)
		{
			free_list(&(info->history));
			info->history = NULL;
		}
		if (info->alias)
		{
			free_list(&(info->alias));
			info->alias = NULL;
		}
		if (info->environ)
		{

			ffree(info->environ);
			info->environ = NULL;
		}
		bfree((void **)info->cmd_buf);
		info->cmd_buf = NULL;
		if (info->readfd > 2)
		{
			close(info->readfd);
			info->readfd = -1;
		}
		_putchar(BUF_FLUSH);
	}
}
