/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** init_objects
*/

#pragma once

typedef int initialize_obj_t(struct object **obj, char *line);

struct call_object {
    char *object;
    initialize_obj_t *func;
};

initialize_obj_t init_sphere;
initialize_obj_t init_plane;
