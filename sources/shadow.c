/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** shadow
*/

#include "raytracer.h"

bool shadow(struct light *light, struct intersection *intersection,
    struct object **objects)
{
    struct vector l = {
        intersection->intersection.x - light->pos.x,
        intersection->intersection.y - light->pos.y,
        intersection->intersection.z - light->pos.z,
    };
    struct ray lightray = {
        .origin = light->pos,
        .direction = l
    };
    struct intersection result;
    double distance =
        vector_distance(&light->pos, &intersection->intersection);

    find_intersection(&lightray, objects, &result);
    return result.distance > distance - 1e-6;
}
