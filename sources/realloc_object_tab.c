/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** realloc_object_tab
*/

#include "raytracer.h"

#include <stdlib.h>

static int get_object_tab_len(struct object **tab)
{
    int i = 0;

    while (tab[i] != NULL)
        i++;
    return i;
}

static int get_light_tab_len(struct light **tab)
{
    int i = 0;

    while (tab[i] != NULL)
        i++;
    return i;
}

struct light **realloc_light_tab(struct light **tab, int new_size)
{
    struct light **new = NULL;

    if (tab == NULL) {
        tab = malloc(sizeof(struct light *) * new_size);
        if (tab == NULL)
            return NULL;
        tab[new_size - 1] = NULL;
        return tab;
    }
    if (get_light_tab_len(tab) == new_size)
        return tab;
    new = malloc(sizeof(struct light *) * (new_size));
    if (new == NULL)
        return NULL;
    for (int i = 0; i != get_light_tab_len(tab); i++)
        new[i] = tab[i];
    new[new_size - 1] = NULL;
    return new;
}

struct object **realloc_object_tab(struct object **tab, int new_size)
{
    int tab_len = 0;
    struct object **new = NULL;

    if (tab == NULL) {
        tab = malloc(sizeof(struct object *) * new_size);
        if (tab == NULL)
            return NULL;
        tab[new_size - 1] = NULL;
        return tab;
    }
    tab_len = get_object_tab_len(tab);
    if (tab_len == new_size)
        return tab;
    new = malloc(sizeof(struct object *) * (new_size));
    if (new == NULL)
        return NULL;
    for (int i = 0; i != tab_len; i++)
        new[i] = tab[i];
    new[new_size - 1] = NULL;
    return new;
}
