/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** realloc_object_tab
*/

#include <stdlib.h>
#include "raytracer.h"

static int get_object_tab_len(const struct object **tab)
{
    int i = 0;

    while (tab[i] != NULL)
        i++;
    return i;
}

struct object **realloc_object_tab(struct object **tab, int const new_size)
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
    tab_len = get_object_tab_len((const struct object **)tab);
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
