#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define BUF_FLUSH (-2)
#define WRITE_BUF_SIZE (4096)

/* Structure for linked list nodes */
typedef struct list_s {
    char *str;
    int num;
    struct list_s *next;
} list_t;

/* Structure for shell information */
typedef struct info_s {
    int readfd;
    /* Add any other members as needed */
} info_t;

/* Function prototypes from atoi.c */
int _atoi(char *s);

/* Function prototypes from lists.c */
size_t list_len(const list_t *h);
void free_strs(char **strs, size_t count);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* Function prototypes from lists1.c */
size_t list_len(const list_t *h);
void free_strs(char **strs, size_t count);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* Function prototypes from main.c */
int main(int ac, char **av);

/* Function prototypes from memory.c */
int bfree(void **ptr);
char *_custom_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* Function prototypes from parser.c */
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

/* Function prototypes from shell_loop.c */
int run_shell(info_t *info, char **av);
int find_builtin(info_t *info);
void find_command(info_t *info);
void fork_command(info_t *info);

/* Function prototypes from string.c */
size_t string_length(const char *s);
int string_compare(const char *s1, const char *s2);
const char *string_starts_with(const char *haystack, const char *needle);
char *string_concatenate(char *dest, const char *src);

/* Function prototypes from string1.c */
char *_str_cpy(char *dest, const char *src);
char *_str_dup(const char *str);
void _str_puts(const char *str);
int _str_putchar(char c);

/* Function prototypes from tokenizer.c */
char *_strchr(char *s, char c);
static int count_words(char *str, char *delim);
char **strtow(char *str, char *delim);

/* Function prototypes from vars.c */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

/* ... (other prototypes) ... */

#endif /* SHELL_H */

