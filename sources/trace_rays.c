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

sfColor trace_ray(
    struct ray *ray, struct object **objects,
    struct light **lights);

sfColor mirror_mirror(
    struct object **objects,
    struct light **lights,
    struct intersection *result)
{
    static int calls = 0;
    struct ray ray = {
        .origin = result->intersection,
        .direction = result->normal
    };
    sfColor col;

    if (calls == 15 || !lights)
        return sfBlack;
    calls++;
    col = trace_ray(&ray, objects, lights);
    calls--;
    return col;
}

sfColor find_intersection(
    struct ray *ray,
    struct object **objects,
    struct light **lights,
    struct intersection *final)
{
    int index = -1;
    struct intersection result;

    final->distance = INFINITY;
    for (int i = 0; objects[i]; i++) {
        if (!objects[i]->intersection(objects[i], ray, &result))
            continue;
        if (result.distance >= final->distance)
            continue;
        index = i;
        *final = result;
    }
    if (index == -1)
        return sfBlack;
    switch (objects[index]->material) {
    case OPAQUE:
        return objects[index]->color;
    case MIRROR:
        return mirror_mirror(objects, lights, final);
    }
}

sfColor trace_ray(struct ray *ray, struct object **objects,
    struct light **lights)
{
    struct intersection result;
    sfColor col = find_intersection(ray, objects, lights, &result);

    return modify_lights(col, lights, &result, objects);
}

void trace_rays(framebuffer_t *buf)
{
    struct sphere s = {
        .obj = { &intersection_sphere, sfRed, MIRROR },
        .center = {200, -100, 400},
        .radius = 42
    };
    struct sphere s2 = {
        .obj = { &intersection_sphere, sfBlue, OPAQUE },
        .center = {0, 200, 800},
        .radius = 200
    };
    struct sphere sun = {
        .obj = { &intersection_sphere, sfYellow, OPAQUE },
        .center = {-200, -200, 1000000},
        .radius = 500000
    };
    struct plane p = {
        .obj = { &intersection_plane, sfGreen, OPAQUE },
        .normal = {0, -10, 0},
        .pos = {0, 100, 0},
    };
    struct plane wallr = {
        .obj = { &intersection_plane, sfMagenta, OPAQUE },
        .normal = {-10, 0, 0},
        .pos = {500, 0, 0},
    };
    struct plane walll = {
        .obj = { &intersection_plane, sfRed, OPAQUE },
        .normal = {10, 0, 0},
        .pos = {-500, 0, 0},
    };
    struct plane wallb = {
        .obj = { &intersection_plane, sfWhite, MIRROR },
        .normal = {0, 0, -10},
        .pos = {0, 0, 1000},
    };
    struct plane wallh = {
        .obj = { &intersection_plane, sfWhite, OPAQUE },
        .normal = {0, 0, 10},
        .pos = {0, 0, -1000},
    };
    struct object *objects[] = { &s.obj, &p.obj, &s2.obj,
        &sun.obj, &wallr.obj, &walll.obj, &wallb.obj, &wallh.obj, NULL };
    struct light l = {
        .pos = {200, -200, 750}
    };
    struct light l2 = {
        .pos = {-200, 0, 650}
    };
    struct light l3 = {
        .pos = {200, 0, 200}
    };
    struct light *lights[] = { &l, &l2, &l3, NULL };
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
