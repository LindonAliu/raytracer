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

int find_intersection(
    struct ray *ray,
    struct object **objects,
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
    return index;
}

sfColor blend_colors(sfColor fg, sfColor bg)
{
    return ((sfColor) {
        (fg.r * fg.a + bg.r * (255 - fg.a)) / 255,
        (fg.g * fg.a + bg.g * (255 - fg.a)) / 255,
        (fg.b * fg.a + bg.b * (255 - fg.a)) / 255,
        bg.a
    });
}

sfColor trace_ray(
    struct ray *ray, struct object **objects,
    struct light **lights, struct intersection *result)
{
    int index = find_intersection(ray, objects, result);
    sfColor col;
    struct intersection copy = *result;

    if (index == -1)
        return sfBlack;
    switch (objects[index]->material) {
    case OPAQUE:
        col = objects[index]->color;
        if (col.a == 255)
            break;
        copy.normal = ray->direction;
        col = modify_lights(col, lights, result, objects);
        col.a = objects[index]->color.a;
        return blend_colors(col, mirror_mirror(objects, lights, &copy));
    case MIRROR:
        col = mirror_mirror(objects, lights, result);
        break;
    }
    return modify_lights(col, lights, result, objects);
}

void trace_rays(framebuffer_t *buf, struct object **objects)
{
    struct light l = {
        .pos = {200, -200, 750},
        .color = {255, 10, 10, 255}
    };
    struct light l2 = {
        .pos = {-200, 0, 650},
        .color = {10, 10, 255, 255}
    };
    struct light l3 = {
        .pos = {200, 0, 200},
        .color = {10, 255, 10, 255}
    };
    struct light *lights[] = { &l, &l2, &l3, NULL };
    struct ray r = {
        .origin = {0, 0, 0},
        .direction = {0, 0, 500}
    };
    struct intersection inter;

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            r.direction.x = (int) (x - WIDTH / 2);
            r.direction.y = (int) (y - HEIGHT / 2);
            set_pixel(buf, x, y, trace_ray(&r, objects, lights, &inter));
        }
    }
}
