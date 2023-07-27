#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable command.
 * @info: Pointer to the info struct (not used in this function).
 * @path: Path to the file to check.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st) != 0)
        return (0);

    if (S_ISREG(st.st_mode))
        return (1);

    return (0);
}

/**
 * dup_chars - Creates a new string by duplicating characters from pathstr.
 * @pathstr: The original PATH string.
 * @start: Starting index to duplicate characters.
 * @stop: Stopping index (exclusive) for duplication.
 *
 * Return: Pointer to the new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i, k;

    for (i = start, k = 0; i < stop; i++)
    {
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    }
    buf[k] = '\0';
    return (buf);
}

/**
 * find_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to the info struct (not used in this function).
 * @pathstr: The PATH string containing directories separated by ':'.
 * @cmd: The command to find in the PATH.
 *
 * Return: Pointer to the full path of the command if found, NULL otherwise.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);

    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }

    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }

            if (is_cmd(info, path))
                return (path);

            if (!pathstr[i])
                break;

            curr_pos = i + 1;
        }
        i++;
    }

    return (NULL);
}
