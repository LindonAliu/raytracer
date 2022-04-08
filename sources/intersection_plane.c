/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** intersection
*/

#include "raytracer.h"

#include <stdbool.h>

double intersection_plane(void *obj, struct ray *r)
{
    struct plane *p = obj;
    double div = p->normal.x * r->direction.x + p->normal.y * r->direction.y
        + p->normal.z * r->direction.z;

    return div > 0;
}
