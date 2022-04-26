/*
** EPITECH PROJECT, 2022
** triangle
** File description:
** FreeKOSOVO
*/

#include <stdbool.h>
#include "raytracer.h"

// ! marche seulement dans le cas où la lumière "tombe" sur le triangle. (donc dans un plan 2D et non 3D).
// TODO: faire les autres cas d'intersections.
// TODO: remplire la structure intersection *out.
// TODO: remettre à la norme.
// * https://forums.futura-sciences.com/mathematiques-college-lycee/874671-intersection-dun-triangle-une.html

bool intersection_triangle(void *obj, struct ray *r, struct intersection *out)
{
    struct triangle *t = obj;

    struct vector U = { .x = t->C.x - t->A.x,
        .y = t->C.y - t->A.y, .z = t->C.z - t->A.z};
    struct vector V = { .x = t->B.x - t->A.x,
        .y = t->B.y - t->A.y, .z = t->B.z - t->A.z};
    
    double D = U.x * V.z - V.x * U.z;

    double la = (V.z * (r->direction.x - t->A.x) - V.x * (r->direction.z - t->A.z)) / D;
    double mu = (U.x * (r->direction.z - t->A.z) - U.z * (r->direction.x - t->A.x)) / D;

    double result = t->A.y + la * U.y + mu * V.y;

    if ((la * mu >= 0) && (la * (1 - la - mu)) >= 0) {
        if (r->direction.y > result)
            return true;
    }
    (void)out;
    return false;
}
