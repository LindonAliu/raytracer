/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** get_color_from_rgb
*/

#include <SFML/Graphics.h>
#include "my.h"

static int hexa_to_decimal(const char *rgb_code)
{
    int len = 1;
    int result = 0;

    for (int i = 0; i < 2; ++i) {
        if (rgb_code[i] >= 'a' && rgb_code[i] <= 'f')
            result |= (rgb_code[i] - 'a' + 10) << (len * 4);
        else if (rgb_code[i] >= 'A' && rgb_code[i] <= 'F')
            result |= (rgb_code[i] - 'A' + 10) << (len * 4);
        else
            result |= (rgb_code[i] - '0') << (len * 4);
        len--;
    }
    return result;
}

sfColor get_color_from_rgb(const char *rgb_code)
{
    sfColor result;

    if (rgb_code[0] == '#')
        rgb_code++;
    result.r = hexa_to_decimal(rgb_code);
    result.g = hexa_to_decimal(rgb_code + 2);
    result.b = hexa_to_decimal(rgb_code + 4);
    if (rgb_code[6] != '\0')
        result.a = hexa_to_decimal(rgb_code + 6);
    else
        result.a = 255;
    return result;
}
