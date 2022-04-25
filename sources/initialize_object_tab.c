/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** initialize_object_tab
*/

#include <stdlib.h>
#include "raytracer.h"
#include "object.h"
#include "my.h"

static const struct call_object (TEST[]) = {
    {.object = "SPHERE", .func = &init_sphere},
    {.object = "PLANE", .func = &init_plane}
};

int initialize_object(struct object **obj, char *line)
{
    char **array = my_str_to_word_array(line);
    int result = 0;

    if (array == NULL)
        return -1;
    for (int i = 0; i != sizeof(TEST) / sizeof(TEST[i]); ++i) {
        if (my_strcmp(array[0], TEST[i].object) == 0)
            result = (TEST[i].func)(obj, line);
        if (result == -1)
            return -1;
    }
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
    return 0;
}
