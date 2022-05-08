/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** init_objects
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

void fill_vector(struct vector *a, int x, int y, int z)
{
    a->x = (double)x;
    a->y = (double)y;
    a->z = (double)z;
}

int init_material(struct object *obj, char *line)
{
    if (my_strcmp(line, "MIRROR") != 0) {
        if (my_strlen(line) != 9 && my_strlen(line) != 7)
            return -1;
        obj->color = get_color_from_rgb(line);
        obj->material = OPAQUE;
    } else {
        obj->color = (sfColor) {.a = 255};
        obj->material = MIRROR;
    }
    return 0;
}

int init_sphere(struct object **obj, char **array)
{
    struct sphere *new = malloc(sizeof(struct sphere));

    if (new == NULL || my_tablen(array) != SPHERE_CONFIG_LEN)
        return -1;
    if (init_material(&new->obj, array[1]) == -1)
        return -1;
    fill_vector(&(new->center), my_getnbr(array[2]), my_getnbr(array[3]),
        my_getnbr(array[4]));
    new->obj.intersection = &intersection_sphere;
    new->radius = (double)my_getnbr(array[5]);
    *obj = &(new->obj);
    return 1;
}

int init_triangle(struct object **obj, char **array)
{
    struct triangle *new = malloc(sizeof(struct triangle));

    if (new == NULL || my_tablen(array) != TRIANGLE_CONFIG_LEN)
        return -1;
    if (init_material(&new->obj, array[1]) == -1)
        return -1;
    new->obj.intersection = &intersection_triangle;
    fill_vector(&(new->a), my_getnbr(array[2]), my_getnbr(array[3]),
        my_getnbr(array[4]));
    fill_vector(&(new->b), my_getnbr(array[5]), my_getnbr(array[6]),
        my_getnbr(array[7]));
    fill_vector(&(new->c), my_getnbr(array[8]), my_getnbr(array[9]),
        my_getnbr(array[10]));
    new->normal = calcul_normal(&new->a, &new->b, &new->c);
    new->d = -vector_product(&new->a, &new->normal);
    new->normal_sq = vector_product(&new->normal, &new->normal);
    *obj = &(new->obj);
    return 1;
}

int init_plane(struct object **obj, char **array)
{
    struct plane *new = malloc(sizeof(struct plane));

    if (new == NULL || my_tablen(array) != PLANE_CONFIG_LEN)
        return -1;
    if (init_material(&new->obj, array[1]) == -1)
        return -1;
    new->obj.intersection = &intersection_plane;
    new->pos.x = (double)my_getnbr(array[2]);
    new->pos.y = (double)my_getnbr(array[3]);
    new->pos.z = (double)my_getnbr(array[4]);
    new->normal.x = (double)my_getnbr(array[5]);
    new->normal.y = (double)my_getnbr(array[6]);
    new->normal.z = (double)my_getnbr(array[7]);
    *obj = &(new->obj);
    return 1;
}
