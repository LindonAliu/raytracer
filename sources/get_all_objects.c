/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** get_all_objects
*/

#include <stdio.h>
#include "raytracer.h"

struct object **get_all_objects(const char *path_to_config)
{
    struct object **result = NULL;
    FILE *file = fopen(path_to_config, "r");
    char *line = NULL;
    size_t size = 0;
    int i = 1;

    if (file == NULL)
        return NULL;
    while (getline(&line, &size, file) != -1) {
        result = realloc_object_tab(result, i + 1);
        if (result == NULL)
            return NULL;
        if (initialize_object(&(result[i - 1]), line) == -1)
            return NULL;
        ++i;
    }
    return result;
}
