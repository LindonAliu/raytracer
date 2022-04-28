/*
** EPITECH PROJECT, 2022
** B-MUL-200-PAR-2-1-myrpg-emil.pedersen
** File description:
** intersection_sphere
*/

#include <stdbool.h>
#include <math.h>
#include "raytracer.h"

double discriminant(double a, double b, double c)
{
    double delta = SQ(b) - (4 * a * c);

    return delta;
}

static double calcu(struct sphere *s, struct ray *r,
    struct intersection *out, double res)
{
    if (res < 0)
        return -1;
    out->intersection = (struct vector) {r->origin.x + res *
        r->direction.x, r->origin.y + res * r->direction.y,
        r->origin.z + res * r->direction.z};
    out->distance = vector_distance(&r->origin, &out->intersection);
    out->normal = (struct vector) {out->intersection.x - s->center.x,
        out->intersection.y - s->center.y, out->intersection.z - s->center.z};
    return out->distance;
}

struct vector pt_init(struct ray *r, struct vector *pt, struct sphere *s)
{
    struct vector temp;

    temp.x = SQ(r->direction.x) +
        SQ(r->direction.y) + SQ(r->direction.z);
    temp.y = (2 * pt->x * r->direction.x) +
        (2 * pt->y * r->direction.y) + (2 * pt->z * r->direction.z);
    temp.z = SQ(pt->x) + SQ(pt->y) + SQ(pt->z) - SQ(s->radius);
    return temp;
}

bool intersection_sphere(void *obj, struct ray *r, struct intersection *out)
{
    struct sphere *s = obj;
    struct vector pt = {.x = r->origin.x - s->center.x,
        .y = r->origin.y - s->center.y, .z = r->origin.z - s->center.z,};
    struct vector pt_sphere = pt_init(r, &pt, s);
    double delta = discriminant(pt_sphere.x, pt_sphere.y, pt_sphere.z);
    double x1 = (-pt_sphere.y + sqrt(delta)) / (2 * pt_sphere.x);
    double x2 = (-pt_sphere.y - sqrt(delta)) / (2 * pt_sphere.x);
    if (delta < 0 || (x1 < 0 && x2 < 0) || isnan(delta))
        return false;
    if (delta == 0) {
        calcu(s, r, out, x1);
    } else if (delta > 0) {
        if (x1 >= 0 && x2 < 0)
            calcu(s, r, out, x1);
        else if (x2 >= 0 && x1 < 0)
            calcu(s, r, out, x2);
        else
            calcu(s, r, out, MIN(x1, x2));
    }
    return true;
}
