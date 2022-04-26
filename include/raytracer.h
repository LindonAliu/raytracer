/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** header
*/

#pragma once

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Window/Event.h>
#include <stdbool.h>

#define SQ(v) ((v) * (v))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

#define WIDTH 800
#define HEIGHT 600

struct vector {
    double x;
    double y;
    double z;
};

struct ray {
    struct vector origin;
    struct vector direction;
};

typedef double intersection_t(void *obj, struct ray *r);

struct object {
    intersection_t *intersection;
    sfColor color;
};

struct sphere {
    struct object obj;
    struct vector center;
    double radius;
};

struct plane {
    struct object obj;
    struct vector pos;
    struct vector normal;
};

typedef struct {
    sfUint8 *pixels;
    unsigned int width;
    unsigned int height;
} framebuffer_t;

framebuffer_t *alloc_framebuffer(int width, int height);
sfRenderWindow *create_render_window(char *title);
void free_framebuffer(framebuffer_t *buf);
void reset_framebuffer(framebuffer_t *buffer, sfColor *col);
void set_pixel(framebuffer_t *buf, int x, int y, sfColor *color);
struct object **realloc_object_tab(struct object **tab, int new_size);
sfColor get_color_from_rgb(char *rgb_code);
int initialize_object(struct object **obj, char *line);
struct object **get_all_objects(const char *path_to_config);

intersection_t intersection_sphere;
intersection_t intersection_plane;
