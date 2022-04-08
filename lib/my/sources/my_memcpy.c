/*
** EPITECH PROJECT, 2021
** lib
** File description:
** memcpy
*/

void my_memcpy(void *dest, const void *src, int n)
{
    for (int i = 0; i < n; i++) {
        ((char *) dest)[i] = ((char *) src)[i];
    }
}
