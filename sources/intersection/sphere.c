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

double vector_distance(struct vector *a, struct vector *b)
{
    return vector_norm(&(struct vector)
    {a->x - b->x, a->y - b->y, a->z - b->z});
}

static double calcul(struct sphere *s, struct ray *r,
struct intersection *out, double res)
{
    out->intersection = (struct vector) {r->origin.x + res * r->direction.x,
    r->origin.y + res * r->direction.y, r->origin.z + res * r->direction.z};
    out->distance = vector_distance(&r->origin, &out->intersection);
    out->normal = (struct vector) {out->intersection.x - s->center.x,
    out->intersection.y - s->center.y, out->intersection.z - s->center.z};
    return out->distance;
}

bool intersection_sphere(void *obj, struct ray *r, struct intersection *out)
{
    struct sphere *s = obj;
    struct vector pt = {.x = r->origin.x - s->center.x,
    .y = r->origin.y - s->center.y, .z = r->origin.z - s->center.z,};
    double a = SQ(r->direction.x) + SQ(r->direction.y) + SQ(r->direction.z);
    double b = (2 * pt.x * r->direction.x) + (2 * pt.y * r->direction.y) + (2 * pt.z * r->direction.z);
    double c = SQ(pt.x) + SQ(pt.y) + SQ(pt.z) - SQ(s->radius);
    double delta = discriminant(a, b, c);
    double distance1;
    double distance2;

    if (a == 0)
        return false;
    if (delta == 0) {
        calcul(s, r, out, (-b) / (2 * a));
    } else if (delta > 0) {
        distance1 = calcul(s, r, out, (-b + sqrt(delta)) / (2 * a));
        distance2 = calcul(s, r, out, (-b - sqrt(delta)) / (2 * a));
        if (distance1 < distance2)
            calcul(s, r, out, (-b + sqrt(delta)) / (2 * a));
    } else
        return false;
    return true;
}
