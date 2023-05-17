/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "my.h"
#include "asm.h"

void nwwrite(int fd, char *buf, size_t size)
{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-result"
    write(fd, buf, size);
    #pragma GCC diagnostic pop
}

void swap_uint32(uint32_t *little)
{
    *little = (*little >> 24) |
        ((*little << 8) & 0x00FF0000) |
        ((*little >> 8) & 0x0000FF00) |
        (*little << 24);
}

int main(int ac, char **av)
{
    if (ac != 2) return 84;
    char *fcontent = read_s_file(av[1]);
    if (!fcontent)
        return 84;
    string_t content = create_string(fcontent);
    nwwrite(1, fcontent, (size_t)my_strlen(fcontent));
    header_t *n = parse_header(&content);
    if (!n) {
        free_string(content);
        free(fcontent);
        return 84;
    }
    free(n);
    free_string(content);
    free(fcontent);
    return (0);
}
