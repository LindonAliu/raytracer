/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** shadow
*/

#include "raytracer.h"

#include <stddef.h>

static int intersect(
    struct light *light, struct intersection *intersection,
    struct object **objects, struct intersection *result)
{
    struct vector l = {
        light->pos.x - intersection->intersection.x,
        light->pos.y - intersection->intersection.y,
        light->pos.z - intersection->intersection.z,
    };
    struct ray lightray = {
        .origin = {
            intersection->intersection.x + l.x * 1e-6,
            intersection->intersection.y + l.y * 1e-6,
            intersection->intersection.z + l.z * 1e-6
        },
        .direction = l
    };

    return find_intersection(&lightray, objects, result);
}

/// Returns a multiplier for the light
/// 0 if completely shadowed, 1 if no shadow
double shadow(struct light *light, struct intersection *intersection,
    struct object **objects)
{
    struct intersection result;
    double distance =
        vector_distance(&light->pos, &intersection->intersection);
    int index = intersect(light, intersection, objects, &result);

    if (result.distance > distance - 1e-6)
        return 1;
    if (objects[index]->material != OPAQUE || objects[index]->color.a == 255)
        return 0;
    return shadow(light, &result, objects)
        * (255 - objects[index]->color.a) / 255.0;
}
