/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** get_all_objects
*/

#include "my.h"
#include "raytracer.h"

#include <stdio.h>
#include <stdlib.h>

static int initialize_scene(struct scene *result)
{
    result->obj = NULL;
    result->lights = NULL;
    return 0;
}

static int object_loop(struct scene *result, char *line, int *obj_index,
    int *lgt_index)
{
    if (my_starts_with(line, "LIGHT")) {
        result->lights = my_reallocarray(result->lights,
            *lgt_index + 1, sizeof(struct light *));
        if (result->lights == NULL)
            return -1;
        if (initialize_light(&((result->lights)[*lgt_index - 1]), line) == -1)
            return -1;
        *lgt_index += 1;
    } else {
        result->obj = my_reallocarray(result->obj,
            *obj_index + 1, sizeof(struct object *));
        if (result->obj == NULL)
            return -1;
        if (initialize_object(&((result->obj)[*obj_index - 1]), line) == -1)
            return -1;
        *obj_index += 1;
    }
    return 0;
}

int get_all_objects(const char *path_to_config, struct scene *result)
{
    FILE *file = fopen(path_to_config, "r");
    char *line = NULL;
    size_t size = 0;
    int obj_index = 1;
    int lgt_index = 1;

    if (file == NULL || initialize_scene(result) == -1)
        return -1;
    while (getline(&line, &size, file) != -1) {
        if (object_loop(result, line, &obj_index, &lgt_index) == -1)
            return -1;
    }
    return 0;
}
