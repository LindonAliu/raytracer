/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** intersection
*/

#include <stdbool.h>
#include "raytracer.h"

bool intersection_plane(void *obj, struct ray *r, struct intersection *out)
{
    struct plane *p = obj;
    double d = -vector_product(&p->pos, &p->normal);
    double divi = vector_product(&r->direction, &p->normal);
    double t = -(vector_product(&p->normal, &r->origin) + d) / divi;

    if (t <= 0 || divi == 0)
        return false;
    out->intersection = (struct vector) {r->origin.x + t * r->direction.x,
        r->origin.y + t * r->direction.y, r->origin.z + t * r->direction.z};
    out->distance = vector_distance(&r->origin, &out->intersection);
    if (divi > 0)
        out->normal = (struct vector) {-p->normal.x,
            -p->normal.y, -p->normal.z};
    else
        out->normal = p->normal;
    return true;
}
