/*
** EPITECH PROJECT, 2022
** duplicate_load_add_error.c
** File description:
** print duplicate load_address option error
*/

#include "corewar.h"

void duplicate_load_add_error(const char *option)
{
    write_void(2, option, my_strlen_const(option));
    write_void(2, ": load address already in use\n"
    "Try 'corewar -h' for more information.\n", 69);
}
