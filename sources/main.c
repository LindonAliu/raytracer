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
    struct scene *scenes = NULL;

    if (argc < 2) {
        my_puterr("Please give a *.rtx file as a parameter\n");
        return 84;
    }
    scenes = get_all_objects(argv[1]);
    if (scenes == NULL)
        return 84;
    raytracer(scenes);
    return 0;
}
