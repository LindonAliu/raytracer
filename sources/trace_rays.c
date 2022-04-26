/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** main
*/

#include "raytracer.h"

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Window/Event.h>

#include <math.h>
#include <stdlib.h>
#include <time.h>

sfColor modify_lights(sfColor color, struct light **lights,
    struct intersection *intersection)
{
    sfColor modified = sfBlack;
    sfColor partial;

    for (int i = 0; lights[i]; i++) {
        partial = light(lights[i], intersection, color);
        modified.r = MAX(modified.r, partial.r);
        modified.g = MAX(modified.g, partial.g);
        modified.b = MAX(modified.b, partial.b);
        modified.a = MAX(modified.a, partial.a);
    }
    return modified;
}

sfColor trace_ray(struct ray *ray, struct object **objects,
    struct light **lights)
{
    sfColor col = sfBlack;
    struct intersection result;
    struct intersection final = { .distance = INFINITY };

    for (int i = 0; objects[i]; i++) {
        if (!objects[i]->intersection(objects[i], ray, &result))
            continue;
        if (result.distance >= final.distance)
            continue;
        col = objects[i]->color;
        final = result;
    }
    return modify_lights(col, lights, &final);
}

void trace_rays(framebuffer_t *buf)
{
    struct sphere s = {
        .obj = { &intersection_sphere, sfRed },
        .center = {0, 300, 800},
        .radius = 53
    };
    struct sphere s2 = {
        .obj = { &intersection_sphere, sfBlue },
        .center = {0, 300, 800},
        .radius = 200
    };
    struct plane p = {
        .obj = { &intersection_plane, sfGreen },
        .normal = {-1, 10, -1},
        .pos = {0, -1, 0},
    };
    struct triangle t = {
        .obj = {&intersection_triangle, sfRed },
        .a = {-50, -50, 400},
        .b = {-50, 50, 400},
        .c = {50, 50, 400}
    };
    struct object *objects[] = { &t.obj, NULL };
    struct light l = {
        .pos = {200, 200, 750}
    };
    struct light *lights[] = { &l, NULL };
    struct ray r = {
        .origin = {0, 0, 0},
        .direction = {0, 0, 500}
    };

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            r.direction.x = (int) (x - WIDTH / 2);
            r.direction.y = (int) (y - HEIGHT / 2);
            set_pixel(buf, x, y, trace_ray(&r, objects, lights));
        }
    }
}
