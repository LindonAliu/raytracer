/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** vectors
*/

#include "raytracer.h"

#include <math.h>

double vector_norm(struct vector *vector)
{
    return sqrt(SQ(vector->x) + SQ(vector->y) + SQ(vector->z));
}

double vector_product(struct vector *lhs, struct vector *rhs)
{
    return lhs->x * rhs->x + lhs->y * rhs->y + lhs->z * rhs->z;
}

