#include "shell.h"

/**
 * _myexit - Exit the shell
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int exit_status;

    if (info->argv[1]) /* Check if there is an exit argument */
    {
        exit_status = _erratoi(info->argv[1]);
        if (exit_status == -1)


        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return (1);
        }
        info->err_num = exit_status;
        return (-2);
    }

    info->err_num = -1;
    return (-2);
}

/**
 * _mycd - Change the current directory of the process
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Always 0
 */
int _mycd(info_t *info)

{
    char *current_dir, *new_dir, buffer[1024];
    int chdir_ret;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1]) /* Check if there is no argument after "cd" */
    {
        new_dir = _getenv(info, "HOME=");
        if (!new_dir)
            chdir_ret = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
        else
            chdir_ret = chdir(new_dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0) /* Check for '-' argument */
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(current_dir);
            _putchar('\n');


            return (1);
        }

        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        chdir_ret = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
    }
    else
    {
        /* Change to the specified directory */
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1) /* Check if chdir failed */
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        /* Update the environment variables */

        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return (0);
}

/**
 * _myhelp - Display help message for the shell
 * @info: Pointer to the info_t structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* Temporary unused workaround */
    return (0);

}
