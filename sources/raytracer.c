/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** raytracer
*/

#include "raytracer.h"
#include "my.h"

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Window/Event.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void handle_events(sfRenderWindow *win)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(win, &event)) {
        if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(win);
    }
}

static void destroy_elements(sfRenderWindow *win, framebuffer_t *buf,
    sfTexture *texture, sfSprite *sprite)
{
    free_framebuffer(buf);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(win);
}

void raytracer(struct scene *scene)
{
    sfRenderWindow *win = create_render_window("Raytracer");
    framebuffer_t *buf = alloc_framebuffer(WIDTH, HEIGHT);
    sfTexture *texture = sfTexture_create(WIDTH, HEIGHT);
    sfSprite *sprite = sfSprite_create();

    sfRenderWindow_setFramerateLimit(win, 60);
    while (sfRenderWindow_isOpen(win)) {
        handle_events(win);
        trace_rays(buf, scene);
        sfTexture_updateFromPixels(texture, buf->pixels,
            buf->width, buf->height, 0, 0);
        sfSprite_setTexture(sprite, texture, sfFalse);
        sfRenderWindow_drawSprite(win, sprite, NULL);
        sfRenderWindow_display(win);
    }
    destroy_elements(win, buf, texture, sprite);
}
