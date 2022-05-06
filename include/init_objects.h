/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** init_objects
*/

#pragma once

typedef int initialize_obj_t(struct object **obj, char **array);

struct call_object {
    char *object;
    initialize_obj_t *func;
};

initialize_obj_t init_sphere;
initialize_obj_t init_plane;
initialize_obj_t init_triangle;

static const struct call_object INIT_OBJECTS_ARRAY[] = {
    {.object = "SPHERE", .func = &init_sphere},
    {.object = "PLANE", .func = &init_plane},
    {.object = "TRIANGLE", .func = &init_triangle}
};
