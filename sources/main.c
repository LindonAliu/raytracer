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
    struct scene scenes;

    if (argc < 2) {
        my_puterr("Please give a *.rtx file as a parameter\n");
        return 84;
    }
    get_all_objects(argv[1], &scenes);
    raytracer(&scenes);
    return 0;
}
