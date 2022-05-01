/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** main
*/

#include "raytracer.h"
#include "my.h"

#include <stddef.h>

int main(int argc, const char *argv[])
{
    struct object **objects = NULL;

    if (argc < 2) {
        my_puterr("Please give a *.rtx file as a parameter\n");
        return 84;
    }
    objects = get_all_objects(argv[1]);
    if (objects == NULL)
        return 84;
    raytracer(objects);
    return 0;
}
