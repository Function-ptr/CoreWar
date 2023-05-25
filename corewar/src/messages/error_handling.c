/*
** EPITECH PROJECT, 2022
** error_handling.c
** File description:
** eroor for argument number
*/

#include "../include/corewar.h"

int error_handling(int argc)
{
    if (argc < 3 || argc > 5) {
        write(2, "Error: Wrong number of arguments\n", 33);
        return (84);
    }
    return (0);
}
