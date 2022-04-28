/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** main
*/

#include "raytracer.h"
#include "object.h"
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
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(win);
    }
}

int main(void)
{
    sfRenderWindow *win = create_render_window("Raytracer");
    framebuffer_t *buf = alloc_framebuffer(WIDTH, HEIGHT);
    sfTexture *texture = sfTexture_create(WIDTH, HEIGHT);
    sfSprite *sprite = sfSprite_create();
    struct object **objects = get_all_objects("./config.txt");

    srand(time(NULL));
    sfRenderWindow_setFramerateLimit(win, 60);
    while (sfRenderWindow_isOpen(win)) {
        handle_events(win);
        trace_rays(buf, objects);
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
