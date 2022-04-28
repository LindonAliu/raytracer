/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** initialize_object_tab
*/

#include <stdlib.h>
#include "raytracer.h"
#include "init_objects.h"
#include "my.h"

static const struct call_object (TEST[]) = {
    {.object = "SPHERE", .func = &init_sphere},
    {.object = "PLANE", .func = &init_plane}
};

static bool check_space_tab(char c)
{
    if (c == ' ' || c == '\t')
        return true;
    return false;
}

int initialize_object(struct object **obj, char *line)
{
    char **array = my_split(line, &check_space_tab, true);
    int result = 0;

    if (array == NULL)
        return -1;
    for (int i = 0; i != ARRAY_SIZE(TEST); ++i) {
        if (my_strcmp(array[0], TEST[i].object) == 0)
            result = TEST[i].func(obj, array);
        if (result == -1)
            return -1;
    }
    free_array(array);
    return 0;
}
