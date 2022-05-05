/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** light
*/

#include "raytracer.h"

#include <SFML/Graphics/Color.h>
#include <math.h>

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

    return ((sfColor) {
        (light->color.r / 255.0) * multiplier * color.r,
        (light->color.g / 255.0) * multiplier * color.g,
        (light->color.b / 255.0) * multiplier * color.b,
        color.a
    });
}

sfColor correct_gamma(struct infcolor color)
{
    sfColor res;

    res.r = (1 - 1 / (2 * color.r / 255.0 + 1)) * 255;
    res.g = (1 - 1 / (2 * color.g / 255.0 + 1)) * 255;
    res.b = (1 - 1 / (2 * color.b / 255.0 + 1)) * 255;
    res.a = 255;
    return res;
}

sfColor modify_lights(
    sfColor color, struct light **lights,
    struct intersection *intersection,
    struct object **objects)
{
    struct infcolor modified = {0};
    sfColor partial;
    double mod;

    for (int i = 0; lights[i]; i++) {
        partial = light(lights[i], intersection, color);
        mod = shadow(lights[i], intersection, objects);
        modified.r += partial.r * mod;
        modified.g += partial.g * mod;
        modified.b += partial.b * mod;
    }
    return correct_gamma(modified);
}
