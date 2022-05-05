/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** mirror material
*/

#include "raytracer.h"

sfColor mirror_mirror(
    struct object **objects,
    struct light **lights,
    struct intersection *result)
{
    static int calls = 0;
    struct ray ray = {
        .origin = {
            result->intersection.x + result->normal.x * 1e-6,
            result->intersection.y + result->normal.y * 1e-6,
            result->intersection.z + result->normal.z * 1e-6
        },
        .direction = result->normal
    };
    sfColor col;

    if (calls == 15 || !lights)
        return sfBlack;
    calls++;
    col = trace_ray(&ray, objects, lights, result);
    calls--;
    return col;
}
