/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** get_color_from_rgb
*/

#include <SFML/Graphics.h>
#include "my.h"

static int hexa_to_decimal(char *rgb_code)
{
    int len = 1;
    int result = 0;

    for (int i = 0; i < 2; ++i) {
        if (rgb_code[i] >= 'a' && rgb_code[i] <= 'f')
            result += (rgb_code[i] - 'a' + 10) * my_compute_power_rec(16, len);
        else if (rgb_code[i] >= 'A' && rgb_code[i] <= 'F')
            result += (rgb_code[i] - 'A' + 10) * my_compute_power_rec(16, len);
        else
            result += (rgb_code[i] - '0') * my_compute_power_rec(16, len);
        len--;
    }
    return result;
}

sfColor get_color_from_rgb(char *rgb_code)
{
    sfColor result;

    if (rgb_code[0] == '#')
        rgb_code++;
    result.r = hexa_to_decimal(rgb_code);
    rgb_code += 2;
    result.g = hexa_to_decimal(rgb_code);
    rgb_code += 2;
    result.b = hexa_to_decimal(rgb_code);
    result.a = 0;
    return result;
}
