/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** initialize_object_tab
*/

#include "raytracer.h"
#include "init_objects.h"
#include "my.h"

#include <stdlib.h>

static bool check_space_tab(char c)
{
    if (c == ' ' || c == '\t')
        return true;
    return false;
}

int my_tablen(char **array)
{
    int i;

    if (array == NULL)
        return -1;
    for (i = 0; array[i] != NULL; ++i);
    return i;
}

int initialize_light(struct light **light, char *line)
{
    char **array = my_split(line, &check_space_tab, true);
    struct light *result = malloc(sizeof(struct light));

    if (array == NULL ||
        my_tablen(array) != 4 ||
        result == NULL)
        return -1;
    fill_vector(&(result->pos), my_getnbr(array[1]), my_getnbr(array[2]),
        my_getnbr(array[3]));
    result->color = sfWhite;
    *light = result;
    free_array(array);
    return 0;
}

int initialize_object(struct object **obj, char *line)
{
    char **array = my_split(line, &check_space_tab, true);
    int result = 0;

    if (array == NULL)
        return -1;
    for (int i = 0; i != ARRAY_SIZE(INIT_OBJECTS_ARRAY); ++i) {
        if (my_strcmp(array[0], INIT_OBJECTS_ARRAY[i].object) == 0)
            result = INIT_OBJECTS_ARRAY[i].func(obj, array);
        if (result == -1)
            return -1;
    }
    if (result == 0)
        return -1;
    free_array(array);
    return 0;
}
