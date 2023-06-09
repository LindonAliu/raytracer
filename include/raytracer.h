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
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SQ(v) ((v) * (v))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

#define WIDTH 800
#define HEIGHT 600
#define PLANE_CONFIG_LEN 8
#define SPHERE_CONFIG_LEN 6
#define TRIANGLE_CONFIG_LEN 11

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

enum material {
    OPAQUE,
    MIRROR
};

struct object {
    intersection_t *intersection;
    sfColor color;
    enum material material;
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
    sfColor color;
};

struct triangle {
    struct object obj;
    struct vector a;
    struct vector b;
    struct vector c;
    /// computed values
    struct vector normal;
    double d;
    double normal_sq;
};

struct infcolor {
    double r;
    double g;
    double b;
};

struct scene {
    struct object **obj;
    struct light **lights;
};

typedef struct {
    sfUint8 *pixels;
    unsigned int width;
    unsigned int height;
} framebuffer_t;

void raytracer(struct scene *scene);
framebuffer_t *alloc_framebuffer(int width, int height);
sfRenderWindow *create_render_window(char *title);
void free_framebuffer(framebuffer_t *buf);
void reset_framebuffer(framebuffer_t *buffer, sfColor *col);
sfColor get_color_from_rgb(char *rgb_code);
int my_tablen(char **array);
int initialize_object(struct object **obj, char *line);
int initialize_light(struct light **light, char *line);
int get_all_objects(const char *path_to_config, struct scene *result);
void fill_vector(struct vector *a, int x, int y, int z);
void set_pixel(framebuffer_t *buf, int x, int y, sfColor color);
void *my_reallocarray(void *ptr, int nmemb, int size);

void trace_rays(framebuffer_t *buf, struct scene *scenes);

sfColor light(struct light *light, struct intersection *intersection,
    sfColor color);
sfColor modify_lights(
    sfColor color, struct light **lights,
    struct intersection *intersection,
    struct object **objects);

int find_intersection(
    struct ray *ray,
    struct object **objects,
    struct intersection *final);
sfColor trace_ray(
    struct ray *ray, struct object **objects,
    struct light **lights, struct intersection *result);

double shadow(struct light *light, struct intersection *intersection,
    struct object **objects);
sfColor mirror_mirror(
    struct object **objects,
    struct light **lights,
    struct intersection *result);
sfColor mirror_reflect(
    struct ray *ray,
    struct object **objects,
    struct light **lights,
    struct intersection *result);

double vector_norm(struct vector *vector);
double vector_product(struct vector *lhs, struct vector *rhs);

double discriminant(double a, double b, double c);
double vector_distance(struct vector *a, struct vector *b);
struct vector pt_init(struct ray *r, struct vector *pt, struct sphere *s);

struct vector calcul_normal(struct vector *a, struct vector *b,
    struct vector *c);

intersection_t intersection_sphere;
intersection_t intersection_plane;
intersection_t intersection_triangle;
