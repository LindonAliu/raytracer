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
