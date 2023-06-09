/*
** EPITECH PROJECT, 2022
** triangle
** File description:
** FreeKOSOVO
*/

#include <stdbool.h>
#include "raytracer.h"

struct vector calcul_normal(struct vector *a, struct vector *b,
    struct vector *c)
{
    struct vector normal = {
        .x = (b->y - a->y) * (c->z - a->z) - (b->z - a->z) * (c->y - a->y),
        .y = (b->z - a->z) * (c->x - a->x) - (b->x - a->x) * (c->z - a->z),
        .z = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x)
    };
    return normal;
}

static bool in_triangle(struct triangle *t, struct vector *intersection,
    struct vector *normal)
{
    struct vector tmp = calcul_normal(intersection, &t->b, &t->c);
    double alpha = vector_product(normal, &tmp) / t->normal_sq;
    struct vector tmp2 = calcul_normal(intersection, &t->c, &t->a);
    double beta = vector_product(normal, &tmp2) / t->normal_sq;
    double gamma = 1 - alpha - beta;

    return (0 <= beta && beta <= 1 && 0 <= alpha && alpha <= 1 &&
        0 <= gamma && gamma <= 1);
}

bool intersection_triangle(void *obj, struct ray *r, struct intersection *out)
{
    struct triangle *t = obj;
    struct vector normal = t->normal;
    double divi = vector_product(&r->direction, &normal);
    double s = -(vector_product(&normal, &r->origin) + t->d) / divi;

    if (s <= 0 || divi == 0)
        return false;
    out->intersection = (struct vector) {r->origin.x + s * r->direction.x,
        r->origin.y + s * r->direction.y, r->origin.z + s * r->direction.z};
    if (!in_triangle(t, &out->intersection, &normal))
        return false;
    out->distance = vector_distance(&r->origin, &out->intersection);
    if (vector_product(&normal, &r->direction) > 0)
        out->normal = (struct vector) {-normal.x, -normal.y, -normal.z};
    else
        out->normal = normal;
    return true;
}
