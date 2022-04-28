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

sfColor find_intersection(struct ray *ray, struct object **objects,
    struct intersection *final)
{
    sfColor col = sfBlack;
    struct intersection result;

    final->distance = INFINITY;
    for (int i = 0; objects[i]; i++) {
        if (!objects[i]->intersection(objects[i], ray, &result))
            continue;
        if (result.distance >= final->distance)
            continue;
        col = objects[i]->color;
        *final = result;
    }
    return col;
}

sfColor trace_ray(struct ray *ray, struct object **objects,
    struct light **lights)
{
    struct intersection result;
    sfColor col = find_intersection(ray, objects, &result);

    return modify_lights(col, lights, &result, objects);
}

void trace_rays(framebuffer_t *buf)
{
    struct sphere s = {
        .obj = { &intersection_sphere, sfRed },
        .center = {0, -100, 700},
        .radius = 53
    };
    struct sphere s2 = {
        .obj = { &intersection_sphere, sfBlue },
        .center = {0, 200, 800},
        .radius = 200
    };
    struct sphere sun = {
        .obj = { &intersection_sphere, sfYellow },
        .center = {-200, -200, 1000000},
        .radius = 500000
    };
    struct plane p = {
        .obj = { &intersection_plane, sfGreen },
        .normal = {0, -10, 0},
        .pos = {0, 100, 0},
    };
    struct object *objects[] = { &s.obj, &p.obj, &s2.obj, &sun.obj, NULL };
    struct light l = {
        .pos = {200, -200, 750}
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
