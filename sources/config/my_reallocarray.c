/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** realloc_object_tab
*/

#include "my.h"
#include "raytracer.h"

#include <stdlib.h>

void *my_reallocarray(void *ptr, int nmemb, int size)
{
    void *result = NULL;

    if (ptr == NULL)
        return malloc(size * nmemb);
    result = malloc(size * nmemb);
    if (result == NULL)
        return NULL;
    my_memcpy(result, ptr, size * (nmemb - 1));
    my_memset((char *) result + size * (nmemb - 1), 0, size);
    free(ptr);
    return result;
}
