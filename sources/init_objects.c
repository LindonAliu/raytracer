/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** init_objects
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

int init_sphere(struct object **obj, char *line)
{
    struct sphere *new = malloc(sizeof(struct sphere));
    char **array = my_str_to_word_array(line);

    if (new == NULL || array == NULL)
        return -1;
    new->obj.color = get_color_from_rgb(array[1]);
    new->center.x = (double)my_getnbr(array[2]);
    new->center.y = (double)my_getnbr(array[3]);
    new->center.z = (double)my_getnbr(array[4]);
    new->obj.intersection = &intersection_sphere;
    new->radius = (double)my_getnbr(array[5]);
    *obj = &(new->obj);
    free_array(array);
    return 0;
}

int init_plane(struct object **obj, char *line)
{
    struct plane *new = malloc(sizeof(struct plane));
    char **array = my_str_to_word_array(line);

    if (new == NULL || array == NULL)
        return -1;
    new->obj.color = get_color_from_rgb(array[1]);
    new->obj.intersection = &intersection_plane;
    new->pos.x = (double)my_getnbr(array[2]);
    new->pos.y = (double)my_getnbr(array[3]);
    new->pos.z = (double)my_getnbr(array[4]);
    new->normal.x = (double)my_getnbr(array[5]);
    new->normal.y = (double)my_getnbr(array[6]);
    new->normal.z = (double)my_getnbr(array[7]);
    *obj = &(new->obj);
    free_array(array);
    return 0;
}
