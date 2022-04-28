/*
** EPITECH PROJECT, 2021
** my_screensaver
** File description:
** Graphics
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/Window.h>
#include <stdlib.h>
#include <SFML/Window.h>
#include "raytracer.h"
#include <string.h>

framebuffer_t *alloc_framebuffer(int width, int height)
{
    sfUint8 *pixels = malloc(width * height * 32 / 8);
    framebuffer_t *buffer = malloc(sizeof(framebuffer_t));

    buffer->width = width;
    buffer->height = height;
    buffer->pixels = pixels;
    memset(pixels, 0, width * height * 32 / 8);
    return buffer;
}

sfRenderWindow *create_render_window(char *title)
{
    sfVideoMode mode = { WIDTH, HEIGHT, 32 };
    return sfRenderWindow_create(mode, title, sfDefaultStyle, NULL);
}

void set_pixel(framebuffer_t *buf, int x, int y, sfColor color)
{
    unsigned int off = (buf->width * y + x) * 4;

    if (x < 0 || y < 0 || off >= (buf->width * buf->height * 4))
        return;
    buf->pixels[off + 0] = color.r;
    buf->pixels[off + 1] = color.g;
    buf->pixels[off + 2] = color.b;
    buf->pixels[off + 3] = color.a;
}

void free_framebuffer(framebuffer_t *buf)
{
    free(buf->pixels);
    free(buf);
}

void reset_framebuffer(framebuffer_t *buffer, sfColor *col)
{
    unsigned int x;
    unsigned int y;

    for (x = 0; x < buffer->width; x++) {
        for (y = 0; y < buffer->height; y++) {
            set_pixel(buffer, x, y, *col);
        }
    }
}
