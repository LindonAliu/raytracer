/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** split string by certain characters
*/

#include "my.h"

#include <stdlib.h>
#include <stdbool.h>

static int overwrite_separators(int len, char *str, split_func *split,
    bool omit_empty)
{
    int words = 0;
    bool separated = 1;
    bool is_sep;

    for (int i = 0; i <= len; i++) {
        is_sep = (*split)(str[i]);
        if (separated && (!is_sep || !omit_empty)) {
            words++;
        }
        if (is_sep) {
            str[i] = 0;
        }
        separated = is_sep;
    }
    return words;
}

static char **split_on_zero_byte(int len, char *str, bool omit_empty,
    int words)
{
    char **split = malloc(sizeof(char *) * (words + 1));
    int separated = 1;
    int word = 0;

    if (split == 0)
        return 0;
    for (int i = 0; i <= len; i++) {
        if (separated && (str[i] != 0 || !omit_empty)) {
            split[word] = str + i;
            word++;
        }
        separated = str[i] == 0;
    }
    split[word] = 0;
    return split;
}

char **my_split(char const *str, split_func *split, bool omit_empty)
{
    int len;
    char *copy;
    char **result;

    if (str == NULL)
        return 0;
    len = my_strlen(str);
    copy = my_strdup(str);
    result = split_on_zero_byte(len, copy, omit_empty,
        overwrite_separators(len, copy, split, omit_empty));
    for (int i = 0; result[i]; i++)
        result[i] = my_strdup(result[i]);
    free(copy);
    return result;
}

void free_array(char **arr)
{
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
