/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** concat strings
*/

#include "my.h"

#include <stdarg.h>
#include <stdlib.h>

char *my_concat(int nb, ...)
{
    va_list ap;
    int len = 0;
    char *result;
    int offset = 0;
    char *curr;

    va_start(ap, nb);
    for (int i = 0; i < nb; i++)
        len += my_strlen(va_arg(ap, char *));
    va_end(ap);
    result = malloc(len + 1);
    va_start(ap, nb);
    for (int i = 0; i < nb; i++) {
        curr = va_arg(ap, char *);
        my_strcpy(result + offset, curr);
        offset += my_strlen(curr);
    }
    va_end(ap);
    return result;
}
