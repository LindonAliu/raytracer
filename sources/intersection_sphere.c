/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** intersection
*/

#include "raytracer.h"

#include <stdbool.h>

bool quadratic_intersects(double a, double b, double c)
{
    double delta = b * b - 4 * a * c;

    if (a == 0)
        return (b == 0 && c == 0) || b != 0;
    if (delta < 0)
        return false;
    return true;
}

bool intersection_sphere(void *obj, struct ray *r, struct intersection *out)
{
    struct sphere *s = obj;
    struct vector pt = {
        .x = r->origin.x - s->center.x,
        .y = r->origin.y - s->center.y,
        .z = r->origin.z - s->center.z,
    };

    return quadratic_intersects(
        SQ(r->direction.x) + SQ(r->direction.y) + SQ(r->direction.z),
        2 * (r->direction.x * pt.x + r->direction.y * pt.y
            + r->direction.z * pt.z),
        SQ(pt.x) + SQ(pt.y) + SQ(pt.z) - SQ(s->radius));
}
