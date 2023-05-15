/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "my.h"
#include "asm.h"

void swap_uint32(uint32_t *little) {
    *little = (*little >> 24) |
        ((*little << 8) & 0x00FF0000) |
        ((*little >> 8) & 0x0000FF00) |
        (*little << 24);
}

int main(int ac, char **av)
{
    if (ac != 2) return 84;
    char *filename = get_filename(av[1]);
    if (!filename) return 84;
    char *fcontent = read_s_file(filename);
    free(filename);
    if (!fcontent)
        return 84;
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-result"
    write(1, fcontent, (size_t)my_strlen(fcontent));
    #pragma GCC diagnostic pop
    free(fcontent);
    return (0);
}
