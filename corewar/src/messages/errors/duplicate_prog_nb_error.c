/*
** EPITECH PROJECT, 2022
** duplicate_prog_nb_error.c
** File description:
** print duplicate prog_number option error
*/

#include "corewar.h"

void duplicate_prog_nb_error(const char *option)
{
    write_void(2, option, my_strlen_const(option));
    write_void(2, ": program number already in use\n"
    "Try 'corewar -h' for more information.\n", 71);
}
