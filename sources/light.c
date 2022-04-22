/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** light
*/

#include "raytracer.h"

sfColor light(struct light *light, struct intersection *intersection,
    sfColor color)
{
    struct vector l = {
        light->pos.x - intersection->intersection.x,
        light->pos.y - intersection->intersection.y,
        light->pos.z - intersection->intersection.z
    };
    double cos_a = vector_product(&intersection->normal, &l) /
        (vector_norm(&intersection->normal) * vector_norm(&l));
    double multiplier = cos_a > 0 ? cos_a : 0;

    return ((sfColor) { multiplier * color.r, multiplier * color.g,
        multiplier * color.b, color.a });
}

sfColor modify_lights(sfColor color, struct light **lights,
    struct intersection *intersection)
{
    sfColor modified = sfBlack;
    sfColor partial;

    for (int i = 0; lights[i]; i++) {
        partial = light(lights[i], intersection, color);
        modified.r = MAX(modified.r, partial.r);
        modified.g = MAX(modified.g, partial.g);
        modified.b = MAX(modified.b, partial.b);
        modified.a = MAX(modified.a, partial.a);
    }
    return modified;
}
