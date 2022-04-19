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

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQ(v) ((v) * (v))

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

struct intersection {
    struct vector intersection;
    struct vector normal;
    double distance;
};

typedef bool intersection_t(void *obj, struct ray *r,
    struct intersection *out);

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

struct light {
    struct vector pos;
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
void set_pixel(framebuffer_t *buf, int x, int y, sfColor color);

void trace_rays(framebuffer_t *buf);

sfColor light(struct light *light, struct intersection *intersection,
    sfColor color);

double vector_norm(struct vector *vector);
double vector_product(struct vector *lhs, struct vector *rhs);

double discriminant(double a, double b, double c);
double vector_distance(struct vector *a, struct vector *b);

intersection_t intersection_sphere;
intersection_t intersection_plane;
