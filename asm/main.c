/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** MAIN
*/

#include "my.h"
#include "asm.h"

int main(int ac, char **av)
{
    if (ac != 2) return 84;
    char *filename = get_filename(av[1]);
    FILE *f = fopen(filename, "r");
    char *s = NULL;
    size_t l = 0;
    while (getline(&s, &l, f) != -1) {
        write(1, s, my_strlen(s));
        free(s);
        s = NULL;
    }
    free(s);
    fclose(f);
    free(filename);
    return (0);
}
