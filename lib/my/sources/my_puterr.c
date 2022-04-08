/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** Displays a string
*/

#include "my.h"

#include <unistd.h>

void my_puterr(char const *str)
{
    write(2, str, my_strlen(str));
}
