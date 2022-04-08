/*
** EPITECH PROJECT, 2021
** Task 18 - my_putnbr_base
** File description:
** Prints a number in given base
*/

#include "my.h"

static unsigned long long find_magnitude(unsigned int n, int base)
{
    unsigned long long magnitude = 1;

    while (n >= magnitude) {
        magnitude *= base;
    }
    return magnitude / base;
}

void my_nbrstr_unsigned(char *buf, unsigned int n, char const *base)
{
    int baselen = my_strlen(base);
    int magnitude = find_magnitude(n, baselen);
    int digit;

    while (magnitude >= 1) {
        digit = (n / magnitude) % baselen;
        *buf = base[digit];
        buf++;
        magnitude /= baselen;
    }
    *buf = 0;
}

void my_nbrstr(char *dest, int nbr, char const *base)
{
    if (nbr < 0) {
        dest[0] = '_';
        my_nbrstr_unsigned(dest + 1, -((unsigned int) nbr), base);
    } else if (nbr == 0) {
        dest[0] = base[0];
        dest[1] = 0;
    } else {
        my_nbrstr_unsigned(dest, nbr, base);
    }
}
