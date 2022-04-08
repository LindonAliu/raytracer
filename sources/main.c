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

#include <stdlib.h>
#include <time.h>

void handle_events(sfRenderWindow *win)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(win, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(win);
    }
}

void trace_rays(framebuffer_t *buf)
{
    struct sphere s = {
        .obj = { &intersection_sphere, sfRed },
        .center = {0, 0, 800},
        .radius = 100
    };
    struct plane p = {
        .obj = { &intersection_plane, sfGreen },
        .normal = {-1, 10, -1},
        .pos = {0, -1, 0},
    };
    struct ray r = {
        .origin = {0, 0, 0},
        .direction = {0, 0, 500}
    };

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            r.direction.x = (int) (x - WIDTH / 2);
            r.direction.y = (int) (y - HEIGHT / 2);
            set_pixel(buf, x, y,
                intersection_sphere(&s, &r) ? &s.obj.color :
                intersection_plane(&p, &r) ? &p.obj.color : &sfBlack);
        }
    }
}

int main(void)
{
    sfRenderWindow *win = create_render_window("Raytracer");
    framebuffer_t *buf = alloc_framebuffer(WIDTH, HEIGHT);
    sfTexture *texture = sfTexture_create(WIDTH, HEIGHT);
    sfSprite *sprite = sfSprite_create();

    srand(time(NULL));
    sfRenderWindow_setFramerateLimit(win, 60);
    while (sfRenderWindow_isOpen(win)) {
        handle_events(win);
        trace_rays(buf);
        sfTexture_updateFromPixels(texture, buf->pixels,
            buf->width, buf->height, 0, 0);
        sfSprite_setTexture(sprite, texture, sfFalse);
        sfRenderWindow_drawSprite(win, sprite, NULL);
        sfRenderWindow_display(win);
    }
    free_framebuffer(buf);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(win);
}
